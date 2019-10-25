/*
  ---------------------
  TTNANS:
  TTNTHRES.C    ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ------------------------
  NODE threshold functions
  for various ANS schemes.
  ------------------------

*/

#include "ttndef.h"
#include "ttndef_o.h"
#include "ttndef_n.h"

#include <math.h>

/* square root. Used in KNC,LVQ */

DATA th_square_root (NODE * np, int stmid)
{
return (DATA)(sqrt(np->stm[stmid]));
}