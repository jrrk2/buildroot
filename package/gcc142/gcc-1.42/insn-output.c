/* Generated automatically by the program `genoutput'
from the machine description file `md'.  */

#include "config.h"
#include "rtl.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "conditions.h"
#include "insn-flags.h"
#include "insn-config.h"

#ifndef __STDC__
#define const
#endif

#include "output.h"
#include "aux-output.c"

#ifndef INSN_MACHINE_INFO
#define INSN_MACHINE_INFO struct dummy1 {int i;}
#endif


static char *
output_0 (operands, insn)
     rtx *operands;
     rtx insn;
{

    compare_collect (SImode, operands[0], operands[1]);
    return "\t\t\t\t# cmpsi\t%0,%1";

}

static char *
output_1 (operands, insn)
     rtx *operands;
     rtx insn;
{

    compare_collect (SImode, operands[0], const0_rtx);
    return "\t\t\t\t# tstsi\t%0";

}

static char *
output_2 (operands, insn)
     rtx *operands;
     rtx insn;
{

    compare_collect (SFmode, operands[0], operands[1]);
    return "\t\t\t\t# cmpsf\t%0,%1";

}

static char *
output_3 (operands, insn)
     rtx *operands;
     rtx insn;
{

    compare_collect (DFmode, operands[0], operands[1]);
    return "\t\t\t\t# cmpdf\t%0,%1";

}

static char *
output_6 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("feq.s\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# beq.s", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("feq.d\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# beq.d", br_ops);
    }
  else
    output_asm_insn ("beq\t%0,%1,%2", br_ops);
  return "";
}

}

static char *
output_7 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("feq.s\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bne.s (inv)", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("feq.d\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bne.d (inv)", br_ops);
    }
  else
    output_asm_insn ("bne\t%0,%1,%2\t# beq inv", br_ops);
  return "";
}

}

static char *
output_8 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("feq.s\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bne.s", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("feq.d\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bne.d", br_ops);
    }
  else
    output_asm_insn ("bne\t%0,%1,%2", br_ops);
  return "";
}

}

static char *
output_9 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("feq.s\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# beq.s (inv)", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("feq.d\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# beq.d (inv)", br_ops);
    }
  else
    output_asm_insn ("beq\t%0,%1,%2\t# bne inv", br_ops);
  return "";
}

}

static char *
output_10 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("flt.s\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# blt.s", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("flt.d\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# blt.d", br_ops);
    }
  else
    output_asm_insn ("blt\t%0,%1,%2", br_ops);
  return "";
}

}

static char *
output_11 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("flt.s\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bge.s (inv)", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("flt.d\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bge.d (inv)", br_ops);
    }
  else
    output_asm_insn ("bge\t%0,%1,%2\t# blt inv", br_ops);
  return "";
}

}

static char *
output_12 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("fle.s\tt0,%1,%0", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# bge.s", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("fle.d\tt0,%1,%0", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# bge.d", br_ops);
    }
  else
    output_asm_insn ("bge\t%0,%1,%2", br_ops);
  return "";
}

}

static char *
output_13 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("fle.s\tt0,%1,%0", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# blt.s (inv)", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("fle.d\tt0,%1,%0", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# blt.d (inv)", br_ops);
    }
  else
    output_asm_insn ("blt\t%0,%1,%2\t# bge inv", br_ops);
  return "";
}

}

static char *
output_14 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("flt.s\tt0,%1,%0", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# bgt.s", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("flt.d\tt0,%1,%0", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# bgt.d", br_ops);
    }
  else
    output_asm_insn ("blt\t%1,%0,%2\t# bgt", br_ops);
  return "";
}

}

static char *
output_15 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("flt.s\tt0,%1,%0", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# ble.s (inv)", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("flt.d\tt0,%1,%0", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# ble.d (inv)", br_ops);
    }
  else
    output_asm_insn ("bge\t%1,%0,%2\t# bgt inv", br_ops);
  return "";
}

}

static char *
output_16 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("fle.s\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# ble.s", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("fle.d\tt0,%0,%1", br_ops);
      output_asm_insn ("bne\tt0,zero,%2\t# ble.d", br_ops);
    }
  else
    output_asm_insn ("bge\t%1,%0,%2\t# ble", br_ops);
  return "";
}

}

static char *
output_17 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn ("fle.s\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bgt.s (inv)", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn ("fle.d\tt0,%0,%1", br_ops);
      output_asm_insn ("beq\tt0,zero,%2\t# bgt.d (inv)", br_ops);
    }
  else
    output_asm_insn ("blt\t%1,%0,%2\t# ble inv", br_ops);
  return "";
}

}

