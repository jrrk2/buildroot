/* Definitions of target machine for GNU compiler.  RISC-V RV32 version.
   Copyright (C) 1992 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 1, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */


/* Use musl CRT files instead of traditional crt0.o.  */
#define STARTFILE_SPEC "crt1.o%s crti.o%s"
#define ENDFILE_SPEC "crtn.o%s"

/* Set the dynamic linker to musl's.  */
#define LINK_SPEC "-dynamic-linker /lib/ld-musl-riscv32.so.1"

/* Link -lc (musl) and use libgcc.a instead of gnulib for the runtime lib.
   The driver hardcodes "gnulib%s" in the link spec, so we also install
   a gnulib symlink → libgcc.a.  But -lc must come before -lgcc so that
   libgcc's __muldi3 etc. can resolve libc references.  */
#define LIB_SPEC "-lc"

/* Names to predefine in the preprocessor for this target machine.  */

#define CPP_PREDEFINES "-Driscv -Driscv32 -Dunix"

/* Print subsidiary information on the compiler version in use.  */

#define TARGET_VERSION fprintf (stderr, " (riscv32)");

/* Run-time compilation parameters selecting different hardware subsets.  */

extern int target_flags;

/* Nonzero if we should generate code to use the FPU.  */
#define TARGET_FPU (target_flags & 1)

/* Nonzero if we should generate code for hard float (D extension).  */
#define TARGET_HARD_FLOAT_D (target_flags & 2)

#define TARGET_SWITCHES  \
  { {"hard-float", 3},		\
    {"soft-float", -3},		\
    { "", TARGET_DEFAULT}}

#define TARGET_DEFAULT 3


/* target machine storage layout */

/* RV32 is little-endian.  */
/* #define BITS_BIG_ENDIAN */
/* #define BYTES_BIG_ENDIAN */
/* #define WORDS_BIG_ENDIAN */

/* Little-endian: least significant word first.  */
#define MOST_SIGNIFICANT_WORD 1
#define LEAST_SIGNIFICANT_WORD 0

/* Number of bits in an addressible storage unit.  */
#define BITS_PER_UNIT 8

/* Width in bits of a "word", which is the contents of a machine register.  */
#define BITS_PER_WORD 32

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD 4

/* Width in bits of a pointer.  */
#define POINTER_SIZE 32

/* Allocation boundary (in *bits*) for storing pointers in memory.  */
#define POINTER_BOUNDARY 32

/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY 32

/* Boundary (in *bits*) on which stack pointer should be aligned.  */
#define STACK_BOUNDARY 64

/* Allocation boundary (in *bits*) for the code of a function.  */
#define FUNCTION_BOUNDARY 32

/* Alignment of field after `int : 0' in a structure.  */
#define EMPTY_FIELD_BOUNDARY 32

/* Every structure's size must be a multiple of this.  */
#define STRUCTURE_SIZE_BOUNDARY 8

/* A bitfield declared as `int' forces `int' alignment for the struct.  */
#define PCC_BITFIELD_TYPE_MATTERS 1

/* No data type wants to be aligned rounder than this.  */
#define BIGGEST_ALIGNMENT 64

/* Define this if move instructions will actually fail to work
   when given unaligned data.  */
#define STRICT_ALIGNMENT

/* When a prototype says `char' or `short', really pass an `int'.  */
#define PROMOTE_PROTOTYPES


/* Standard register usage.  */

/* Number of actual hardware registers.
   The hardware registers are assigned numbers for the compiler
   from 0 to just below FIRST_PSEUDO_REGISTER.

   RV32 has 32 integer registers (x0-x31) and 32 floating point
   registers (f0-f31).  */

#define FIRST_PSEUDO_REGISTER 64

/* Internal macros to classify register numbers.  */

#define GP_REG_FIRST 0
#define GP_REG_LAST  31
#define GP_REG_NUM   (GP_REG_LAST - GP_REG_FIRST + 1)

#define FP_REG_FIRST 32
#define FP_REG_LAST  63
#define FP_REG_NUM   (FP_REG_LAST - FP_REG_FIRST + 1)

#define GP_REG_P(REGNO) ((unsigned) ((REGNO) - GP_REG_FIRST) < GP_REG_NUM)
#define FP_REG_P(REGNO) ((unsigned) ((REGNO) - FP_REG_FIRST) < FP_REG_NUM)

/* RTX-safe versions for use in insn output templates (operands are rtx).
   Return false for MEM, CONST_INT, etc. — only true for REG in the class.  */
#define RTX_GP_REG_P(X) (GET_CODE (X) == REG && GP_REG_P (REGNO (X)))
#define RTX_FP_REG_P(X) (GET_CODE (X) == REG && FP_REG_P (REGNO (X)))

