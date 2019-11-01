/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2017 Slawomir Wojtasiak
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

/** @file fcml_instructions.h
 * Instruction codes and addressing modes/instruction forms.
 * @copyright Copyright (C) 2010-2017 Slawomir Wojtasiak. All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */

#ifndef FCML_INSTRUCTIONS_H_
#define FCML_INSTRUCTIONS_H_

/**
 * @defgroup INSTRUCTION_TYPES_GROUP Instructions types.
 * Instructions types.
 * @{
 */

#define    FCML_AMT_UNDEF      0x0000000000000000UL
/* Grouping. */
#define    FCML_AMT_SSEx       0x0000000000000001UL
#define    FCML_AMT_VEXx       0x0000000000000002UL
#define    FCML_AMT_SIMD       0x0000000000000004UL
/* CPUID. */
#define    FCML_AMT_GPI        0x0000000000000008UL
#define    FCML_AMT_FPU        0x0000000000000010UL
#define    FCML_AMT_MMX        0x0000000000000020UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE        0x0000000000000040UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE2       0x0000000000000080UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE3       0x0000000000000100UL | FCML_AMT_SSEx
#define    FCML_AMT_SSSE3      0x0000000000000200UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE41      0x0000000000000400UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE42      0x0000000000000800UL | FCML_AMT_SSEx
#define    FCML_AMT_SSE4A      0x0000000000001000UL | FCML_AMT_SSEx
#define    FCML_AMT_AVX        0x0000000000002000UL | FCML_AMT_VEXx
#define    FCML_AMT_AVX2       0x0000000000004000UL | FCML_AMT_VEXx
#define    FCML_AMT_AES        0x0000000000008000UL
#define    FCML_AMT_SYSTEM     0x0000000000010000UL
#define    FCML_AMT_3DNOW      0x0000000000020000UL | FCML_AMT_MMX
#define    FCML_AMT_TBM        0x0000000000040000UL | FCML_AMT_VEXx
#define    FCML_AMT_BMI1       0x0000000000080000UL
#define    FCML_AMT_BMI2       0x0000000000100000UL
#define    FCML_AMT_HLE        0x0000000000200000UL
#define    FCML_AMT_ADX        0x0000000000400000UL
#define    FCML_AMT_CLMUL      0x0000000000800000UL
#define    FCML_AMT_F16C       0x0000000001000000UL | FCML_AMT_VEXx
#define    FCML_AMT_RDRAND     0x0000000002000000UL
#define    FCML_AMT_RDSEED     0x0000000004000000UL
#define    FCML_AMT_PRFCHW     0x0000000008000000UL
#define    FCML_AMT_LWP        0x0000000010000000UL | FCML_AMT_SIMD
#define    FCML_AMT_SVM        0x0000000020000000UL
#define    FCML_AMT_FSGSBASE   0x0000000040000000UL
#define    FCML_AMT_FMA        0x0000000080000000UL | FCML_AMT_SIMD
#define    FCML_AMT_FMA4       0x0000000100000000UL | FCML_AMT_SIMD
#define    FCML_AMT_XOP        0x0000000200000000UL | FCML_AMT_SIMD
#define    FCML_AMT_EDX        0x0000000400000000UL
#define    FCML_AMT_ABM        0x0000000800000000UL
#define    FCML_AMT_VMX        0x0000001000000000UL
#define    FCML_AMT_SMX        0x0000002000000000UL
#define    FCML_AMT_POPCNT     0x0000004000000000UL
#define    FCML_AMT_RTM        0x0000008000000000UL
/* Control transfer instructions. */
#define    FCML_AMT_CTI        0x0000010000000000UL
#define    FCML_AMT_BRANCH     0x0000020000000000UL
/* End of control transfer instructions. */
#define    FCML_AMT_AVX512     0x0000040000000000UL
/* Shortcuts. */
#define    FCML_AMT_MMX_SIMD    FCML_AMT_MMX    | FCML_AMT_SIMD
#define    FCML_AMT_SSE_SIMD    FCML_AMT_SSE    | FCML_AMT_SIMD
#define    FCML_AMT_SSE2_SIMD   FCML_AMT_SSE2   | FCML_AMT_SIMD
#define    FCML_AMT_SSE3_SIMD   FCML_AMT_SSE3   | FCML_AMT_SIMD
#define    FCML_AMT_SSSE3_SIMD  FCML_AMT_SSSE3  | FCML_AMT_SIMD
#define    FCML_AMT_SSE41_SIMD  FCML_AMT_SSE41  | FCML_AMT_SIMD
#define    FCML_AMT_SSE42_SIMD  FCML_AMT_SSE42  | FCML_AMT_SIMD
#define    FCML_AMT_AVX_SIMD    FCML_AMT_AVX    | FCML_AMT_SIMD
#define    FCML_AMT_AVX2_SIMD   FCML_AMT_AVX2   | FCML_AMT_SIMD
#define    FCML_AMT_3DNOW_SIMD  FCML_AMT_3DNOW  | FCML_AMT_SIMD
#define    FCML_AMT_AVX512_SIMD FCML_AMT_AVX512 | FCML_AMT_SIMD

/** @} */