static char *
output_18 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bltu\t%0,%1,%2", br_ops);
  return "";
}

}

static char *
output_19 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bgeu\t%0,%1,%2\t# bltu inv", br_ops);
  return "";
}

}

static char *
output_20 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bgeu\t%0,%1,%2", br_ops);
  return "";
}

}

static char *
output_21 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bltu\t%0,%1,%2\t# bgeu inv", br_ops);
  return "";
}

}

static char *
output_22 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bltu\t%1,%0,%2\t# bgtu", br_ops);
  return "";
}

}

static char *
output_23 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bgeu\t%1,%0,%2\t# bgtu inv", br_ops);
  return "";
}

}

static char *
output_24 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bgeu\t%1,%0,%2\t# bleu", br_ops);
  return "";
}

}

static char *
output_25 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn ("bltu\t%1,%0,%2\t# bleu inv", br_ops);
  return "";
}

}

static char *
output_26 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == REG)
    return "mv\t%0,%1";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == CONST_INT)
    {
      if (INTVAL (operands[1]) == 0)
        return "mv\t%0,zero";
      if (SMALL_INT (operands[1]))
        return "li\t%0,%1";
      return "li\t%0,%1";
    }
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == MEM)
    return output_load (operands, "w");
  if (GET_CODE (operands[0]) == MEM && GET_CODE (operands[1]) == REG)
    return output_store (operands, "w");
  if (GET_CODE (operands[0]) == REG)
    {
      if (GET_CODE (operands[1]) == SYMBOL_REF
          || GET_CODE (operands[1]) == LABEL_REF
          || GET_CODE (operands[1]) == CONST)
        return "la\t%0,%1";
      return "li\t%0,%1";
    }
  abort ();
}

}

static char *
output_27 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == REG)
    {
      /* Sign-extend 16-bit value in register.  */
      output_asm_insn ("slli\t%0,%1,16", operands);
      return "srai\t%0,%0,16";
    }
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == CONST_INT)
    return "li\t%0,%1";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == MEM)
    return output_load (operands, "h");
  if (GET_CODE (operands[0]) == MEM && GET_CODE (operands[1]) == REG)
    return output_store (operands, "h");
  if (GET_CODE (operands[0]) == REG)
    return "li\t%0,%1";
  abort ();
}

}

static char *
output_28 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == REG)
    return "andi\t%0,%1,0xff";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == CONST_INT)
    return "li\t%0,%1";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == MEM)
    return output_load (operands, "b");
  if (GET_CODE (operands[0]) == MEM && GET_CODE (operands[1]) == REG)
    return output_store (operands, "b");
  if (GET_CODE (operands[0]) == REG)
    return "li\t%0,%1";
  abort ();
}

}

static char *
output_29 (operands, insn)
     rtx *operands;
     rtx insn;
{
 return output_move_double (operands);
}

static char *
output_30 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (RTX_FP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        return "fmv.s\t%0,%1";
      if (GET_CODE (operands[1]) == MEM)
        return "flw\t%0,%1";
      if (RTX_GP_REG_P (operands[1]))
        return "fmv.w.x\t%0,%1";
    }
  if (GET_CODE (operands[0]) == MEM)
    {
      if (RTX_FP_REG_P (operands[1]))
        return "fsw\t%1,%0";
      if (RTX_GP_REG_P (operands[1]))
        return "sw\t%1,%0";
    }
  if (RTX_GP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        return "fmv.x.w\t%0,%1";
      if (RTX_GP_REG_P (operands[1]))
        return "mv\t%0,%1";
      if (GET_CODE (operands[1]) == MEM)
        return "lw\t%0,%1";
    }
  abort ();
}

}

static char *
output_31 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (RTX_FP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        return "fmv.d\t%0,%1";
      if (GET_CODE (operands[1]) == MEM)
        return "fld\t%0,%1";
      if (RTX_GP_REG_P (operands[1]))
        {
          /* FP ← GP pair: go through stack.  */
          output_asm_insn ("addi\tsp,sp,-8", operands);
          output_asm_insn ("sw\t%1,0(sp)", operands);
          output_asm_insn ("sw\t%D1,4(sp)", operands);
          output_asm_insn ("fld\t%0,0(sp)", operands);
          output_asm_insn ("addi\tsp,sp,8", operands);
          return "";
        }
    }
  if (GET_CODE (operands[0]) == MEM)
    {
      if (RTX_FP_REG_P (operands[1]))
        return "fsd\t%1,%0";
      if (RTX_GP_REG_P (operands[1]))
        return output_move_double (operands);
    }
  if (RTX_GP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        {
          /* GP pair ← FP: go through stack.  */
          output_asm_insn ("addi\tsp,sp,-8", operands);
          output_asm_insn ("fsd\t%1,0(sp)", operands);
          output_asm_insn ("lw\t%0,0(sp)", operands);
          output_asm_insn ("lw\t%D0,4(sp)", operands);
          output_asm_insn ("addi\tsp,sp,8", operands);
          return "";
        }
      return output_move_double (operands);
    }
  abort ();
}

}

