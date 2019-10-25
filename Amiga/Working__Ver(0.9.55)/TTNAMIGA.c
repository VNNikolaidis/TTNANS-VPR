/*
  ---------------------
  TTNANS:
  TTNAMIGA.C   ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  --------------------------
  Additional Definitions for
  AMIGA's SASC compiler that
  do not fit elsewhere.
  --------------------------
*/

#include "TTNDEF.hpp"

#ifdef _AMIGA_

#include "ttnbool.hpp"
#include <time.h>                                      /* for rand().    */
#include <math.h>                                      /* for drand48(). */

int ten_to_power(int x)                       /* cruel, I am in a hurry! */
{
if(x<=0)return 1;
if(x==1)return 10;
return 10*ten_to_power(x-1);
}


/*-----------------------------------------------------------------------*/

void randomize(void)
{}

/*
int random(int hi)
{
if (hi<=0) return 0;
return (int)(RAND_MAX/rand())%hi;
}
*/

int random(int hi)
{
if (hi<=0) return 0;
return (int)(drand48()*hi*hi)%hi; /* see drand48() (uniform 0..1) (unix) */
}

/*-----------------------------------------------------------------------*/

void itoa(int orignum, char * dest, int base)
{
int i=0,j=1;
int r,num;

if(base!=10) mprintf("Warning: this version of itoa is base 10 only.\n");

num=orignum;

if(num<0)
 {
 dest[i]='-';
 i++;
 num=-num;
 }

if(num==0)
 {
 dest[i]='0';
 i++;
 }
else
 {
 while(num>=ten_to_power(j)) j++;
 j--;
 while(j>=0)
  {
  r=(int)num/ten_to_power(j);
  num=num%ten_to_power(j);
  dest[i]=(char)(48+r);
  i++;
  j--;
  }
 }
dest[i]='\0';
}

#endif