/** Instruction forms. */
enum fcml_en_instruction_addr_mode_codes {
    FCML_AM_UNKNOWN = 0,
    FCML_AM_NO_OPERANS,
    FCML_AM_IMM8,
    FCML_AM_IMMO,
    FCML_AM_ER8_IMM8,
    FCML_AM_R8_IMM8,
    FCML_AM_ERO_IMMO,
    FCML_AM_RM8_IMM8,
    FCML_AM_RMO_IMMO,
    FCML_AM_R0_IMM0,
    FCML_AM_RMO_IMM8,
    FCML_AM_RM8_R8,
    FCML_AM_R8_RM8,
    FCML_AM_R8_MOFF8,
    FCML_AM_MOFF8_R8,
    FCML_AM_R16_RM8,
    FCML_AM_RO_RM16,
    FCML_AM_RMO_RO,
    FCML_AM_RO_RMO,
    FCML_AM_RO_MOFFO,
    FCML_AM_RO_MO,
    FCML_AM_MOFFO_RO,
    FCML_AM_MO_RO,
    FCML_AM_RO_RM8,
    FCML_AM_RM_SR,
    FCML_AM_SR_RM,
    FCML_AM_R32_DR,
    FCML_AM_R64_DR,
    FCML_AM_DR_R32,
    FCML_AM_DR_R64,
    FCML_AM_R32_CR,
    FCML_AM_R64_CR,
    FCML_AM_CR_R32,
    FCML_AM_CR_R64,
    FCML_AM_RO_RMO_IMM8,
    FCML_AM_RO_RMO_IMMO,
    FCML_AM_R32A_RM32_R32B,
    FCML_AM_R64A_RM64_R64B,
    FCML_AM_R32_RM32,
    FCML_AM_R64_RM64,
    FCML_AM_R32_RM32_R32,
    FCML_AM_R64_RM64_R64,
    FCML_AM_REL16,
    FCML_AM_PTR16_O,
    FCML_AM_M16_O,
    FCML_AM_M8_M8,
    FCML_AM_MO_MO,
    FCML_AM_M8,
    FCML_AM_M16,
    FCML_AM_M32,
    FCML_AM_M64,
    FCML_AM_M80,
    FCML_AM_M128,
    FCML_AM_RX_RM32,
    FCML_AM_RX_RM64,
    FCML_AM_RX_RX_RM32,
    FCML_AM_RX_RX_RM64,
    FCML_AM_R32_RXM64,
    FCML_AM_R64_RXM64,
    FCML_AM_RM8,
    FCML_AM_RMO,
    FCML_AM_RO,
    FCML_AM_SRO,
    FCML_AM_SR_FSGSO,
    FCML_AM_ST0_ST,
    FCML_AM_ST_ST0,
    FCML_AM_ST,
    FCML_AM_M2BYTE,
    FCML_AM_AX,
    FCML_AM_R64_M128,
    FCML_AM_R32_M128,
    FCML_AM_RX_RX_I8_I8,
    FCML_AM_RX_RX,
    FCML_AM_REL8,
    FCML_AM_REL0
};

/**
 * @defgroup INSTRUCTION_GROUP Supported instructions codes.
 * Set of all supported instructions. Names are based on Intel syntax.
 * @{
 */