static char *
output_34 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[1]) == MEM)
    return "lhu\t%0,%1";
  /* From register: mask to 16 bits.  */
  output_asm_insn ("slli\t%0,%1,16", operands);
  return "srli\t%0,%0,16";
}

}

static char *
output_35 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[1]) == MEM)
    return "lbu\t%0,%1";
  return "andi\t%0,%1,0xff";
}

}

static char *
output_36 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[1]) == MEM)
    return "lbu\t%0,%1";
  return "andi\t%0,%1,0xff";
}

}

static char *
output_37 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[1]) == MEM)
    return "lb\t%0,%1";
  output_asm_insn ("slli\t%0,%1,24", operands);
  return "srai\t%0,%0,24";
}

}

static char *
output_38 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[1]) == MEM)
    return "lh\t%0,%1";
  output_asm_insn ("slli\t%0,%1,16", operands);
  return "srai\t%0,%0,16";
}

}

static char *
output_39 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[1]) == MEM)
    return "lb\t%0,%1";
  output_asm_insn ("slli\t%0,%1,24", operands);
  return "srai\t%0,%0,24";
}

}

static char *
output_42 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) != CONST_INT)
    return "add\t%0,%1,%2";
  if (SMALL_INT (operands[2]))
    return "addi\t%0,%1,%2";
  /* Large constant: use t0 as temp.  */
  return "lui\tt0,%%hi(%2)\n\taddi\tt0,t0,%%lo(%2)\n\tadd\t%0,%1,t0";
}

}

static char *
output_43 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "addi\t%0,%1,%2";
  return "add\t%0,%1,%2";
}

}

static char *
output_44 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) != CONST_INT)
    return "sub\t%0,%1,%2";
  if (GET_CODE (operands[2]) == CONST_INT
      && (unsigned) (-INTVAL (operands[2]) + 0x800) < 0x1000)
    {
      operands[2] = gen_rtx (CONST_INT, VOIDmode, -INTVAL (operands[2]));
      return "addi\t%0,%1,%2";
    }
  return "lui\tt0,%%hi(%2)\n\taddi\tt0,t0,%%lo(%2)\n\tsub\t%0,%1,t0";
}

}

static char *
output_45 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      operands[2] = gen_rtx (CONST_INT, VOIDmode, -INTVAL (operands[2]));
      return "addi\t%0,%1,%2";
    }
  return "sub\t%0,%1,%2";
}

}

static char *
output_52 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "andi\t%0,%1,%2";
  return "and\t%0,%1,%2";
}

}

static char *
output_53 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "ori\t%0,%1,%2";
  return "or\t%0,%1,%2";
}

}

static char *
output_54 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "xori\t%0,%1,%2";
  return "xor\t%0,%1,%2";
}

}

static char *
output_56 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "slli\t%0,%1,%2";
  return "sll\t%0,%1,%2";
}

}

static char *
output_57 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "srai\t%0,%1,%2";
  return "sra\t%0,%1,%2";
}

}

static char *
output_58 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  if (GET_CODE (operands[2]) == CONST_INT)
    return "srli\t%0,%1,%2";
  return "srl\t%0,%1,%2";
}

}

static char *
output_75 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  register rtx target = XEXP (operands[0], 0);
  if (GET_CODE (target) == SYMBOL_REF)
    return "call\t%0";
  else
    return "jalr\tra,%0";
}

}

static char *
output_76 (operands, insn)
     rtx *operands;
     rtx insn;
{

{
  register rtx target = XEXP (operands[1], 0);
  if (GET_CODE (target) == SYMBOL_REF)
    return "call\t%1";
  else
    return "jalr\tra,%1";
}

}

