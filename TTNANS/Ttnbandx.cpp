
/* --------------------
   TTNANS:
   TTNBANDX.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------------
   Batch + Experimentation Module
   ------------------------------
*/

#include "ttndef.h"
#include "ttnpros.h"
#include "ttnsets.h"
#include "ttnui.h"

#include <string.h>

#include "ttndata1.h"
#include "ttndata2.h"
#include "ttnmemor.h"
#include "ttnmain.h"
#include "ttnprep3.h"
#include "ttnans.h"
#include "ttnfile.h"

/*--------------------------------------------------------------------------*/

void batch_n_filename(char * infname,
                      int runnum,
                      char * outfname,
                      char * ext)
{
mhintclear();
mhintf(false,"File names for batch output files may be longer than 8 characters\n");
mhintf(false,"since an '_#' is added to the original (given) file name.\n");
mhintf(false,"(# = number of the batch run).\n");
mhintf(false,"If you are planning to call Axum for DOS on these data files,\n");
mhintf(false,"it is suggested that you keep the first part of the filename\n");
mhintf(false,"(before '.') as small as possible (<4 chars long) to avoid \n");
mhintf(false,"problems caused by the MS-DOS FAT (8.3) filename format.\n");

int j=0;
char buffer[FILENAMELENGTH];

while((infname[j]!='\0')&&                  /* Find '.' or end            */
	  (infname[j]!='.'))j++;

strcpy(outfname,"");
strcpy(buffer,"");
strncat(outfname,infname,j);
if(runnum>=0)itoa(runnum,buffer,10);
strcat(outfname,"_");
strcat(outfname,buffer);
strcat(outfname,ext);
}

/*--------------------------------------------------------------------------*/

void batch_show_and_save(bool interactive,int curstep,bool saveclasses)
{
char fnameout [FILENAMELENGTH];
char fnameout2[FILENAMELENGTH];
char fnameout3[FILENAMELENGTH];

if((TGBL prbfname!=NULL)&&(strcmp(TGBL prbfname,"")!=0))
 {
 batch_n_filename(TGBL prbfname,curstep,fnameout,"");
 batch_n_filename(TGBL prbfname,curstep,fnameout2,".cla");
 batch_n_filename(TGBL prbfname,curstep,fnameout3,".out");

 if(interactive)
  {
  ShowClassif();
  ShowOutput();
  SaveClassif("","TTNANS batch and experimentation results",true);
  SavePreprocessedClasses (fnameout,true);
  SaveClasses(TGBL prbfname,fnameout,true);
  SaveOutput("","ANS batch and experiment (TGBL output) Layer values.\n",true);
  }
 else
  {
  SaveClassif(fnameout2,"TTNANS experimentation results",false);
  if(saveclasses)
   {
   SavePreprocessedClasses (fnameout,false);
   SaveClasses(TGBL prbfname,fnameout,false);
   }
  SaveOutput(fnameout3,"ANS batch and experiment (TGBL output) Layer values.\n",false);
  }
 }
}

/*-------------------------------------------------------------------------*/