/* 1 for registers that have pervasive standard uses
   and are not available for the register allocator.

   RV32 ABI:
     x0  = zero (hardwired zero)
     x1  = ra   (return address — caller-saved, but used by call/ret)
     x2  = sp   (stack pointer)
     x3  = gp   (global pointer)
     x4  = tp   (thread pointer)
*/
#define FIXED_REGISTERS \
 {1, 1, 1, 1, 1, 1, 1, 1,	/* x0-x7:   zero,ra,sp,gp,tp,t0-t2 (t0-t2 reserved as scratch) */ \
  0, 0, 0, 0, 0, 0, 0, 0,	/* x8-x15:  s0-s1,a0-a5 */ \
  0, 0, 0, 0, 0, 0, 0, 0,	/* x16-x23: a6-a7,s2-s7 */ \
  0, 0, 0, 0, 0, 0, 0, 0,	/* x24-x31: s8-s11,t3-t6 */ \
				\
  0, 0, 0, 0, 0, 0, 0, 0,	/* f0-f7:   ft0-ft7 */ \
  0, 0, 0, 0, 0, 0, 0, 0,	/* f8-f15:  fs0-fs1,fa0-fa5 */ \
  0, 0, 0, 0, 0, 0, 0, 0,	/* f16-f23: fa6-fa7,fs2-fs7 */ \
  0, 0, 0, 0, 0, 0, 0, 0}	/* f24-f31: fs8-fs11,ft8-ft11 */


/* 1 for registers not available across function calls.
   These must include the FIXED_REGISTERS and also any
   registers that can be used without being saved.
   The latter must include the registers where values are returned
   and the register where structure-value addresses are passed.

   RV32 caller-saved (call-clobbered):
     x1(ra), x5-x7(t0-t2), x10-x17(a0-a7), x28-x31(t3-t6)
     f0-f7(ft0-ft7), f10-f17(fa0-fa7), f28-f31(ft8-ft11)
*/
#define CALL_USED_REGISTERS \
 {1, 1, 1, 1, 1, 1, 1, 1,	/* x0-x7:   zero,ra,sp,gp,tp,t0-t2 */ \
  0, 0, 1, 1, 1, 1, 1, 1,	/* x8-x15:  s0-s1,a0-a5 */ \
  1, 1, 0, 0, 0, 0, 0, 0,	/* x16-x23: a6-a7,s2-s7 */ \
  0, 0, 0, 0, 1, 1, 1, 1,	/* x24-x31: s8-s11,t3-t6 */ \
				\
  1, 1, 1, 1, 1, 1, 1, 1,	/* f0-f7:   ft0-ft7 */ \
  0, 0, 1, 1, 1, 1, 1, 1,	/* f8-f15:  fs0-fs1,fa0-fa7 */ \
  1, 1, 0, 0, 0, 0, 0, 0,	/* f16-f23: fa6-fa7,fs2-fs7 */ \
  0, 0, 0, 0, 1, 1, 1, 1}	/* f24-f31: fs8-fs11,ft8-ft11 */


/* Return number of consecutive hard regs needed starting at reg REGNO
   to hold something of mode MODE.
   On RV32, all registers are one word (32 bits).
   DFmode and DImode need 2 GPRs, but only 1 FP reg pair for DFmode.  */

#define HARD_REGNO_NREGS(REGNO, MODE)   \
  (FP_REG_P (REGNO)			\
   ? 1					\
   : ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))

/* Value is 1 if hard register REGNO can hold a value of machine-mode MODE.
   On RV32: GPRs hold integer modes. FP regs hold float modes.
   DFmode in GPRs needs even register pair.
   RISC-V D extension: every FP reg is 64-bit, no even/odd restriction.  */

/* Allow DFmode in GP registers even when FPU is enabled.
   This is needed for variadic function argument passing (ILP32D ABI
   passes unnamed doubles in GP register pairs).  The register allocator
   is steered away from putting FP values in GP regs by
   PREFERRED_RELOAD_CLASS and the instruction constraints (FP operations
   require 'f' regs), so this only triggers when necessary (reload).  */
#define HARD_REGNO_MODE_OK(REGNO, MODE) \
  (GP_REG_P (REGNO)							\
   ? ((GET_MODE_SIZE (MODE) <= 4) || ((REGNO) & 1) == 0)		\
   : (TARGET_FPU							\
      ? ((MODE) == SFmode || (MODE) == DFmode)				\
      : 0))

/* Value is 1 if it is a good idea to tie two pseudo registers
   when one has mode MODE1 and one has mode MODE2.  */
#define MODES_TIEABLE_P(MODE1, MODE2) \
  (((MODE1) == SFmode || (MODE1) == DFmode) \
   == ((MODE2) == SFmode || (MODE2) == DFmode))

/* Register to use for pushing function arguments.  */
#define STACK_POINTER_REGNUM 2

/* Offset from the stack pointer to the first available location.  */
#define STACK_POINTER_OFFSET 0

/* Base register for access to local variables of the function.  */
#define FRAME_POINTER_REGNUM 8

/* Value should be nonzero if functions must have frame pointers.
   Zero means the frame pointer need not be set up (and parms
   may be accessed via the stack pointer) in functions that seem suitable.  */
#define FRAME_POINTER_REQUIRED 0

/* Base register for access to arguments of the function.  */
#define ARG_POINTER_REGNUM FRAME_POINTER_REGNUM

/* Register in which static-chain is passed to a function.  */
#define STATIC_CHAIN_REGNUM 5	/* t0 */

/* Register in which address to store a structure value
   is passed to a function.  */
