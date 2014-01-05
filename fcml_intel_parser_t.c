/*
 * fcml_intel_parser.c
 *
 *  Created on: 29-06-2013
 *      Author: tAs
 */

#include "fcml_intel_parser_t.h"

#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <fcml_ceh.h>
#include <fcml_common.h>
#include <fcml_types.h>
#include <fcml_errors.h>
#include <fcml_intel_parser.h>
#include <fcml_intel_dialect.h>
#include <string.h>

fcml_st_dialect *internal_dialect_intel = NULL;

int fcml_tf_parser_suite_init(void) {
	fcml_fn_intel_dialect_init( FCML_INTEL_DIALECT_CF_DEFAULT, &internal_dialect_intel );
	return 0;
}

int fcml_tf_parser_suite_cleanup(void) {
    fcml_fn_intel_dialect_free( internal_dialect_intel );
	return 0;
}

void fcml_tf_parser_int_parse_test1(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 80-90", &result ), FCML_CEH_GEC_NO_ERROR );
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

void fcml_tf_parser_int_parse_test2(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 0xFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, 0xFF );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test3(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 0xFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)0x0FFF );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test4(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 0xFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)0xFFFF );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test5(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 0xFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)0x000FFFFF );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test6(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 0xFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)0xFFFFFFFF );
	} else {
	    CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test7(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 0xFFFFFFFFFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, 0xFFFFFFFFFFFFFFFFUL );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test8(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov -0xFFFFFFFFFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)1 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test9(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov -0xFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)(fcml_int16_t)-255 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test10(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 1+2", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)(fcml_int8_t)3 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test11(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 1+2*8/(15-13)-1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)8 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test12(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 65535", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)0xFFFF );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test13(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov -32768", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)-32768 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test14(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov (-2147483647 - 1)", &result ), FCML_CEH_GEC_NO_ERROR );
	CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
	CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
	CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
	CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)(-2147483647 - 1) );
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test15(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov (-9223372036854775807 - 1)", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)(-9223372036854775807LL - 1) );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test16(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 18446744073709551615", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)18446744073709551615ULL );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test17(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 5675", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_16 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm16, (fcml_uint16_t)5675 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test18(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 2147483647", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)2147483647 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test19(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 4294967295", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_32 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm32, (fcml_uint32_t)4294967295U );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test20(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 4294967296", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)4294967296ULL );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test21(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov -0xFFFFFFFF", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_64 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_TRUE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm64, (fcml_uint64_t)-4294967295LL );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test22(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 255", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, 0xFF );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test23(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, 1 );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test24(void) {
    fcml_st_parser_result *result;
    CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov dword ptr [0x0000FFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result->instruction != NULL ) {
        CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.size, FCML_DS_16 );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.off16, (fcml_int16_t)0xFFFF );
    } else {
        CU_FAIL();
    }
    fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test25(void) {
    fcml_st_parser_result *result;
    CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov dword ptr [0xFF-1]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result->instruction != NULL ) {
        CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.size, FCML_DS_16 );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.off16, 254 );
    } else {
        CU_FAIL();
    }
    fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test26(void) {
    fcml_st_parser_result *result;
    CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov dword ptr [-1]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result->instruction != NULL ) {
        CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.size, FCML_DS_16 );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.off16, (fcml_int16_t)0xFFFF );
    } else {
        CU_FAIL();
    }
    fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test27(void) {
    fcml_st_parser_result *result;
    CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov dword ptr [0xFFFFFFFFFFFFFFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result->instruction != NULL ) {
        CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_OFFSET );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.size, FCML_DS_64 );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.offset.off64, 0xFFFFFFFFFFFFFFFFULL );
    } else {
        CU_FAIL();
    }
    fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test28(void) {
    fcml_st_parser_result *result;
    CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov dword ptr [eax+0xFFFFFFFFFFFFFFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result->instruction != NULL ) {
        CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_COMBINED );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.base.type, FCML_REG_GPR );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.base.reg, FCML_REG_EAX );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.displacement.size, FCML_DS_64 );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.displacement.dis64, 0xFFFFFFFFFFFFFFFFULL );
    } else {
        CU_FAIL();
    }
    fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test29(void) {
    fcml_st_parser_result *result;
    CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "mov xmmword ptr [eax+0xFFFFFFFFFFFFFFFF]", &result ), FCML_CEH_GEC_NO_ERROR );
    if( result->instruction != NULL ) {
        CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_ADDRESS );
        CU_ASSERT_EQUAL( result->instruction->operands[0].hints, FCML_OP_HINT_MULTIMEDIA_INSTRUCTION );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.address_form, FCML_AF_COMBINED );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.base.type, FCML_REG_GPR );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.base.reg, FCML_REG_EAX );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.displacement.size, FCML_DS_64 );
        CU_ASSERT_EQUAL( result->instruction->operands[0].address.effective_address.displacement.dis64, 0xFFFFFFFFFFFFFFFFULL );
    } else {
        CU_FAIL();
    }
    fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test30(void) {
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "lock mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->prefixes, FCML_PREFIX_LOCK );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test31(void) {
	// Check if multiple prefixes are allowed.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "lock repne repe mov 1", &result ), FCML_CEH_GEC_NO_ERROR );
	if( result->instruction != NULL ) {
		CU_ASSERT_EQUAL( result->instruction->operands[0].type, FCML_EOT_IMMEDIATE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm_size, FCML_DS_8 );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.is_signed, FCML_FALSE );
		CU_ASSERT_EQUAL( result->instruction->operands[0].immediate.imm8, (fcml_uint8_t)1 );
		CU_ASSERT_EQUAL( result->instruction->prefixes, FCML_PREFIX_LOCK | FCML_PREFIX_REPE | FCML_PREFIX_REPNE );
	} else {
        CU_FAIL();
    }
	fcml_fn_parser_result_free( result );
}

