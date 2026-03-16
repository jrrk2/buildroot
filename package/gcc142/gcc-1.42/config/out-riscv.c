/* Subroutines for insn-output.c for RISC-V RV32.
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

/* Note: This file is #included from insn-output.c, which already includes
   config.h, rtl.h, regs.h, hard-reg-set.h, real.h, conditions.h,
   insn-flags.h, insn-config.h, and output.h.  */

#include <stdio.h>
#include "tree.h"
#include "flags.h"

extern void debug_rtx ();
extern void abort_with_insn ();
extern FILE *asm_out_file;
extern tree current_function_decl;
extern char call_used_regs[];
extern int frame_pointer_needed;

/* Routines to merge the compare and branch operators into a single entity.  */

static rtx branch_cmp_op[2];
static enum machine_mode branch_cmp_mode;

/* Save the mode and operands on the current compare operator.  */

void
compare_collect (mode, op0, op1)
     enum machine_mode mode;
     rtx op0;
     rtx op1;
{
  branch_cmp_op[0] = op0;
  branch_cmp_op[1] = op1;
  branch_cmp_mode = mode;
}

/* Return the mode and operands saved with compare_collect for use
   in a branch operator.  */

void
compare_restore (operands, mode, insn)
     rtx *operands;
     enum machine_mode *mode;
     rtx insn;
{
  if (!branch_cmp_op[0])
    abort_with_insn (insn, "compare_restore did not follow compare_collect");

  operands[0] = branch_cmp_op[0];
  operands[1] = branch_cmp_op[1];
  *mode = branch_cmp_mode;

  /* RV32 branch instructions only accept register operands.
     If either comparison operand is a constant, use x0 for zero
     or emit a load into a temp register (t1 or t2).  */
  if (*mode == SImode)
    {
      if (GET_CODE (operands[0]) == CONST_INT)
	{
	  if (INTVAL (operands[0]) == 0)
	    operands[0] = gen_rtx (REG, SImode, 0);  /* x0 = zero */
	  else
	    {
	      output_asm_insn ("li\tt1,%0", operands);
	      operands[0] = gen_rtx (REG, SImode, 6);  /* t1 = x6 */
	    }
	}
      if (GET_CODE (operands[1]) == CONST_INT)
	{
	  if (INTVAL (operands[1]) == 0)
	    operands[1] = gen_rtx (REG, SImode, 0);  /* x0 = zero */
	  else
	    {
	      rtx save0 = operands[0];
	      operands[0] = operands[1];
	      output_asm_insn ("li\tt2,%0", operands);
	      operands[0] = save0;
	      operands[1] = gen_rtx (REG, SImode, 7);  /* t2 = x7 */
	    }
	}
    }

  /* If the next insn is not a JUMP (after accounting for line numbers),
     zero out the branch_cmp_array.  Switch statements implemented as if's
     tend to have multiple jumps.  */
  do
    {
      insn = NEXT_INSN (insn);
    }
  while (insn && GET_CODE (insn) == NOTE);

  if (!insn || GET_CODE (insn) != JUMP_INSN)
    {
      branch_cmp_op[0] = NULL;
      branch_cmp_op[1] = NULL;
      branch_cmp_mode = VOIDmode;
    }
}


/* Return truth value of whether OP can be used as an operand
   where a register or 12 bit signed integer is needed.  */

int
arith_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return (register_operand (op, mode)
	  || (GET_CODE (op) == CONST_INT && SMALL_INT (op)));
}

/* Return truth value of whether OP can be used as an operand in a two
   address arithmetic insn (such as a lui+addi sequence) of mode MODE.  */

int
arith32_operand (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return (register_operand (op, mode) || GET_CODE (op) == CONST_INT);
}

/* Return truth value of whether OP is an integer which fits in 12 bits.  */

int
small_int (op, mode)
     rtx op;
     enum machine_mode mode;
{
  return (GET_CODE (op) == CONST_INT && SMALL_INT (op));
}


/* Compute the upper 20 bits for a lui instruction, adjusting for the
   sign extension of the lower 12 bits.  When bit 11 of the value is set,
   the lower 12 bits (addi) will be sign-extended, effectively subtracting
   0x1000.  So we need to add 0x1000 to the upper bits to compensate.  */

