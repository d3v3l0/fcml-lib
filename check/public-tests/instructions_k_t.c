/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcml_assembler.h>
#include "instructions_k_t.h"
#include "instructions_base_t.h"

fcml_bool fcml_tf_instructions_k_suite_init(void) {
    return FCML_TRUE;
}

fcml_bool fcml_tf_instructions_k_suite_cleanup(void) {
    return FCML_TRUE;
}

void fcml_tf_instruction_KADDW(void) {
    FCML_I3264( "kaddw k1,k2,k3", 0xC5, 0xEC, 0x4A, 0xCB );
    FCML_A3264( "kaddw %k3,%k2,%k1", 0xC5, 0xEC, 0x4A, 0xCB );
    FCML_I3264( "kaddw k7,k7,k7", 0xC5, 0xC4, 0x4A, 0xFF );
    FCML_I64_A_FAILED( "kaddw k7,k7,qword [rax]", 0xC5, 0xC4, 0x4A, 0x38 );
}

void fcml_tf_instruction_KADDB(void) {
    FCML_I3264( "kaddb k1,k2,k3", 0xC5, 0xED, 0x4A, 0xCB );
    FCML_A3264( "kaddb %k3,%k2,%k1", 0xC5, 0xED, 0x4A, 0xCB );
}

void fcml_tf_instruction_KADDD(void) {
    FCML_I3264( "kaddd k1,k2,k3", 0xC4, 0xE1, 0xED, 0x4A, 0xCB );
    FCML_A3264( "kaddd %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x4A, 0xCB );
}

void fcml_tf_instruction_KADDQ(void) {
    FCML_I3264( "kaddq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x4A, 0xCB );
    FCML_A3264( "kaddq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x4A, 0xCB );
}

void fcml_tf_instruction_KANDW(void) {
    FCML_I3264( "kandw k1,k2,k3", 0xC5, 0xEC, 0x41, 0xCB );
    FCML_A3264( "kandw %k3,%k2,%k1", 0xC5, 0xEC, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDB(void) {
    FCML_I3264( "kandb k1,k2,k3", 0xC5, 0xED, 0x41, 0xCB );
    FCML_A3264( "kandb %k3,%k2,%k1", 0xC5, 0xED, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDD(void) {
    FCML_I3264( "kandd k1,k2,k3", 0xC4, 0xE1, 0xED, 0x41, 0xCB );
    FCML_A3264( "kandd %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDQ(void) {
    FCML_I3264( "kandq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x41, 0xCB );
    FCML_A3264( "kandq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x41, 0xCB );
}

void fcml_tf_instruction_KANDNW(void) {
    FCML_I3264( "kandnw k1,k2,k3", 0xC5, 0xEC, 0x42, 0xCB );
    FCML_A3264( "kandnw %k3,%k2,%k1", 0xC5, 0xEC, 0x42, 0xCB );
}

void fcml_tf_instruction_KANDNB(void) {
    FCML_I3264( "kandnb k1,k2,k3", 0xC5, 0xED, 0x42, 0xCB );
    FCML_A3264( "kandnb %k3,%k2,%k1", 0xC5, 0xED, 0x42, 0xCB );
}

void fcml_tf_instruction_KANDND(void) {
    FCML_I3264( "kandnd k1,k2,k3", 0xC4, 0xE1, 0xED, 0x42, 0xCB );
    FCML_A3264( "kandnd %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x42, 0xCB );
}

void fcml_tf_instruction_KANDNQ(void) {
    FCML_I3264( "kandnq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x42, 0xCB );
    FCML_A3264( "kandnq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x42, 0xCB );
}

void fcml_tf_instruction_KMOVB(void) {
    FCML_I32( "kmovb k1,byte ptr [eax]", 0xC5, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovb k1,byte ptr [rax]", 0xC5, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovb k1,k2", 0xC5, 0xF9, 0x90, 0xCA );
    FCML_I32_A( "kmovb k1,[eax]", 0xC5, 0xF9, 0x90, 0x08 );

    FCML_I32( "kmovb byte ptr [eax],k1", 0xC5, 0xF9, 0x91, 0x08 );
    FCML_I64( "kmovb byte ptr [rax],k1", 0xC5, 0xF9, 0x91, 0x08 );

    FCML_I3264( "kmovb k2,eax", 0xC5, 0xF9, 0x92, 0xD0 );
    FCML_I3264( "kmovb eax,k2", 0xC5, 0xF9, 0x93, 0xC2 );
}

void fcml_tf_instruction_KMOVW(void) {
    FCML_I32( "kmovw k1,word ptr [eax]", 0xC5, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovw k1,word ptr [rax]", 0xC5, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovw k1,k2", 0xC5, 0xF8, 0x90, 0xCA );
    FCML_I32_A( "kmovw k1,[eax]", 0xC5, 0xF8, 0x90, 0x08 );

    FCML_I32( "kmovw word ptr [eax],k1", 0xC5, 0xF8, 0x91, 0x08 );
    FCML_I64( "kmovw word ptr [rax],k1", 0xC5, 0xF8, 0x91, 0x08 );

    FCML_I3264( "kmovw k2,eax", 0xC5, 0xF8, 0x92, 0xD0 );
    FCML_I3264( "kmovw eax,k2", 0xC5, 0xF8, 0x93, 0xC2 );
}

void fcml_tf_instruction_KMOVD(void) {
    FCML_I32( "kmovd k1,dword ptr [eax]", 0xC4, 0xE1, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovd k1,dword ptr [rax]", 0xC4, 0xE1, 0xF9, 0x90, 0x08 );
    FCML_I64( "kmovd k1,k2", 0xC4, 0xE1, 0xF9, 0x90, 0xCA );
    FCML_I32_A( "kmovd k1,[eax]", 0xC4, 0xE1, 0xF9, 0x90, 0x08 );

    FCML_I32( "kmovd dword ptr [eax],k1", 0xC4, 0xE1, 0xF9, 0x91, 0x08 );
    FCML_I64( "kmovd dword ptr [rax],k1", 0xC4, 0xE1, 0xF9, 0x91, 0x08 );

    FCML_I3264( "kmovd k2,eax", 0xC5, 0xFB, 0x92, 0xD0 );
    FCML_I3264( "kmovd eax,k2", 0xC5, 0xFB, 0x93, 0xc2 );
}

void fcml_tf_instruction_KMOVQ(void) {
    FCML_I32( "kmovq k1,qword ptr [eax]", 0xC4, 0xE1, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovq k1,qword ptr [rax]", 0xC4, 0xE1, 0xF8, 0x90, 0x08 );
    FCML_I64( "kmovq k1,k2", 0xC4, 0xE1, 0xF8, 0x90, 0xCA );
    FCML_I32_A( "kmovq k1,[eax]", 0xC4, 0xE1, 0xF8, 0x90, 0x08 );

    FCML_I32( "kmovq qword ptr [eax],k1", 0xC4, 0xE1, 0xF8, 0x91, 0x08 );
    FCML_I64( "kmovq qword ptr [rax],k1", 0xC4, 0xE1, 0xF8, 0x91, 0x08 );

    FCML_I64( "kmovq k2,rax", 0xC4, 0xE1, 0xFB, 0x92, 0xD0 );
    FCML_I64( "kmovq rdx,k0", 0xC4, 0xE1, 0xFB, 0x93, 0xD0 );
}

void fcml_tf_instruction_KNOTW(void) {
    FCML_I3264( "knotw k1,k3", 0xC5, 0xF8, 0x44, 0xCB );
    FCML_A3264( "knotw %k3,%k1", 0xC5, 0xF8, 0x44, 0xCB );
}

void fcml_tf_instruction_KNOTB(void) {
    FCML_I3264( "knotb k1,k3", 0xC5, 0xF9, 0x44, 0xCB );
    FCML_A3264( "knotb %k3,%k1", 0xC5, 0xF9, 0x44, 0xCB );
}

void fcml_tf_instruction_KNOTD(void) {
    FCML_I3264( "knotd k1,k3", 0xC4, 0xE1, 0xF9, 0x44, 0xCB );
    FCML_A3264( "knotd %k3,%k1", 0xC4, 0xE1, 0xF9, 0x44, 0xCB );
}

void fcml_tf_instruction_KNOTQ(void) {
    FCML_I3264( "knotq k1,k3", 0xC4, 0xE1, 0xF8, 0x44, 0xCB );
    FCML_A3264( "knotq %k3,%k1", 0xC4, 0xE1, 0xF8, 0x44, 0xCB );
}

void fcml_tf_instruction_KORW(void) {
    FCML_I3264( "korw k1,k2,k3", 0xC5, 0xEC, 0x45, 0xCB );
    FCML_A3264( "korw %k3,%k2,%k1", 0xC5, 0xEC, 0x45, 0xCB );
}

void fcml_tf_instruction_KORB(void) {
    FCML_I3264( "korb k1,k2,k3", 0xC5, 0xED, 0x45, 0xCB );
    FCML_A3264( "korb %k3,%k2,%k1", 0xC5, 0xED, 0x45, 0xCB );
}

void fcml_tf_instruction_KORD(void) {
    FCML_I3264( "kord k1,k2,k3", 0xC4, 0xE1, 0xED, 0x45, 0xCB );
    FCML_A3264( "kord %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x45, 0xCB );
}

void fcml_tf_instruction_KORQ(void) {
    FCML_I3264( "korq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x45, 0xCB );
    FCML_A3264( "korq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x45, 0xCB );
}

void fcml_tf_instruction_KORTESTW(void) {
    FCML_I3264( "kortestw k1,k3", 0xC5, 0xf8, 0x98, 0xCB );
    FCML_A3264( "kortestw %k3,%k1", 0xC5, 0xf8, 0x98, 0xCB );
}

void fcml_tf_instruction_KORTESTB(void) {
    FCML_I3264( "kortestb k1,k3", 0xC5, 0xf9, 0x98, 0xCB );
    FCML_A3264( "kortestb %k3,%k1", 0xC5, 0xf9, 0x98, 0xCB );
}

void fcml_tf_instruction_KORTESTD(void) {
    FCML_I3264( "kortestd k1,k3", 0xC4, 0xE1, 0xf9, 0x98, 0xCB );
    FCML_A3264( "kortestd %k3,%k1", 0xC4, 0xE1, 0xf9, 0x98, 0xCB );
}

void fcml_tf_instruction_KORTESTQ(void) {
    FCML_I3264( "kortestq k1,k3", 0xC4, 0xE1, 0xf8, 0x98, 0xCB );
    FCML_A3264( "kortestq %k3,%k1", 0xC4, 0xE1, 0xf8, 0x98, 0xCB );
}

void fcml_tf_instruction_KSHIFTLW(void) {
    FCML_I3264( "kshiftlw k1,k3,0ah", 0xC4, 0xE3, 0xF9, 0x32, 0xCB, 0x0A );
    FCML_A3264( "kshiftlw $0x0a,%k3,%k1", 0xC4, 0xE3, 0xF9, 0x32, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTLB(void) {
    FCML_I3264( "kshiftlb k1,k3,0ah", 0xC4, 0xE3, 0x79, 0x32, 0xCB, 0x0A );
    FCML_A3264( "kshiftlb $0x0a,%k3,%k1", 0xC4, 0xE3, 0x79, 0x32, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTLD(void) {
    FCML_I3264( "kshiftld k1,k3,0ah", 0xC4, 0xE3, 0x79, 0x33, 0xCB, 0x0A );
    FCML_A3264( "kshiftld $0x0a,%k3,%k1", 0xC4, 0xE3, 0x79, 0x33, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTLQ(void) {
    FCML_I3264( "kshiftlq k1,k3,0ah", 0xC4, 0xE3, 0xF9, 0x33, 0xCB, 0x0A );
    FCML_A3264( "kshiftlq $0x0a,%k3,%k1", 0xC4, 0xE3, 0xF9, 0x33, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTRW(void) {
    FCML_I3264( "kshiftrw k1,k3,0ah", 0xC4, 0xE3, 0xF9, 0x30, 0xCB, 0x0A );
    FCML_A3264( "kshiftrw $0x0a,%k3,%k1", 0xC4, 0xE3, 0xF9, 0x30, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTRB(void) {
    FCML_I3264( "kshiftrb k1,k3,0ah", 0xC4, 0xE3, 0x79, 0x30, 0xCB, 0x0A );
    FCML_A3264( "kshiftrb $0x0a,%k3,%k1", 0xC4, 0xE3, 0x79, 0x30, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTRD(void) {
    FCML_I3264( "kshiftrd k1,k3,0ah", 0xC4, 0xE3, 0x79, 0x31, 0xCB, 0x0A );
    FCML_A3264( "kshiftrd $0x0a,%k3,%k1", 0xC4, 0xE3, 0x79, 0x31, 0xCB, 0x0A );
}

void fcml_tf_instruction_KSHIFTRQ(void) {
    FCML_I3264( "kshiftrq k1,k3,0ah", 0xC4, 0xE3, 0xF9, 0x31, 0xCB, 0x0A );
    FCML_A3264( "kshiftrq $0x0a,%k3,%k1", 0xC4, 0xE3, 0xF9, 0x31, 0xCB, 0x0A );
}

void fcml_tf_instruction_KTESTW(void) {
    FCML_I3264( "ktestw k1,k3", 0xC5, 0xf8, 0x99, 0xCB );
    FCML_A3264( "ktestw %k3,%k1", 0xC5, 0xf8, 0x99, 0xCB );
}

void fcml_tf_instruction_KTESTB(void) {
    FCML_I3264( "ktestb k1,k3", 0xC5, 0xf9, 0x99, 0xCB );
    FCML_A3264( "ktestb %k3,%k1", 0xC5, 0xf9, 0x99, 0xCB );
}

void fcml_tf_instruction_KTESTD(void) {
    FCML_I3264( "ktestd k1,k3", 0xC4, 0xE1, 0xf9, 0x99, 0xCB );
    FCML_A3264( "ktestd %k3,%k1", 0xC4, 0xE1, 0xf9, 0x99, 0xCB );
}

void fcml_tf_instruction_KTESTQ(void) {
    FCML_I3264( "ktestq k1,k3", 0xC4, 0xE1, 0xf8, 0x99, 0xCB );
    FCML_A3264( "ktestq %k3,%k1", 0xC4, 0xE1, 0xf8, 0x99, 0xCB );
}

void fcml_tf_instruction_KXNORW(void) {
    FCML_I3264( "kxnorw k1,k2,k3", 0xC5, 0xEC, 0x46, 0xCB );
    FCML_A3264( "kxnorw %k3,%k2,%k1", 0xC5, 0xEC, 0x46, 0xCB );
}

void fcml_tf_instruction_KXNORB(void) {
    FCML_I3264( "kxnorb k1,k2,k3", 0xC5, 0xED, 0x46, 0xCB );
    FCML_A3264( "kxnorb %k3,%k2,%k1", 0xC5, 0xED, 0x46, 0xCB );
}

void fcml_tf_instruction_KXNORD(void) {
    FCML_I3264( "kxnord k1,k2,k3", 0xC4, 0xE1, 0xED, 0x46, 0xCB );
    FCML_A3264( "kxnord %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x46, 0xCB );
}

void fcml_tf_instruction_KXNORQ(void) {
    FCML_I3264( "kxnorq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x46, 0xCB );
    FCML_A3264( "kxnorq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x46, 0xCB );
}

void fcml_tf_instruction_KXORW(void) {
    FCML_I3264( "kxorw k1,k2,k3", 0xC5, 0xEC, 0x47, 0xCB );
    FCML_A3264( "kxorw %k3,%k2,%k1", 0xC5, 0xEC, 0x47, 0xCB );
}

void fcml_tf_instruction_KXORB(void) {
    FCML_I3264( "kxorb k1,k2,k3", 0xC5, 0xED, 0x47, 0xCB );
    FCML_A3264( "kxorb %k3,%k2,%k1", 0xC5, 0xED, 0x47, 0xCB );
}

void fcml_tf_instruction_KXORD(void) {
    FCML_I3264( "kxord k1,k2,k3", 0xC4, 0xE1, 0xED, 0x47, 0xCB );
    FCML_A3264( "kxord %k3,%k2,%k1", 0xC4, 0xE1, 0xED, 0x47, 0xCB );
}

void fcml_tf_instruction_KXORQ(void) {
    FCML_I3264( "kxorq k1,k2,k3", 0xC4, 0xE1, 0xEC, 0x47, 0xCB );
    FCML_A3264( "kxorq %k3,%k2,%k1", 0xC4, 0xE1, 0xEC, 0x47, 0xCB );
}

fcml_stf_test_case fctl_ti_instructions_k[] = {
    { "fcml_tf_instruction_KADDW", fcml_tf_instruction_KADDW },
    { "fcml_tf_instruction_KADDB", fcml_tf_instruction_KADDB },
    { "fcml_tf_instruction_KADDD", fcml_tf_instruction_KADDD },
    { "fcml_tf_instruction_KADDQ", fcml_tf_instruction_KADDQ },
    { "fcml_tf_instruction_KANDW", fcml_tf_instruction_KANDW },
    { "fcml_tf_instruction_KANDB", fcml_tf_instruction_KANDB },
    { "fcml_tf_instruction_KANDD", fcml_tf_instruction_KANDD },
    { "fcml_tf_instruction_KANDQ", fcml_tf_instruction_KANDQ },
    { "fcml_tf_instruction_KANDNW", fcml_tf_instruction_KANDNW },
    { "fcml_tf_instruction_KANDNB", fcml_tf_instruction_KANDNB },
    { "fcml_tf_instruction_KANDND", fcml_tf_instruction_KANDND },
    { "fcml_tf_instruction_KANDNQ", fcml_tf_instruction_KANDNQ },
    { "fcml_tf_instruction_KMOVB", fcml_tf_instruction_KMOVB },
    { "fcml_tf_instruction_KMOVW", fcml_tf_instruction_KMOVW },
    { "fcml_tf_instruction_KMOVD", fcml_tf_instruction_KMOVD },
    { "fcml_tf_instruction_KMOVQ", fcml_tf_instruction_KMOVQ },
    { "fcml_tf_instruction_KNOTB", fcml_tf_instruction_KNOTB },
    { "fcml_tf_instruction_KNOTW", fcml_tf_instruction_KNOTW },
    { "fcml_tf_instruction_KNOTD", fcml_tf_instruction_KNOTD },
    { "fcml_tf_instruction_KNOTQ", fcml_tf_instruction_KNOTQ },
    { "fcml_tf_instruction_KORB", fcml_tf_instruction_KORB },
    { "fcml_tf_instruction_KORW", fcml_tf_instruction_KORW },
    { "fcml_tf_instruction_KORD", fcml_tf_instruction_KORD },
    { "fcml_tf_instruction_KORQ", fcml_tf_instruction_KORQ },
    { "fcml_tf_instruction_KORTESTB", fcml_tf_instruction_KORTESTB },
    { "fcml_tf_instruction_KORTESTW", fcml_tf_instruction_KORTESTW },
    { "fcml_tf_instruction_KORTESTD", fcml_tf_instruction_KORTESTD },
    { "fcml_tf_instruction_KORTESTQ", fcml_tf_instruction_KORTESTQ },
    { "fcml_tf_instruction_KSHIFTLW", fcml_tf_instruction_KSHIFTLW },
    { "fcml_tf_instruction_KSHIFTLB", fcml_tf_instruction_KSHIFTLB },
    { "fcml_tf_instruction_KSHIFTLD", fcml_tf_instruction_KSHIFTLD },
    { "fcml_tf_instruction_KSHIFTLQ", fcml_tf_instruction_KSHIFTLQ },
    { "fcml_tf_instruction_KSHIFTRW", fcml_tf_instruction_KSHIFTRW },
    { "fcml_tf_instruction_KSHIFTRB", fcml_tf_instruction_KSHIFTRB },
    { "fcml_tf_instruction_KSHIFTRD", fcml_tf_instruction_KSHIFTRD },
    { "fcml_tf_instruction_KSHIFTRQ", fcml_tf_instruction_KSHIFTRQ },
    { "fcml_tf_instruction_KTESTB", fcml_tf_instruction_KTESTB },
    { "fcml_tf_instruction_KTESTW", fcml_tf_instruction_KTESTW },
    { "fcml_tf_instruction_KTESTD", fcml_tf_instruction_KTESTD },
    { "fcml_tf_instruction_KTESTQ", fcml_tf_instruction_KTESTQ },
    { "fcml_tf_instruction_KXNORW", fcml_tf_instruction_KXNORW },
    { "fcml_tf_instruction_KXNORB", fcml_tf_instruction_KXNORB },
    { "fcml_tf_instruction_KXNORD", fcml_tf_instruction_KXNORD },
    { "fcml_tf_instruction_KXNORQ", fcml_tf_instruction_KXNORQ },
    { "fcml_tf_instruction_KXORW", fcml_tf_instruction_KXORW },
    { "fcml_tf_instruction_KXORB", fcml_tf_instruction_KXORB },
    { "fcml_tf_instruction_KXORD", fcml_tf_instruction_KXORD },
    { "fcml_tf_instruction_KXORQ", fcml_tf_instruction_KXORQ },
    FCML_STF_NULL_TEST
};

fcml_stf_test_suite fctl_si_instructions_k = {
    "suite-fctl_ti_instructions_k", fcml_tf_instructions_k_suite_init,
    fcml_tf_instructions_k_suite_cleanup, fctl_ti_instructions_k
};