void fcml_tf_parser_int_parse_test32(void) {
	// Duplicated prefixes aren't allowed.
	fcml_st_parser_result *result;
	CU_ASSERT_EQUAL( fcml_intel_parse( internal_dialect_intel, "lock lock mov 1", &result ), FCML_CEH_GEC_INVALID_INPUT );
	if( result->instruction != NULL ) {
        CU_FAIL("Instruction should be NULL.");
	} else if( result->errors.errors ){
		fcml_st_ceh_error_container *cont = &(result->errors);
		CU_ASSERT_EQUAL( cont->errors->level, FCML_EN_CEH_EL_ERROR );
		CU_ASSERT_EQUAL( cont->errors->code, ( FCML_EN_X64IP_ERROR_INV_SYNTAX ) );
		CU_ASSERT_STRING_EQUAL( "Doubled prefixes.", cont->errors->message );
    } else {
    	CU_FAIL("Errors can not be null here.");
    }
	fcml_fn_parser_result_free( result );
}

CU_TestInfo fcml_ti_parser[] = {
    { "fcml_tf_parser_int_parse_test1", fcml_tf_parser_int_parse_test1 },
    { "fcml_tf_parser_int_parse_test2", fcml_tf_parser_int_parse_test2 },
    { "fcml_tf_parser_int_parse_test3", fcml_tf_parser_int_parse_test3 },
    { "fcml_tf_parser_int_parse_test4", fcml_tf_parser_int_parse_test4 },
    { "fcml_tf_parser_int_parse_test5", fcml_tf_parser_int_parse_test5 },
    { "fcml_tf_parser_int_parse_test6", fcml_tf_parser_int_parse_test6 },
    { "fcml_tf_parser_int_parse_test7", fcml_tf_parser_int_parse_test7 },
    { "fcml_tf_parser_int_parse_test8", fcml_tf_parser_int_parse_test8 },
    { "fcml_tf_parser_int_parse_test9", fcml_tf_parser_int_parse_test9 },
    { "fcml_tf_parser_int_parse_test10", fcml_tf_parser_int_parse_test10 },
    { "fcml_tf_parser_int_parse_test11", fcml_tf_parser_int_parse_test11 },
    { "fcml_tf_parser_int_parse_test12", fcml_tf_parser_int_parse_test12 },
    { "fcml_tf_parser_int_parse_test13", fcml_tf_parser_int_parse_test13 },
    { "fcml_tf_parser_int_parse_test14", fcml_tf_parser_int_parse_test14 },
    { "fcml_tf_parser_int_parse_test15", fcml_tf_parser_int_parse_test15 },
    { "fcml_tf_parser_int_parse_test16", fcml_tf_parser_int_parse_test16 },
    { "fcml_tf_parser_int_parse_test17", fcml_tf_parser_int_parse_test17 },
    { "fcml_tf_parser_int_parse_test18", fcml_tf_parser_int_parse_test18 },
    { "fcml_tf_parser_int_parse_test19", fcml_tf_parser_int_parse_test19 },
    { "fcml_tf_parser_int_parse_test20", fcml_tf_parser_int_parse_test20 },
    { "fcml_tf_parser_int_parse_test21", fcml_tf_parser_int_parse_test21 },
    { "fcml_tf_parser_int_parse_test22", fcml_tf_parser_int_parse_test22 },
    { "fcml_tf_parser_int_parse_test23", fcml_tf_parser_int_parse_test23 },
    { "fcml_tf_parser_int_parse_test24", fcml_tf_parser_int_parse_test24 },
    { "fcml_tf_parser_int_parse_test25", fcml_tf_parser_int_parse_test25 },
    { "fcml_tf_parser_int_parse_test26", fcml_tf_parser_int_parse_test26 },
    { "fcml_tf_parser_int_parse_test27", fcml_tf_parser_int_parse_test27 },
    { "fcml_tf_parser_int_parse_test28", fcml_tf_parser_int_parse_test28 },
    { "fcml_tf_parser_int_parse_test29", fcml_tf_parser_int_parse_test29 },
    { "fcml_tf_parser_int_parse_test30", fcml_tf_parser_int_parse_test30 },
    { "fcml_tf_parser_int_parse_test31", fcml_tf_parser_int_parse_test31 },
    { "fcml_tf_parser_int_parse_test32", fcml_tf_parser_int_parse_test32 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_intel_parser[] = {
    { "suite-fcml-parser", fcml_tf_parser_suite_init, fcml_tf_parser_suite_cleanup, fcml_ti_parser },
    CU_SUITE_INFO_NULL,
};