#define STRUCT_VALUE_REGNUM 10	/* a0 */

/* Define this if addresses of constant functions
   shouldn't be put through pseudo regs where they can be cse'd.  */
#define NO_FUNCTION_CSE


/* Define the classes of registers for register constraints in the
   machine description.  Also define ranges of constants.  */

enum reg_class { NO_REGS, GR_REGS, FP_REGS, ALL_REGS, LIM_REG_CLASSES };

#define N_REG_CLASSES (int) LIM_REG_CLASSES

#define GENERAL_REGS GR_REGS

/* Give names of register classes as strings for dump file.  */

#define REG_CLASS_NAMES \
 {"NO_REGS", "GR_REGS", "FP_REGS", "ALL_REGS" }

/* Define which registers fit in which classes.
   This is an initializer for a vector of HARD_REG_SET
   of length N_REG_CLASSES.  */

#define REG_CLASS_CONTENTS \
 {{0x00000000, 0x00000000},	\
  {0xffffffff, 0x00000000},	\
  {0x00000000, 0xffffffff},	\
  {0xffffffff, 0xffffffff}}

/* The same information, inverted:
   Return the class number of the smallest class containing
   reg number REGNO.  */

#define REGNO_REG_CLASS(REGNO) \
  (FP_REG_P (REGNO) ? FP_REGS : GR_REGS)

/* Define a table for register class superclasses.  */
#define REG_CLASS_SUPERCLASSES  \
 {{LIM_REG_CLASSES},		\
  {ALL_REGS,LIM_REG_CLASSES},	\
  {ALL_REGS,LIM_REG_CLASSES},	\
  {LIM_REG_CLASSES}}

/* The inverse relationship:
   for each class, a list of all reg classes contained in it.  */
#define REG_CLASS_SUBCLASSES	\
 {{LIM_REG_CLASSES},		\
  {GR_REGS,LIM_REG_CLASSES},	\
  {FP_REGS,LIM_REG_CLASSES},	\
  {GR_REGS, FP_REGS, ALL_REGS, LIM_REG_CLASSES}}

/* Define a table for register class subunion.  */
#define REG_CLASS_SUBUNION \
 {{NO_REGS,  GR_REGS,   FP_REGS,  ALL_REGS},	\
  {GR_REGS,  GR_REGS,   ALL_REGS, ALL_REGS},	\
  {FP_REGS,  ALL_REGS,  FP_REGS,  ALL_REGS},	\
  {ALL_REGS, ALL_REGS,  ALL_REGS, ALL_REGS}}

/* The class value for index registers, and the one for base regs.  */
#define INDEX_REG_CLASS GR_REGS
#define BASE_REG_CLASS  GR_REGS

/* Get reg_class from a letter such as appears in the machine description.  */

#define REG_CLASS_FROM_LETTER(C) \
  ((C) == 'f' ? FP_REGS : NO_REGS)

/* The letters I, J, K, L and M in a register constraint string
   can be used to stand for particular ranges of immediate operands.
   This macro defines what the ranges are.
   C is the letter, and VALUE is a constant value.
   Return 1 if VALUE is in the range specified by C.

   For RV32:
     `I' is used for 12-bit signed immediates (-2048..2047)
     `J' is used for zero
     `K' is used for unsigned 5-bit (shift amounts, 0..31)  */

#define SMALL_INT(X) ((unsigned) (INTVAL (X) + 0x800) < 0x1000)

#define CONST_OK_FOR_LETTER_P(VALUE, C)  \
  ((C) == 'I' ? (unsigned) ((VALUE) + 0x800) < 0x1000	\
   : (C) == 'J' ? (VALUE) == 0				\
   : (C) == 'K' ? (unsigned) (VALUE) < 0x20		\
   : 0)

/* Similar, but for floating constants, and defining letters G and H.
   Here VALUE is the CONST_DOUBLE rtx itself.  */

#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C) \
  ((C) == 'G' && CONST_DOUBLE_LOW ((VALUE)) == 0 \
   && CONST_DOUBLE_HIGH ((VALUE)) == 0)

/* Given an rtx X being reloaded into a reg required to be
   in class CLASS, return the class of reg to actually use.  */

#define PREFERRED_RELOAD_CLASS(X,CLASS) \
  (((GET_MODE(X) == SFmode) || (GET_MODE(X) == DFmode)) \
   ? (TARGET_FPU ? FP_REGS : (CLASS))			 \
   : ((GET_MODE(X) == VOIDmode) ? GR_REGS : (CLASS)))

/* Return the maximum number of consecutive registers
   needed to represent mode MODE in a register of class CLASS.  */

#define CLASS_MAX_NREGS(CLASS, MODE) \
  ((CLASS) == FP_REGS				\
   ? 1						\
   : ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))


/* Stack layout; function entry, exit and calling.  */

/* Define this if pushing a word on the stack
   makes the stack pointer a smaller address.  */
#define STACK_GROWS_DOWNWARD

/* Define this if the nominal address of the stack frame
   is at the high-address end of the local variables;
   that is, each additional local variable allocated
   goes at a more negative offset in the frame.  */
#define FRAME_GROWS_DOWNWARD

/* Offset within stack frame to start allocating local variables at.  */
#define STARTING_FRAME_OFFSET 0