int
riscv_hi20 (value)
     int value;
{
  /* If bit 11 is set, the lo12 will be negative, so add 0x1000 */
  if (value & 0x800)
    return ((value + 0x1000) >> 12) & 0xfffff;
  else
    return (value >> 12) & 0xfffff;
}

/* Compute the lower 12 bits (sign-extended) for an addi instruction.  */

int
riscv_lo12 (value)
     int value;
{
  int lo = value & 0xfff;
  /* Sign-extend from 12 bits */
  if (lo & 0x800)
    lo |= ~0xfff;
  return lo;
}


/* Output a load instruction that handles constant addresses by splitting
   into lui+load.  OPERANDS[0] is the destination register, OPERANDS[1]
   is the memory source.  Returns the template string for output_asm_insn.  */

char *
output_load (operands, suffix)
     rtx *operands;
     char *suffix;
{
  static char buf[128];
  sprintf (buf, "l%s\t%%0,%%1", suffix);
  return buf;
}

/* Output a store instruction that handles symbolic (global) addresses.
   RV32 store to symbol requires a temp register: "sw rs, symbol, t0".
   The assembler expands this to lui t0,%hi(sym) ; sw rs,%lo(sym)(t0).  */

char *
output_store (operands, suffix)
     rtx *operands;
     char *suffix;
{
  rtx addr = XEXP (operands[0], 0);
  static char buf[128];

  if (GET_CODE (addr) == SYMBOL_REF
      || GET_CODE (addr) == CONST
      || GET_CODE (addr) == LABEL_REF)
    {
      sprintf (buf, "s%s\t%%1,%%0,t0", suffix);
    }
  else
    {
      sprintf (buf, "s%s\t%%1,%%0", suffix);
    }
  return buf;
}


/* Output a two-word (64-bit) move sequence for DImode or DFmode
   when using GPRs.  */

char *
output_move_double (operands)
     rtx *operands;
{
  rtx dst = operands[0];
  rtx src = operands[1];

  if (GET_CODE (dst) == REG && GET_CODE (src) == REG)
    {
      int dstno = REGNO (dst);
      int srcno = REGNO (src);

      /* If source and dest overlap, be careful about order.  */
      if (dstno == srcno + 1)
	{
	  /* Move high word first.  */
	  output_asm_insn ("mv\t%D0,%D1", operands);
	  output_asm_insn ("mv\t%0,%1", operands);
	}
      else
	{
	  output_asm_insn ("mv\t%0,%1", operands);
	  output_asm_insn ("mv\t%D0,%D1", operands);
	}
    }
  else if (GET_CODE (dst) == REG && GET_CODE (src) == MEM)
    {
      rtx addr = XEXP (src, 0);
      if (GET_CODE (addr) == REG)
	{
	  rtx ops[2];
	  ops[0] = operands[0];
	  ops[1] = addr;
	  output_asm_insn ("lw\t%0,0(%1)", ops);
	  ops[0] = gen_rtx (REG, SImode, REGNO (operands[0]) + 1);
	  output_asm_insn ("lw\t%0,4(%1)", ops);
	}
      else if (GET_CODE (addr) == PLUS
	       && GET_CODE (XEXP (addr, 0)) == REG
	       && GET_CODE (XEXP (addr, 1)) == CONST_INT)
	{
	  int offset = INTVAL (XEXP (addr, 1));
	  rtx ops[4];
	  ops[0] = operands[0];
	  ops[1] = XEXP (addr, 0);
	  ops[2] = gen_rtx (CONST_INT, VOIDmode, offset);
	  ops[3] = gen_rtx (CONST_INT, VOIDmode, offset + 4);
	  output_asm_insn ("lw\t%0,%2(%1)", ops);
	  ops[0] = gen_rtx (REG, SImode, REGNO (operands[0]) + 1);
	  output_asm_insn ("lw\t%0,%3(%1)", ops);
	}
      else
	{
	  /* Let assembler handle complex addresses.  */
	  output_asm_insn ("lw\t%0,%1", operands);
	  output_asm_insn ("lw\t%D0,%1+4", operands);
	}
    }
  else if (GET_CODE (dst) == MEM && GET_CODE (src) == REG)
    {
      rtx addr = XEXP (dst, 0);
      if (GET_CODE (addr) == REG)
	{
	  rtx ops[2];
	  ops[0] = addr;
	  ops[1] = operands[1];
	  output_asm_insn ("sw\t%1,0(%0)", ops);
	  ops[1] = gen_rtx (REG, SImode, REGNO (operands[1]) + 1);
	  output_asm_insn ("sw\t%1,4(%0)", ops);
	}
      else if (GET_CODE (addr) == PLUS
	       && GET_CODE (XEXP (addr, 0)) == REG
	       && GET_CODE (XEXP (addr, 1)) == CONST_INT)
	{
	  int offset = INTVAL (XEXP (addr, 1));
	  rtx ops[4];
	  ops[0] = XEXP (addr, 0);
	  ops[1] = operands[1];
	  ops[2] = gen_rtx (CONST_INT, VOIDmode, offset);
	  ops[3] = gen_rtx (CONST_INT, VOIDmode, offset + 4);
	  output_asm_insn ("sw\t%1,%2(%0)", ops);
	  ops[1] = gen_rtx (REG, SImode, REGNO (operands[1]) + 1);
	  output_asm_insn ("sw\t%1,%3(%0)", ops);
	}
      else
	{
	  output_asm_insn ("sw\t%1,%0", operands);
	  output_asm_insn ("sw\t%D1,%0+4", operands);
	}
    }
  else if (GET_CODE (dst) == REG && GET_CODE (src) == CONST_INT)
    {
      output_asm_insn ("li\t%0,%1", operands);
      /* High word is sign extension */
      if (INTVAL (src) < 0)
	output_asm_insn ("li\t%D0,-1", operands);
      else
	output_asm_insn ("li\t%D0,0", operands);
    }
  else
    abort ();

  return "";
}