char * const insn_template[] =
  {
    0,
    0,
    0,
    0,
    "j %l0",
    "jr %0",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "andi %0,%1,0xff",
    "slli %0,%1,16ntsrait%0,%0,16",
    0,
    0,
    0,
    0,
    0,
    0,
    "fcvt.d.s %0,%1",
    "fcvt.s.d %0,%1",
    0,
    0,
    0,
    0,
    "mul %0,%1,%2",
    "div %0,%1,%2",
    "divu %0,%1,%2",
    "rem %0,%1,%2",
    "remu %0,%1,%2",
    "neg %0,%1",
    0,
    0,
    0,
    "not %0,%1",
    0,
    0,
    0,
    "fadd.s %0,%1,%2",
    "fsub.s %0,%1,%2",
    "fmul.s %0,%1,%2",
    "fdiv.s %0,%1,%2",
    "fneg.s %0,%1",
    "fabs.s %0,%1",
    "fadd.d %0,%1,%2",
    "fsub.d %0,%1,%2",
    "fmul.d %0,%1,%2",
    "fdiv.d %0,%1,%2",
    "fneg.d %0,%1",
    "fabs.d %0,%1",
    "fcvt.s.w %0,%1",
    "fcvt.d.w %0,%1",
    "fcvt.w.s %0,%1,rtz",
    "fcvt.w.d %0,%1,rtz",
    0,
    0,
    "nop",
    "jr %0",
  };

char *(*const insn_outfun[])() =
  {
    output_0,
    output_1,
    output_2,
    output_3,
    0,
    0,
    output_6,
    output_7,
    output_8,
    output_9,
    output_10,
    output_11,
    output_12,
    output_13,
    output_14,
    output_15,
    output_16,
    output_17,
    output_18,
    output_19,
    output_20,
    output_21,
    output_22,
    output_23,
    output_24,
    output_25,
    output_26,
    output_27,
    output_28,
    output_29,
    output_30,
    output_31,
    0,
    0,
    output_34,
    output_35,
    output_36,
    output_37,
    output_38,
    output_39,
    0,
    0,
    output_42,
    output_43,
    output_44,
    output_45,
    0,
    0,
    0,
    0,
    0,
    0,
    output_52,
    output_53,
    output_54,
    0,
    output_56,
    output_57,
    output_58,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    output_75,
    output_76,
    0,
    0,
  };

rtx (*const insn_gen_function[]) () =
  {
    gen_cmpsi,
    0,
    gen_cmpsf,
    gen_cmpdf,
    gen_jump,
    gen_tablejump,
    gen_beq,
    0,
    gen_bne,
    0,
    gen_blt,
    0,
    gen_bge,
    0,
    gen_bgt,
    0,
    gen_ble,
    0,
    gen_bltu,
    0,
    gen_bgeu,
    0,
    gen_bgtu,
    0,
    gen_bleu,
    0,
    gen_movsi,
    gen_movhi,
    gen_movqi,
    gen_movdi,
    gen_movsf,
    gen_movdf,
    gen_truncsiqi2,
    gen_truncsihi2,
    gen_zero_extendhisi2,
    gen_zero_extendqisi2,
    gen_zero_extendqihi2,
    gen_extendqihi2,
    gen_extendhisi2,
    gen_extendqisi2,
    gen_extendsfdf2,
    gen_truncdfsf2,
    0,
    gen_addsi3,
    0,
    gen_subsi3,
    gen_mulsi3,
    gen_divsi3,
    gen_udivsi3,
    gen_modsi3,
    gen_umodsi3,
    gen_negsi2,
    gen_andsi3,
    gen_iorsi3,
    gen_xorsi3,
    gen_one_cmplsi2,
    gen_ashlsi3,
    gen_ashrsi3,
    gen_lshrsi3,
    gen_addsf3,
    gen_subsf3,
    gen_mulsf3,
    gen_divsf3,
    gen_negsf2,
    gen_abssf2,
    gen_adddf3,
    gen_subdf3,
    gen_muldf3,
    gen_divdf3,
    gen_negdf2,
    gen_absdf2,
    gen_floatsisf2,
    gen_floatsidf2,
    gen_fix_truncsfsi2,
    gen_fix_truncdfsi2,
    gen_call,
    gen_call_value,
    gen_nop,
    gen_indirect_jump,
  };

const int insn_n_operands[] =
  {
    2,
    1,
    2,
    2,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    2,
    3,
    3,
    3,
    2,
    3,
    3,
    3,
    3,
    3,
    3,
    3,
    2,
    2,
    3,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    3,
    0,
    1,
  };

const int insn_n_dups[] =
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
  };