/* Offset of first parameter from the argument pointer register value.  */
#define FIRST_PARM_OFFSET(FNDECL) 0

/* Offset from top-of-stack address to location to store the
   function parameter if it can't go in a register.  */
#define FIRST_PARM_CALLER_OFFSET(FNDECL) 0

/* When a parameter is passed in a register, stack space is still
   allocated for it.  */
/* #define REG_PARM_STACK_SPACE */

/* Value is 1 if returning from a function call automatically
   pops the arguments described by the number-of-args field in the call.  */

#define RETURN_POPS_ARGS(FUNTYPE) 0

/* Symbolic macros for the registers used to return integer and floating
   point values.  */

#define GP_RETURN 10		/* a0 */
#define FP_RETURN 42		/* fa0 = f10, but register 10+32=42 */

/* Symbolic macros for the first/last argument registers.  */

#define GP_ARG_FIRST 10		/* a0 = x10 */
#define GP_ARG_LAST  17		/* a7 = x17 */
#define FP_ARG_FIRST 42		/* fa0 = f10, register 10+32=42 */
#define FP_ARG_LAST  49		/* fa7 = f17, register 17+32=49 */

#define MAX_ARGS_IN_REGISTERS 8

/* Define how to find the value returned by a library function
   assuming the value has mode MODE.  */

#define LIBCALL_VALUE(MODE) \
  gen_rtx (REG, MODE, \
	   (TARGET_FPU && GET_MODE_CLASS (MODE) == MODE_FLOAT) \
	    ? FP_RETURN : GP_RETURN)

/* Define how to find the value returned by a function.
   VALTYPE is the data type of the value (as a tree).
   If the precise function being called is known, FUNC is its FUNCTION_DECL;
   otherwise, FUNC is 0.  */

#define FUNCTION_VALUE(VALTYPE, FUNC) LIBCALL_VALUE (TYPE_MODE (VALTYPE))

/* 1 if N is a possible register number for a function value.  */

#define FUNCTION_VALUE_REGNO_P(N) ((N) == GP_RETURN || (N) == FP_RETURN)

/* 1 if N is a possible register number for function argument passing.  */

#define FUNCTION_ARG_REGNO_P(N) \
  (((N) >= GP_ARG_FIRST && (N) <= GP_ARG_LAST) \
   || (TARGET_FPU && (N) >= FP_ARG_FIRST && (N) <= FP_ARG_LAST))


/* Define a data type for recording info about an argument list
   during the scan of that argument list.  This data type should
   hold all necessary information about the function itself
   and about the args processed so far, enough to enable macros
   such as FUNCTION_ARG to determine where the next arg should go.

   On RV32, this is a single integer, which is a number of words
   of arguments scanned so far.
   Thus 8 or more means all following args should go on the stack.  */

#define CUMULATIVE_ARGS int

/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.  */

#define INIT_CUMULATIVE_ARGS(CUM,FNTYPE) ((CUM) = 0)

/* Update the data in CUM to advance over an argument
   of mode MODE and data type TYPE.  */

extern int riscv_function_arg_advance_val ();
#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED) \
  ((CUM) = riscv_function_arg_advance_val (CUM, MODE, TYPE, NAMED))

/* Determine where to put an argument to a function.
   Value is zero to push the argument on the stack,
   or a hard register in which to store the argument.

   On RV32 the first 8 args go in a0-a7 (x10-x17).
   FP args go in fa0-fa7 if FPU is enabled.  */

extern struct rtx_def *riscv_function_arg ();
#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) \
  riscv_function_arg (CUM, MODE, TYPE, NAMED)

/* For an arg passed partly in registers and partly in memory,
   this is the number of registers used.
   For args passed entirely in registers or entirely in memory, zero.  */

#define FUNCTION_ARG_PARTIAL_NREGS(CUM, MODE, TYPE, NAMED) 0


/* This macro generates the assembly code for function entry.  */

extern void riscv_function_prologue ();

#define FUNCTION_PROLOGUE(FILE, SIZE) riscv_function_prologue (FILE, SIZE)

/* This macro generates the assembly code for function exit.  */

extern void riscv_function_epilogue ();

#define FUNCTION_EPILOGUE(FILE, SIZE) riscv_function_epilogue (FILE, SIZE)

/* Tell prologue and epilogue if a register should be saved/restored.  */

#define MUST_SAVE_REGISTER(regno) \
 ((regs_ever_live[regno] && !call_used_regs[regno]) \
  || (regno == FRAME_POINTER_REGNUM && frame_pointer_needed) \
  || (regno == 1 && regs_ever_live[1]))

/* ALIGN FRAMES on double word boundaries.  */
#define AL_ADJUST_ALIGN(LOC) (((LOC) + 7) & ~7)

/* EXIT_IGNORE_STACK should be nonzero if, when returning from a function,
   the stack pointer does not matter.  */

#define EXIT_IGNORE_STACK 1


