/* Generated automatically by the program `genrecog'
from the machine description file `md'.  */

#include "config.h"
#include "rtl.h"
#include "insn-config.h"
#include "recog.h"
#include "real.h"

/* `recog' contains a decision tree
   that recognizes whether the rtx X0 is a valid instruction.

   recog returns -1 if the rtx is not valid.
   If the rtx is valid, recog returns a nonnegative number
   which is the insn code number for the pattern that matched.
   This is the same as the order in the machine description of
   the entry that matched.  This number can be used as an index into
   insn_templates and insn_n_operands (found in insn-output.c)
   or as an argument to output_insn_hairy (also in insn-output.c).  */

rtx recog_operand[MAX_RECOG_OPERANDS];

rtx *recog_operand_loc[MAX_RECOG_OPERANDS];

rtx *recog_dup_loc[MAX_DUP_OPERANDS];

char recog_dup_num[MAX_DUP_OPERANDS];

extern rtx recog_addr_dummy;

#define operands recog_operand

int
recog_1 (x0, insn)
     register rtx x0;
     rtx insn;
{
  register rtx x1, x2, x3, x4, x5;
  rtx x6, x7, x8, x9, x10, x11;
  int tem;
 L32:
  x1 = XEXP (x0, 1);
  x2 = XEXP (x1, 0);
 switch (GET_CODE (x2))
  {
  case EQ:
  if (1)
    goto L33;
  break;
  case NE:
  if (1)
    goto L51;
  break;
  case LT:
  if (1)
    goto L69;
  break;
  case GE:
  if (1)
    goto L87;
  break;
  case GT:
  if (1)
    goto L105;
  break;
  case LE:
  if (1)
    goto L123;
  break;
  case LTU:
  if (1)
    goto L141;
  break;
  case GEU:
  if (1)
    goto L159;
  break;
  case GTU:
  if (1)
    goto L177;
  break;
  case LEU:
  if (1)
    goto L195;
  break;
  }
  goto ret0;
 L33:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L34;
  goto ret0;
 L34:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L35;
  goto ret0;
 L35:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L36;
  if (x2 == pc_rtx && 1)
    goto L45;
  goto ret0;
 L36:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L37; }
  goto ret0;
 L37:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 6;
  goto ret0;
 L45:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L46;
  goto ret0;
 L46:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 7; }
  goto ret0;
 L51:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L52;
  goto ret0;
 L52:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L53;
  goto ret0;
 L53:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L54;
  if (x2 == pc_rtx && 1)
    goto L63;
  goto ret0;
 L54:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L55; }
  goto ret0;
 L55:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 8;
  goto ret0;
 L63:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L64;
  goto ret0;
 L64:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 9; }
  goto ret0;
 L69:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L70;
  goto ret0;
 L70:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L71;
  goto ret0;
 L71:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L72;
  if (x2 == pc_rtx && 1)
    goto L81;
  goto ret0;
 L72:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L73; }
  goto ret0;
 L73:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 10;
  goto ret0;
 L81:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L82;
  goto ret0;
 L82:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 11; }
  goto ret0;
 L87:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L88;
  goto ret0;
 L88:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L89;
  goto ret0;
 L89:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L90;
  if (x2 == pc_rtx && 1)
    goto L99;
  goto ret0;
 L90:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L91; }
  goto ret0;
 L91:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 12;
  goto ret0;
 L99:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L100;
  goto ret0;
 L100:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 13; }
  goto ret0;
 L105:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L106;
  goto ret0;
 L106:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L107;
  goto ret0;
 L107:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L108;
  if (x2 == pc_rtx && 1)
    goto L117;
  goto ret0;
 L108:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L109; }
  goto ret0;
 L109:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 14;
  goto ret0;
 L117:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L118;
  goto ret0;
 L118:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 15; }
  goto ret0;
 L123:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L124;
  goto ret0;
 L124:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L125;
  goto ret0;
 L125:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L126;
  if (x2 == pc_rtx && 1)
    goto L135;
  goto ret0;
 L126:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L127; }
  goto ret0;
 L127:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 16;
  goto ret0;
 L135:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L136;
  goto ret0;
 L136:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 17; }
  goto ret0;
 L141:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L142;
  goto ret0;
 L142:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L143;
  goto ret0;
 L143:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L144;
  if (x2 == pc_rtx && 1)
    goto L153;
  goto ret0;
 L144:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L145; }
  goto ret0;
 L145:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 18;
  goto ret0;
 L153:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L154;
  goto ret0;
 L154:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 19; }
  goto ret0;
 L159:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L160;
  goto ret0;
 L160:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L161;
  goto ret0;
 L161:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L162;
  if (x2 == pc_rtx && 1)
    goto L171;
  goto ret0;
 L162:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L163; }
  goto ret0;
 L163:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 20;
  goto ret0;
 L171:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L172;
  goto ret0;
 L172:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 21; }
  goto ret0;
 L177:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L178;
  goto ret0;
 L178:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L179;
  goto ret0;
 L179:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L180;
  if (x2 == pc_rtx && 1)
    goto L189;
  goto ret0;
 L180:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L181; }
  goto ret0;
 L181:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 22;
  goto ret0;
 L189:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L190;
  goto ret0;
 L190:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 23; }
  goto ret0;
 L195:
  x3 = XEXP (x2, 0);
  if (x3 == cc0_rtx && 1)
    goto L196;
  goto ret0;
 L196:
  x3 = XEXP (x2, 1);
  if (x3 == const0_rtx && 1)
    goto L197;
  goto ret0;
 L197:
  x2 = XEXP (x1, 1);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L198;
  if (x2 == pc_rtx && 1)
    goto L207;
  goto ret0;
 L198:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; goto L199; }
  goto ret0;
 L199:
  x2 = XEXP (x1, 2);
  if (x2 == pc_rtx && 1)
    return 24;
  goto ret0;
 L207:
  x2 = XEXP (x1, 2);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L208;
  goto ret0;
 L208:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[0] = x3; return 25; }
  goto ret0;
 ret0: return -1;
}