/* Abort after printing out a specific insn.  */

void
abort_with_insn (insn, reason)
     rtx insn;
     char *reason;
{
  error (reason);
  debug_rtx (insn);
  abort ();
}


/* Set up the stack and frame for the function.  */

void
riscv_function_prologue (file, size)
     FILE *file;
     int size;
{
  int tsize;
  int regno;
  int num_saved_regs = 0;
  int push_loc;

  /* Calculate total frame size:
     = local variables (rounded up to 8) + saved registers + outgoing args */

  tsize = AL_ADJUST_ALIGN (size);

  /* Count saved registers by walking the exact same conditions as the
     save code below.  This avoids any mismatch between counting and saving.  */
  if (regs_ever_live[1] || frame_pointer_needed)
    num_saved_regs += 4;  /* ra */
  if (frame_pointer_needed)
    num_saved_regs += 4;  /* s0 */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (MUST_SAVE_REGISTER (regno) && GP_REG_P (regno)
	&& regno != 1 && regno != FRAME_POINTER_REGNUM)
      num_saved_regs += 4;
  if (TARGET_FPU)
    for (regno = FP_REG_FIRST; regno <= FP_REG_LAST; regno++)
      if (regs_ever_live[regno] && !call_used_regs[regno])
	num_saved_regs += TARGET_HARD_FLOAT_D ? 8 : 4;

  num_saved_regs = AL_ADJUST_ALIGN (num_saved_regs);
  tsize += num_saved_regs;
  tsize = AL_ADJUST_ALIGN (tsize);

  fprintf (file, "\t# PROLOGUE: frame=%d, saved=%d\n", size, num_saved_regs);

  /* Allocate stack frame.  */
  if (tsize > 0)
    {
      if (tsize <= 2047)
	fprintf (file, "\taddi\tsp,sp,-%d\n", tsize);
      else
	fprintf (file, "\tlui\tt0,%%hi(%d)\n\taddi\tt0,t0,%%lo(%d)\n\tsub\tsp,sp,t0\n",
		 tsize, tsize);
    }

  /* Save registers at the BOTTOM of the frame (low sp offsets).
     Local variables occupy the upper part of the frame (near the frame
     pointer), so saving registers at the bottom avoids overlap.

     Frame layout (stack grows down):
       sp + tsize    = old sp (= s0 after frame pointer setup)
       sp + num_saved .. sp + tsize - 1  = local variables
       sp + 0 .. sp + num_saved - 1      = saved registers  */

  push_loc = 0;

  /* Save return address if needed.  */
  if (regs_ever_live[1] || frame_pointer_needed)
    {
      fprintf (file, "\tsw\tra,%d(sp)\n", push_loc);
      push_loc += 4;
    }

  /* Save frame pointer if needed.  */
  if (frame_pointer_needed)
    {
      fprintf (file, "\tsw\ts0,%d(sp)\n", push_loc);
      push_loc += 4;
    }

  /* Save callee-saved registers.  */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (MUST_SAVE_REGISTER (regno)
	&& GP_REG_P (regno)
	&& regno != 1		/* ra already saved */
	&& regno != FRAME_POINTER_REGNUM)  /* s0/fp already saved */
      {
	fprintf (file, "\tsw\t%s,%d(sp)\n", reg_names[regno], push_loc);
	push_loc += 4;
      }

  /* Save FP registers.  D extension has 64-bit FP regs, use fsd/fld.  */
  if (TARGET_FPU)
    for (regno = FP_REG_FIRST; regno <= FP_REG_LAST; regno++)
      if (regs_ever_live[regno] && !call_used_regs[regno])
	{
	  if (TARGET_HARD_FLOAT_D)
	    {
	      fprintf (file, "\tfsd\t%s,%d(sp)\n", reg_names[regno], push_loc);
	      push_loc += 8;
	    }
	  else
	    {
	      fprintf (file, "\tfsw\t%s,%d(sp)\n", reg_names[regno], push_loc);
	      push_loc += 4;
	    }
	}

  /* Set up frame pointer.  */
  if (frame_pointer_needed)
    {
      if (tsize <= 2047)
	fprintf (file, "\taddi\ts0,sp,%d\n", tsize);
      else
	fprintf (file, "\tlui\tt0,%%hi(%d)\n\taddi\tt0,t0,%%lo(%d)\n\tadd\ts0,sp,t0\n",
		 tsize, tsize);
    }

  fprintf (file, "\t# END PROLOGUE\n");
}