void batch_run_using_classes(char * fname,DATA (*workfunction)(char *,int))
{
DATA J=-1;
DATA minJ = LARGEDATA;
DATA maxJ = SMALLDATA;
int minrunnum=-1;
int maxrunnum=-1;

char buffer [FILENAMELENGTH];
char buffer2[FILENAMELENGTH];
char extent[5];
int runnum=0;

int msel=-1;
char mtitle[]="Batch-run file type selection menu";
char *menu[]={"0...Skip this part - Use default.",
			  "1...Use full descriptor class files     (*.F*).",
			  "2...Use selected descriptor class files (*.X*).",
			  "3...Use scaled descriptor class files   (*.S*)."};

if((fname==NULL)||(strcmp(fname,"")==0))
 {
 mprintf("No Filename.No action taken.\n");
 return;
 }

batch_n_filename(fname,-1,buffer,"");

msel=mmenu(mtitle,menu,4,3);
switch(msel)
 {
 default:
 case 0 : strcpy(extent,".x0");break;
 case 1 : strcpy(extent,".f0");break;
 case 2 : strcpy(extent,".x0");break;
 case 3 : strcpy(extent,".s0");break;
 }

mprintf("Using %s*%s files.\n",buffer,extent);

/*
if(mrequest_yn("Use full descriptor cluster files (*.f*)?"))
 strcpy(extent,".f0");
else
 strcpy(extent,".x0");
*/

batch_n_filename(fname,runnum,buffer2,extent);

mprintf("Attempting to open group %s.\n",buffer);

if(!FileExists(buffer2))
 {
 mprintf("Can not continue, file %s does not exist.\n",buffer2);
 mprintf("Current value = ");
 mprintf(DATAFORMAT,J);
 mprintf(" will be returned.\n");
 }
else
 while(FileExists(buffer2))
  {
  mprintf("Processing file set %s...\n",buffer);
  J=workfunction(buffer2,runnum);

  if(J<minJ)
   {
   minJ=J;
   minrunnum=runnum;
   }
  if(J>maxJ)
   {
   maxJ=J;
   maxrunnum=runnum;
   }
  runnum++;
  batch_n_filename(fname,runnum,buffer2,extent);
  }

mprintf(" \n");

if(minrunnum>-1)
 {
 mprintf("Minimum Value = ");
 mprintf(DATAFORMAT,minJ);
 mprintf(" found on set %s%d.\n",buffer,minrunnum);
 }
if(maxrunnum>-1)
 {
 mprintf("Maximum Value = ");
 mprintf(DATAFORMAT,maxJ);
 mprintf(" found on set %s%d.\n",buffer,maxrunnum);
 mprintf(" \n");
 }
}

/*-------------------------------------------------------------------------*/

void batch_run_using_classification(char * prbfname,
                                    DATA (*workfunction)(char *,char *,int))
{
DATA J=-1;
DATA minJ = LARGEDATA;
DATA maxJ = SMALLDATA;
int minrunnum=-1;
int maxrunnum=-1;
char buffer [FILENAMELENGTH];
char buffer2[FILENAMELENGTH];
int runnum=0;

if((prbfname==NULL)||(strcmp(prbfname,"")==0))
 {
 mprintf("No Filename.No action taken.\n");
 return;
 }

batch_n_filename(prbfname,-1,buffer,"");

mprintf("Using %s*.cla.\n",buffer);

batch_n_filename(prbfname,runnum,buffer2,".cla");

mprintf("Attempting to open group %s.\n",buffer);

if(!FileExists(buffer2))
 {
 mprintf("Can not continue, file %s does not exist.\n",buffer2);
 mprintf("Current value = ");
 mprintf(DATAFORMAT,J);
 mprintf(" will be returned.\n");
 }
else
 while(FileExists(buffer2))
  {
  mprintf("Processing file %s.\n",buffer2);
  J=workfunction(prbfname,buffer2,runnum);

  if(J<minJ)
   {
   minJ=J;
   minrunnum=runnum;
   }
  if(J>maxJ)
   {
   maxJ=J;
   maxrunnum=runnum;
   }
  runnum++;
  batch_n_filename(prbfname,runnum,buffer2,".cla");
  mprintf("Checking for file %s.\n",buffer2);
  }

mprintf(" \n");

if(minrunnum>-1)
 {
 mprintf("Minimum Value = ");
 mprintf(DATAFORMAT,minJ);
 mprintf(" found on set %s%d.\n",buffer,minrunnum);
 }
if(maxrunnum>-1)
 {
 mprintf("Maximum Value = ");
 mprintf(DATAFORMAT,maxJ);
 mprintf(" found on set %s%d.\n",buffer,maxrunnum);
 mprintf(" \n");
 }
}

/*--------------------------------------------------------------------------*/

int vary_initial_weights_menu(void)
{
int msel=-1;

char mtitle[]="Initial Weight Initialization Menu";
char *menu[]={"0...Skip this part.",
              "1...Some standard initialization (specified later).",
			  "2...Random number in 0..1 range.",
              "3...Random number in some other range.",
              "4...Random number in training set's Ranges.",
              "5...Maximum distance training items.",
              "6...Maximum distance training items (low RAM).",
              "7...Maximum distance training items starting from mean (low RAM).",
              "8...Randomly picked training items.",
              "9...First training items.",
             };

while((TGBL no_error)&&(msel!=0))
 {
 msel=mmenu(mtitle,menu,10,9);
 switch(msel)
  {
  case 0 : break;
  case 1 : return IW_NOT_SET;
  case 2 : return IW_ZERO_TO_ONE;
  case 3 : return IW_USD_RANGE;
  case 4 : return IW_RANDOM_IN_TRAINING_SET_RANGE;
  case 5 : return IW_DISTANT_TRAIN_ITEMS;
  case 6 : return IW_DISTANT_TRAIN_ITEMS_LOW_RAM;
  case 7 : return IW_DISTANT_TRAIN_ITEMS_START_MEAN;
  case 8 : return IW_RANDOM_TRAINING_SET_ITEM;
  case 9 : return IW_FIRST_TRAINING_SET_ITEM;
  default: return IW_NOT_SET;
  }
 }
return IW_NOT_SET;
}

