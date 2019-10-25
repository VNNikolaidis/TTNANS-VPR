/*
  ---------------------
  TTNANS:
  TTNUI.C      ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  User Interface.
  ---------------------

*/

//#define TTNUI                                   /* don't include TTNUI.H */

/*

- ttnui includes functions like:

extern int  mprintf(const char * __format,...);
extern int  mprint_(const char * text);
extern int  mhintf(bool addtosessionfile, const char * __format,...);
extern void mhintclear();
extern void mforcedisplay(void);
extern void mcls(void);
extern void mbeep(void);
extern void mwait(void);
extern void mstarttick(char * message);
extern void mtick(int cur,int max);
extern void mendtick(void);
extern bool mrequest_yn(char * tx);
extern int  mrequest_int(char * tx);
extern DATA mrequest_DATA(char * tx);
extern int  mmenu(char * mtitle, char ** mlist,int mitems, int maxsel);
extern void mplot_bar(DATA data[],int datasize,DATA maxindata);                    

*/

#include "ttndef.h"

#ifdef _CONSOLE

#include "ttnpros.h"
#include "ttnmain.h"
#include "ttnbool.h"
#include "ttnreprt.h"
#include "ttnmemor.h"

#include <ctype.h>

#include "ttnpros.h"
#include <stdarg.h>			// ANSI-style variable arguments.
#define BELL 7

/*-----------------------------------------------------------------------*/

int mprintf(const char * __format,...)
{
char buff[255];

va_list ap;

va_start(ap,__format);
vsprintf(buff,__format, ap);
va_end(ap);

printf("%s",buff);
ReportToSessionFile(buff);
return 1;
}

/*-----------------------------------------------------------------------*/

int  mprint_(const char * text)
{return mprintf(text);}

/*-----------------------------------------------------------------------*/

int  mhintf(bool ShowAndAddToSessionFile, const char * __format,...)
{
char buff[255];

if(ShowAndAddToSessionFile)
 {
 va_list ap;

 va_start(ap,__format);
 vsprintf(buff,__format, ap);
 va_end(ap);

 printf(buff);

//if(addtosessionfile)
 ReportToSessionFile(buff);
 }
return 1;
}

/*-----------------------------------------------------------------------*/

void mhintclear()
{
//printf("\n");
}

/*-----------------------------------------------------------------------*/

void mforcedisplay(void)
{
/* mprintf("<End_Of_Paragraph>\n");  */
}

void mcls(void)
{
for(unsigned i=0;i<100;i++) printf("\n");
/*clrscr();*/
}

void mbeep(void)
{
mprintf("%c",BELL);
}

void mwait(void)
{
int i;

fflush(stdin);
mprintf("\nPress a key to continue....");
i=getchar();
mprintf("%c\n",i);
}

/*-----------------------------------------------------------------------*/

BOOL mrequest_yn(char * tx)             /* a basic yes/no request can be */
{                                       /* replaced by GUI one.          */
char c;

mprintf("%s",tx);
mprintf(" (Y/N)? ");
for(;;)
 {
 c=(char)getc(stdin);
 if((c=='y')||(c=='Y')) {mprintf("(YES)\n");return TRUE;}
 if((c=='n')||(c=='N')) {mprintf("(NO) \n");return FALSE;}
 }
}

/*-----------------------------------------------------------------------*/

void mmessage(char * tx)				/* MessageBox-type output if UI. */
{
mprintf("%s",tx);
}

/*-----------------------------------------------------------------------*/

int mrequest_int(char * tx)             /* a basic int request can be    */
{                                       /* replaced by GUI one.          */
int c;
BOOL found;

mprintf("%s (integer) : ",tx);

found=FALSE;
while(!found)                           /* Skip non-digit input.         */
 {
 c=getc(stdin);
 if(isdigit(c)||(c=='+')||(c=='-'))
  {
  ungetc(c,stdin);
  found=TRUE;
  }
 }
scanf("%d",&c);
mprintf("(%d)\n",c);
return c;
}

