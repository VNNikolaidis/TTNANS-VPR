/*
  ---------------------
  TTNANS:
  ---------------------
  Vasilis.N.Nikolaidis
  --------------------------
  Additional Definitions for some compilers
  (e.g. MS Visual C++ 5.0 compiler) that
  do not fit elsewhere.
  --------------------------
*/

#include "ttndef.h"

#ifdef _MY_RANDOM_

#include <stdlib.h>

void randomize(void)
{}


int random(int hi)
{
if (hi<=0) return 0;
return ((int)(rand()%hi));
/*assert(ret);return ret;*/
}

#endif