/* If the memory address ADDR is relative to the frame pointer,
   correct it to be relative to the stack pointer instead.

   Frame layout (saved registers at BOTTOM, locals at TOP):
     sp + tsize (= fp)     = old sp
     sp + num_saved .. sp + tsize - 1  = local variables
     sp + 0 .. sp + num_saved - 1      = saved registers

   So fp + X = sp + tsize + DEPTH + X, where tsize = locals + num_saved.  */

#define FIX_FRAME_POINTER_ADDRESS(ADDR,DEPTH) \
{ int offset = -1;							\
  rtx regs = stack_pointer_rtx;						\
  if (ADDR == frame_pointer_rtx)					\
    offset = 0;								\
  else if (GET_CODE (ADDR) == PLUS && XEXP (ADDR, 0) == frame_pointer_rtx \
	   && GET_CODE (XEXP (ADDR, 1)) == CONST_INT)			\
    offset = INTVAL (XEXP (ADDR, 1));					\
  else if (GET_CODE (ADDR) == PLUS && XEXP (ADDR, 0) == frame_pointer_rtx) \
    { rtx other_reg = XEXP (ADDR, 1);					\
      offset = 0;							\
      regs = gen_rtx (PLUS, Pmode, stack_pointer_rtx, other_reg); }	\
  else if (GET_CODE (ADDR) == PLUS && XEXP (ADDR, 1) == frame_pointer_rtx) \
    { rtx other_reg = XEXP (ADDR, 0);					\
      offset = 0;							\
      regs = gen_rtx (PLUS, Pmode, stack_pointer_rtx, other_reg); }	\
  if (offset >= 0)							\
    { int _r, _saved = 0;						\
      extern char call_used_regs[];					\
      extern int get_frame_size ();					\
      /* Count saved regs to match prologue: ra + callee-saved.  */	\
      if (regs_ever_live[1]) _saved += 4;				\
      for (_r = 0; _r < FIRST_PSEUDO_REGISTER; _r++)			\
        if (regs_ever_live[_r] && ! call_used_regs[_r])			\
          _saved += (FP_REG_P (_r) && TARGET_HARD_FLOAT_D) ? 8 : 4;	\
      _saved = AL_ADJUST_ALIGN (_saved);				\
      offset += AL_ADJUST_ALIGN (get_frame_size ()) + _saved;		\
      ADDR = plus_constant (regs, offset + (DEPTH)); } }


/* Addressing modes, and classification of registers for them.  */

/* #define HAVE_POST_INCREMENT */
/* #define HAVE_POST_DECREMENT */
/* #define HAVE_PRE_DECREMENT */
/* #define HAVE_PRE_INCREMENT */

/* These assume that REGNO is a hard or pseudo reg number.
   They give nonzero only if REGNO is a hard reg of the suitable class
   or a pseudo reg currently allocated to a suitable hard reg.  */

#define REGNO_OK_FOR_INDEX_P(REGNO) \
  ((REGNO) < FIRST_PSEUDO_REGISTER	\
   ? GP_REG_P (REGNO)			\
   : (reg_renumber[REGNO] >= 0 && GP_REG_P (reg_renumber[REGNO])))

#define REGNO_OK_FOR_BASE_P(REGNO) REGNO_OK_FOR_INDEX_P (REGNO)

#define REGNO_OK_FOR_FP_P(REGNO) \
  ((REGNO) < FIRST_PSEUDO_REGISTER	\
   ? FP_REG_P (REGNO)			\
   : (reg_renumber[REGNO] >= 0 && FP_REG_P (reg_renumber[REGNO])))


/* The macros REG_OK_FOR..._P assume that the arg is a REG rtx
   and check its validity for a certain class.
   We have two alternate definitions for each of them.
   The usual definition accepts all pseudo regs; the other rejects
   them unless they have been allocated suitable hard regs.  */

#ifndef REG_OK_STRICT

/* Nonzero if X is a hard reg that can be used as an index
   or if it is a pseudo reg.  */
#define REG_OK_FOR_INDEX_P(X) \
  (REGNO (X) < FIRST_PSEUDO_REGISTER ? GP_REG_P (REGNO (X)) : 1)
#define REG_OK_FOR_BASE_P(X) REG_OK_FOR_INDEX_P(X)

#else

#define REG_OK_FOR_INDEX_P(X) REGNO_OK_FOR_INDEX_P (REGNO (X))
#define REG_OK_FOR_BASE_P(X) REGNO_OK_FOR_BASE_P (REGNO (X))

#endif


/* Maximum number of registers that can appear in a valid memory address.
   RV32 only supports base+offset, so just 1 register.  */

#define MAX_REGS_PER_ADDRESS 1

/* Recognize any constant value that is a valid address.  */

#define CONSTANT_ADDRESS_P(X) CONSTANT_P (X)

/* Nonzero if the constant value X is a legitimate general operand.
   It is given that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */

#define LEGITIMATE_CONSTANT_P(X) (GET_CODE (X) != CONST_DOUBLE)

/* GO_IF_LEGITIMATE_ADDRESS recognizes an RTL expression
   that is a valid memory address for an instruction.
   The MODE argument is the machine mode for the MEM expression
   that wants to use this address.

   On RV32, the valid addresses are:
     REG
     REG + 12-bit signed offset
     constant (will need lui+load sequence in output)

   Constants are only valid for integer modes — the assembler can
   auto-expand "lw rd,symbol" (using rd as scratch for the address),
   but cannot expand "fld fd,symbol" (FP regs can't hold addresses).
   For float modes, the compiler must load the address into a GP reg.  */