/* Do any necessary cleanup after a function to restore stack, frame,
   and regs.  */

void
riscv_function_epilogue (file, size)
     FILE *file;
     int size;
{
  int tsize;
  int regno;
  int num_saved_regs = 0;
  int push_loc;
  int ra_loc, fp_loc;

  tsize = AL_ADJUST_ALIGN (size);

  /* Count saved registers — must match the prologue exactly.  */
  if (regs_ever_live[1] || frame_pointer_needed)
    num_saved_regs += 4;
  if (frame_pointer_needed)
    num_saved_regs += 4;
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (MUST_SAVE_REGISTER (regno) && GP_REG_P (regno)
	&& regno != 1 && regno != FRAME_POINTER_REGNUM)
      num_saved_regs += 4;
  if (TARGET_FPU)
    for (regno = FP_REG_FIRST; regno <= FP_REG_LAST; regno++)
      if (regs_ever_live[regno] && !call_used_regs[regno])
	num_saved_regs += TARGET_HARD_FLOAT_D ? 8 : 4;

  num_saved_regs = AL_ADJUST_ALIGN (num_saved_regs);
  tsize += num_saved_regs;
  tsize = AL_ADJUST_ALIGN (tsize);

  fprintf (file, "\t# EPILOGUE\n");

  /* Reset sp from frame pointer.  During the function body, sp may have
     been modified by dynamic outgoing argument pushes.  Restore it to the
     post-prologue value so sp-relative offsets for register loads work.  */
  if (frame_pointer_needed)
    {
      if (tsize <= 2048)
	fprintf (file, "\taddi\tsp,s0,-%d\n", tsize);
      else
	fprintf (file, "\tlui\tt0,%%hi(%d)\n\taddi\tt0,t0,%%lo(%d)\n\tsub\tsp,s0,t0\n",
		 tsize, tsize);
    }

  /* Restore registers from the bottom of the frame, matching
     the prologue save order.  Compute offsets in the same way.  */
  push_loc = 0;
  ra_loc = -1;
  fp_loc = -1;

  if (regs_ever_live[1] || frame_pointer_needed)
    {
      ra_loc = push_loc;
      push_loc += 4;
    }

  if (frame_pointer_needed)
    {
      fp_loc = push_loc;
      push_loc += 4;
    }

  /* Restore callee-saved GPRs.  */
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (MUST_SAVE_REGISTER (regno)
	&& GP_REG_P (regno)
	&& regno != 1
	&& regno != FRAME_POINTER_REGNUM)
      {
	fprintf (file, "\tlw\t%s,%d(sp)\n", reg_names[regno], push_loc);
	push_loc += 4;
      }

  /* Restore FP registers.  D extension has 64-bit FP regs, use fld.  */
  if (TARGET_FPU)
    for (regno = FP_REG_FIRST; regno <= FP_REG_LAST; regno++)
      if (regs_ever_live[regno] && !call_used_regs[regno])
	{
	  if (TARGET_HARD_FLOAT_D)
	    {
	      fprintf (file, "\tfld\t%s,%d(sp)\n", reg_names[regno], push_loc);
	      push_loc += 8;
	    }
	  else
	    {
	      fprintf (file, "\tflw\t%s,%d(sp)\n", reg_names[regno], push_loc);
	      push_loc += 4;
	    }
	}

  /* Restore frame pointer.  */
  if (fp_loc >= 0)
    fprintf (file, "\tlw\ts0,%d(sp)\n", fp_loc);

  /* Restore return address.  */
  if (ra_loc >= 0)
    fprintf (file, "\tlw\tra,%d(sp)\n", ra_loc);

  /* Deallocate stack frame.  */
  if (tsize > 0)
    {
      if (tsize <= 2047)
	fprintf (file, "\taddi\tsp,sp,%d\n", tsize);
      else
	fprintf (file, "\tlui\tt0,%%hi(%d)\n\taddi\tt0,t0,%%lo(%d)\n\tadd\tsp,sp,t0\n",
		 tsize, tsize);
    }

  fprintf (file, "\tret\n");
  fprintf (file, "\t# END EPILOGUE\n");
}


