/*
 * fcml_def_enc.c
 *
 *  Created on: 14-04-2013
 *      Author: tAs
 */

#include "fcml_def.h"
#include "fcml_env.h"

typedef fcml_ptr (*fcml_fnp_def_addr_mode_args_decoder)( fcml_uint32_t encoded_addr_mode );

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_imm( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_imm *imm_args = (fcml_sf_def_tma_imm*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_imm));
	if( imm_args ) {
		imm_args->encoded_imm_size = ( encoded_addr_mode & 0x0000FF00) >> 8;
		imm_args->encoded_ex_imm_size = encoded_addr_mode & 0x000000FF;
	}
	return imm_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_explicit_reg( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_explicit_reg *explicit_reg_args = (fcml_sf_def_tma_explicit_reg*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_explicit_reg));
	if( explicit_reg_args ) {
		explicit_reg_args->reg_type = ( encoded_addr_mode & 0x0000F000 ) >> 12;
		explicit_reg_args->reg_num = ( encoded_addr_mode & 0x00000F00 ) >> 8;
		explicit_reg_args->encoded_reg_size = encoded_addr_mode & 0x000000FF;
	}
	return explicit_reg_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_opcode_reg( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_opcode_reg *opcode_reg_args = (fcml_sf_def_tma_opcode_reg*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_opcode_reg));
	if( opcode_reg_args ) {
		opcode_reg_args->reg_type = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
		opcode_reg_args->encoded_reg_size = encoded_addr_mode & 0x000000FF;
	}
	return opcode_reg_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_immediate_dis_relative( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_immediate_dis_relative *immediate_dis_relative_args = (fcml_sf_def_tma_immediate_dis_relative*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_immediate_dis_relative));
	if( immediate_dis_relative_args ) {
		immediate_dis_relative_args->encoded_imm_size = encoded_addr_mode & 0x000000FF;
	}
	return immediate_dis_relative_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_explicit_gps_reg_addressing( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_explicit_gps_reg_addressing *explicit_gps_reg_addressing_args = (fcml_sf_def_tma_explicit_gps_reg_addressing*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_explicit_gps_reg_addressing));
	if( explicit_gps_reg_addressing_args ) {
		explicit_gps_reg_addressing_args->reg_num = ( encoded_addr_mode & 0x00FF0000 ) >> 16;
		explicit_gps_reg_addressing_args->encoded_operand_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
		explicit_gps_reg_addressing_args->encoded_segment_register = encoded_addr_mode & 0x000000FF;
	}
	return explicit_gps_reg_addressing_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_explicit_ib( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_explicit_ib *explicit_ib_args = (fcml_sf_def_tma_explicit_ib*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_explicit_ib));
	if( explicit_ib_args ) {
		explicit_ib_args->ib = encoded_addr_mode & 0x000000FF;
	}
	return explicit_ib_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_segment_relative_offset( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_segment_relative_offset *segment_relative_offset_args = (fcml_sf_def_tma_segment_relative_offset*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_segment_relative_offset));
	if( segment_relative_offset_args ) {
		segment_relative_offset_args->encoded_operand_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
		segment_relative_offset_args->encoded_segment_register = encoded_addr_mode & 0x000000FF;
	}
	return segment_relative_offset_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_rm( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_rm *rm_args = (fcml_sf_def_tma_rm*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_rm));
	if( rm_args ) {
		rm_args->reg_type = ( encoded_addr_mode & 0x000000F0 ) >> 4;
		rm_args->encoded_register_operand_size = ( encoded_addr_mode & 0x0000FF00 ) >> 8;
		rm_args->encoded_memory_operand_size = ( encoded_addr_mode & 0x00FF0000 ) >> 16;
		rm_args->flags = encoded_addr_mode & 0x0000000F;
	}
	return rm_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_r( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_r *r_args = (fcml_sf_def_tma_r*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_r));
	if( r_args ) {
		r_args->reg_type =  encoded_addr_mode & 0x0000000F;
		r_args->encoded_register_operand_size = (encoded_addr_mode & 0x00000FF0) >> 4;
	}
	return r_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_vex_vvvv( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_vex_vvvv_reg *vex_vvvv_args = (fcml_sf_def_tma_vex_vvvv_reg*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_vex_vvvv_reg));
	if( vex_vvvv_args ) {
		vex_vvvv_args->reg_type =  encoded_addr_mode & 0x0000000F;
		vex_vvvv_args->encoded_register_size = (encoded_addr_mode & 0x00000FF0) >> 4;
	}
	return vex_vvvv_args;
}

