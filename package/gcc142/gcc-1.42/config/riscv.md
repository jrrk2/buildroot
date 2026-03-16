;;  riscv.md    Machine Description for RISC-V RV32IMAFD
;;  Copyright (C) 1992 Free Software Foundation, Inc.

;; This file is part of GNU CC.

;; GNU CC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 1, or (at your option)
;; any later version.

;; GNU CC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GNU CC; see the file COPYING.  If not, write to
;; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

;;
;;  ....................
;;
;;          COMPARISONS
;;
;;  ....................
;;
;; RV32 has no hardware condition codes register.  We use the MIPS
;; compare_collect/compare_restore pattern: compare insns save their
;; operands, and branch insns retrieve them to emit fused compare+branch.

(define_insn "cmpsi"
  [(set (cc0)
	(compare (match_operand:SI 0 "register_operand" "r")
		 (match_operand:SI 1 "arith_operand" "rI")))]
  ""
  "*
    compare_collect (SImode, operands[0], operands[1]);
    return \"\\t\\t\\t\\t# cmpsi\\t%0,%1\";
")

(define_insn ""
  [(set (cc0)
	(match_operand:SI 0 "register_operand" "r"))]
  ""
  "*
    compare_collect (SImode, operands[0], const0_rtx);
    return \"\\t\\t\\t\\t# tstsi\\t%0\";
")

(define_insn "cmpsf"
  [(set (cc0)
	(compare (match_operand:SF 0 "register_operand" "f")
		 (match_operand:SF 1 "register_operand" "f")))]
  "TARGET_FPU"
  "*
    compare_collect (SFmode, operands[0], operands[1]);
    return \"\\t\\t\\t\\t# cmpsf\\t%0,%1\";
")

(define_insn "cmpdf"
  [(set (cc0)
	(compare (match_operand:DF 0 "register_operand" "f")
		 (match_operand:DF 1 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "*
    compare_collect (DFmode, operands[0], operands[1]);
    return \"\\t\\t\\t\\t# cmpdf\\t%0,%1\";
")


;;
;;  ....................
;;
;;          BRANCHES
;;
;;  ....................
;;
;; Branch patterns: retrieve compare operands, emit fused compare+branch.
;; RV32 has beq, bne, blt, bge, bltu, bgeu as native instructions.
;; For bgt/ble/bgtu/bleu we swap operands: bgt a,b = blt b,a
;; For FP branches we use feq.s/flt.s/fle.s into temp GPR + bne/beq.

;; Unconditional jump
(define_insn "jump"
  [(set (pc)
	(label_ref (match_operand 0 "" "")))]
  ""
  "j %l0")

;; Table jump (switch)
(define_insn "tablejump"
  [(set (pc)
	(match_operand:SI 0 "register_operand" "r"))
   (use (label_ref (match_operand 1 "" "")))]
  ""
  "jr %0")


;; beq: branch if equal
(define_insn "beq"
  [(set (pc)
	(if_then_else (eq (cc0)
			  (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"feq.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# beq.s\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"feq.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# beq.d\", br_ops);
    }
  else
    output_asm_insn (\"beq\\t%0,%1,%2\", br_ops);
  return \"\";
}
")

;; beq inverted (branch if NOT equal — falls through to label_ref)
(define_insn ""
  [(set (pc)
	(if_then_else (eq (cc0)
			  (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"feq.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bne.s (inv)\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"feq.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bne.d (inv)\", br_ops);
    }
  else
    output_asm_insn (\"bne\\t%0,%1,%2\\t# beq inv\", br_ops);
  return \"\";
}
")

;; bne: branch if not equal
(define_insn "bne"
  [(set (pc)
	(if_then_else (ne (cc0)
			  (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"feq.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bne.s\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"feq.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bne.d\", br_ops);
    }
  else
    output_asm_insn (\"bne\\t%0,%1,%2\", br_ops);
  return \"\";
}
")

;; bne inverted
(define_insn ""
  [(set (pc)
	(if_then_else (ne (cc0)
			  (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"feq.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# beq.s (inv)\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"feq.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# beq.d (inv)\", br_ops);
    }
  else
    output_asm_insn (\"beq\\t%0,%1,%2\\t# bne inv\", br_ops);
  return \"\";
}
")

;; blt: branch if less than (signed)
(define_insn "blt"
  [(set (pc)
	(if_then_else (lt (cc0)
			  (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"flt.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# blt.s\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"flt.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# blt.d\", br_ops);
    }
  else
    output_asm_insn (\"blt\\t%0,%1,%2\", br_ops);
  return \"\";
}
")

;; blt inverted
(define_insn ""
  [(set (pc)
	(if_then_else (lt (cc0)
			  (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"flt.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bge.s (inv)\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"flt.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bge.d (inv)\", br_ops);
    }
  else
    output_asm_insn (\"bge\\t%0,%1,%2\\t# blt inv\", br_ops);
  return \"\";
}
")

;; bge: branch if greater than or equal (signed)
(define_insn "bge"
  [(set (pc)
	(if_then_else (ge (cc0)
			  (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"fle.s\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# bge.s\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"fle.d\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# bge.d\", br_ops);
    }
  else
    output_asm_insn (\"bge\\t%0,%1,%2\", br_ops);
  return \"\";
}
")

;; bge inverted
(define_insn ""
  [(set (pc)
	(if_then_else (ge (cc0)
			  (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"fle.s\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# blt.s (inv)\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"fle.d\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# blt.d (inv)\", br_ops);
    }
  else
    output_asm_insn (\"blt\\t%0,%1,%2\\t# bge inv\", br_ops);
  return \"\";
}
")

;; bgt: branch if greater than (signed) — swap operands: blt %1,%0
(define_insn "bgt"
  [(set (pc)
	(if_then_else (gt (cc0)
			  (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"flt.s\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# bgt.s\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"flt.d\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# bgt.d\", br_ops);
    }
  else
    output_asm_insn (\"blt\\t%1,%0,%2\\t# bgt\", br_ops);
  return \"\";
}
")

;; bgt inverted
(define_insn ""
  [(set (pc)
	(if_then_else (gt (cc0)
			  (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"flt.s\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# ble.s (inv)\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"flt.d\\tt0,%1,%0\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# ble.d (inv)\", br_ops);
    }
  else
    output_asm_insn (\"bge\\t%1,%0,%2\\t# bgt inv\", br_ops);
  return \"\";
}
")

;; ble: branch if less than or equal (signed) — swap: bge %1,%0
(define_insn "ble"
  [(set (pc)
	(if_then_else (le (cc0)
			  (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"fle.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# ble.s\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"fle.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"bne\\tt0,zero,%2\\t# ble.d\", br_ops);
    }
  else
    output_asm_insn (\"bge\\t%1,%0,%2\\t# ble\", br_ops);
  return \"\";
}
")

;; ble inverted
(define_insn ""
  [(set (pc)
	(if_then_else (le (cc0)
			  (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  if (mode == SFmode)
    {
      output_asm_insn (\"fle.s\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bgt.s (inv)\", br_ops);
    }
  else if (mode == DFmode)
    {
      output_asm_insn (\"fle.d\\tt0,%0,%1\", br_ops);
      output_asm_insn (\"beq\\tt0,zero,%2\\t# bgt.d (inv)\", br_ops);
    }
  else
    output_asm_insn (\"blt\\t%1,%0,%2\\t# ble inv\", br_ops);
  return \"\";
}
")

;; bltu: branch if less than (unsigned)
(define_insn "bltu"
  [(set (pc)
	(if_then_else (ltu (cc0)
			   (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bltu\\t%0,%1,%2\", br_ops);
  return \"\";
}
")

;; bltu inverted
(define_insn ""
  [(set (pc)
	(if_then_else (ltu (cc0)
			   (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bgeu\\t%0,%1,%2\\t# bltu inv\", br_ops);
  return \"\";
}
")

;; bgeu: branch if greater than or equal (unsigned)
(define_insn "bgeu"
  [(set (pc)
	(if_then_else (geu (cc0)
			   (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bgeu\\t%0,%1,%2\", br_ops);
  return \"\";
}
")

;; bgeu inverted
(define_insn ""
  [(set (pc)
	(if_then_else (geu (cc0)
			   (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bltu\\t%0,%1,%2\\t# bgeu inv\", br_ops);
  return \"\";
}
")

;; bgtu: branch if greater than (unsigned) — swap: bltu %1,%0
(define_insn "bgtu"
  [(set (pc)
	(if_then_else (gtu (cc0)
			   (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bltu\\t%1,%0,%2\\t# bgtu\", br_ops);
  return \"\";
}
")

;; bgtu inverted
(define_insn ""
  [(set (pc)
	(if_then_else (gtu (cc0)
			   (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bgeu\\t%1,%0,%2\\t# bgtu inv\", br_ops);
  return \"\";
}
")

;; bleu: branch if less than or equal (unsigned) — swap: bgeu %1,%0
(define_insn "bleu"
  [(set (pc)
	(if_then_else (leu (cc0)
			   (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bgeu\\t%1,%0,%2\\t# bleu\", br_ops);
  return \"\";
}
")

;; bleu inverted
(define_insn ""
  [(set (pc)
	(if_then_else (leu (cc0)
			   (const_int 0))
		      (pc)
		      (label_ref (match_operand 0 "" ""))))]
  ""
  "*
{
  rtx br_ops[3];
  enum machine_mode mode;
  compare_restore (br_ops, &mode, insn);
  br_ops[2] = operands[0];
  output_asm_insn (\"bltu\\t%1,%0,%2\\t# bleu inv\", br_ops);
  return \"\";
}
")


;;
;;  ....................
;;
;;          MOVES
;;
;;  ....................
;;

;; SImode moves (32-bit integer)
(define_insn "movsi"
  [(set (match_operand:SI 0 "general_operand" "=r,r,m,r")
	(match_operand:SI 1 "general_operand"  "r,i,r,m"))]
  ""
  "*
{
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == REG)
    return \"mv\\t%0,%1\";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == CONST_INT)
    {
      if (INTVAL (operands[1]) == 0)
        return \"mv\\t%0,zero\";
      if (SMALL_INT (operands[1]))
        return \"li\\t%0,%1\";
      return \"li\\t%0,%1\";
    }
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == MEM)
    return output_load (operands, \"w\");
  if (GET_CODE (operands[0]) == MEM && GET_CODE (operands[1]) == REG)
    return output_store (operands, \"w\");
  if (GET_CODE (operands[0]) == REG)
    {
      if (GET_CODE (operands[1]) == SYMBOL_REF
          || GET_CODE (operands[1]) == LABEL_REF
          || GET_CODE (operands[1]) == CONST)
        return \"la\\t%0,%1\";
      return \"li\\t%0,%1\";
    }
  abort ();
}
")

;; HImode moves (16-bit integer)
(define_insn "movhi"
  [(set (match_operand:HI 0 "general_operand" "=r,r,m,r")
	(match_operand:HI 1 "general_operand"  "r,i,r,m"))]
  ""
  "*
{
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == REG)
    {
      /* Sign-extend 16-bit value in register.  */
      output_asm_insn (\"slli\\t%0,%1,16\", operands);
      return \"srai\\t%0,%0,16\";
    }
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == CONST_INT)
    return \"li\\t%0,%1\";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == MEM)
    return output_load (operands, \"h\");
  if (GET_CODE (operands[0]) == MEM && GET_CODE (operands[1]) == REG)
    return output_store (operands, \"h\");
  if (GET_CODE (operands[0]) == REG)
    return \"li\\t%0,%1\";
  abort ();
}
")

;; QImode moves (8-bit integer)
(define_insn "movqi"
  [(set (match_operand:QI 0 "general_operand" "=r,r,m,r")
	(match_operand:QI 1 "general_operand"  "r,i,r,m"))]
  ""
  "*
{
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == REG)
    return \"andi\\t%0,%1,0xff\";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == CONST_INT)
    return \"li\\t%0,%1\";
  if (GET_CODE (operands[0]) == REG && GET_CODE (operands[1]) == MEM)
    return output_load (operands, \"b\");
  if (GET_CODE (operands[0]) == MEM && GET_CODE (operands[1]) == REG)
    return output_store (operands, \"b\");
  if (GET_CODE (operands[0]) == REG)
    return \"li\\t%0,%1\";
  abort ();
}
")

;; DImode moves (64-bit integer, two-word)
(define_insn "movdi"
  [(set (match_operand:DI 0 "general_operand" "=r,r,m")
	(match_operand:DI 1 "general_operand"  "r,im,r"))]
  ""
  "* return output_move_double (operands);")

;; SFmode moves (single-precision float)
(define_insn "movsf"
  [(set (match_operand:SF 0 "general_operand" "=f,f,m,r,f,r,r,m")
	(match_operand:SF 1 "general_operand"  "f,m,f,f,r,r,m,r"))]
  ""
  "*
{
  if (RTX_FP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        return \"fmv.s\\t%0,%1\";
      if (GET_CODE (operands[1]) == MEM)
        return \"flw\\t%0,%1\";
      if (RTX_GP_REG_P (operands[1]))
        return \"fmv.w.x\\t%0,%1\";
    }
  if (GET_CODE (operands[0]) == MEM)
    {
      if (RTX_FP_REG_P (operands[1]))
        return \"fsw\\t%1,%0\";
      if (RTX_GP_REG_P (operands[1]))
        return \"sw\\t%1,%0\";
    }
  if (RTX_GP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        return \"fmv.x.w\\t%0,%1\";
      if (RTX_GP_REG_P (operands[1]))
        return \"mv\\t%0,%1\";
      if (GET_CODE (operands[1]) == MEM)
        return \"lw\\t%0,%1\";
    }
  abort ();
}
")

;; DFmode moves (double-precision float)
;; Alternatives: f←f, f←m, m←f, r←im, m←r, r←f, f←r
;; The r←f and f←r cases go through memory (no direct 64-bit FP↔GP on RV32).
(define_insn "movdf"
  [(set (match_operand:DF 0 "general_operand" "=f,f,m,r,m,r,f")
	(match_operand:DF 1 "general_operand"  "f,m,f,im,r,f,r"))]
  ""
  "*
{
  if (RTX_FP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        return \"fmv.d\\t%0,%1\";
      if (GET_CODE (operands[1]) == MEM)
        return \"fld\\t%0,%1\";
      if (RTX_GP_REG_P (operands[1]))
        {
          /* FP ← GP pair: go through stack.  */
          output_asm_insn (\"addi\\tsp,sp,-8\", operands);
          output_asm_insn (\"sw\\t%1,0(sp)\", operands);
          output_asm_insn (\"sw\\t%D1,4(sp)\", operands);
          output_asm_insn (\"fld\\t%0,0(sp)\", operands);
          output_asm_insn (\"addi\\tsp,sp,8\", operands);
          return \"\";
        }
    }
  if (GET_CODE (operands[0]) == MEM)
    {
      if (RTX_FP_REG_P (operands[1]))
        return \"fsd\\t%1,%0\";
      if (RTX_GP_REG_P (operands[1]))
        return output_move_double (operands);
    }
  if (RTX_GP_REG_P (operands[0]))
    {
      if (RTX_FP_REG_P (operands[1]))
        {
          /* GP pair ← FP: go through stack.  */
          output_asm_insn (\"addi\\tsp,sp,-8\", operands);
          output_asm_insn (\"fsd\\t%1,0(sp)\", operands);
          output_asm_insn (\"lw\\t%0,0(sp)\", operands);
          output_asm_insn (\"lw\\t%D0,4(sp)\", operands);
          output_asm_insn (\"addi\\tsp,sp,8\", operands);
          return \"\";
        }
      return output_move_double (operands);
    }
  abort ();
}
")


;;
;;  ....................
;;
;;          TRUNCATION / EXTENSION
;;
;;  ....................
;;

;; truncsiqi2: truncate SI to QI (keep low 8 bits)
(define_insn "truncsiqi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
	(truncate:QI (match_operand:SI 1 "register_operand" "r")))]
  ""
  "andi %0,%1,0xff")

;; truncsihi2: truncate SI to HI (keep low 16 bits, sign-extend)
(define_insn "truncsihi2"
  [(set (match_operand:HI 0 "register_operand" "=r")
	(truncate:HI (match_operand:SI 1 "register_operand" "r")))]
  ""
  "slli %0,%1,16\n\tsrai\t%0,%0,16")

;; zero_extendhisi2: zero-extend HI to SI
(define_insn "zero_extendhisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(zero_extend:SI (match_operand:HI 1 "general_operand" "r,m")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM)
    return \"lhu\\t%0,%1\";
  /* From register: mask to 16 bits.  */
  output_asm_insn (\"slli\\t%0,%1,16\", operands);
  return \"srli\\t%0,%0,16\";
}
")

;; zero_extendqisi2: zero-extend QI to SI
(define_insn "zero_extendqisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(zero_extend:SI (match_operand:QI 1 "general_operand" "r,m")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM)
    return \"lbu\\t%0,%1\";
  return \"andi\\t%0,%1,0xff\";
}
")

;; zero_extendqihi2: zero-extend QI to HI
(define_insn "zero_extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
	(zero_extend:HI (match_operand:QI 1 "general_operand" "r,m")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM)
    return \"lbu\\t%0,%1\";
  return \"andi\\t%0,%1,0xff\";
}
")

;; extendqihi2: sign-extend QI to HI
(define_insn "extendqihi2"
  [(set (match_operand:HI 0 "register_operand" "=r,r")
	(sign_extend:HI (match_operand:QI 1 "general_operand" "r,m")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM)
    return \"lb\\t%0,%1\";
  output_asm_insn (\"slli\\t%0,%1,24\", operands);
  return \"srai\\t%0,%0,24\";
}
")

;; extendhisi2: sign-extend HI to SI
(define_insn "extendhisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(sign_extend:SI (match_operand:HI 1 "general_operand" "r,m")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM)
    return \"lh\\t%0,%1\";
  output_asm_insn (\"slli\\t%0,%1,16\", operands);
  return \"srai\\t%0,%0,16\";
}
")

;; extendqisi2: sign-extend QI to SI
(define_insn "extendqisi2"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
	(sign_extend:SI (match_operand:QI 1 "general_operand" "r,m")))]
  ""
  "*
{
  if (GET_CODE (operands[1]) == MEM)
    return \"lb\\t%0,%1\";
  output_asm_insn (\"slli\\t%0,%1,24\", operands);
  return \"srai\\t%0,%0,24\";
}
")

;; extendsfdf2: extend single to double float
(define_insn "extendsfdf2"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(float_extend:DF (match_operand:SF 1 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fcvt.d.s %0,%1")

;; truncdfsf2: truncate double to single float
(define_insn "truncdfsf2"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(float_truncate:SF (match_operand:DF 1 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fcvt.s.d %0,%1")


;;
;;  ....................
;;
;;          INTEGER ARITHMETIC
;;
;;  ....................
;;

;; Addition

;; Pattern for large constant addition (frame pointer / stack pointer)
(define_insn ""
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (match_operand:SI 1 "register_operand" "r")
		 (match_operand:SI 2 "immediate_operand" "i")))]
  "operands[1] == stack_pointer_rtx || operands[1] == frame_pointer_rtx"
  "*
{
  if (GET_CODE (operands[2]) != CONST_INT)
    return \"add\\t%0,%1,%2\";
  if (SMALL_INT (operands[2]))
    return \"addi\\t%0,%1,%2\";
  /* Large constant: use t0 as temp.  */
  return \"lui\\tt0,%%hi(%2)\\n\\taddi\\tt0,t0,%%lo(%2)\\n\\tadd\\t%0,%1,t0\";
}
")

(define_insn "addsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(plus:SI (match_operand:SI 1 "register_operand" "%r")
		 (match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"addi\\t%0,%1,%2\";
  return \"add\\t%0,%1,%2\";
}
")

;; Subtraction

;; Pattern for large constant subtraction
(define_insn ""
  [(set (match_operand:SI 0 "register_operand" "=r")
	(minus:SI (match_operand:SI 1 "register_operand" "r")
		  (match_operand:SI 2 "immediate_operand" "i")))]
  "operands[1] == stack_pointer_rtx || operands[1] == frame_pointer_rtx"
  "*
{
  if (GET_CODE (operands[2]) != CONST_INT)
    return \"sub\\t%0,%1,%2\";
  if (GET_CODE (operands[2]) == CONST_INT
      && (unsigned) (-INTVAL (operands[2]) + 0x800) < 0x1000)
    {
      operands[2] = gen_rtx (CONST_INT, VOIDmode, -INTVAL (operands[2]));
      return \"addi\\t%0,%1,%2\";
    }
  return \"lui\\tt0,%%hi(%2)\\n\\taddi\\tt0,t0,%%lo(%2)\\n\\tsub\\t%0,%1,t0\";
}
")

(define_insn "subsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(minus:SI (match_operand:SI 1 "register_operand" "r")
		  (match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    {
      operands[2] = gen_rtx (CONST_INT, VOIDmode, -INTVAL (operands[2]));
      return \"addi\\t%0,%1,%2\";
    }
  return \"sub\\t%0,%1,%2\";
}
")

;; Multiplication (RV32M)
(define_insn "mulsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mult:SI (match_operand:SI 1 "register_operand" "r")
		 (match_operand:SI 2 "register_operand" "r")))]
  ""
  "mul %0,%1,%2")

;; Division (RV32M)
(define_insn "divsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(div:SI (match_operand:SI 1 "register_operand" "r")
		(match_operand:SI 2 "register_operand" "r")))]
  ""
  "div %0,%1,%2")

(define_insn "udivsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(udiv:SI (match_operand:SI 1 "register_operand" "r")
		 (match_operand:SI 2 "register_operand" "r")))]
  ""
  "divu %0,%1,%2")

;; Modulus (RV32M)
(define_insn "modsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(mod:SI (match_operand:SI 1 "register_operand" "r")
		(match_operand:SI 2 "register_operand" "r")))]
  ""
  "rem %0,%1,%2")

(define_insn "umodsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(umod:SI (match_operand:SI 1 "register_operand" "r")
		 (match_operand:SI 2 "register_operand" "r")))]
  ""
  "remu %0,%1,%2")

;; Negate
(define_insn "negsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(neg:SI (match_operand:SI 1 "register_operand" "r")))]
  ""
  "neg %0,%1")


;; Logical operations

(define_insn "andsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(and:SI (match_operand:SI 1 "register_operand" "%r")
		(match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"andi\\t%0,%1,%2\";
  return \"and\\t%0,%1,%2\";
}
")

(define_insn "iorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(ior:SI (match_operand:SI 1 "register_operand" "%r")
		(match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"ori\\t%0,%1,%2\";
  return \"or\\t%0,%1,%2\";
}
")

(define_insn "xorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(xor:SI (match_operand:SI 1 "register_operand" "%r")
		(match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"xori\\t%0,%1,%2\";
  return \"xor\\t%0,%1,%2\";
}
")

;; One's complement
(define_insn "one_cmplsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(not:SI (match_operand:SI 1 "register_operand" "r")))]
  ""
  "not %0,%1")


;;
;;  ....................
;;
;;          SHIFTS
;;
;;  ....................
;;

(define_insn "ashlsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(ashift:SI (match_operand:SI 1 "register_operand" "r")
		   (match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"slli\\t%0,%1,%2\";
  return \"sll\\t%0,%1,%2\";
}
")

(define_insn "ashrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(ashiftrt:SI (match_operand:SI 1 "register_operand" "r")
		     (match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"srai\\t%0,%1,%2\";
  return \"sra\\t%0,%1,%2\";
}
")

(define_insn "lshrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(lshiftrt:SI (match_operand:SI 1 "register_operand" "r")
		     (match_operand:SI 2 "arith_operand" "rI")))]
  ""
  "*
{
  if (GET_CODE (operands[2]) == CONST_INT)
    return \"srli\\t%0,%1,%2\";
  return \"srl\\t%0,%1,%2\";
}
")


;;
;;  ....................
;;
;;          FLOATING POINT ARITHMETIC
;;
;;  ....................
;;

;; Single-precision FP arithmetic

(define_insn "addsf3"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(plus:SF (match_operand:SF 1 "register_operand" "f")
		 (match_operand:SF 2 "register_operand" "f")))]
  "TARGET_FPU"
  "fadd.s %0,%1,%2")

(define_insn "subsf3"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(minus:SF (match_operand:SF 1 "register_operand" "f")
		  (match_operand:SF 2 "register_operand" "f")))]
  "TARGET_FPU"
  "fsub.s %0,%1,%2")

(define_insn "mulsf3"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(mult:SF (match_operand:SF 1 "register_operand" "f")
		 (match_operand:SF 2 "register_operand" "f")))]
  "TARGET_FPU"
  "fmul.s %0,%1,%2")

(define_insn "divsf3"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(div:SF (match_operand:SF 1 "register_operand" "f")
		(match_operand:SF 2 "register_operand" "f")))]
  "TARGET_FPU"
  "fdiv.s %0,%1,%2")

(define_insn "negsf2"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(neg:SF (match_operand:SF 1 "register_operand" "f")))]
  "TARGET_FPU"
  "fneg.s %0,%1")

(define_insn "abssf2"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(abs:SF (match_operand:SF 1 "register_operand" "f")))]
  "TARGET_FPU"
  "fabs.s %0,%1")


;; Double-precision FP arithmetic

(define_insn "adddf3"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(plus:DF (match_operand:DF 1 "register_operand" "f")
		 (match_operand:DF 2 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fadd.d %0,%1,%2")

(define_insn "subdf3"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(minus:DF (match_operand:DF 1 "register_operand" "f")
		  (match_operand:DF 2 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fsub.d %0,%1,%2")

(define_insn "muldf3"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(mult:DF (match_operand:DF 1 "register_operand" "f")
		 (match_operand:DF 2 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fmul.d %0,%1,%2")

(define_insn "divdf3"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(div:DF (match_operand:DF 1 "register_operand" "f")
		(match_operand:DF 2 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fdiv.d %0,%1,%2")

(define_insn "negdf2"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(neg:DF (match_operand:DF 1 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fneg.d %0,%1")

(define_insn "absdf2"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(abs:DF (match_operand:DF 1 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fabs.d %0,%1")


;;
;;  ....................
;;
;;          FP CONVERSIONS
;;
;;  ....................
;;

;; Integer to float
(define_insn "floatsisf2"
  [(set (match_operand:SF 0 "register_operand" "=f")
	(float:SF (match_operand:SI 1 "register_operand" "r")))]
  "TARGET_FPU"
  "fcvt.s.w %0,%1")

(define_insn "floatsidf2"
  [(set (match_operand:DF 0 "register_operand" "=f")
	(float:DF (match_operand:SI 1 "register_operand" "r")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fcvt.d.w %0,%1")

;; Float to integer (truncating)
(define_insn "fix_truncsfsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(fix:SI (match_operand:SF 1 "register_operand" "f")))]
  "TARGET_FPU"
  "fcvt.w.s %0,%1,rtz")

(define_insn "fix_truncdfsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(fix:SI (match_operand:DF 1 "register_operand" "f")))]
  "TARGET_FPU && TARGET_HARD_FLOAT_D"
  "fcvt.w.d %0,%1,rtz")


;;
;;  ....................
;;
;;          FUNCTION CALLS
;;
;;  ....................
;;

(define_insn "call"
  [(call (match_operand 0 "memory_operand" "m")
	 (match_operand 1 "" "i"))]
  ""
  "*
{
  register rtx target = XEXP (operands[0], 0);
  if (GET_CODE (target) == SYMBOL_REF)
    return \"call\\t%0\";
  else
    return \"jalr\\tra,%0\";
}
")

(define_insn "call_value"
  [(set (match_operand 0 "" "=rf")
	(call (match_operand 1 "memory_operand" "m")
	      (match_operand 2 "" "i")))]
  ""
  "*
{
  register rtx target = XEXP (operands[1], 0);
  if (GET_CODE (target) == SYMBOL_REF)
    return \"call\\t%1\";
  else
    return \"jalr\\tra,%1\";
}
")


;; Return
;; No "return" insn -- function returns fall through to FUNCTION_EPILOGUE
;; which restores callee-saved registers and emits ret.

;; Nop
(define_insn "nop"
  [(const_int 0)]
  ""
  "nop")


;; Indirect jump (for computed goto, longjmp, etc.)
(define_insn "indirect_jump"
  [(set (pc)
	(match_operand:SI 0 "register_operand" "r"))]
  ""
  "jr %0")