/* Determine where to put a function argument.
   Returns a REG rtx for arguments passed in registers, or 0 for stack.
   On ILP32D, named FP args use FP registers; unnamed (variadic) args
   and args when no prototype is in scope use GP registers.
   Doubles in GP registers require an aligned even-odd register pair.  */

rtx
riscv_function_arg (cum, mode, type, named)
     int cum;
     enum machine_mode mode;
     tree type;
     int named;
{
  if (cum >= MAX_ARGS_IN_REGISTERS)
    return 0;

  /* Named FP args use FP registers when hardware FPU available.  */
  if (named && TARGET_FPU && GET_MODE_CLASS (mode) == MODE_FLOAT)
    {
      if (cum < MAX_ARGS_IN_REGISTERS)
	return gen_rtx (REG, mode, FP_ARG_FIRST + cum);
      return 0;
    }

  /* Doubles in GP regs need even-aligned register pair on RV32.  */
  if (GET_MODE_SIZE (mode) > UNITS_PER_WORD)
    {
      int aligned = (cum + 1) & ~1;	/* round up to even */
      if (aligned + 1 >= MAX_ARGS_IN_REGISTERS)
	return 0;	/* doesn't fit in remaining arg regs */
      return gen_rtx (REG, mode, GP_ARG_FIRST + aligned);
    }

  return gen_rtx (REG, mode, GP_ARG_FIRST + cum);
}


/* Advance the cumulative argument counter past one argument.
   Returns the new CUM value.
   Named FP args advance by 1 (one FP register).
   Doubles in GP regs align to even and advance by 2.  */

int
riscv_function_arg_advance_val (cum, mode, type, named)
     int cum;
     enum machine_mode mode;
     tree type;
     int named;
{
  int size;

  /* Named FP args: each uses one FP register slot.  */
  if (named && TARGET_FPU && GET_MODE_CLASS (mode) == MODE_FLOAT)
    return cum + 1;

  size = (mode != BLKmode)
    ? (GET_MODE_SIZE (mode) + 3) / 4
    : (int_size_in_bytes (type) + 3) / 4;

  /* Doubles in GP regs: align to even register pair first.  */
  if (GET_MODE_SIZE (mode) > UNITS_PER_WORD)
    cum = (cum + 1) & ~1;

  return cum + size;
}