/** Instruction codes. */
typedef enum fcml_en_instruction {
    F_UNKNOWN,
    F_AAA,
    F_JCC,
    F_AAD,
    F_AAM,
    F_AAS,
    F_ADC,
    F_ADD,
    F_ADDPD,
    F_VADDPD,
    F_ADDPS,
    F_VADDPS,
    F_ADDSD,
    F_VADDSD,
    F_ADDSS,
    F_VADDSS,
    F_ADDSUBPD,
    F_VADDSUBPD,
    F_ADDSUBPS,
    F_VADDSUBPS,
    F_AESDEC,
    F_VAESDEC,
    F_AESDECLAST,
    F_VAESDECLAST,
    F_AESENC,
    F_VAESENC,
    F_AESENCLAST,
    F_VAESENCLAST,
    F_AESIMC,
    F_VAESIMC,
    F_AESKEYGENASSIST,
    F_VAESKEYGENASSIST,
    F_AND,
    F_ANDPD,
    F_VANDPD,
    F_ANDPS,
    F_VANDPS,
    F_ANDNPD,
    F_VANDNPD,
    F_ANDNPS,
    F_VANDNPS,
    F_ARPL,
    F_ANDN,
    F_ADCX,
    F_ADOX,
    F_BLENDPD,
    F_VBLENDPD,
    F_BLENDPS,
    F_VBLENDPS,
    F_BLENDVPD,
    F_VBLENDVPD,
    F_BLENDVPS,
    F_VBLENDVPS,
    F_BOUND,
    F_BSF,
    F_BSR,
    F_BSWAP,
    F_BT,
    F_BTC,
    F_BTR,
    F_BTS,
    F_BEXR,
    F_BLCFILL,
    F_BLCI,
    F_BLCIC,
    F_BLCMSK,
    F_BLCS,
    F_BLSFILL,
    F_BLSI,
    F_BLSIC,
    F_BLSMSK,
    F_BLSR,
    F_BZHI,
    F_CALL,
    F_CBW,
    F_CWDE = F_CBW,
    F_CDQE = F_CBW,
    F_CLC,
    F_CLD,
    F_CLFLUSH,
    F_CLI,
    F_CLGI,
    F_CLTS,
    F_CMC,
    F_CMOV,
    F_CMP,
    F_CMPPD,
    F_VCMPPD,
    F_CMPPS,
    F_VCMPPS,
    F_CMPS,
    F_CMPSD,
    F_VCMPSD,
    F_CMPSS,
    F_VCMPSS,
    F_CMPXCHG,
    F_CMPXCHGxB,
    F_CPUID,
    F_CRC32,
    F_CVTDQ2PD,
    F_VCVTDQ2PD,
    F_CVTDQ2PS,
    F_VCVTDQ2PS,
    F_CVTPD2DQ,
    F_VCVTPD2DQ,
    F_CVTPD2PI,
    F_CVTPD2PS,
    F_VCVTPD2PS,
    F_CVTPI2PD,
    F_CVTPI2PS,
    F_CVTPS2DQ,
    F_VCVTPS2DQ,
    F_CVTPS2PD,
    F_VCVTPS2PD,
    F_CVTPS2PI,
    F_CVTSD2SI,
    F_VCVTSD2SI,
    F_CVTSD2SS,
    F_VCVTSD2SS,
    F_CVTSI2SD,
    F_VCVTSI2SD,
    F_CVTSI2SS,
    F_VCVTSI2SS,
    F_CVTSS2SD,
    F_VCVTSS2SD,
    F_CVTSS2SI,
    F_VCVTSS2SI,
    F_CVTTPD2DQ,
    F_VCVTTPD2DQ,
    F_CVTTPD2PI,
    F_CVTTPS2DQ,
    F_VCVTTPS2DQ,
    F_CVTTPS2PI,
    F_CVTTSD2SI,
    F_VCVTTSD2SI,
    F_CVTTSS2SI,
    F_VCVTTSS2SI,
    F_CWD,
    F_CDQ = F_CWD,
    F_CQO = F_CWD,
    F_COMISD,
    F_VCOMISD,
    F_COMISS,
    F_VCOMISS,
    F_DAA,
    F_DAS,
    F_DEC,
    F_DIV,
    F_DIVPD,
    F_VDIVPD,
    F_DIVPS,
    F_VDIVPS,
    F_DIVSD,
    F_VDIVSD,
    F_DIVSS,
    F_VDIVSS,
    F_DPPD,
    F_VDPPD,
    F_DPPS,
    F_VDPPS,
    F_EMMS,
    F_ENTER,
    F_EXTRACTPS,
    F_VEXTRACTPS,
    F_EXTRQ,
    F_F2XM1,
    F_FABS,
    F_FADD,
    F_FIADD,
    F_FADDP,
    F_FBLD,
    F_FBSTP,
    F_FCHS,
    F_FCLEX,
    F_FNCLEX,
    F_FCMOVB,
    F_FCMOVE,
    F_FCMOVBE,
    F_FCMOVU,
    F_FCMOVNB,
    F_FCMOVNE,
    F_FCMOVNBE,
    F_FCMOVNU,
    F_FCOS,
    F_FCOM,
    F_FCOMP,
    F_FCOMPP,
    F_FCOMI,
    F_FCOMIP,
    F_FUCOMI,
    F_FUCOMIP,
    F_FDECSTP,
    F_FDIV,
    F_FDIVP,
    F_FIDIV,
    F_FDIVR,
    F_FDIVRP,
    F_FIDIVR,
    F_FFREE,
    F_FICOM,
    F_FICOMP,
    F_FILD,
    F_FINCSTP,
    F_FINIT,
    F_FNINIT,
    F_FIST,
    F_FISTP,
    F_FLD,
    F_FLD1,
    F_FLDL2T,
    F_FLDL2E,
    F_FLDPI,
    F_FLDLG2,
    F_FLDLN2,
    F_FLDZ,
    F_FLDCW,
    F_FLDENV,
    F_FMUL,
    F_FMULP,
    F_FIMUL,
    F_FNOP,
    F_FPATAN,
    F_FPREM,
    F_FPREM1,
    F_FPTAN,
    F_FRNDINT,
    F_FRSTOR,
    F_FSAVE,
    F_FNSAVE,
    F_FSCALE,
    F_FSIN,
    F_FSINCOS,
    F_FSQRT,
    F_FST,
    F_FSTP,
    F_FSTCW,
    F_FNSTCW,
    F_FSTENV,
    F_FNSTENV,
    F_FSTSW,
    F_FNSTSW,
    F_FSUB,
    F_FSUBP,
    F_FISUB,
    F_FSUBR,
    F_FSUBRP,
    F_FISUBR,
    F_FTST,
    F_FUCOM,
    F_FUCOMP,
    F_FUCOMPP,
    F_FXAM,
    F_FXCH,
    F_FXRSTOR,
    F_FXRSTOR64,
    F_FXSAVE,
    F_FXSAVE64,
    F_FXTRACT,
    F_FYL2X,
    F_FYL2XP1,
    F_FEMMS,
    F_FISTTP,
    F_GETSEC,
    F_HADDPD,
    F_VHADDPD,
    F_HADDPS,
    F_VHADDPS,
    F_HLT,
    F_HSUBPD,
    F_VHSUBPD,
    F_HSUBPS,
    F_VHSUBPS,
    F_INVEPT,
    F_INVVPID,
    F_IDIV,
    F_IMUL,
    F_IN,
    F_INC,
    F_INS,
    F_INSERTPS,
    F_VINSERTPS,
    F_VEXTRACTF128,
    F_VEXTRACTF32X4,
    F_VEXTRACTF64X2,
    F_VEXTRACTF32X8,
    F_VEXTRACTF64X4,
    F_VEXTRACTI32X4,
    F_VEXTRACTI64X2,
    F_VEXTRACTI32X8,
    F_VEXTRACTI64X4,
    F_VINSERTF128,
    F_VFIXUPIMMPD,
    F_VFIXUPIMMPS,
    F_VFIXUPIMMSD,
    F_VFIXUPIMMSS,
    F_INSERTQ,
    F_INT3,
    F_INT,
    F_INTO,
    F_INVD,
    F_INVLPG,
    F_INVLPGA,
    F_INVPCID,
    F_IRET,
    F_JCXZ,
    F_JECXZ = F_JCXZ,
    F_JRCXZ = F_JCXZ,
    F_JMP,
    F_KADDB,
    F_KADDD,
    F_KADDW,
    F_KADDQ,
    F_KANDB,
    F_KANDD,
    F_KANDW,
    F_KANDQ,
    F_KANDNB,
    F_KANDND,
    F_KANDNW,
    F_KANDNQ,
    F_KMOVB,
    F_KMOVW,
    F_KMOVD,
    F_KMOVQ,
    F_KNOTB,
    F_KNOTW,
    F_KNOTD,
    F_KNOTQ,
    F_KORB,
    F_KORW,
    F_KORD,
    F_KORQ,
    F_KORTESTB,
    F_KORTESTW,
    F_KORTESTD,
    F_KORTESTQ,
    F_KSHIFTLW,
    F_KSHIFTLB,
    F_KSHIFTLQ,
    F_KSHIFTLD,
    F_KSHIFTRW,
    F_KSHIFTRB,
    F_KSHIFTRQ,
    F_KSHIFTRD,
    F_KTESTB,
    F_KTESTW,
    F_KTESTD,
    F_KTESTQ,
    F_KXNORB,
    F_KXNORD,
    F_KXNORW,
    F_KXNORQ,
    F_KXORB,
    F_KXORD,
    F_KXORW,
    F_KXORQ,
    F_LAR,
    F_LAHF,
    F_LDDQU,
    F_VLDDQU,
    F_LDMXCSR,
    F_VLDMXCSR,
    F_LDS,
    F_LSS,
    F_LES,
    F_LFS,
    F_LGS,
    F_LEA,
    F_LEAVE,
    F_LFENCE,
    F_LLWPCB,
    F_LGDT,
    F_LIDT,
    F_LLDT,
    F_LMSW,
    F_LODS,
    F_LOOP,
    F_LOOPE,
    F_LOOPNE,
    F_LWPINS,
    F_LWPVAL,
    F_LSL,
    F_LTR,
    F_LZCNT,
    F_MASKMOVDQU,
    F_VMASKMOVDQU,
    F_MASKMOVQ,
    F_VMASKMOVPS,
    F_VMASKMOVPD,
    F_VPMASKMOVD,
    F_VPMASKMOV,
    F_VPMASKMOVQ,
    F_MAXPD,
    F_VMAXPD,
    F_MAXPS,
    F_VMAXPS,
    F_MAXSD,
    F_VMAXSD,
    F_MAXSS,
    F_VMAXSS,
    F_MFENCE,
    F_MINPD,
    F_VMINPD,
    F_MINPS,
    F_VMINPS,
    F_MINSD,
    F_VMINSD,
    F_MINSS,
    F_VMINSS,
    F_MONITOR,
    F_MOVAPD,
    F_VMOVAPD,
    F_MOVAPS,
    F_VMOVAPS,
    F_MOVBE,
    F_MOV,
    F_MOVD,
    F_VMOVD,
    F_MOVQ,
    F_VMOVQ,
    F_MOVDDUP,
    F_VMOVDDUP,
    F_MOVDQA,
    F_VMOVDQA,
    F_VMOVDQA32,
    F_VMOVDQA64,
    F_MOVDQU,
    F_VMOVDQU,
    F_VMOVDQU8,
    F_VMOVDQU16,
    F_VMOVDQU32,
    F_VMOVDQU64,
    F_MOVDQ2Q,
    F_MOVHLPS,
    F_VMOVHLPS,
    F_MOVHPD,
    F_VMOVHPD,
    F_MOVHPS,
    F_VMOVHPS,
    F_MOVLHPS,
    F_VMOVLHPS,
    F_MOVLPD,
    F_VMOVLPD,
    F_MOVLPS,
    F_VMOVLPS,
    F_MOVMSKPD,
    F_VMOVMSKPD,
    F_MOVMSKPS,
    F_VMOVMSKPS,
    F_MOVNTDQA,
    F_VMOVNTDQA,
    F_MOVNTDQ,
    F_VMOVNTDQ,
    F_MOVS,
    F_MOVNTI,
    F_MOVNTPD,
    F_VMOVNTPD,
    F_MOVNTPS,
    F_VMOVNTPS,
    F_MOVNTSD,
    F_MOVNTSS,
    F_MOVNTQ,
    F_MOVQ2DQ,
    F_MOVSD,
    F_VMOVSD,
    F_MOVSHDUP,
    F_VMOVSHDUP,
    F_MOVSLDUP,
    F_VMOVSLDUP,
    F_MOVSS,
    F_VMOVSS,
    F_MOVSX,
    F_MOVSXD,
    F_MOVUPD,
    F_VMOVUPD,
    F_MOVUPS,
    F_VMOVUPS,
    F_MOVZX,
    F_MPSADBW,
    F_VMPSADBW,
    F_MUL,
    F_MULPD,
    F_VMULPD,
    F_MULPS,
    F_VMULPS,
    F_MULSD,
    F_VMULSD,
    F_MULSS,
    F_VMULSS,
    F_MWAIT,
    F_NEG,
    F_NOP,
    F_NOT,
    F_OR,
    F_ORPD,
    F_VORPD,
    F_ORPS,
    F_VORPS,
    F_OUT,
    F_OUTS,
    F_PABSW,
    F_PABSB,
    F_PABSD,
    F_VPABSB,
    F_VPABSW,
    F_VPABSD,
    F_VPABSQ,
    F_VPACKSSWB,
    F_PACKSSWB,
    F_VPACKSSDW,
    F_PACKSSDW,
    F_PACKUSDW,
    F_VPACKUSDW,
    F_PACKUSWB,
    F_VPACKUSWB,
    F_VPADDW,
    F_PADDW,
    F_VPADDB,
    F_VPADDD,
    F_PADDB,
    F_PADDD,
    F_VPADDSW,
    F_PADDSB,
    F_PADDSW,
    F_VPADDSB,
    F_PADDUSW,
    F_PADDUSB,
    F_VPADDUSW,
    F_PADDQ,
    F_VPADDUSB,
    F_VPADDQ,
    F_POP,
    F_PUSH,
    F_POPA,
    F_POPAD,
    F_POPF,
    F_POPFQ,
    F_POPFD,
    F_PUSHA,
    F_PUSHF,
    F_PUSHAD,
    F_PUSHFQ,
    F_PUSHFD,
    F_PAVGUSB,
    F_PF2ID,
    F_PFACC,
    F_PFADD,
    F_PFCMPEQ,
    F_PFCMPGE,
    F_PFCMPGT,
    F_PFMAX,
    F_PFMIN,
    F_PFMUL,
    F_PFRCP,
    F_PFRCPIT1,
    F_PFRCPIT2,
    F_PFRSQIT1,
    F_PFRSQRT,
    F_PFSUB,
    F_PFSUBR,
    F_PI2FD,
    F_PMULHRW,
    F_PF2IW,
    F_PFNACC,
    F_PFPNACC,
    F_PI2FW,
    F_PSWAPD,
    F_PALIGNR,
    F_VPALIGNR,
    F_PAND,
    F_VPAND,
    F_VPANDD,
    F_VPANDQ,
    F_PANDN,
    F_VPANDN,
    F_VPANDND,
    F_VPANDNQ,
    F_PAUSE,
    F_PAVGW,
    F_PAVGB,
    F_VPAVGW,
    F_VPAVGB,
    F_PBLENDVB,
    F_VPBLENDVB,
    F_PBLENDW,
    F_VPBLENDW,
    F_VPBLENDD,
    F_PCLMULQDQ,
    F_VPCLMULQDQ,
    F_PCMPEQW,
    F_PCMPEQB,
    F_PCMPEQD,
    F_VPCMPEQD,
    F_VPCMPEQW,
    F_VPCMPEQB,
    F_PCMPEQQ,
    F_VPCMPEQQ,
    F_PCMPESTRI,
    F_VPCMPESTRI,
    F_PCMPESTRM,
    F_VPCMPESTRM,
    F_PCMPGTW,
    F_PCMPGTD,
    F_PCMPGTB,
    F_VPCMPGTW,
    F_VPCMPGTD,
    F_VPCMPGTB,
    F_PCMPGTQ,
    F_VPCMPGTQ,
    F_PCMPISTRI,
    F_VPCMPISTRI,
    F_PCMPISTRM,
    F_VPCMPISTRM,
    F_VPEXTRB,
    F_VPEXTRQ,
    F_PEXTRQ,
    F_PEXTRB,
    F_PEXTRD,
    F_VPEXTRD,
    F_PEXTRW,
    F_VPEXTRW,
    F_VPHADDW,
    F_VPHADDD,
    F_PHADDD,
    F_PHADDW,
    F_PHADDSW,
    F_VPHADDSW,
    F_PHMINPOSUW,
    F_VPHMINPOSUW,
    F_PHSUBD,
    F_PHSUBW,
    F_VPHSUBD,
    F_VPHSUBW,
    F_PHSUBSW,
    F_VPHSUBSW,
    F_PINSRD,
    F_VPINSRQ,
    F_PINSRQ,
    F_PINSRB,
    F_VPINSRD,
    F_VPINSRB,
    F_PINSRW,
    F_VPINSRW,
    F_PMADDUBSW,
    F_VPMADDUBSW,
    F_PMADDWD,
    F_VPMADDWD,
    F_PMAXSB,
    F_VPMAXSB,
    F_PMAXSD,
    F_VPMAXSD,
    F_VPMAXSQ,
    F_PMAXSW,
    F_VPMAXSW,
    F_PMAXUB,
    F_VPMAXUB,
    F_PMAXUD,
    F_VPMAXUD,
    F_VPMAXUQ,
    F_PMAXUW,
    F_VPMAXUW,
    F_PMINSB,
    F_VPMINSB,
    F_PMINSD,
    F_VPMINSD,
    F_VPMINSQ,
    F_PMINSW,
    F_VPMINSW,
    F_PMINUW,
    F_VPMINUW,
    F_PMINUB,
    F_VPMINUB,
    F_PMINUD,
    F_VPMINUD,
    F_VPMINUQ,
    F_PMOVMSKB,
    F_VPMOVMSKB,
    F_VPMOVSXBQ,
    F_PMOVSXBW,
    F_PMOVSXWQ,
    F_VPMOVSXWQ,
    F_PMOVSXWD,
    F_PMOVSXBD,
    F_VPMOVSXDQ,
    F_VPMOVSXWD,
    F_PMOVSXBQ,
    F_VPMOVSXBW,
    F_PMOVSXDQ,
    F_VPMOVSXBD,
    F_PMOVZXWD,
    F_PMOVZXDQ,
    F_VPMOVZXDQ,
    F_PMOVZXWQ,
    F_VPMOVZXBQ,
    F_PMOVZXBQ,
    F_VPMOVZXWD,
    F_VPMOVZXBD,
    F_VPMOVZXWQ,
    F_PMOVZXBD,
    F_VPMOVZXBW,
    F_PMOVZXBW,
    F_PMULDQ,
    F_PMULHRSW,
    F_PMULHUW,
    F_VPMULDQ,
    F_VPMULHRSW,
    F_VPMULHUW,
    F_PMULHW,
    F_VPMULHW,
    F_PMULUDQ,
    F_VPMULUDQ,
    F_PMULLW,
    F_PMULLD,
    F_VPMULLD,
    F_VPMULLQ,
    F_VPMULLW,
    F_POPCNT,
    F_POR,
    F_VPOR,
    F_VPORD,
    F_VPORQ,
    F_PREFETCHT2,
    F_PREFETCHW,
    F_PREFETCHT1,
    F_PREFETCHNTA,
    F_PREFETCHT0,
    F_PREFETCHWT1,
    F_PSADBW,
    F_VPSADBW,
    F_PSHUFB,
    F_PSHUFD,
    F_PSHUFHW,
    F_VPSHUFD,
    F_VPSHUFB,
    F_PSHUFLW,
    F_PSHUFW,
    F_VPSHUFLW,
    F_VPSHUFHW,
    F_VPSIGNB,
    F_VPSIGND,
    F_PSIGNW,
    F_PSIGNB,
    F_VPSIGNW,
    F_PSIGND,
    F_PSLLDQ,
    F_VPSLLDQ,
    F_PSLLQ,
    F_PSLLD,
    F_VPSLLW,
    F_VPSLLQ,
    F_PSLLW,
    F_VPSLLD,
    F_VPSRAW,
    F_PSRAD,
    F_PSRAW,
    F_VPSRAD,
    F_VPSRAQ,
    F_PSRLDQ,
    F_VPSRLDQ,
    F_VPSRLQ,
    F_PSRLQ,
    F_PSRLD,
    F_PSRLW,
    F_VPSRLD,
    F_VPSRLW,
    F_VPSUBD,
    F_PSUBD,
    F_PSUBW,
    F_VPSUBB,
    F_VPSUBQ,
    F_PSUBB,
    F_VPSUBW,
    F_PSUBQ,
    F_PSUBSB,
    F_VPSUBSW,
    F_VPSUBSB,
    F_PSUBSW,
    F_VPSUBUSW,
    F_VPSUBUSB,
    F_PSUBUSB,
    F_PSUBUSW,
    F_VPTEST,
    F_PTEST,
    F_PUNPCKLBW,
    F_PUNPCKLQDQ,
    F_VPUNPCKLWD,
    F_VPUNPCKLQDQ,
    F_VPUNPCKLBW,
    F_PUNPCKLWD,
    F_PUNPCKLDQ,
    F_VPUNPCKLDQ,
    F_VPUNPCKHWD,
    F_PUNPCKHDQ,
    F_PUNPCKHWD,
    F_PUNPCKHQDQ,
    F_VPUNPCKHQDQ,
    F_VPUNPCKHBW,
    F_PUNPCKHBW,
    F_VPUNPCKHDQ,
    F_PXOR,
    F_VPXOR,
    F_VPXORD,
    F_VPXORQ,
    F_PREFETCH,
    F_RCL,
    F_RCR,
    F_ROL,
    F_ROR,
    F_RET,
    F_RETF,
    F_RCPPS,
    F_VRCPPS,
    F_RCPSS,
    F_VRCPSS,
    F_RDFSBASE,
    F_RDGSBASE,
    F_RDRAND,
    F_RDTSCP,
    F_RDTSC,
    F_RDPMC,
    F_RDMSR,
    F_ROUNDPD,
    F_VROUNDPD,
    F_ROUNDPS,
    F_VROUNDPS,
    F_ROUNDSD,
    F_VROUNDSD,
    F_ROUNDSS,
    F_VROUNDSS,
    F_RSM,
    F_RSQRTPS,
    F_VRSQRTPS,
    F_RSQRTSS,
    F_VRSQRTSS,
    F_SAHF,
    F_SAR,
    F_SAL,
    F_SHL = F_SAL,
    F_SHR,
    F_SBB,
    F_SCAS,
    F_SET,
    F_STOS,
    F_SUB,
    F_SFENCE,
    F_SGDT,
    F_SHLD,
    F_SHRD,
    F_SKINIT,
    F_SLWPCB,
    F_SHUFPD,
    F_VSHUFPD,
    F_SHUFPS,
    F_VSHUFPS,
    F_SIDT,
    F_SLDT,
    F_SMSW,
    F_SQRTPD,
    F_VSQRTPD,
    F_SQRTPS,
    F_VSQRTPS,
    F_SQRTSD,
    F_VSQRTSD,
    F_SQRTSS,
    F_VSQRTSS,
    F_STC,
    F_STD,
    F_STGI,
    F_STI,
    F_STMXCSR,
    F_VSTMXCSR,
    F_STR,
    F_SUBPD,
    F_VSUBPD,
    F_SUBPS,
    F_VSUBPS,
    F_SUBSD,
    F_VSUBSD,
    F_SUBSS,
    F_VSUBSS,
    F_SWAPGS,
    F_SYSCALL,
    F_SYSENTER,
    F_SYSEXIT,
    F_SYSRET,
    F_TEST,
    F_T1MSKC,
    F_UCOMISD,
    F_VUCOMISD,
    F_UCOMISS,
    F_VUCOMISS,
    F_UD2,
    F_UNPCKHPD,
    F_VUNPCKHPD,
    F_UNPCKHPS,
    F_VUNPCKHPS,
    F_UNPCKLPD,
    F_VUNPCKLPD,
    F_UNPCKLPS,
    F_VUNPCKLPS,
    F_VMLOAD,
    F_VMRUN,
    F_VMSAVE,
    F_VFRCZPD,
    F_VFRCZPS,
    F_VFRCZSD,
    F_VFRCZSS,
    F_VPCMOV,
    F_VPERMIL2PD,
    F_VPERMIL2PS,
    F_VPHADDBD,
    F_VPHADDBW,
    F_VPHADDBQ,
    F_VPHADDDQ,
    F_VPHADDUBD,
    F_VPHADDUBQ,
    F_VPHADDUBW,
    F_VPHADDUDQ,
    F_VPHADDUWD,
    F_VPHADDUWQ,
    F_VPHADDWD,
    F_VPHADDWQ,
    F_VPHSUBBW,
    F_VPHSUBDQ,
    F_VPHSUBWD,
    F_VPMACSDD,
    F_VPMACSDQH,
    F_VPMACSDQL,
    F_VPMACSSDD,
    F_VPMACSSDQH,
    F_VPMACSSDQL,
    F_VPMACSSWD,
    F_VPMACSSWW,
    F_VPMACSWD,
    F_VPMACSWW,
    F_VPMADCSSWD,
    F_VPMADCSWD,
    F_VPPERM,
    F_VPROTD,
    F_VPROTB,
    F_VPROTQ,
    F_VPROTW,
    F_VPSHAB,
    F_VPSHAD,
    F_VPSHAQ,
    F_VPSHAW,
    F_VPSHLB,
    F_VPSHLD,
    F_VPSHLQ,
    F_VPSHLW,
    F_VFMADD213PD,
    F_VFMADDPD,
    F_VFMADD132PD,
    F_VFMADD231PD,
    F_VFMADDPS,
    F_VFMADD231PS,
    F_VFMADD132PS,
    F_VFMADD213PS,
    F_VFMADD132SD,
    F_VFMADD213SD,
    F_VFMADDSD,
    F_VFMADD231SD,
    F_VFMADD132SS,
    F_VFMADD213SS,
    F_VFMADDSS,
    F_VFMADD231SS,
    F_VFMADDSUB132PD,
    F_VFMADDSUB213PD,
    F_VFMADDSUBPD,
    F_VFMADDSUB231PD,
    F_VFMADDSUB231PS,
    F_VFMADDSUBPS,
    F_VFMADDSUB132PS,
    F_VFMADDSUB213PS,
    F_VFMSUBADDPD,
    F_VFMSUBADD213PD,
    F_VFMSUBADD132PD,
    F_VFMSUBADD231PD,
    F_VFMSUBADDPS,
    F_VFMSUBADD213PS,
    F_VFMSUBADD132PS,
    F_VFMSUBADD231PS,
    F_VFMSUB213PD,
    F_VFMSUBPD,
    F_VFMSUB132PD,
    F_VFMSUB231PD,
    F_VFMSUB213PS,
    F_VFMSUBPS,
    F_VFMSUB132PS,
    F_VFMSUB231PS,
    F_VFMSUBSD,
    F_VFMSUB231SD,
    F_VFMSUB132SD,
    F_VFMSUB213SD,
    F_VFMSUB231SS,
    F_VFMSUB213SS,
    F_VFMSUB132SS,
    F_VFMSUBSS,
    F_VFNMADD231PD,
    F_VFNMADDPD,
    F_VFNMADD132PD,
    F_VFNMADD213PD,
    F_VFNMADD231PS,
    F_VFNMADD132PS,
    F_VFNMADD213PS,
    F_VFNMADDPS,
    F_VFNMADD213SD,
    F_VFNMADDSD,
    F_VFNMADD231SD,
    F_VFNMADD132SD,
    F_VFNMADD213SS,
    F_VFNMADDSS,
    F_VFNMADD231SS,
    F_VFNMADD132SS,
    F_VFNMSUB132PD,
    F_VFNMSUB213PD,
    F_VFNMSUB231PD,
    F_VFNMSUBPD,
    F_VFNMSUBPS,
    F_VFNMSUB213PS,
    F_VFNMSUB132PS,
    F_VFNMSUB231PS,
    F_VFNMSUBSD,
    F_VFNMSUB231SD,
    F_VFNMSUB213SD,
    F_VFNMSUB132SD,
    F_VFNMSUBSS,
    F_VFNMSUB132SS,
    F_VFNMSUB213SS,
    F_VFNMSUB231SS,
    F_VFPCLASSPD,
    F_VFPCLASSPS,
    F_VFPCLASSSD,
    F_VFPCLASSSS,
    F_BEXTR,
    F_VPBROADCASTW,
    F_VPBROADCASTB,
    F_VPBROADCASTD,
    F_VPBROADCASTQ,
    F_VBROADCASTI32X2,
    F_VBROADCASTI32X4,
    F_VBROADCASTI64X2,
    F_VBROADCASTI32X8,
    F_VBROADCASTI64X4,
    F_VPBROADCASTMB2Q,
    F_VPBROADCASTMW2D,
    F_VPCMPB,
    F_VPCMPUB,
    F_VPCMPW,
    F_VPCMPUW,
    F_VPCMPD,
    F_VPCMPUD,
    F_VPCMPQ,
    F_VPCMPUQ,
    F_VCOMPRESSPD,
    F_VCOMPRESSPS,
    F_VPCOMPRESSD,
    F_VPCOMPRESSQ,
    F_VCVTPD2QQ,
    F_VCVTTPS2UQQ,
    F_VCVTTPS2QQ,
    F_VCVTPD2UDQ,
    F_VCVTTPD2UQQ,
    F_VCVTTPS2UDQ,
    F_VMPTRLD,
    F_VCVTPD2UQQ,
    F_VMPTRST,
    F_VMCLEAR,
    F_VMREAD,
    F_VMWRITE,
    F_VMLAUNCH,
    F_VMRESUME,
    F_VMXOFF,
    F_VMXON,
    F_VMCALL,
    F_VMFUNC,
    F_VALIGND,
    F_VALIGNQ,
    F_VBLENDMPD,
    F_VBLENDMPS,
    F_VBROADCASTSD,
    F_VBROADCASTSS,
    F_VBROADCASTI128,
    F_VBROADCASTF128,
    F_VBROADCASTF32X2,
    F_VBROADCASTF32X4,
    F_VBROADCASTF32X8,
    F_VBROADCASTF64X2,
    F_VBROADCASTF64X4,
    F_VCVTPH2PS,
    F_VCVTPS2PH,
    F_VCVTPS2QQ,
    F_VCVTPS2UDQ,
    F_VCVTPS2UQQ,
    F_VCVTQQ2PD,
    F_VCVTQQ2PS,
    F_VCVTSD2USI,
    F_VCVTSS2USI,
    F_VCVTTSD2USI,
    F_VCVTTSS2USI,
    F_VCVTTPD2QQ,
    F_VCVTUDQ2PS,
    F_VCVTUQQ2PD,
    F_VCVTUSI2SD,
    F_VCVTUSI2SS,
    F_VCVTUQQ2PS,
    F_VCVTUDQ2PD,
    F_VCVTTPD2UDQ,
    F_VDBPSADBW,
    F_VEXPANDPD,
    F_VEXPANDPS,
    F_VERR,
    F_VERW,
    F_VMMCALL,
    F_VPERMILPD,
    F_VPERMILPS,
    F_VPERM2F128,
    F_VPERM2I128,
    F_VPERMI2W,
    F_VPERMI2D,
    F_VPERMI2Q,
    F_VPERMI2PS,
    F_VPERMI2PD,
    F_VPERMT2B,
    F_VPERMT2W,
    F_VPERMT2D,
    F_VPERMT2Q,
    F_VPERMT2PS,
    F_VPERMT2PD,
    F_VPEXPANDD,
    F_VPEXPANDQ,
    F_VPLZCNTD,
    F_VPLZCNTQ,
    F_VPMOVB2M,
    F_VPMOVW2M,
    F_VPMOVD2M,
    F_VPMOVQ2M,
    F_VPMOVM2B,
    F_VPMOVM2W,
    F_VPMOVM2D,
    F_VPMOVM2Q,
    F_VPMOVDB,
    F_VPMOVSDB,
    F_VPMOVUSDB,
    F_VPMOVDW,
    F_VPMOVSDW,
    F_VPMOVUSDW,
    F_VPMOVQB,
    F_VPMOVSQB,
    F_VPMOVUSQB,
    F_VPMOVQD,
    F_VPMOVSQD,
    F_VPMOVUSQD,
    F_VPMOVQW,
    F_VPMOVSQW,
    F_VPMOVUSQW,
    F_VPMOVWB,
    F_VPMOVSWB,
    F_VPMOVUSWB,
    F_VPMULTISHIFTQB,
    F_VPROLVD,
    F_VPROLVQ,
    F_VPROLD,
    F_VPROLQ,
    F_VPRORVD,
    F_VPRORVQ,
    F_VPRORD,
    F_VPRORQ,
    F_VPSCATTERDD,
    F_VPSCATTERDQ,
    F_VPSCATTERQD,
    F_VPSCATTERQQ,
    F_VPSLLVW,
    F_VPSLLVD,
    F_VPSLLVQ,
    F_VPMADD52HUQ,
    F_VPMADD52LUQ,
    F_VEXTRACTI128,
    F_VINSERTI128,
    F_VPSRAVW,
    F_VPSRAVD,
    F_VPSRAVQ,
    F_VPERMD,
    F_VPERMW,
    F_VPERMI2B,
    F_VPERMB,
    F_VPSRLVW,
    F_VPSRLVD,
    F_VPSRLVQ,
    F_VPTERNLOGD,
    F_VPTERNLOGQ,
    F_VPTESTMB,
    F_VPTESTMW,
    F_VPTESTMD,
    F_VPTESTMQ,
    F_VPTESTNMB,
    F_VPTESTNMW,
    F_VPTESTNMD,
    F_VPTESTNMQ,
    F_VRANGEPD,
    F_VRANGEPS,
    F_VRANGESD,
    F_VRANGESS,
    F_VRCP14PD,
    F_VRCP14PS,
    F_VRCP14SD,
    F_VRCP14SS,
    F_VREDUCEPD,
    F_VREDUCEPS,
    F_VREDUCESD,
    F_VREDUCESS,
    F_VRNDSCALEPD,
    F_VRNDSCALEPS,
    F_VRNDSCALESD,
    F_VRNDSCALESS,
    F_VRSQRT14PD,
    F_VRSQRT14PS,
    F_VRSQRT14SD,
    F_VRSQRT14SS,
    F_VSCALEFPD,
    F_VSCALEFPS,
    F_VSCALEFSD,
    F_VSCALEFSS,
    F_VSCATTERDPS,
    F_VSCATTERDPD,
    F_VSCATTERQPS,
    F_VSCATTERQPD,
    F_VSHUFF32X4,
    F_VSHUFF64X2,
    F_VSHUFI32X4,
    F_VSHUFI64X2,
    F_VPERMPD,
    F_VPERMQ,
    F_VPERMPS,
    F_VTESTPS,
    F_VTESTPD,
    F_VGATHERDPD,
    F_VGATHERQPD,
    F_VGATHERDPS,
    F_VGATHERQPS,
    F_VPGATHERDD,
    F_VPGATHERQD,
    F_VPGATHERDQ,
    F_VPGATHERQQ,
    F_VGETEXPPD,
    F_VGETEXPPS,
    F_VGETEXPSD,
    F_VGETEXPSS,
    F_VGETMANTPD,
    F_VGETMANTPS,
    F_VGETMANTSD,
    F_VGETMANTSS,
    F_VINSERTF32X4,
    F_VINSERTF64X2,
    F_VINSERTF32X8,
    F_VINSERTF64X4,
    F_VINSERTI32X4,
    F_VINSERTI64X2,
    F_VINSERTI32X8,
    F_VINSERTI64X4,
    F_VPBLENDMB,
    F_VPBLENDMW,
    F_VPBLENDMD,
    F_VPBLENDMQ,
    F_VZEROALL,
    F_VZEROUPPER,
    F_VPCOMB,
    F_VPCOMW,
    F_VPCOMD,
    F_VPCOMQ,
    F_VPCOMUB,
    F_VPCOMUW,
    F_VPCOMUD,
    F_VPCOMUQ,
    F_WAIT,
    F_FWAIT = F_WAIT,
    F_WBINVD,
    F_WRFSBASE,
    F_WRGSBASE,
    F_WRMSR,
    F_XLAT,
    F_XOR,
    F_XADD,
    F_XCHG,
    F_XGETBV,
    F_XORPD,
    F_VXORPD,
    F_XORPS,
    F_VXORPS,
    F_XRSTOR,
    F_XRSTOR64,
    F_XSAVE,
    F_XSAVE64,
    F_XSAVEOPT,
    F_XSAVEOPT64,
    F_XSETBV,
    F_MULX,
    F_PDEP,
    F_PEXT,
    F_RORX,
    F_SHLX,
    F_SHRX,
    F_SARX,
    F_TZCNT,
    F_TZMSK,
    F_XABORT,
    F_XBEGIN,
    F_XEND,
    F_XTEST,
    F_RDSEED,
    F_CLAC,
    F_STAC,
    F_V4FMADDPS,
    F_V4FNMADDPS,
    F_V4FMADDSS,
    F_V4FNMADDSS,
    F_VEXP2PD,
    F_VEXP2PS,
    F_VGATHERPF0DPS,
    F_VGATHERPF0QPS,
    F_VGATHERPF0DPD,
    F_VGATHERPF0QPD,
    F_VGATHERPF1DPS,
    F_VGATHERPF1QPS,
    F_VGATHERPF1DPD,
    F_VGATHERPF1QPD,
    F_VP4DPWSSDS,
    F_VP4DPWSSD,
    F_VRCP28PD,
    F_VRCP28SD,
    F_VRCP28PS,
    F_VRCP28SS
} fcml_en_instruction;

/** @} */

/**
 * @defgroup PSEUDO_OPERATIONS_GROUP Supported pseudo operations.
 * @{
 */

/** Pseudo operations. */
typedef enum fcml_en_pseudo_operations {
    /** Set if there is no pseudo operation. */
    FP_NO_PSEUDO_OP,
    /** db / .byte */
    FP_DB
} fcml_en_pseudo_operations;

/** @} */

#endif /* FCML_INSTRUCTIONS_H_ */