int
recog_2 (x0, insn)
     register rtx x0;
     rtx insn;
{
  register rtx x1, x2, x3, x4, x5;
  rtx x6, x7, x8, x9, x10, x11;
  int tem;
 L237:
  x1 = XEXP (x0, 1);
  if (GET_MODE (x1) != SImode)
    goto ret0;
 switch (GET_CODE (x1))
  {
  case ZERO_EXTEND:
  if (1)
    goto L238;
  break;
  case SIGN_EXTEND:
  if (1)
    goto L254;
  break;
  case PLUS:
  if (1)
    goto L270;
  break;
  case MINUS:
  if (1)
    goto L280;
  break;
  case MULT:
  if (1)
    goto L290;
  break;
  case DIV:
  if (1)
    goto L295;
  break;
  case UDIV:
  if (1)
    goto L300;
  break;
  case MOD:
  if (1)
    goto L305;
  break;
  case UMOD:
  if (1)
    goto L310;
  break;
  case NEG:
  if (1)
    goto L315;
  break;
  case AND:
  if (1)
    goto L319;
  break;
  case IOR:
  if (1)
    goto L324;
  break;
  case XOR:
  if (1)
    goto L329;
  break;
  case NOT:
  if (1)
    goto L334;
  break;
  case ASHIFT:
  if (1)
    goto L338;
  break;
  case ASHIFTRT:
  if (1)
    goto L343;
  break;
  case LSHIFTRT:
  if (1)
    goto L348;
  break;
  case FIX:
  if (1)
    goto L417;
  break;
  }
  goto ret0;
 L238:
  x2 = XEXP (x1, 0);
  if (general_operand (x2, HImode))
    { recog_operand[1] = x2; return 34; }
 L242:
  if (general_operand (x2, QImode))
    { recog_operand[1] = x2; return 35; }
  goto ret0;
 L254:
  x2 = XEXP (x1, 0);
  if (general_operand (x2, HImode))
    { recog_operand[1] = x2; return 38; }
 L258:
  if (general_operand (x2, QImode))
    { recog_operand[1] = x2; return 39; }
  goto ret0;
 L270:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L271; }
  goto ret0;
 L271:
  x2 = XEXP (x1, 1);
  if (immediate_operand (x2, SImode))
    { recog_operand[2] = x2; if (operands[1] == stack_pointer_rtx || operands[1] == frame_pointer_rtx) return 42; }
 L276:
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 43; }
  goto ret0;
 L280:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L281; }
  goto ret0;
 L281:
  x2 = XEXP (x1, 1);
  if (immediate_operand (x2, SImode))
    { recog_operand[2] = x2; if (operands[1] == stack_pointer_rtx || operands[1] == frame_pointer_rtx) return 44; }
 L286:
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 45; }
  goto ret0;
 L290:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L291; }
  goto ret0;
 L291:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    { recog_operand[2] = x2; return 46; }
  goto ret0;
 L295:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L296; }
  goto ret0;
 L296:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    { recog_operand[2] = x2; return 47; }
  goto ret0;
 L300:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L301; }
  goto ret0;
 L301:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    { recog_operand[2] = x2; return 48; }
  goto ret0;
 L305:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L306; }
  goto ret0;
 L306:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    { recog_operand[2] = x2; return 49; }
  goto ret0;
 L310:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L311; }
  goto ret0;
 L311:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    { recog_operand[2] = x2; return 50; }
  goto ret0;
 L315:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; return 51; }
  goto ret0;
 L319:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L320; }
  goto ret0;
 L320:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 52; }
  goto ret0;
 L324:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L325; }
  goto ret0;
 L325:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 53; }
  goto ret0;
 L329:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L330; }
  goto ret0;
 L330:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 54; }
  goto ret0;
 L334:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; return 55; }
  goto ret0;
 L338:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L339; }
  goto ret0;
 L339:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 56; }
  goto ret0;
 L343:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L344; }
  goto ret0;
 L344:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 57; }
  goto ret0;
 L348:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; goto L349; }
  goto ret0;
 L349:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[2] = x2; return 58; }
  goto ret0;
 L417:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; if (TARGET_FPU) return 73; }
 L421:
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 74; }
  goto ret0;
 ret0: return -1;
}

