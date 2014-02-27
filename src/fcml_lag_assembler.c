/*
 * fcml_lag_assembler.c
 *
 *  Created on: Feb 22, 2014
 *      Author: tas
 */

#include <fcml_lag_assembler.h>
#include <fcml_parser.h>
#include <fcml_parser_int.h>
#include "fcml_env.h"
#include "fcml_coll.h"
#include "fcml_apc_ast.h"
#include "fcml_errors.h"
#include "fcml_messages.h"
#include "fcml_utils.h"

/*
 *         jmp second
start:  jmp finish
        rb  124
second: jmp 249-(finish-start)
finish: ret
 */

typedef struct fcml_ist_lag_pass_holder {
	/* Pass number. */
	fcml_int pass;
} fcml_ist_lag_pass_holder;

/* Holds information about last symbol value modification. */
typedef struct fcml_ist_lag_symbol_state {
	/* Name of the symbol. */
	fcml_string symbol_name;
	/* Pass which modified symbol. */
	fcml_int pass;
} fcml_ist_symbol_state;

typedef struct fcml_ist_lag_instruction {
	fcml_parser_ip ip;
	/* Next instruction. */
	struct fcml_ist_lag_instruction *next;
	/* If instruction has symbols, we have its AST just to reassemble it when needed. */
	fcml_st_parser_ast ast;
	/* List of symbols used by instruction. Every symbol is represented by its name (list of fcml_string). */
	fcml_st_coll_list *used_symbols;
	/* Number of undefined symbols when instruction was assembled last time. */
	fcml_int undefined_symbols;
	/* Assembled instruction. */
	fcml_st_assembled_instruction *instruction;
	/* Line number where instruction is defined. */
	fcml_int line;
	/* Generated instruction can not be shorter than */
	fcml_int size_guard;
} fcml_ist_lag_instruction;

/* Details about processing errors. */
typedef struct fcml_ist_lag_error_details {
	/* Errors. */
	fcml_st_ceh_error_container errors;
	/* Line where assembling failed. */
	fcml_int line;
} fcml_ist_lag_error_details;

/* Context shared between multiple passes. */
typedef struct fcml_ist_lag_processing_context {
	/* Parsed/Converted/Assembled instructions. */
	fcml_ist_lag_instruction *first_instruction;
	fcml_ist_lag_instruction *last_instruction;
	/* One line assembler used to assemble code. */
	fcml_st_assembler_context assembler_context;
	/* Global errors going here. */
	fcml_ist_lag_error_details error_details;
} fcml_ist_log_asseblation_context;

/* Returns true if any of the symbols from given list exists in the state map. */
fcml_bool fcml_ifn_lag_is_any_symbol_modified( fcml_coll_map symbol_state_map, fcml_st_coll_list *symbol_names ) {
	if( symbol_names ) {
		fcml_st_coll_list_element *element = symbol_names->head;
		while( element ) {
			fcml_string symbol_name = (fcml_string)element->item;
			if( fcml_fn_coll_map_get( symbol_state_map, symbol_name ) ) {
				return FCML_TRUE;
			}
			element = element->next;
		}
	}
	return FCML_FALSE;
}

/* Frees symbol state structure used by secod pass and laters. */
void fcml_ifn_lag_map_symbol_state_free( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	if( value ) {
		/* Symbol name is managed by parser context, so it can not be free'd here. */
		fcml_ist_symbol_state *symbol = (fcml_ist_symbol_state*)value;
		fcml_fn_env_memory_free( symbol );
	}
}

/* Decides if symbol state has to be removed from state stable. */
fcml_bool fcml_ifn_lag_map_prev_pass_symbol_if( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	fcml_bool remove = FCML_FALSE;
	fcml_ist_lag_pass_holder *pass_holder = (fcml_ist_lag_pass_holder*)args;
	if( value && pass_holder ) {
		fcml_ist_symbol_state *symbol = (fcml_ist_symbol_state*)value;
		if( symbol->pass < pass_holder->pass ) {
			remove = FCML_TRUE;
		}
	}
	return remove;
}

