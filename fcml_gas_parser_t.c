/*
 * fcml_gas_parser_t.c
 *
 *  Created on: Nov 16, 2013
 *      Author: tas
 */


/*
 * fcml_intel_parser.c
 *
 *  Created on: 29-06-2013
 *      Author: tAs
 */

#include "fcml_gas_parser_t.h"

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <fcml_ceh.h>
#include <fcml_common.h>
#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_gas_parser.h>
#include <fcml_gas_dialect.h>
#include <string.h>

fcml_st_dialect *internal_dialect_gas = NULL;

int fcml_tf_gas_parser_suite_init(void) {
	fcml_fn_gas_dialect_init( FCML_GAS_DIALECT_CF_DEFAULT, &internal_dialect_gas );
	return 0;
}

int fcml_tf_gas_parser_suite_cleanup(void) {
    if( internal_dialect_gas ) {
        fcml_fn_gas_dialect_free( internal_dialect_gas );
    }
	return 0;
}

void fcml_tf_parser_gas_parse_test1(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "mov $80-90", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)-10 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test2(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "mov (%eax)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.base.size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.base.reg, FCML_REG_EAX );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test3(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:(%rax)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_RAX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test4(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:(%rax,%rbx)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_RAX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test5(void) {
	// Index only.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:(,%rbx)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_UNDEF );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test6(void) {
	// Index only.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:(,%rbx,4)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_UNDEF );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.scale_factor, 4 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test7(void) {
	// Index only.
	fcml_st_parser_result *result = NULL;
	CU_ASSERT_NOT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:(,%rbx,)", &result ), FCML_CEH_GEC_NO_ERROR );
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test8(void) {
	// Index only.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:0x100(,%rbx,4)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_UNDEF );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.scale_factor, 4 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.displacement.size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.displacement.dis16, (fcml_uint16_t)0x100 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test9(void) {
	// Index only.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:0x100", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_OFFSET );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.offset.size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.offset.off16, (fcml_uint16_t)0x100 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test10(void) {
	// Index only.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,%cs:0x100(%rax,%rbx,4)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_RAX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.index.reg, FCML_REG_RBX );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.scale_factor, 4 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.displacement.size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.displacement.dis16, (fcml_uint16_t)0x100 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.segment_selector.segment_selector.reg, FCML_REG_CS );
	} else {
		CU_FAIL();
	}
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test11(void) {
	// RIP only.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "movq $1,0x100(%rip)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.address_form, FCML_AF_COMBINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.reg, FCML_REG_UNDEFINED );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.base.type, FCML_REG_IP );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.displacement.size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[1].address.effective_address.displacement.dis16, (fcml_uint16_t)0x100 );
	} else {
		CU_FAIL();
	}
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_gas_parse_test12(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_gas_parse( internal_dialect_gas, "mov *0x80", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
		CU_ASSERT_EQUAL( result->instruction->hints, FCML_HINT_INDIRECT_POINTER );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

CU_TestInfo fcml_ti_parser_gas[] = {
    { "fcml_tf_parser_gas_parse_test1", fcml_tf_parser_gas_parse_test1 },
    { "fcml_tf_parser_gas_parse_test2", fcml_tf_parser_gas_parse_test2 },
    { "fcml_tf_parser_gas_parse_test3", fcml_tf_parser_gas_parse_test3 },
    { "fcml_tf_parser_gas_parse_test4", fcml_tf_parser_gas_parse_test4 },
    { "fcml_tf_parser_gas_parse_test5", fcml_tf_parser_gas_parse_test5 },
    { "fcml_tf_parser_gas_parse_test6", fcml_tf_parser_gas_parse_test6 },
    { "fcml_tf_parser_gas_parse_test7", fcml_tf_parser_gas_parse_test7 },
    { "fcml_tf_parser_gas_parse_test8", fcml_tf_parser_gas_parse_test8 },
    { "fcml_tf_parser_gas_parse_test9", fcml_tf_parser_gas_parse_test9 },
    { "fcml_tf_parser_gas_parse_test10", fcml_tf_parser_gas_parse_test10 },
    { "fcml_tf_parser_gas_parse_test11", fcml_tf_parser_gas_parse_test11 },
    { "fcml_tf_parser_gas_parse_test12", fcml_tf_parser_gas_parse_test12 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_gas_parser[] = {
    { "suite-fcml-parser-at&t", fcml_tf_gas_parser_suite_init, fcml_tf_gas_parser_suite_cleanup, fcml_ti_parser_gas },
    CU_SUITE_INFO_NULL,
};