int
recog_3 (x0, insn)
     register rtx x0;
     rtx insn;
{
  register rtx x1, x2, x3, x4, x5;
  rtx x6, x7, x8, x9, x10, x11;
  int tem;
 L1:
  x1 = XEXP (x0, 0);
  if (x1 == cc0_rtx && 1)
    goto L2;
  if (x1 == pc_rtx && 1)
    goto L20;
 L426:
  if (1)
    { recog_operand[0] = x1; goto L427; }
 L216:
 switch (GET_MODE (x1))
  {
  case QImode:
  if (general_operand (x1, QImode))
    { recog_operand[0] = x1; goto L217; }
 L228:
  if (register_operand (x1, QImode))
    { recog_operand[0] = x1; goto L229; }
  break;
  case HImode:
  if (general_operand (x1, HImode))
    { recog_operand[0] = x1; goto L214; }
 L232:
  if (register_operand (x1, HImode))
    { recog_operand[0] = x1; goto L233; }
  break;
  case SImode:
  if (general_operand (x1, SImode))
    { recog_operand[0] = x1; goto L211; }
 L236:
  if (register_operand (x1, SImode))
    { recog_operand[0] = x1; goto L237; }
  break;
  case DImode:
  if (general_operand (x1, DImode))
    { recog_operand[0] = x1; goto L220; }
  break;
  case SFmode:
  if (general_operand (x1, SFmode))
    { recog_operand[0] = x1; goto L223; }
 L264:
  if (register_operand (x1, SFmode))
    { recog_operand[0] = x1; goto L265; }
  break;
  case DFmode:
  if (general_operand (x1, DFmode))
    { recog_operand[0] = x1; goto L226; }
 L260:
  if (register_operand (x1, DFmode))
    { recog_operand[0] = x1; goto L261; }
  break;
  }
  goto ret0;
 L2:
  x1 = XEXP (x0, 1);
  if (GET_CODE (x1) == COMPARE && 1)
    goto L3;
 L7:
  if (register_operand (x1, SImode))
    { recog_operand[0] = x1; return 1; }
  x1 = XEXP (x0, 0);
  goto L426;
 L3:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[0] = x2; goto L4; }
 L11:
  if (register_operand (x2, SFmode))
    { recog_operand[0] = x2; goto L12; }
 L16:
  if (register_operand (x2, DFmode))
    { recog_operand[0] = x2; goto L17; }
  goto L7;
 L4:
  x2 = XEXP (x1, 1);
  if (arith_operand (x2, SImode))
    { recog_operand[1] = x2; return 0; }
  x2 = XEXP (x1, 0);
  goto L11;
 L12:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; if (TARGET_FPU) return 2; }
  x2 = XEXP (x1, 0);
  goto L16;
 L17:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 3; }
  goto L7;
 L20:
  x1 = XEXP (x0, 1);
  if (GET_CODE (x1) == LABEL_REF && 1)
    goto L21;
  if (GET_CODE (x1) == IF_THEN_ELSE && 1)
    goto L32;
 L433:
  if (register_operand (x1, SImode))
    { recog_operand[0] = x1; return 78; }
  x1 = XEXP (x0, 0);
  goto L426;
 L21:
  x2 = XEXP (x1, 0);
  if (1)
    { recog_operand[0] = x2; return 4; }
  goto L433;
 L32:
  tem = recog_1 (x0, insn);
  if (tem >= 0) return tem;
  goto L433;
 L427:
  x1 = XEXP (x0, 1);
  if (GET_CODE (x1) == CALL && 1)
    goto L428;
  x1 = XEXP (x0, 0);
  goto L216;
 L428:
  x2 = XEXP (x1, 0);
  if (memory_operand (x2, VOIDmode))
    { recog_operand[1] = x2; goto L429; }
  x1 = XEXP (x0, 0);
  goto L216;
 L429:
  x2 = XEXP (x1, 1);
  if (1)
    { recog_operand[2] = x2; return 76; }
  x1 = XEXP (x0, 0);
  goto L216;
 L217:
  x1 = XEXP (x0, 1);
  if (general_operand (x1, QImode))
    { recog_operand[1] = x1; return 28; }
  x1 = XEXP (x0, 0);
  goto L228;
 L229:
  x1 = XEXP (x0, 1);
  if (GET_CODE (x1) == TRUNCATE && GET_MODE (x1) == QImode && 1)
    goto L230;
  goto ret0;
 L230:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; return 32; }
  goto ret0;
 L214:
  x1 = XEXP (x0, 1);
  if (general_operand (x1, HImode))
    { recog_operand[1] = x1; return 27; }
  x1 = XEXP (x0, 0);
  goto L232;
 L233:
  x1 = XEXP (x0, 1);
  if (GET_MODE (x1) != HImode)
    goto ret0;
  if (GET_CODE (x1) == TRUNCATE && 1)
    goto L234;
  if (GET_CODE (x1) == ZERO_EXTEND && 1)
    goto L246;
  if (GET_CODE (x1) == SIGN_EXTEND && 1)
    goto L250;
  goto ret0;
 L234:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; return 33; }
  goto ret0;
 L246:
  x2 = XEXP (x1, 0);
  if (general_operand (x2, QImode))
    { recog_operand[1] = x2; return 36; }
  goto ret0;
 L250:
  x2 = XEXP (x1, 0);
  if (general_operand (x2, QImode))
    { recog_operand[1] = x2; return 37; }
  goto ret0;
 L211:
  x1 = XEXP (x0, 1);
  if (general_operand (x1, SImode))
    { recog_operand[1] = x1; return 26; }
  x1 = XEXP (x0, 0);
  goto L236;
 L237:
  return recog_2 (x0, insn);
 L220:
  x1 = XEXP (x0, 1);
  if (general_operand (x1, DImode))
    { recog_operand[1] = x1; return 29; }
  goto ret0;
 L223:
  x1 = XEXP (x0, 1);
  if (general_operand (x1, SFmode))
    { recog_operand[1] = x1; return 30; }
  x1 = XEXP (x0, 0);
  goto L264;
 L265:
  x1 = XEXP (x0, 1);
  if (GET_MODE (x1) != SFmode)
    goto ret0;
 switch (GET_CODE (x1))
  {
  case FLOAT_TRUNCATE:
  if (1)
    goto L266;
  break;
  case PLUS:
  if (1)
    goto L353;
  break;
  case MINUS:
  if (1)
    goto L358;
  break;
  case MULT:
  if (1)
    goto L363;
  break;
  case DIV:
  if (1)
    goto L368;
  break;
  case NEG:
  if (1)
    goto L373;
  break;
  case ABS:
  if (1)
    goto L377;
  break;
  case FLOAT:
  if (1)
    goto L409;
  break;
  }
  goto ret0;
 L266:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 41; }
  goto ret0;
 L353:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; goto L354; }
  goto ret0;
 L354:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SFmode))
    { recog_operand[2] = x2; if (TARGET_FPU) return 59; }
  goto ret0;
 L358:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; goto L359; }
  goto ret0;
 L359:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SFmode))
    { recog_operand[2] = x2; if (TARGET_FPU) return 60; }
  goto ret0;
 L363:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; goto L364; }
  goto ret0;
 L364:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SFmode))
    { recog_operand[2] = x2; if (TARGET_FPU) return 61; }
  goto ret0;
 L368:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; goto L369; }
  goto ret0;
 L369:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SFmode))
    { recog_operand[2] = x2; if (TARGET_FPU) return 62; }
  goto ret0;
 L373:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; if (TARGET_FPU) return 63; }
  goto ret0;
 L377:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; if (TARGET_FPU) return 64; }
  goto ret0;
 L409:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; if (TARGET_FPU) return 71; }
  goto ret0;
 L226:
  x1 = XEXP (x0, 1);
  if (general_operand (x1, DFmode))
    { recog_operand[1] = x1; return 31; }
  x1 = XEXP (x0, 0);
  goto L260;
 L261:
  x1 = XEXP (x0, 1);
  if (GET_MODE (x1) != DFmode)
    goto ret0;
 switch (GET_CODE (x1))
  {
  case FLOAT_EXTEND:
  if (1)
    goto L262;
  break;
  case PLUS:
  if (1)
    goto L381;
  break;
  case MINUS:
  if (1)
    goto L386;
  break;
  case MULT:
  if (1)
    goto L391;
  break;
  case DIV:
  if (1)
    goto L396;
  break;
  case NEG:
  if (1)
    goto L401;
  break;
  case ABS:
  if (1)
    goto L405;
  break;
  case FLOAT:
  if (1)
    goto L413;
  break;
  }
  goto ret0;
 L262:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SFmode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 40; }
  goto ret0;
 L381:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; goto L382; }
  goto ret0;
 L382:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, DFmode))
    { recog_operand[2] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 65; }
  goto ret0;
 L386:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; goto L387; }
  goto ret0;
 L387:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, DFmode))
    { recog_operand[2] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 66; }
  goto ret0;
 L391:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; goto L392; }
  goto ret0;
 L392:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, DFmode))
    { recog_operand[2] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 67; }
  goto ret0;
 L396:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; goto L397; }
  goto ret0;
 L397:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, DFmode))
    { recog_operand[2] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 68; }
  goto ret0;
 L401:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 69; }
  goto ret0;
 L405:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, DFmode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 70; }
  goto ret0;
 L413:
  x2 = XEXP (x1, 0);
  if (register_operand (x2, SImode))
    { recog_operand[1] = x2; if (TARGET_FPU && TARGET_HARD_FLOAT_D) return 72; }
  goto ret0;
 ret0: return -1;
}