#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, ADDR) \
{ if (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X))		\
    goto ADDR;							\
  if (GET_CODE (X) == PLUS					\
      && GET_CODE (XEXP (X, 0)) == REG				\
      && REG_OK_FOR_BASE_P (XEXP (X, 0))			\
      && GET_CODE (XEXP (X, 1)) == CONST_INT			\
      && INTVAL (XEXP (X, 1)) >= -0x800				\
      && INTVAL (XEXP (X, 1)) < 0x800)				\
    goto ADDR;							\
  if (CONSTANT_ADDRESS_P (X)					\
      && GET_MODE_CLASS (MODE) != MODE_FLOAT)			\
    goto ADDR;							\
}

/* Try machine-dependent ways of modifying an illegitimate address
   to be legitimate.  If we find one, return the new, valid address.  */

#define LEGITIMIZE_ADDRESS(X,OLDX,MODE,WIN) \
{ if (GET_CODE (X) == PLUS && CONSTANT_ADDRESS_P (XEXP (X, 1)))  \
    (X) = gen_rtx (PLUS, SImode, XEXP (X, 0),			  \
		   copy_to_mode_reg (SImode, XEXP (X, 1)));	  \
  if (GET_CODE (X) == PLUS && CONSTANT_ADDRESS_P (XEXP (X, 0)))  \
    (X) = gen_rtx (PLUS, SImode, XEXP (X, 1),			  \
		   copy_to_mode_reg (SImode, XEXP (X, 0)));	  \
  if (memory_address_p (MODE, X))				  \
    goto WIN; }

/* Go to LABEL if ADDR (a legitimate address expression)
   has an effect that depends on the machine mode it is used for.  */

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL)

/* Specify the machine mode that this machine uses
   for the index in the tablejump instruction.  */
#define CASE_VECTOR_MODE SImode

/* Define this if the tablejump instruction expects the table
   to contain offsets from the address of the table.
   Do not define this if the table should contain absolute addresses.  */
/* #define CASE_VECTOR_PC_RELATIVE */

/* Specify the tree operation to be used to convert reals to integers.  */
#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR

/* This is the kind of divide that is easiest to do in the general case.  */
#define EASY_DIV_EXPR TRUNC_DIV_EXPR

/* Define this as 1 if `char' should by default be signed; else as 0.  */
#define DEFAULT_SIGNED_CHAR 0

/* Max number of bytes we can move from memory to memory
   in one reasonably fast instruction.  */
#define MOVE_MAX 4

/* Nonzero if access to memory by bytes is slow and undesirable.  */
#define SLOW_BYTE_ACCESS 0

/* We assume that the store-condition-codes instructions store 0 for false
   and some other value for true.  This is the value stored for true.  */

#define STORE_FLAG_VALUE 1

/* Declarations for condition code stuff.  */
extern void compare_collect ();
extern void compare_restore ();

/* Define if shifts truncate the shift count
   which implies one can omit a sign-extension or zero-extension
   of a shift count.  RV32 only uses the low 5 bits.  */
#define SHIFT_COUNT_TRUNCATED

/* Value is 1 if truncating an integer of INPREC bits to OUTPREC bits
   is done just by pretending it is already truncated.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1

/* Specify the machine mode that pointers have.
   After generation of rtl, the compiler makes no further distinction
   between pointers and any other objects of this machine mode.  */
#define Pmode SImode

/* A function address in a call instruction
   is a word address (for indexing purposes)
   so give the MEM rtx a word's mode.  */

#define FUNCTION_MODE SImode

/* Compute the cost of computing a constant rtl expression RTX
   whose rtx-code is CODE.  */

#define CONST_COSTS(RTX,CODE) \
  case CONST_INT:						\
    /* Constant zero is super cheap due to register x0.  */	\
    if (RTX == const0_rtx) return 0;				\
    if ((unsigned) (INTVAL (RTX) + 0x800) < 0x1000) return 1;	\
  case CONST:							\
  case LABEL_REF:						\
  case SYMBOL_REF:						\
    return 3;							\
  case CONST_DOUBLE:						\
    return 5;


/* Tell final.c how to eliminate redundant test instructions.
   RV32 has no hardware condition codes register; comparisons are
   fused into branches.  So we always reset cc_status.  */

#define NOTICE_UPDATE_CC(EXP, INSN) CC_STATUS_INIT;


/* Control the assembler format that we output.  */

/* Output at beginning of assembler file.  */

#define ASM_FILE_START(file)

/* Output to assembler file text saying following lines
   may contain character constants, extra white space, comments, etc.  */

#define ASM_APP_ON " #APP\n"

/* Output to assembler file text saying following lines
   no longer contain unusual constructs.  */

#define ASM_APP_OFF " #NO_APP\n"

/* Output before read-only data.  */

#define TEXT_SECTION_ASM_OP "\t.text"

/* Output before writable data.  */

#define DATA_SECTION_ASM_OP "\t.data"

