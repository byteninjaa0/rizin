// SPDX-FileCopyrightText: 2015-2018 oddcoder <ahmedsoliman@oddcoder.com>
// SPDX-FileCopyrightText: 2015-2018 thestr4ng3r <info@florianmaerkl.de>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef PIC_PIC18_H
#define PIC_PIC18_H

#include <rz_asm.h>
#include "pic.h"

static inline bool is_pic18(const char *x) {
	return RZ_STR_EQ(x, "highend") ||
		RZ_STR_EQ(x, "pic") ||
		RZ_STR_EQ(x, "pic18");
}

typedef enum {
	PIC18_OPCODE_ADDLW,
	PIC18_OPCODE_ADDWF,
	PIC18_OPCODE_ADDWFC,
	PIC18_OPCODE_ANDWF,
	PIC18_OPCODE_ANDLW,

	PIC18_OPCODE_BCF,
	PIC18_OPCODE_BSF,
	PIC18_OPCODE_BTG,
	PIC18_OPCODE_BTFSC,
	PIC18_OPCODE_BTFSS,
	PIC18_OPCODE_BNN,
	PIC18_OPCODE_BN,
	PIC18_OPCODE_BNOV,
	PIC18_OPCODE_BOV,
	PIC18_OPCODE_BNC,
	PIC18_OPCODE_BC,
	PIC18_OPCODE_BNZ,
	PIC18_OPCODE_BZ,
	PIC18_OPCODE_BRA,

	PIC18_OPCODE_COMF,
	PIC18_OPCODE_CALL,
	PIC18_OPCODE_CLRWDT,
	PIC18_OPCODE_CLRF,
	PIC18_OPCODE_CPFSGT,
	PIC18_OPCODE_CPFSEQ,
	PIC18_OPCODE_CPFSLT,

	PIC18_OPCODE_DAW,
	PIC18_OPCODE_DECF,
	PIC18_OPCODE_DECFSZ,
	PIC18_OPCODE_DCFSNZ,

	PIC18_OPCODE_GOTO,

	PIC18_OPCODE_IORWF,
	PIC18_OPCODE_INFSNZ,
	PIC18_OPCODE_INCF,
	PIC18_OPCODE_INCFSZ,
	PIC18_OPCODE_IORLW,

	PIC18_OPCODE_LFSR,

	PIC18_OPCODE_MOVF,
	PIC18_OPCODE_MOVWF,
	PIC18_OPCODE_MULWF,
	PIC18_OPCODE_MOVLB,
	PIC18_OPCODE_MOVFF,
	PIC18_OPCODE_MOVLW,
	PIC18_OPCODE_MULLW,

	PIC18_OPCODE_NOP,
	PIC18_OPCODE_NEGF,

	PIC18_OPCODE_POP,
	PIC18_OPCODE_PUSH,

	PIC18_OPCODE_RETURN,
	PIC18_OPCODE_RETFIE,
	PIC18_OPCODE_RLNCF,
	PIC18_OPCODE_RRNCF,
	PIC18_OPCODE_RLCF,
	PIC18_OPCODE_RRCF,
	PIC18_OPCODE_RCALL,
	PIC18_OPCODE_RESET,
	PIC18_OPCODE_RETLW,

	PIC18_OPCODE_SLEEP,
	PIC18_OPCODE_SETF,
	PIC18_OPCODE_SUBWF,
	PIC18_OPCODE_SUBWFB,
	PIC18_OPCODE_SUBFWB,
	PIC18_OPCODE_SWAPF,
	PIC18_OPCODE_SUBLW,

	PIC18_OPCODE_TBLRDs,
	PIC18_OPCODE_TBLRDis,
	PIC18_OPCODE_TBLRDsd,
	PIC18_OPCODE_TBLRDsi,
	PIC18_OPCODE_TBLWTMs,
	PIC18_OPCODE_TBLWTis,
	PIC18_OPCODE_TBLWTMsd,
	PIC18_OPCODE_TBLWTMsi,
	PIC18_OPCODE_TSTFSZ,

	PIC18_OPCODE_XORWF,
	PIC18_OPCODE_XORLW,

	PIC18_OPCODE_INVALID
} Pic18Opcode;

typedef enum {
	NO_ARG,
	FDA_T,
	SD_T,
	FBA_T,
	K4_T,
	K8_T,
	K20_T,
	K20S_T,
	S_T,
	N8_T,
	N11_T,
	FA_T,
	FK_T,
} Pic18ArgsKind;

typedef struct {
	ut64 addr;
	Pic18Opcode code;
	const char *mnemonic;
	char operands[32];
	ut8 size;
	Pic18ArgsKind args_kind;
	struct {
		ut32 k : 20;
		ut16 n : 11;
		ut16 d;
		ut16 s;
		ut8 f;
		ut8 a : 1;
		ut8 b : 3;
	};
} Pic18Op;

const char *pic18_regname(size_t index);
const char *pic18_regname_extra(size_t index);
ut8 pic18_status(const char *name);
ut8 pic18_rcon(const char *name);
ut8 pic18_intcon(const char *name);
bool pic18_disasm_op(Pic18Op *op, ut64 addr, const ut8 *buff, ut64 len);
int pic18_disassemble(RzAsm *a, RzAsmOp *asm_op, const ut8 *b, int l);

int pic18_op(RzAnalysis *analysis, RzAnalysisOp *aop, ut64 addr,
	const ut8 *buf, int len, RzAnalysisOpMask mask);
char *pic18_get_reg_profile(RzAnalysis *esil);
RzAnalysisILConfig *pic18_il_config(RZ_NONNULL RzAnalysis *analysis);

#endif // PIC_PIC18_H
