/* ---------------------
   ANS System defs v.0.1
   ---------------------
   Vasilis.N.Nikolaidis
   --------------------- */

#ifndef TTNDEF_S
#define TTNDEF_S

/*-----------------------------------------------------------------------*/

#define PT_SUPERVISED   0                      /* Problem training types */
#define PT_UNSUPERVISED 1
#define PT_CLUSTERING   2

#define CONNECTEDFULL   0                        /*      fully connected */
#define CONNECTEDPART   1                        /*  partially connected */
#define CONNECTFORWARDS 10
#define CONNECTTWOWAYS  20
                                                /* ERRORS:               */
#define MEMORYERR 1                             /* allocating memory     */
#define INPUTFERR 2                             /* input file            */
#define OUTPUFERR 3                             /* output file           */
#define READWRERR 4                             /* read/write            */
#define SYSTEMERR 5                             /* system                */
#define ANSINTERR 6                             /* A.N.S. integrity      */
#define EOFILEERR 7                             /* End-Of-File           */
#define MEMGRDERR 8                             /* memory guard          */
#define NULPTRERR 9                             /* null pointer          */
#define PRBDEFERR 10                            /* problem definition    */
#define DATASTERR 11                            /* data (test/train) set */
#define ARITHMERR 12                            /* arithmetic            */
#define USRABRERR 13							/* user aborted			 */

												/* Connection Weight     */
												/* Initializat. Settings:*/

#define IW_ANS_STANDARD					  255	/*  Algorithm's Standard */
#define IW_NOT_SET							0
#define IW_USE_WEIGHT_SET					1
#define IW_USE_PREDEFINED_WEIGHT_SET		2
#define IW_ZERO_TO_ONE						3
#define IW_USD_RANGE						4
#define IW_DISTANT_TRAIN_ITEMS				5
#define IW_DISTANT_TRAIN_ITEMS_LOW_RAM		6
#define IW_RANDOM_IN_TRAINING_SET_RANGE		7
#define IW_RANDOM_TRAINING_SET_ITEM			8
#define IW_MINUS_ONE_TO_ONE					9
#define IW_FIRST_TRAINING_SET_ITEM			10
#define IW_DISTANT_TRAIN_ITEMS_START_MEAN	11

												/* Set ReOrder constants */
#define SRE_NOT_SET                   255
#define SRE_NO_CHANGE                   0
#define SRE_ARBITRARY                   1
#define SRE_RANDOM                      2
#define SRE_SORT                        3
#define SRE_REVERSE_SORT                4
#define SRE_ON_DISTANCE                 5
#define SRE_ON_DISTANCE_LOW_RAM         6
#define SRE_ON_DISTANCE_START_MEAN		7 
#define SRE_DISTANCE_CENTER             8
#define SRE_DISTANCE_MEAN               9
#define SRE_ALL_COMBINATIONS            10

#endif /* not defined TTNSDEFS */

/*---------------------------------------------------- NotePad ------------
TTNANS source and program are NOT Public Domain.
TTNANS (c) 1994-1995 Vasilios N. Nikolaidis.
-------------------------------------------------------------------------*/