/* How to refer to registers in assembler output.
   This sequence is indexed by compiler's hard-register-number (see above).  */

#define REGISTER_NAMES \
{"zero","ra", "sp", "gp", "tp", "t0", "t1", "t2",	\
 "s0",  "s1", "a0", "a1", "a2", "a3", "a4", "a5",	\
 "a6",  "a7", "s2", "s3", "s4", "s5", "s6", "s7",	\
 "s8",  "s9", "s10","s11","t3", "t4", "t5", "t6",	\
 "ft0", "ft1","ft2","ft3","ft4","ft5","ft6","ft7",	\
 "fs0", "fs1","fa0","fa1","fa2","fa3","fa4","fa5",	\
 "fa6", "fa7","fs2","fs3","fs4","fs5","fs6","fs7",	\
 "fs8", "fs9","fs10","fs11","ft8","ft9","ft10","ft11"}

/* How to renumber registers for dbx and gdb.  */

#define DBX_REGISTER_NUMBER(REGNO) (REGNO)

/* On Sun 4, this limit is 2048.  We use 1500 to be safe.  */
#define DBX_CONTIN_LENGTH 1500


/* Define results of standard character escape sequences.  */
#define TARGET_BELL 007
#define TARGET_BS 010
#define TARGET_TAB 011
#define TARGET_NEWLINE 012
#define TARGET_VT 013
#define TARGET_FF 014
#define TARGET_CR 015


/* Print an instruction operand X on file FILE.
   CODE is the code from the %-spec that requested printing this operand.

   RV32 codes:
     'M' - print the most significant word register of a DImode pair
     'L' - print the least significant word register of a DImode pair
     'D' - print register+1 (next register in pair)  */

#define PRINT_OPERAND(FILE, X, CODE)				\
{ if (GET_CODE (X) == REG)					\
    {								\
      int regnum = REGNO (X);					\
      if (CODE == 'M')						\
	regnum += MOST_SIGNIFICANT_WORD;			\
      else if (CODE == 'L')					\
	regnum += LEAST_SIGNIFICANT_WORD;			\
      else if (CODE == 'D')					\
	regnum++;						\
      fprintf (FILE, "%s", reg_names[regnum]);			\
    }								\
  else if (GET_CODE (X) == MEM)					\
    output_address (XEXP (X, 0));				\
  else if (GET_CODE (X) == CONST_DOUBLE)			\
    {								\
      union { double d; int i[2]; } u;				\
      u.i[0] = CONST_DOUBLE_LOW (X);				\
      u.i[1] = CONST_DOUBLE_HIGH (X);				\
      if (GET_MODE (X) == SFmode)				\
	{							\
	  float f;						\
	  f = u.d;						\
	  u.d = f;						\
	}							\
      fprintf (FILE, "%.20e", u.d);				\
    }								\
  else								\
    output_addr_const (FILE, X);				\
}


/* Print a memory operand whose address is X, on file FILE.
   For RV32, addresses are offset(reg) format.  */

#define PRINT_OPERAND_ADDRESS(FILE, ADDR) \
{ register rtx addr = ADDR;					\
  switch (GET_CODE (addr))					\
    {								\
    default:							\
      abort ();							\
      break;							\
    case REG:							\
      fprintf (FILE, "0(%s)", reg_names[REGNO (addr)]);		\
      break;							\
    case PLUS:							\
      {								\
	register rtx reg = (rtx)0;				\
	register rtx offset = (rtx)0;				\
	register rtx arg0 = XEXP (addr, 0);			\
	register rtx arg1 = XEXP (addr, 1);			\
	if (GET_CODE (arg0) == REG)				\
	  { reg = arg0; offset = arg1; }			\
	else if (GET_CODE (arg1) == REG)			\
	  { reg = arg1; offset = arg0; }			\
	else							\
	  abort ();						\
	output_addr_const (FILE, offset);			\
	fprintf (FILE, "(%s)", reg_names[REGNO (reg)]);		\
      }								\
      break;							\
    case LABEL_REF:						\
    case SYMBOL_REF:						\
    case CONST_INT:						\
    case CONST:							\
      output_addr_const (FILE, addr);				\
      break;							\
    }								\
}


/* This is how to output the definition of a user-level label named NAME.  */

#define ASM_OUTPUT_LABEL(FILE,NAME) \
  do { assemble_name (FILE, NAME); fputs (":\n", FILE); } while (0)

/* This is how to output a command to make the user-level label named NAME
   defined for reference from other files.  */

#define ASM_GLOBALIZE_LABEL(FILE,NAME) \
  do { fputs ("\t.globl\t", FILE); assemble_name (FILE, NAME); \
       fputs ("\n", FILE); } while (0)

/* This is how to output a reference to a user-level label named NAME.
   `assemble_name' uses this.  */

#define ASM_OUTPUT_LABELREF(FILE,NAME) \
  fprintf (FILE, "%s", NAME)

/* This is how to output an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.  */

#define ASM_OUTPUT_INTERNAL_LABEL(FILE,PREFIX,NUM) \
  fprintf (FILE, "%s%d:\n", PREFIX, NUM)

/* This is how to store into the string LABEL
   the symbol_ref name of an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.
   This is suitable for output with `assemble_name'.  */