fcml_ptr fcml_fnp_def_addr_mode_args_decoder_vsib( fcml_uint32_t encoded_addr_mode ) {
	fcml_sf_def_tma_vsib *vsib_args = (fcml_sf_def_tma_vsib*)fcml_fn_env_memory_alloc(sizeof(fcml_sf_def_tma_vsib));
	if( vsib_args ) {
		vsib_args->vector_index_register =  encoded_addr_mode >> 2;
		vsib_args->index_value_size = encoded_addr_mode & 0x03;
	}
	return vsib_args;

}

#define FCML_DEF_DECODERS_COUNT		( sizeof( fcml_def_addr_mode_args_decoders ) / sizeof( fcml_fnp_def_addr_mode_args_decoder ) )

fcml_fnp_def_addr_mode_args_decoder fcml_def_addr_mode_args_decoders[] = {
	NULL,
	fcml_fnp_def_addr_mode_args_decoder_imm,
	fcml_fnp_def_addr_mode_args_decoder_explicit_reg,
	fcml_fnp_def_addr_mode_args_decoder_opcode_reg,
	fcml_fnp_def_addr_mode_args_decoder_immediate_dis_relative,
	NULL,
	NULL,
	fcml_fnp_def_addr_mode_args_decoder_explicit_gps_reg_addressing,
	fcml_fnp_def_addr_mode_args_decoder_explicit_ib,
	fcml_fnp_def_addr_mode_args_decoder_segment_relative_offset,
	fcml_fnp_def_addr_mode_args_decoder_rm,
	fcml_fnp_def_addr_mode_args_decoder_r,
	fcml_fnp_def_addr_mode_args_decoder_vex_vvvv,
	NULL,
	fcml_fnp_def_addr_mode_args_decoder_vsib
};

fcml_st_def_decoded_addr_mode* fcml_fnp_def_decode_addr_mode_args( fcml_uint32_t encoded_addr_mode, fcml_ceh_error *error ) {
	*error = FCML_CEH_GEC_NO_ERROR;
	fcml_st_def_decoded_addr_mode *addr_mode = (fcml_st_def_decoded_addr_mode*)fcml_fn_env_memory_alloc(sizeof(fcml_st_def_decoded_addr_mode));
	if( addr_mode ) {
		addr_mode->addr_mode = ( encoded_addr_mode & 0xFF000000 ) >> 24;
		if( addr_mode->addr_mode > FCML_DEF_DECODERS_COUNT ) {
			*error = FCML_CEH_GEC_INVALID_INPUT;
			fcml_fn_env_memory_free( addr_mode );
			return NULL;
		}
		addr_mode->addr_mode_args = NULL;
		fcml_fnp_def_addr_mode_args_decoder args_decoder = fcml_def_addr_mode_args_decoders[addr_mode->addr_mode];
		if( args_decoder ) {
			addr_mode->addr_mode_args = args_decoder( encoded_addr_mode & 0x00FFFFFF );
		}
	}
	return addr_mode;
}

void fcml_fnp_def_free_addr_mode( fcml_st_def_decoded_addr_mode *decoded_addr_mode ) {
	if( decoded_addr_mode ) {
		if( decoded_addr_mode->addr_mode_args ) {
			fcml_fn_env_memory_free( decoded_addr_mode->addr_mode_args );
		}
		fcml_fn_env_memory_free(decoded_addr_mode);
	}
}
