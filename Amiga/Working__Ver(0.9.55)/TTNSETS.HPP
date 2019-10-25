#ifndef TTNSETS
#define TTNSETS

/*--------------------------------- extern Globals -------------------*/

/* defined in ttnmain.c: */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

extern int  inputdim;          /* dimention (width) of train,test set.*/
extern int  outputdim;         /* dimention (width) of desired output.*/

extern int  trainsetsize;      /* number of train-set records.        */
extern int  testsetsize;       /* number of test-set records.         */

extern DATA ** trainset;       /* train set records.                  */
extern DATA ** desired;        /* desired outputs for train set.      */
extern DATA ** testset;        /* test set records.                   */

extern DATA ** output;         /* actual output for each test item.   */
extern DATA *  classif;        /* single output for each test item,   */
                               /* (after winner-takes-all selection). */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define IS_SUPERVISED_PROBLEM     ((desired!=NULL))
#define IS_UNSUPERVISED_PROBLEM   ((desired==NULL)&&(testset!=trainset))
#define IS_CLUSTERING_PROBLEM     ((desired==NULL)&&(testset==trainset))

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#endif
