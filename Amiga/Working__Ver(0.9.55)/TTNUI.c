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

#define TTNUI                                   /* don't include TTNUI.H */

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"

#include "TTNREPRT.HPP"
#include "TTNMEMOR.HPP"

#include <ctype.h>

/*---------------------------------------------------System Dependant----*/

#ifdef _MSDOS_
#define _TEXTBASED_
#include <conio.h>
#endif

/*-----------------------------------------------------------------------*/

#ifdef _AMIGA_
#define _TEXTBASED_
#endif

/*-----------------------------------------------------------------------*/

#ifdef _PURETEXT_
#define _TEXTBASED_
#endif

/*-----------------------------------------------------------------------*/

#ifdef _MSWINDOWS_
#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <dir.h>
#include <string.h>
#include <stdarg.h>
#include <share.h>
#include <fcntl.h>

#include "ttnident.hpp"
#include "ttngui0.hpp"

extern char outputtitle[TEXTTITLESIZE];
extern char mitem[MITEMNUM][MITEMLENGTH];

extern int  gui0_CLSflag;

extern int  gui0_input_int(void);
extern DATA gui0_input_DATA(void);
extern BOOL gui0_input_BOOL(void);
extern int  gui0_menu(void);
extern void gui0_beep(void);
extern void gui0_cls(void);
extern void gui0_puts(char *);
extern void gui0_wait(void);

extern int  gui0_CLSflag;

extern char startup_dir [255];
extern char *filename(char **,char *);

char lin[256];                         /* lines in output (edit) window. */
unsigned int nchars=0;                 /* chars in output (edit) window. */

int linepos=0;

void copy_to_title(char * cr)
{
strncpy(outputtitle,cr,TEXTTITLESIZE);
outputtitle[TEXTTITLESIZE-1]='\0';
}

void copy_to_menu(int i,char * cr)
{
if(i<MITEMNUM)
 {
 strncpy(mitem[i],cr,MITEMLENGTH);
 mitem[i][MITEMLENGTH-1]='\0';
 }
}

void mbeep(void)
{
gui0_beep();
}

void mwait(void)
{
gui0_wait();
}

void mcls(void);

int mprintf(const char * __format,...)
{
char buff[255];
int i,len;

BOOL hasCR=FALSE;
va_list ap;

va_start(ap,__format);
vsprintf(buff,__format, ap);
va_end(ap);

gui0_puts(buff);

len=strlen(buff);
nchars=nchars+len;

for(i=0;i<len;i++)
 if(buff[i]=='\n') hasCR=TRUE;
if(hasCR)linepos++;
if((hasCR)&&
   ((linepos>150)||(nchars>64000L)))
   mcls();

ReportToSessionFile(buff);
return 1;
}

void mcls(void)
{
if(gui0_CLSflag)
 {
 gui0_cls();
 }
linepos=0;
nchars=0;
mprintf("\n");
}

void mforcedisplay(void)
{
/* mprintf("<End_Of_Paragraph>\n");  */
}


/*-----------------------------------------------------------------------*/

BOOL mrequest_yn(char * tx)             /* for winshell */
{
BOOL b;

copy_to_title(tx);
b=(BOOL)gui0_input_BOOL();

ReportToSessionFile(tx);
if(b)
 ReportToSessionFile("(YES)\n");
else
 ReportToSessionFile("(NO)\n");

mcls();
return b;
}

/*-----------------------------------------------------------------------*/

int mrequest_int(char * tx)
{
int i;

copy_to_title(tx);
i=(int)gui0_input_int();

ReportToSessionFile(tx);
mprintf("(%d)\n",i);
mcls();

return i;
}

/*-----------------------------------------------------------------------*/

DATA mrequest_DATA(char * tx)
{
DATA d;

copy_to_title(tx);
d=(DATA)gui0_input_DATA();

ReportToSessionFile(tx);
mprintf("(");
mprintf(DATAFORMAT,d);
mprintf(")\n");
mcls();

return d;
}

/*-----------------------------------------------------------------------*/

int mmenu(char ** mlist,int mitems,int firstmline,int minsel,int maxsel)
{
int i,s=minsel-1;

mcls();

for(i=0;i<MITEMNUM;i++) copy_to_menu(i,"");

while((s<minsel)||(s>maxsel))
 {
 for(i=firstmline;i<mitems;i++)
  copy_to_menu(i-firstmline,mlist[i]);

 copy_to_title("");

 for(i=0;i<firstmline;i++)
  {
  if((strlen(mlist[i])+strlen(outputtitle))<=TEXTTITLESIZE)
   strcat(outputtitle,mlist[i]);
  }
 outputtitle[TEXTTITLESIZE-1]='\0';
 s=gui0_menu();
 }

for(i=0;i<mitems;i++)
 {
 ReportToSessionFile(mlist[i]);
 ReportToSessionFile("\n");
 }

mprintf("(%d)\n",s);
mcls();

return s;
}

/*-----------------------------------------------------------------------*/
#endif  /* _MSWINDOWS_ */
/*-----------------------------------------------------------------------*/

#ifdef _TEXTBASED_

#include "TTNPROS.hpp"
#include <stdarg.h>
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

void mforcedisplay(void)
{
/* mprintf("<End_Of_Paragraph>\n");  */
}

void mcls(void)
{
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
mprintf("Press a key to continue....");
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

int mmenu(char ** mlist,int mitems,int firstmline,int minsel,int maxsel)
{
int i,s=minsel-1;

mprintf("\n\n");
for(i=0;i<firstmline;i++)
 mprintf("%s\n",mlist[i]);

while((s<minsel)||(s>maxsel))
 {
 mprintf("\n");
 for(i=firstmline;i<mitems;i++)
  mprintf("%s\n",mlist[i]);
 mprintf("\n");
 s=mrequest_int("Please enter selection : ");
 }
mcls();
return s;
}

/*-----------------------------------------------------------------------*/
#endif  /* TEXTBASED */




/*- - - - - - - - - - - - - Common to all. - - - - - - - - - - - - - - - */
/*-----------------------------------------------------------------------*/
/* simple bar plot (using text) can be replaced by GUI one.              */

#define PLOTBARMAX 50

void mplot_bar(DATA data[],                           /* Data to plot.   */
               int  dsize,                            /* Number of items.*/
               DATA max)                              /* Max data (100%) */
{
int * p;
int i,j;

if((!no_error)||(dsize>99))
 {
 mprintf("MPLOTBAT: Can not plot (more than 100 items?).\n");
 }
else
 {
 p=(int *)MMalloc(dsize*sizeof(int));

 if(no_error)
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

void mstarttick(char * message)
{
currtickpos=0;
mticking=TRUE;
mcls();
ReportTime();
mprintf("%s\n",message);
mprintf("\n");
mprintf("___________________________________________________\n");
mprintf("                                                  1\n");
mprintf("0    1    2    3    4    5    6    7    8    9    0\n");
mprintf("024680246802468024680246802468024680246802468024680 %\n");
}

void mtick(int cur,int max)
{
int i,steps,percent;

if(mticking)
 {
 percent=(int)(((long)50*cur)/max);
 steps=percent-currtickpos;
 for(i=0;i<steps;i++) mprintf("^");
 currtickpos=percent;
 fflush(stdout);
 }
}


void mendtick(void)
{
if(mticking)
 {
 mprintf("X\n");
 mprintf("Done.\n");
 mticking=FALSE;
 ReportTime();
 mcls();
 }
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

/* - - - - - - - - - - - - -  end common to all - - - - - - - - - - - -  */