/*-----------------------------------------------------------------------*/

DATA mrequest_DATA(char * tx)           /* a basic DATA request can be   */
{                                       /* replaced by GUI one.          */
DATA c;
mprintf("%s (",tx);
mprintf(DATADESCRI);
mprintf(") : ");
scanf(DATAFORMAT,&c);
mprintf("(");
mprintf(DATAFORMAT,c);
mprintf(")\n");
return c;
}

/*-----------------------------------------------------------------------*/
int  mmenu(char * mtitle, char ** mlist,int mitems, int maxsel)
{
int i,s=-1;

if(NOT(TGBL no_error)) return 0;		// On error select 0 - exit.

mprintf("\n\n  ## %s ##  \n",mtitle);

while((s<0)||(s>maxsel))
 {
 mprintf("\n");
 for(i=0;i<mitems;i++)
  mprintf("%s\n",mlist[i]);
 mprintf("\n");
 s=mrequest_int("Please enter selection : ");
 }
mcls();
mprintf("\n");
return s;
}

/*-----------------------------------------------------------------------*/
/* simple bar plot (using text) can be replaced by GUI one.              */

#define PLOTBARMAX 50

void mplot_bar(DATA data[],                           /* Data to plot.   */
			   int  dsize,                            /* Number of items.*/
			   DATA max)                              /* Max data (100%) */
{
int * p;
int i,j;

if((!(TGBL no_error))||(dsize>99))
 {
 mprintf("MPLOTBAT: Can not plot (more than 100 items?).\n");
 }
else
 {
 p=(int *)MMalloc(dsize*sizeof(int));

 if((TGBL no_error))
  {
  for(i=0;i<dsize;i++)
   p[i]=(int)((data[i]/max)*PLOTBARMAX);

  for(i=0;i<dsize;i++)
   {
   if(i<10)mprintf("0");
   mprintf("%d :",i);

   for(j=0;j<PLOTBARMAX;j++)
	if(j<=p[i])
     mprintf("_");
    else
     mprintf(" ");

   mprintf(" ");
   mprintf(DATAFORMAT,data[i]);
   mprintf(".\n");
   }
  mprintf("\n");
  }
 MFree(p);
 }
mwait();
}


/*-----------------------------------------------------------------------*/
/* Display a progress report.                                            */


int currtickpos;
BOOL mticking=FALSE;

void mtick(int cur,int max)
{
int i,steps,percent;

if(mticking)
 {
 percent=(int)(((long)50*cur)/max);
 if(percent>100) percent=100;
 steps=percent-currtickpos;
 for(i=0;i<steps;i++)
  {
  printf("^");
  fflush(stdout);
  }
 currtickpos=percent;
 }
}

void mendtick(void)
{
if(mticking)
 {
 mtick(100,100);
 mprintf("\n");
 mprintf("- Done -\n");
 mticking=FALSE;
 ReportTime();
 mcls();
 }
}

void mstarttick(char * message)
{
if(mticking) mendtick();

currtickpos=0;
mticking=TRUE;
mcls();
ReportTime();
mprintf("- %s -\n",message);
printf("\n");
printf("___________________________________________________\n");
printf("                                                  1\n");
printf("0    1    2    3    4    5    6    7    8    9    0\n");
printf("024680246802468024680246802468024680246802468024680 %\n");
}


/*
void mendtick(void)
{
int i,steps;
if(mticking)
 {
 steps=50-currtickpos;
 mprintf("*");

 if(steps>1)
  {
  for(i=1;i<steps;i++) mprintf(".");
  mprintf("Done.\n");
  }
 mprintf("\n");
 mticking=FALSE;
 ReportTime();
 mcls();
 }
}
*/

/*-----------------------------------------------------------------------*/

#endif  /* TEXTBASED */