#define ASM_GENERATE_INTERNAL_LABEL(LABEL,PREFIX,NUM) \
  sprintf (LABEL, "*%s%d", PREFIX, NUM)

/* This is how to output an assembler line defining a `double' constant.  */

#define ASM_OUTPUT_DOUBLE(FILE,VALUE)  \
{					\
  union { double d; int l[2]; } u2;	\
  u2.d = VALUE;				\
  fprintf (FILE, "\t.word\t0x%08x\n\t.word\t0x%08x\t# double %.20g\n", \
	   u2.l[0], u2.l[1], u2.d);	\
}

/* This is how to output an assembler line defining a `float' constant.  */

#define ASM_OUTPUT_FLOAT(FILE,VALUE)  \
{					\
  union { float f; int l; } u2;		\
  u2.f = VALUE;				\
  fprintf (FILE, "\t.word\t0x%08x\t# float %.12g\n", u2.l, (double) u2.f); \
}

/* This is how to output an assembler line defining an `int' constant.  */

#define ASM_OUTPUT_INT(FILE,VALUE)  \
( fprintf (FILE, "\t.word\t"),		\
  output_addr_const (FILE, (VALUE)),	\
  fprintf (FILE, "\n"))

/* Likewise for `char' and `short' constants.  */

#define ASM_OUTPUT_SHORT(FILE,VALUE)  \
( fprintf (FILE, "\t.half\t"),		\
  output_addr_const (FILE, (VALUE)),	\
  fprintf (FILE, "\n"))

#define ASM_OUTPUT_CHAR(FILE,VALUE)  \
( fprintf (FILE, "\t.byte\t"),		\
  output_addr_const (FILE, (VALUE)),	\
  fprintf (FILE, "\n"))

/* This is how to output an assembler line for a numeric constant byte.  */

#define ASM_OUTPUT_BYTE(FILE,VALUE)  \
  fprintf (FILE, "\t.byte\t0x%x\n", (VALUE))

/* This is how to output an element of a case-vector that is absolute.  */

#define ASM_OUTPUT_ADDR_VEC_ELT(FILE, VALUE) \
  fprintf (FILE, "\t.word\tL%d\n", VALUE)

/* This is how to output an element of a case-vector that is relative.  */

#define ASM_OUTPUT_ADDR_DIFF_ELT(FILE, VALUE, REL)  \
  fprintf (FILE, "\t.word\tL%d-L%d\n", VALUE, REL)

/* This is how to output an assembler line
   that says to advance the location counter
   to a multiple of 2**LOG bytes.  */

#define ASM_OUTPUT_ALIGN(FILE,LOG) \
  if ((LOG) != 0) \
    fprintf (FILE, "\t.align\t%d\n", (LOG))

#define ASM_OUTPUT_SKIP(FILE,SIZE)  \
  fprintf (FILE, "\t.space\t%u\n", (SIZE))

/* This says how to output an assembler line
   to define a global common symbol.  */

#define ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED) \
( fputs ("\t.comm\t", (FILE)),			\
  assemble_name ((FILE), (NAME)),		\
  fprintf ((FILE), ",%u\n", (SIZE)))

/* This says how to output an assembler line
   to define a local common symbol.  */

#define ASM_OUTPUT_LOCAL(FILE, NAME, SIZE, ROUNDED) \
( fputs ("\t.lcomm\t", (FILE)),			\
  assemble_name ((FILE), (NAME)),		\
  fprintf ((FILE), ",%u\n", (ROUNDED)))

/* Store in OUTPUT a string (made with alloca) containing
   an assembler-name for a local static variable named NAME.
   LABELNO is an integer which is different for each call.  */

#define ASM_FORMAT_PRIVATE_NAME(OUTPUT, NAME, LABELNO) \
( (OUTPUT) = (char *) alloca (strlen ((NAME)) + 10), \
  sprintf ((OUTPUT), "%s.%d", (NAME), (LABELNO)))

/* Define the parentheses used to group arithmetic operations
   in assembler code.  */

#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"

/* Push/pop register to/from stack for profiling.  */
#define ASM_OUTPUT_REG_PUSH(STREAM, REGNO)  \
  fprintf (STREAM, "\taddi\tsp,sp,-4\n\tsw\t%s,0(sp)\n", reg_names[REGNO])

#define ASM_OUTPUT_REG_POP(STREAM, REGNO)  \
  fprintf (STREAM, "\tlw\t%s,0(sp)\n\taddi\tsp,sp,4\n", reg_names[REGNO])

/* Output assembler code to FILE to increment profiler label # LABELNO
   for profiling a function entry.  */

#define FUNCTION_PROFILER(FILE, LABELNO) \
  fprintf (FILE, "\t# profiler: label %d\n", (LABELNO))

/* Generate DBX debugging information.  */

#define DBX_DEBUGGING_INFO

/* This is how to output a note the debugger telling it the line number
   to which the following sequence of instructions corresponds.  */

#define ASM_OUTPUT_SOURCE_LINE(FILE, LINE)		\
  { static int sym_lineno = 1;				\
    fprintf (FILE, "\t# line %d\n", LINE);		\
    sym_lineno += 1; }