/*--------------------------------------------------------------------------*/

void show_reordering_warning(void)
{
mhintclear();
mhintf(true,"To change the presentation order, the training set will be reordered.\n");
mhintf(true,"Reordering changes to the training set will remain until you load the\n");
mhintf(true,"problem (*.prb) file again (or you load another problem).\n");
mhintf(true,"You are now about to choose a reordering techique for the training set.\n");
mhintf(true," \n");
mwait();
}

/*--------------------------------------------------------------------------*/

void get_bandx_output_ranges(int * min,int *max, int * step, int * repeat)
{
int min_outdim=0,
	max_outdim=0,
	step_outdim=0,
	repeat_outdim=-1;

if(mrequest_yn("Experiment with output sizes (or repeated runs?)"))
 {
 while((step_outdim<1)||
		(min_outdim<1)||
		(max_outdim<1)||
		(repeat_outdim<0)||
		(min_outdim>max_outdim))
  {
  min_outdim=mrequest_int("Select minimum output size.");
  max_outdim=mrequest_int("Select maximum output size.");
  step_outdim=mrequest_int("Select output size step.");
  repeat_outdim=mrequest_int("Repeat how many times per output step?");
  mcls();
  }
 }
else
 {
 min_outdim=(TGBL outputdim);
 max_outdim=(TGBL outputdim);
 step_outdim=1;
 repeat_outdim=1;
 }

*min=min_outdim;
*max=max_outdim;
*step=step_outdim;
*repeat=repeat_outdim;
}

/*--------------------------------------------------------------------------*/
/* Runs one_ans_one_problem experimentation. The function used to start     */
/* the actual algorithm is pased as parameter (such function is 'ans_menu').*/
/* if preselect==-1 shows menu.                                             */

/* IMPORTANT:																*/
/* function 'non_ans_module' (in ttnother.cpp) calls this with preselect=5	*/
/* (presentation order, output size) to run; if you change the menu, adjust */
/* the non_ans_module(5...) function to the apropriate parameter.			*/