/* Adds symbol status to the map. */
fcml_ceh_error fcml_ifn_lag_add_symbol_state( fcml_coll_map symbol_state_map, fcml_string symbol, fcml_int pass ) {
	fcml_ist_symbol_state *state = (fcml_ist_symbol_state*)fcml_fn_coll_map_get( symbol_state_map, symbol );
	if( state ) {
		state->pass = pass;
	} else {
		state = (fcml_ist_symbol_state*)fcml_fn_env_memory_alloc( sizeof( fcml_ist_symbol_state* ) );
		if( !state ) {
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
		state->pass = pass;
		state->symbol_name = symbol;
		fcml_int map_error = 0;
		fcml_fn_coll_map_put( symbol_state_map, symbol, state, &map_error );
		if( map_error ) {
			/* Can not add symbol to the map. */
			fcml_fn_env_memory_free( state );
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
	}
	return FCML_CEH_GEC_NO_ERROR;
}

/* Allocates map used as fast-access storage for symbols statuses. */
fcml_coll_map fcml_ifn_lag_alloc_symbol_state_map() {
	fcml_st_coll_map_descriptor map_descriptor = fcml_coll_map_descriptor_string;
	map_descriptor.entry_free_function = &fcml_ifn_lag_map_symbol_state_free;
	fcml_int map_error = 0;
	return fcml_fn_coll_map_alloc( &map_descriptor, 10, &map_error );
}

/* Removes all symbols from previous passes. */
void fcml_ifn_lag_clean_symbol_state_map( fcml_coll_map symbol_state_map, fcml_int pass ) {
	fcml_ist_lag_pass_holder holder;
	holder.pass = pass;
	fcml_fn_coll_map_remove_if( symbol_state_map, &fcml_ifn_lag_map_prev_pass_symbol_if, &holder );
}

/* Adds new instruction to the processing context. */
fcml_ist_lag_instruction *fcml_ifn_lag_add_lag_instruction_to_context( fcml_ist_log_asseblation_context *processing_ctx ) {
	fcml_ist_lag_instruction *lag_instruction = (fcml_ist_lag_instruction*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_ist_lag_instruction ) );
	if( !lag_instruction ) {
		return NULL;
	}
	if( !processing_ctx->first_instruction ) {
		processing_ctx->first_instruction = lag_instruction;
		processing_ctx->last_instruction = lag_instruction;
	} else {
		processing_ctx->last_instruction->next = lag_instruction;
		processing_ctx->last_instruction = lag_instruction;
	}
	return lag_instruction;
}

/* Free lag instruction. */
void fcml_ifn_lag_free_instruction( fcml_ist_lag_instruction *instruction, fcml_st_symbol_table *symbol_table ) {
	if( instruction ) {
		if( instruction->next ) {
			fcml_ifn_lag_free_instruction( instruction->next, symbol_table );
		}
		/* It is really important! Remember that the same symbol is stored
		 * in the internal symbol table, and  it's symbol table that is
		 * responsible for freeing it.
		 */
		if( instruction->ast.symbol && symbol_table ) {
			/* Anyway, if symbol table is given, remove symbol from it here. */
			fcml_fn_symbol_remove( symbol_table, instruction->ast.symbol->symbol );
		}
		instruction->ast.symbol = NULL;
		/* Free everything else. */
		fcml_fn_parser_free_ast( &(instruction->ast) );
		/* Free assembled instruction. */
		if( instruction->instruction ) {
			fcml_fn_assembler_instruction_free( instruction->instruction );
		}
		/* Free symbols list but leave symbols themselves alone. */
		if( instruction->used_symbols ) {
			fcml_fn_coll_list_free( instruction->used_symbols, NULL, NULL );
		}
		fcml_fn_env_memory_free( instruction );
	}
}

void fcml_ifn_lag_detach_instruction( fcml_st_assembled_instruction **instructions, fcml_st_assembled_instruction *choosen_instruction ) {
	fcml_st_assembled_instruction **current = instructions;
	fcml_bool found = FCML_FALSE;
	do {
		if( *current == choosen_instruction ) {
			*current = choosen_instruction->next;
			found = FCML_TRUE;
		}
		current = &((*current)->next);
	} while( !found && *current );
}

fcml_st_assembled_instruction *fcml_ifn_lag_choose_second_pass_best_instruction( fcml_ist_lag_instruction *lag_instruction, fcml_st_assembled_instruction **instructions, fcml_st_assembled_instruction *choosen_instruction ) {
	fcml_int guard = lag_instruction->size_guard;
	if( !lag_instruction->undefined_symbols && guard > 0 ) {
		fcml_st_assembled_instruction *chosen_instruction = NULL;
		/* Choose the longest form. */
		fcml_st_assembled_instruction *current = *instructions;
		while( current ) {
			if( !chosen_instruction && guard <= current->code_length ) {
				chosen_instruction = current;
			} else if( current->code_length > chosen_instruction->code_length && guard <= current->code_length ) {
				chosen_instruction = current;
			}
			current = current->next;
		}
	}
	if( !lag_instruction->undefined_symbols ) {
		if( choosen_instruction->code_length > lag_instruction->instruction->code_length ) {
			lag_instruction->size_guard = choosen_instruction->code_length;
		}
	}

	/* Detach chosen instruction. */
	fcml_ifn_lag_detach_instruction( instructions, choosen_instruction );

	return choosen_instruction;
}

/* Chooses best instruction as a result for the first pass. */
fcml_st_assembled_instruction *fcml_ifn_lag_choose_first_pass_best_instruction( fcml_int ignored_symbols, fcml_st_assembler_result *assembler_result ) {

	fcml_st_assembled_instruction *chosen_instruction = NULL;

	if( ignored_symbols > 0 ) {
		/* Choose the longest form. */
		fcml_st_assembled_instruction *current = assembler_result->instructions;
		while( current ) {
			if( !chosen_instruction ) {
				chosen_instruction = current;
			} else if( current->code_length > chosen_instruction->code_length ) {
				chosen_instruction = current;
			}
			current = current->next;
		}
	} else {
		/* Default chooser chooses the shortest for for us. */
		chosen_instruction = assembler_result->chosen_instruction;
	}

	/* Detach instruction to avoid its deallocation. */
	fcml_ifn_lag_detach_instruction( &(assembler_result->instructions ), chosen_instruction );

	return chosen_instruction;
}

/* First pass of the load-and-go assembler. */
fcml_ceh_error fcml_ifn_lag_assembler_pass_1( fcml_st_lag_assembler_context *context, const fcml_string *source_code, fcml_ist_log_asseblation_context *processing_ctx, fcml_bool *invoke_next_pass ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_assembler_context *assembler_context = &(processing_ctx->assembler_context);

	/* Parses instructions one by one. Every parsed instruction is
	 * then converted to CIF and assembled. Assembler should return
	 * all allowed forms of assembled instruction. If all symbols
	 * were known, the shortest instruction for is chosen; otherwise
	 * the longest one.
	 */
	fcml_st_parser_context parser_context = {0};
	parser_context.config.ignore_undefined_symbols = FCML_TRUE;
	parser_context.config.override_labels = FCML_FALSE;
	parser_context.ip = ( assembler_context->entry_point.addr_form == FCML_AF_64_BIT ) ? assembler_context->entry_point.ip.rip : assembler_context->entry_point.ip.eip;
	parser_context.dialect = context->dialect;

	fcml_st_assembler_result assembler_result;
	fcml_fn_assembler_result_prepare( &assembler_result );

	fcml_st_parser_result parser_result;
	fcml_fn_parser_result_prepare( &parser_result );

	fcml_int line = 0;

	fcml_string instruction;

	/* Parse source code, line by line. */
	while( ( instruction = source_code[line] ) ) {

		processing_ctx->error_details.line = line;

		/* Check if line is blank. */

		fcml_int length = fcml_fn_env_str_strlen( instruction );
		if( length > FCML_PARSER_MAX_INSTRUCTION_LEN ) {
			fcml_fn_ceh_add_error( &(processing_ctx->error_details.errors), fcml_fn_msg_get_message( FCML_MC_SEGMENT_PARSED_LINE_TO_LONG ),
					FCML_CEH_MEC_ERROR_PARSED_LINE_TOO_LONG, FCML_EN_CEH_EL_ERROR );
			error = FCML_CEH_GEC_INVALID_INPUT;
			break;
		}

		/* Empty lines should be ignored. */
		if( !fcml_fn_env_str_strblank( instruction ) ) {

			/* Allocate space for current instruction. */
			fcml_ist_lag_instruction *lag_instruction = fcml_ifn_lag_add_lag_instruction_to_context( processing_ctx );
			if( !lag_instruction ) {
				break;
			}

			fcml_st_parser_ast *ast = &(lag_instruction->ast);

			/* Parse instruction to AST. */
			error = fcml_fn_parse_to_ast( &parser_context, instruction, ast );
			if( error ) {
				fcml_fn_ceh_move_errors( &(processing_ctx->error_details.errors), &(ast->errors) );
				break;
			}

			/* There is symbol definition, so store it in symbol table. */
			if( ast->symbol ) {

				/* Check if symbol is already defined. */
				if( fcml_fn_symbol_get( context->symbol_table, ast->symbol->symbol ) ) {
					fcml_fn_msg_add_error_message( &(processing_ctx->error_details.errors), FCML_MC_SEGMENT_SYMBOL_ALREADY_DEFINED,
							FCML_CEH_MEC_ERROR_SYMBOL_ALREADY_DEFINED, FCML_EN_CEH_EL_ERROR, ast->symbol->symbol );
					/* Already defined. It doesn't finish up inside symbol table, which should free it later, so
					 * we have to free it manually here.
					 */
					fcml_fn_symbol_free( ast->symbol );
					ast->symbol = NULL;
					error = FCML_CEH_GEC_INVALID_INPUT;
					break;
				}

				/* Take into account that the same symbol is hold by AST and symbol table.
				 * It is detached from AST when AST is free'd and in result symbol table
				 * is responsible for freeing it.
				 */
				error = fcml_fn_symbol_add( context->symbol_table, ast->symbol );
				if( error ) {
					/* It doesn't finish up inside symbol table, which should free
					 * it later, so we have to free it manually here.
					 */
					fcml_fn_symbol_free( ast->symbol );
					ast->symbol = NULL;
					break;
				}

			}

			lag_instruction->line = line;

			fcml_int code_length = 0;

			/* Check if there is any instruction to assemble. */
			if( ast->tree ) {

				/* Convert AST to common instruction format. */

				fcml_st_cif_converter_context cif_context = {0};
				cif_context.ignore_undefined_symbols = FCML_TRUE;
				cif_context.symbol_table = context->symbol_table;

				fcml_st_instruction *cif_instruction;

				error = fcml_fn_ast_to_cif_converter( &cif_context, ast->tree, &cif_instruction );
				if( error ) {
					/* Should never happened, because we ignore undefined symbols. */
					break;
				}

				lag_instruction->undefined_symbols = cif_context.ignored_symbols;

				/* There are undefined symbols, so next phase is definitely needed. */
				if( cif_context.ignored_symbols > 0 ) {
					*invoke_next_pass = FCML_TRUE;
				}

				/* Assemble instruction. */

				if( assembler_context->entry_point.addr_form == FCML_AF_64_BIT ) {
					assembler_context->entry_point.ip.rip = (fcml_uint64_t)parser_context.ip;
				} else {
					assembler_context->entry_point.ip.eip = (fcml_uint32_t)parser_context.ip;
				}

				/* In case of first pass even if instruction fails, we will try again in the
				 * next pass, because it might fail because of some calculations that take
				 * place after choosing default value for undefined symbols.
				 */
				error = fcml_fn_assemble( assembler_context, cif_instruction, &assembler_result );
				if( !error ) {

					/* Free instruction model. */
					fcml_fn_ast_free_converted_cif( cif_instruction );

					cif_instruction = NULL;

					/* Choose the best instruction. */
					fcml_st_assembled_instruction *chosen_instruction = fcml_ifn_lag_choose_first_pass_best_instruction( cif_context.ignored_symbols, &assembler_result );

					code_length += chosen_instruction->code_length;

					lag_instruction->instruction = chosen_instruction;

					/* Move instruction warnings if there are any. */
					fcml_fn_ceh_move_errors( &(lag_instruction->instruction->errors), &(assembler_result.errors) );

					/* Instruction uses symbols, so extract it just in order to make
					 * them visible later in second stage, because we have to reassemble
					 * instructions which use modified symbols.
					 */
					if( cif_context.evaluated_symbols > 0 ) {
						error = fcml_fn_ast_extract_used_symbols( ast->tree, &(lag_instruction->used_symbols) );
						if( error ) {
							break;
						}
					}

				} else {
					error = FCML_CEH_GEC_NO_ERROR;
				}

				lag_instruction->ip = parser_context.ip;
			}

			/* Increment instruction pointer. */

			parser_context.ip += code_length;
		}

		line++;
	}

	fcml_fn_assembler_result_free( &assembler_result );

	fcml_fn_parser_result_free( &parser_result );

	return error;

}

fcml_ceh_error fcml_ifn_lag_assembler_pass_2_to_n( fcml_st_lag_assembler_context *context, fcml_ist_log_asseblation_context *processing_ctx ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_assembler_context *assembler_context = &(processing_ctx->assembler_context);

	fcml_st_assembler_result assembler_result;
	fcml_fn_assembler_result_prepare( &assembler_result );

	/* Allocate map for information about symbols modifications. */
	fcml_coll_map symbol_state_map = fcml_ifn_lag_alloc_symbol_state_map();
	if( !symbol_state_map ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}

	/* Passes counter. */
	fcml_int pass = 2;

	fcml_bool invoke_next_pass = FCML_TRUE;

	/* Main loop of second and further passes. */
	while( !error && invoke_next_pass ) {

		fcml_ist_lag_instruction *lag_instruction = processing_ctx->first_instruction;

		fcml_parser_ip ip_disp = 0;

		while( lag_instruction ) {

			processing_ctx->error_details.line = lag_instruction->line;

			lag_instruction->ip += ip_disp;

			fcml_st_symbol *def_symbol = lag_instruction->ast.symbol;

			/* Update defined symbol if there is such need. */

			if( def_symbol && ip_disp != 0 ) {

				def_symbol->value += ip_disp;

				/* Adds symbol to the map of recently modified symbols. */
				error = fcml_ifn_lag_add_symbol_state( symbol_state_map, def_symbol->symbol, pass );
				if( error ) {
					break;
				}

			}

			/* Instruction has to be reassembled in three cases. If it ignored
			 * any undefined symbol in the first phase, if it uses any symbol
			 * which is marked as recently modified and the last case if instruction
			 * IP has been modified and instruction uses symbols.
			 */
			if( !lag_instruction->instruction || lag_instruction->undefined_symbols ||
					( lag_instruction->used_symbols && ip_disp ) ||
					fcml_ifn_lag_is_any_symbol_modified( symbol_state_map, lag_instruction->used_symbols ) ) {

				fcml_st_instruction *cif_instruction;

				fcml_st_cif_converter_context cif_context = {0};
				cif_context.ignore_undefined_symbols = FCML_TRUE;
				cif_context.symbol_table = context->symbol_table;

				/* Regenerate instruction with new/modified symbols. */

				error = fcml_fn_ast_to_cif_converter( &cif_context, lag_instruction->ast.tree, &cif_instruction );
				if( error ) {
					break;
				}

				lag_instruction->undefined_symbols = cif_context.ignored_symbols;
				if( lag_instruction->undefined_symbols ) {
					fcml_fn_ast_free_converted_cif( cif_instruction );
					/* Undefined symbol. */
					break;
				}

				/* Assemble instruction. */

				if( assembler_context->entry_point.addr_form == FCML_AF_64_BIT ) {
					assembler_context->entry_point.ip.rip = (fcml_uint64_t)lag_instruction->ip;
				} else {
					assembler_context->entry_point.ip.eip = (fcml_uint32_t)lag_instruction->ip;
				}

				error = fcml_fn_assemble( assembler_context, cif_instruction, &assembler_result );
				if( error ) {
					fcml_fn_ast_free_converted_cif( cif_instruction );
					break;
				}

				fcml_fn_ast_free_converted_cif( cif_instruction );

				fcml_int code_length = lag_instruction->instruction->code_length;

				/* Choose the best instruction form. */

				fcml_st_assembled_instruction *choosen_instruction = fcml_ifn_lag_choose_second_pass_best_instruction( lag_instruction, &(assembler_result.instructions), assembler_result.chosen_instruction );

				if( lag_instruction->instruction ) {
					/* Free previous instruction. */
					fcml_fn_assembler_instruction_free( lag_instruction->instruction );
				}

				lag_instruction->instruction = choosen_instruction;

				ip_disp += ( (fcml_int)lag_instruction->instruction->code_length - code_length );

			}

			lag_instruction = lag_instruction->next;
		}

		/* Remove symbols from previous passes. */
		fcml_ifn_lag_clean_symbol_state_map( symbol_state_map, pass );

		/* Invoke next phase if and only if current phase modified any symbols. */
		invoke_next_pass = fcml_fn_coll_map_size( symbol_state_map ) > 0;

		pass++;
	}

	/* Free all symbol states stored in the map. Take into
	 * account that map should be already empty here if
	 * assemblation succeeded.
	 */
	fcml_fn_coll_map_free( symbol_state_map );

	fcml_fn_assembler_result_free( &assembler_result );

	return error;
}

/* Copies assembled instructions from LAG context to the result. */
void fcml_ifn_lag_convert_instructions( fcml_ist_log_asseblation_context *processing_ctx, fcml_st_lag_assembler_result *result ) {
	fcml_ist_lag_instruction *first_instruction = processing_ctx->first_instruction;
	fcml_ist_lag_instruction *current = first_instruction;
	while( current ) {
		fcml_ist_lag_instruction *next = current->next;
		current->instruction->next = next->instruction;
		/* Detach assembled instruction from lag instruction. */
		current->instruction = NULL;
		current = next;
	}
	result->instructions = first_instruction->instruction;
}

/* Assembles code available in "source_code" array. */
fcml_ceh_error LIB_CALL fcml_ifn_lag_assemble_core( fcml_st_lag_assembler_context *context, const fcml_string *source_code, fcml_st_lag_assembler_result *result ) {

	fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

	fcml_ist_log_asseblation_context processing_ctx = {0};

	/* Free result of the previous assemblation. */

	fcml_fn_lag_assembler_result_free( result );

	/* Allocate symbol table, if it hasn't been defined yet. */
	fcml_bool local_st = FCML_FALSE;
	if( !context->symbol_table ) {
		context->symbol_table = fcml_fn_symbol_table_alloc();
		if( !context->symbol_table ) {
			return FCML_CEH_GEC_OUT_OF_MEMORY;
		}
		local_st = FCML_TRUE;
	}

	fcml_st_assembler_context *assembler_context = &(processing_ctx.assembler_context);

	/* It's really important to use default implementations of optimizer and chooser here. */

	assembler_context->assembler = context->assembler;
	assembler_context->configuration = context->configuration;
	assembler_context->configuration.optimizer = &fcml_fn_asm_default_optimizer;
	assembler_context->configuration.chooser = &fcml_fn_asm_default_instruction_chooser;
	assembler_context->entry_point = context->entry_point;

	/* Pass 1 */

	fcml_bool invoke_next_pass = FCML_FALSE;

	error = fcml_ifn_lag_assembler_pass_1( context, source_code, &processing_ctx, &invoke_next_pass );

	/* Pass 2 */

	if( !error && invoke_next_pass ) {
		fcml_ifn_lag_assembler_pass_2_to_n( context, &processing_ctx );
	}

	/* Prepare result. */
	fcml_ifn_lag_convert_instructions( &processing_ctx, result );

	/* Free all assembled instructions. In case of error clean symbol table as well. */
	fcml_ifn_lag_free_instruction( processing_ctx.first_instruction, error ? context->symbol_table : NULL );

	/* It's our own symbol table so free it. Remember that user's symbol table is populated
	 * with symbols defined while assembling. It can be useful to get these information
	 * when code is already assembled, but it has also disadvantages, because user have
	 * to free them. Fortunately it is completely transparent functionality realized by
	 * "fcml_fn_symbol_table_free" function which user is obliged to call anyway.
	 */
	if( local_st ) {
		fcml_fn_symbol_table_free( context->symbol_table );
		context->symbol_table = NULL;
	}

	return error;

}

/* Load-and-go assembler. */
fcml_ceh_error LIB_CALL fcml_fn_lag_assemble( fcml_st_lag_assembler_context *context, const fcml_string *source_code, fcml_st_lag_assembler_result *result ) {

	fcml_ceh_error error = fcml_ifn_lag_assemble_core( context, source_code, result );

	if( error ) {
		// Try to convert error code to error message if there is such need.
		fcml_fn_utils_convert_gec_to_error_info( context->configuration.enable_error_messages, &(result->errors), error );
	}

	return error;
}

/* Free result of the load-and-go assemblation process. */
void LIB_CALL fcml_fn_lag_assembler_result_free( fcml_st_lag_assembler_result *result ) {
	if( result ) {
		fcml_fn_ceh_free_errors_only( &(result->errors) );
		fcml_st_assembled_instruction *instruction = result->instructions;
		if( instruction ) {
			fcml_st_assembled_instruction *next = instruction->next;
			fcml_fn_assembler_instruction_free( instruction );
			instruction = next;
		}
		result->error_line = 0;
		result->instructions = NULL;
	}
}

void LIB_CALL fcml_fn_lag_assembler_result_prepare( fcml_st_lag_assembler_result *result ) {
	if( result ) {
		fcml_fn_env_memory_clear( result, sizeof( fcml_st_lag_assembler_result ) );
	}
}