int
recog (x0, insn)
     register rtx x0;
     rtx insn;
{
  register rtx x1, x2, x3, x4, x5;
  rtx x6, x7, x8, x9, x10, x11;
  int tem;
 L0:
 switch (GET_CODE (x0))
  {
  case SET:
  if (1)
    goto L1;
  break;
  case PARALLEL:
  if (XVECLEN (x0, 0) == 2 && 1)
    goto L23;
  break;
  case CALL:
  if (1)
    goto L423;
  break;
  case CONST_INT:
  if (x0 == const0_rtx && 1)
    return 77;
  break;
  }
  goto ret0;
 L1:
  return recog_3 (x0, insn);
 L23:
  x1 = XVECEXP (x0, 0, 0);
  if (GET_CODE (x1) == SET && 1)
    goto L24;
  goto ret0;
 L24:
  x2 = XEXP (x1, 0);
  if (x2 == pc_rtx && 1)
    goto L25;
  goto ret0;
 L25:
  x2 = XEXP (x1, 1);
  if (register_operand (x2, SImode))
    { recog_operand[0] = x2; goto L26; }
  goto ret0;
 L26:
  x1 = XVECEXP (x0, 0, 1);
  if (GET_CODE (x1) == USE && 1)
    goto L27;
  goto ret0;
 L27:
  x2 = XEXP (x1, 0);
  if (GET_CODE (x2) == LABEL_REF && 1)
    goto L28;
  goto ret0;
 L28:
  x3 = XEXP (x2, 0);
  if (1)
    { recog_operand[1] = x3; return 5; }
  goto ret0;
 L423:
  x1 = XEXP (x0, 0);
  if (memory_operand (x1, VOIDmode))
    { recog_operand[0] = x1; goto L424; }
  goto ret0;
 L424:
  x1 = XEXP (x0, 1);
  if (1)
    { recog_operand[1] = x1; return 75; }
  goto ret0;
 ret0: return -1;
}