void one_ans_one_problem_menu(int preselect,
							  int algorithm_launcher(int,bool,bool,bool,int))
{
int msel=preselect;
int ans,weight_initialization,re_type,combinations,k;
int min_outdim=0,max_outdim=0,step_outdim=0,v_outdim=0,repeat,v_repeat;
int batchrunnum=0;

bool interactive=false;
bool save_classes=false;

char mtitle[]="Experimentation Menu";
char *menu[]={"0...None, Go Back.",
			  "1...Initial weights.",
			  "2...Training item presentation order.",
              "3...Output size.",
              "4...Initial weights and presentation order.",
			  "5...Presentation order, output size (or repeated runs).",
			  "6...Initial weights, presentation order, output size (repeated runs)."
			 };

ANS_processing_menu(1);									/* Load problem...                */
ANS_processing_menu(2);					                /* preprocess sets...             */

if((TGBL no_error)&&(IS_CLUSTERING_PROBLEM))      /*  (TGBL testset) == (TGBL trainset)...*/
 {
 mhintclear();
 mhintf(true,"This is an clustering problem, i.e. training and testing sets     \n");
 mhintf(true,"are identical (currently stored in one array). However, to be     \n");
 mhintf(true,"able to experiment with the training item presentation order (by  \n");
 mhintf(true,"reordering the training set) while keeping the testing set in its \n");
 mhintf(true,"original order, a new storage area for testing set is created and \n");
 mhintf(true,"a copy of the current training set is stored there. This is also  \n");
 mhintf(true,"necessary for correctly saving results (original order is needed).\n");
 mhintf(true," \n");

 CreateTestset();
 Copy2dDATASet((TGBL trainset),(TGBL testset),(TGBL trainsetsize),(TGBL inputdim));
 mprintf("Done, new testing set allocated and copied.\n\n");
 }

ANS_processing_menu(3);									/* show sets			        */

ans=algorithm_launcher(-1,true,true,false,-1);

while((TGBL no_error)&&(msel!=0)&&(ans!=0))
 {
 if(msel<0)
  msel=mmenu(mtitle,menu,7,6);

 if(msel!=0)
  {
  mhintclear();
  mhintf(true,"You have the option of running the batch with results being saved \n");
  mhintf(true,"automatically, or stopping after each training/testing cycle to show\n");
  mhintf(true,"and save the results.\n");
  interactive=mrequest_yn("Stop for results while running batch?");
  if(!interactive)
   {
   save_classes=mrequest_yn("Save class files (*.x*,*.f*) during batch?");
   if(TGBL show_ans_option) (TGBL show_ans_option)=mrequest_yn("Allow the option to show ANS structure?");
   }
  }

 switch(msel)
  {
  case 0: break;

  case 1: weight_initialization=vary_initial_weights_menu();
		  algorithm_launcher(ans,true,false,true,weight_initialization);
		  batch_show_and_save(true,0,save_classes);
		  break;

  case 2: show_reordering_warning();
		  re_type=ordering_info(SRE_NOT_SET,&combinations,(TGBL trainsetsize),(TGBL inputdim),true);
		  for(k=0;k<combinations;k++)
		   {
		   mprintf("Combination %d (out of %d).\n",k+1,combinations);
		   reorder_set(re_type,k,(TGBL trainset),(TGBL trainsetsize),(TGBL inputdim));
		   if(interactive)ANS_processing_menu(3);
		   algorithm_launcher(ans,true,false,true,IW_ANS_STANDARD);
		   if(TGBL ANS_run_success)
			batch_show_and_save(interactive,k,save_classes);
		   }
		  break;

  case 3: if(IS_SUPERVISED_PROBLEM)
		   {
		   mprintf("Invalid option.\n");
		   mprintf("Can not vary output size on a supervised problem!\n");
		   }
		  else
		   {
		   get_bandx_output_ranges(&min_outdim,&max_outdim,&step_outdim,&repeat);
		   for(v_outdim=min_outdim;v_outdim<=max_outdim;v_outdim+=step_outdim)
		   for(v_repeat=0;v_repeat<repeat;v_repeat++)
			{
			(TGBL outputdim)=v_outdim;

			if((TGBL output)!=NULL) /* if an old (TGBL output) set is malloced ...  */
			 {
			 FreeOutput();          /* free it and ....                      */
			 CreateOutput();        /* create a new with the new (TGBL outputdim).  */
			 }

  		    mprintf(" \n");
			mprintf("Next: running batch number %d.\n",batchrunnum);
			mprintf("output size: %d.\n",(TGBL outputdim));
			if(interactive)ANS_processing_menu(3);
			algorithm_launcher(ans,true,false,true,IW_ANS_STANDARD);
			if(TGBL ANS_run_success)
			 {
			 batch_show_and_save(interactive,batchrunnum,save_classes);
			 batchrunnum++;
			 }
			}
		   }	
		   
		  break;

  case 4: weight_initialization=vary_initial_weights_menu();
		  show_reordering_warning();
		  re_type=ordering_info(SRE_NOT_SET,&combinations,(TGBL trainsetsize),(TGBL inputdim),true);
		  for(k=0;k<combinations;k++)
		   {
		   mprintf("Combination %d (out of %d).\n",k+1,combinations);
		   reorder_set(re_type,k,(TGBL trainset),(TGBL trainsetsize),(TGBL inputdim));
		   if(interactive)ANS_processing_menu(3);
		   algorithm_launcher(ans,true,false,true,weight_initialization);
		   if(TGBL ANS_run_success)
			batch_show_and_save(interactive,k,save_classes);
		   }
		  break;

  case 5: if(IS_SUPERVISED_PROBLEM)
		   {
		   mprintf("Invalid option.\n");
		   mprintf("Can not vary output size on a supervised problem!\n");
		   }
		  else
		   {
		   get_bandx_output_ranges(&min_outdim,&max_outdim,&step_outdim,&repeat);
		   show_reordering_warning();
		   re_type=ordering_info(SRE_NOT_SET,&combinations,(TGBL trainsetsize),(TGBL inputdim),true);

		   for(v_outdim=min_outdim;v_outdim<=max_outdim;v_outdim+=step_outdim)
		   for(v_repeat=0;v_repeat<repeat;v_repeat++)
			{
			(TGBL outputdim)=v_outdim;

			if((TGBL output)!=NULL) /* if an old (TGBL output) set is malloced ...  */
			 {
			 FreeOutput();          /* free it and ....                      */
			 CreateOutput();        /* create a new with the new (TGBL outputdim).  */
			 }

			for(k=0;k<combinations;k++)
			 {
			 mprintf(" \n");
			 mprintf("Next: running batch number %d.\n",batchrunnum);
			 mprintf("output size: %d.\n",(TGBL outputdim));
			 mprintf("Re-ordering Combination: %d (out of %d).\n",k+1,combinations);
			 reorder_set(re_type,k,(TGBL trainset),(TGBL trainsetsize),(TGBL inputdim));
			 if(interactive)ANS_processing_menu(3);
			 algorithm_launcher(ans,true,false,true,IW_ANS_STANDARD);
			 if(TGBL ANS_run_success)
			  {
			  batch_show_and_save(interactive,batchrunnum,save_classes);
			  batchrunnum++;
			  }
			 }
			}
		   }
		  break;

  case 6: if(IS_SUPERVISED_PROBLEM)
		   {
		   mprintf("Invalid option.\n");
		   mprintf("Can not vary output size on a supervised problem!\n");
		   }
		  else
		   {
		   get_bandx_output_ranges(&min_outdim,&max_outdim,&step_outdim,&repeat);
		   weight_initialization=vary_initial_weights_menu();
		   show_reordering_warning();
		   re_type=ordering_info(SRE_NOT_SET,&combinations,(TGBL trainsetsize),(TGBL inputdim),true);

		   for(v_outdim=min_outdim;v_outdim<=max_outdim;v_outdim+=step_outdim)
		   for(v_repeat=0;v_repeat<repeat;v_repeat++)
			{
			(TGBL outputdim)=v_outdim;

			if((TGBL output)!=NULL)       /* if an old (TGBL output) set is malloced ...  */
			 {
			 FreeOutput();         /* free it and ....                      */
			 CreateOutput();       /* create a new with the new (TGBL outputdim).  */
			 }

			for(k=0;k<combinations;k++)
			 {
			 mprintf(" \n");
			 mprintf("Next: running batch number %d.\n",batchrunnum);
			 mprintf("output size: %d.\n",(TGBL outputdim));
			 mprintf("Re-ordering Combination: %d (out of %d).\n",k+1,combinations);
			 reorder_set(re_type,k,(TGBL trainset),(TGBL trainsetsize),(TGBL inputdim));
			 if(interactive)ANS_processing_menu(3);
			 algorithm_launcher(ans,true,false,true,weight_initialization);
			 if(TGBL ANS_run_success)
			  {
			  batch_show_and_save(interactive,batchrunnum,save_classes);
			  batchrunnum++;
			  }
			 }
			}
		   }
		  break;

  default:break;
  }
 msel=0;
 }
}

/*--------------------------------------------------------------------------*/

void batch_experiment_menu(void)
{
int msel=-1;

char mtitle[]="Batch and Experimentation Menu";
char *menu[]={"0...Go Back.",
			  "1...One ANS, one problem.",
			  "2...Many ANSs, one problem.",
			  "3...One ANS, many problems.",
			  "4...Many ANSs, many problems."
			 };

while((TGBL no_error)&&(msel!=0))
 {
 msel=mmenu(mtitle,menu,5,4);
 switch(msel)
  {
  case 0: break;

  case 1: TGBL show_ans_option = true;
		  one_ans_one_problem_menu(-1,ans_menu);
		  break;


  case 2: mprintf("Not implemented in this version.\n");
		  mwait();
		  break;

  case 3: mprintf("Not implemented in this version.\n");
		  mwait();
		  break;

  case 4: mprintf("Not implemented in this version.\n");
		  mwait();
		  break;

  default:break;
  }
 }
}

/*-----------------------------------------------------------------------*/