char *const insn_operand_constraint[][MAX_RECOG_OPERANDS] =
  {
    { "r", "rI", },
    { "r", },
    { "f", "f", },
    { "f", "f", },
    { 0 },
    { "r", },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { "=r,r,m,r", "r,i,r,m", },
    { "=r,r,m,r", "r,i,r,m", },
    { "=r,r,m,r", "r,i,r,m", },
    { "=r,r,m", "r,im,r", },
    { "=f,f,m,r,f,r,r,m", "f,m,f,f,r,r,m,r", },
    { "=f,f,m,r,m,r,f", "f,m,f,im,r,f,r", },
    { "=r", "r", },
    { "=r", "r", },
    { "=r,r", "r,m", },
    { "=r,r", "r,m", },
    { "=r,r", "r,m", },
    { "=r,r", "r,m", },
    { "=r,r", "r,m", },
    { "=r,r", "r,m", },
    { "=f", "f", },
    { "=f", "f", },
    { "=r", "r", "i", },
    { "=r", "%r", "rI", },
    { "=r", "r", "i", },
    { "=r", "r", "rI", },
    { "=r", "r", "r", },
    { "=r", "r", "r", },
    { "=r", "r", "r", },
    { "=r", "r", "r", },
    { "=r", "r", "r", },
    { "=r", "r", },
    { "=r", "%r", "rI", },
    { "=r", "%r", "rI", },
    { "=r", "%r", "rI", },
    { "=r", "r", },
    { "=r", "r", "rI", },
    { "=r", "r", "rI", },
    { "=r", "r", "rI", },
    { "=f", "f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", },
    { "=f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", "f", },
    { "=f", "f", },
    { "=f", "f", },
    { "=f", "r", },
    { "=f", "r", },
    { "=r", "f", },
    { "=r", "f", },
    { "m", "i", },
    { "=rf", "m", "i", },
    { 0 },
    { "r", },
  };

const enum machine_mode insn_operand_mode[][MAX_RECOG_OPERANDS] =
  {
    { SImode, SImode, },
    { SImode, },
    { SFmode, SFmode, },
    { DFmode, DFmode, },
    { VOIDmode },
    { SImode, },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { VOIDmode },
    { SImode, SImode, },
    { HImode, HImode, },
    { QImode, QImode, },
    { DImode, DImode, },
    { SFmode, SFmode, },
    { DFmode, DFmode, },
    { QImode, SImode, },
    { HImode, SImode, },
    { SImode, HImode, },
    { SImode, QImode, },
    { HImode, QImode, },
    { HImode, QImode, },
    { SImode, HImode, },
    { SImode, QImode, },
    { DFmode, SFmode, },
    { SFmode, DFmode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SImode, SImode, SImode, },
    { SFmode, SFmode, SFmode, },
    { SFmode, SFmode, SFmode, },
    { SFmode, SFmode, SFmode, },
    { SFmode, SFmode, SFmode, },
    { SFmode, SFmode, },
    { SFmode, SFmode, },
    { DFmode, DFmode, DFmode, },
    { DFmode, DFmode, DFmode, },
    { DFmode, DFmode, DFmode, },
    { DFmode, DFmode, DFmode, },
    { DFmode, DFmode, },
    { DFmode, DFmode, },
    { SFmode, SImode, },
    { DFmode, SImode, },
    { SImode, SFmode, },
    { SImode, DFmode, },
    { VOIDmode, VOIDmode, },
    { VOIDmode, VOIDmode, VOIDmode, },
    { VOIDmode },
    { SImode, },
  };

const char insn_operand_strict_low[][MAX_RECOG_OPERANDS] =
  {
    { 0, 0, },
    { 0, },
    { 0, 0, },
    { 0, 0, },
    { 0 },
    { 0, },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, },
    { 0, 0, 0, },
    { 0 },
    { 0, },
  };

int (*const insn_operand_predicate[][MAX_RECOG_OPERANDS])() =
  {
    { register_operand, arith_operand, },
    { register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { 0 },
    { register_operand, },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { general_operand, general_operand, },
    { general_operand, general_operand, },
    { general_operand, general_operand, },
    { general_operand, general_operand, },
    { general_operand, general_operand, },
    { general_operand, general_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, general_operand, },
    { register_operand, general_operand, },
    { register_operand, general_operand, },
    { register_operand, general_operand, },
    { register_operand, general_operand, },
    { register_operand, general_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, immediate_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, immediate_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, arith_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { register_operand, register_operand, },
    { memory_operand, 0, },
    { 0, memory_operand, 0, },
    { 0 },
    { register_operand, },
  };

#ifndef DEFAULT_MACHINE_INFO
#define DEFAULT_MACHINE_INFO 0
#endif

const INSN_MACHINE_INFO insn_machine_info[] =
  {
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
     { DEFAULT_MACHINE_INFO },
  };

const int insn_n_alternatives[] =
  {
    1,
    1,
    1,
    1,
     0,
    1,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
    4,
    4,
    4,
    3,
    8,
    7,
    1,
    1,
    2,
    2,
    2,
    2,
    2,
    2,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
     0,
    1,
  };
