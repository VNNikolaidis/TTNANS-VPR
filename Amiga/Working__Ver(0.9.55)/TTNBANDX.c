
/* --------------------
   TTNANS:
   TTNBANDX.C  ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   ------------------------------
   Batch + Experimentation Module
   ------------------------------
*/

#include "ttndef.hpp"
#include "ttnbool.hpp"
#include "ttnpros.hpp"
#include "ttnsets.hpp"

#include <string.h>

#include "TTNDATA1.HPP"
#include "TTNDATA2.HPP"
#include "TTNMEMOR.HPP"
#include "TTNMAIN.HPP"
#include "TTNPREP3.HPP"
#include "TTNANS.HPP"
#include "TTNFILE.HPP"

/*--------------------------------------------------------------------------*/

void batch_n_filename(char * infname,
                      int runnum,
                      char * outfname,
                      char * ext)
{
int j=0;
char buffer[10];

while((infname[j]!='\0')&&                  /* Find '.' or end            */
	  (infname[j]!='.'))j++;

if(infname[j]=='\0')j=FILENAMEMARKER;

strcpy(outfname,"");
strcpy(buffer,"");
strncat(outfname,infname,j);
if(runnum>=0)itoa(runnum,buffer,10);
strcat(outfname,buffer);
strcat(outfname,ext);
}

/*--------------------------------------------------------------------------*/

void batch_show_and_save(BOOL interactive,int curstep,BOOL saveclasses)
{
char fnameout [FILENAMELENGTH];
char fnameout2[FILENAMELENGTH];
char fnameout3[FILENAMELENGTH];

if((prbfname!=NULL)&&(strcmp(prbfname,"")!=0))
 {
 batch_n_filename(prbfname,curstep,fnameout,"");
 batch_n_filename(prbfname,curstep,fnameout2,".cla");
 batch_n_filename(prbfname,curstep,fnameout3,".out");

 if(interactive)
  {
  ShowClassif();
  ShowOutput();
  SaveClassif("","ANS batch and experiment results.\n",TRUE);
  SaveClasses(prbfname,fnameout,TRUE);
  SaveOutput("","ANS batch and experiment output Layer values.\n",TRUE);

  }
 else
  {
  SaveClassif(fnameout2,"ANS experimentation results.\n",FALSE);
  if(saveclasses) SaveClasses(prbfname,fnameout,FALSE);
  SaveOutput(fnameout3,"ANS batch and experiment output Layer values.\n",FALSE);
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

if((fname==NULL)||(strcmp(fname,"")==0))
 {
 mprintf("No Filename.No action taken.\n");
 return;
 }

batch_n_filename(fname,-1,buffer,"");

mprintf("Following the file %d-character-max naming convention:\n",FILENAMEMARKER);
mprintf("Using %s*.f* or %s*.x* files.\n",buffer,buffer);

if(mrequest_yn("Use full descriptor cluster files (*.f*)?"))
 strcpy(extent,".f0");
else
 strcpy(extent,".x0");

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

mprintf("Following the file %d-character-max naming convention:\n",FILENAMEMARKER);
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

char *menu[]={
              "Initial Weight Initialization Menu",
              "0...Skip this part.",
              "1...Some standard initialization (specified later).",
              "2...Random number in 0..1 range.",
              "3...Random number in some other range.",
              "4...Random number in Training Set's Ranges.",
              "5...Maximum distance Training Items.",
              "6...Maximum distance Training Items (low RAM).",
              "7...Randomly picked Training Items.",
              "8...First Training Items.",
             };

while((no_error)&&(msel!=0))
 {
 msel=mmenu(menu,10,1,0,8);
 switch(msel)
  {
  case 0 : break;
  case 1 : return IW_NOT_SET;
  case 2 : return IW_ZERO_TO_ONE;
  case 3 : return IW_USD_RANGE;
  case 4 : return IW_RANDOM_IN_TRAINING_SET_RANGE;
  case 5 : return IW_DISTANT_TRAIN_ITEMS;
  case 6 : return IW_DISTANT_TRAIN_ITEMS_LOW_RAM;
  case 7 : return IW_RANDOM_TRAINING_SET_ITEM;
  case 8 : return IW_FIRST_TRAINING_SET_ITEM;
  default: return IW_NOT_SET;
  }
 }
return IW_NOT_SET;
}

/*--------------------------------------------------------------------------*/

void show_reordering_warning(void)
{
mprintf("To change the presentation order, the training set will be reordered.\n");
mprintf("Reordering changes to the training set will remain until you load the\n");
mprintf("problem (*.prb) file again (or you load another problem).\n");
mprintf("You are now about to choose a reordering techique for the training set.\n");
mprintf("\n");
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
  repeat_outdim=mrequest_int("Repeat how many times per output step?.");
  mcls();
  }
 }
else
 {
 min_outdim=outputdim;
 max_outdim=outputdim;
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

void one_ans_one_problem_menu(int preselect,
							  int algorithm_launcher(int,BOOL,BOOL,BOOL,int))
{
int msel=preselect;
int ans,weight_initialization,re_type,combinations,k;
int min_outdim=0,max_outdim=0,step_outdim=0,v_outdim=0,repeat,v_repeat;
int batchrunnum=0;

BOOL interactive=FALSE;
BOOL save_classes=FALSE;

char *menu[]={"--------------------",
			  "Experimentation Menu",
			  "--------------------",
			  "0...None. Return to previous menu.",
			  "1...Initial weights.",
			  "2...Training item presentation order.",
              "3...Initial weights and presentation order.",
			  "4...Presentation order, output size (or repeated runs).",
			  "5...Initial weights, presentation order, output size (repeated runs)."
			 };

problem_menu(1);                          /* Load problem...                */

if((no_error)&&(IS_CLUSTERING_PROBLEM))   /* if the testset == trainset...  */
 {
 mprintf("This is an clustering problem, i.e. training and testing sets     \n");
 mprintf("are identical (currently stored in one array). However, to be     \n");
 mprintf("able to experiment with the training item presentation order (by  \n");
 mprintf("reordering the training set) while keeping the testing set in its \n");
 mprintf("original order, a new storage area for testing set is created and \n");
 mprintf("a copy of the current training set is stored there. This is also  \n");
 mprintf("necessary for correctly saving results (original order is needed).\n");
 mprintf("\n");

 CreateTestset();
 Copy2dDATASet(trainset,testset,trainsetsize,inputdim);
 mprintf("Done, new testing set allocated and copied.\n\n");
 }

problem_menu(2);                      /* preprocess sets...                 */
problem_menu(3);                      /* show sets                          */

ans=algorithm_launcher(-1,TRUE,TRUE,FALSE,-1);

while((no_error)&&(msel!=0)&&(ans!=0))
 {
 if(msel<0)
  msel=mmenu(menu,9,3,0,5);

 if(msel!=0)
  {
  mprintf("You have the option of running the batch with results being saved \n");
  mprintf("automaticaly, or stoping after each training/testing cycle to show\n");
  mprintf("and save the results.\n");
  interactive=mrequest_yn("Stop for results while running batch?");
  if(!interactive)
   save_classes=mrequest_yn("Save class files (*.x*,*.f*) during batch?");
  }

 switch(msel)
  {
  case 0: break;

  case 1: weight_initialization=vary_initial_weights_menu();
		  algorithm_launcher(ans,TRUE,FALSE,TRUE,weight_initialization);
		  batch_show_and_save(TRUE,0,save_classes);
		  break;

  case 2: show_reordering_warning();
		  re_type=ordering_info(SRE_NOT_SET,&combinations,trainsetsize,inputdim,TRUE);
		  for(k=0;k<combinations;k++)
		   {
		   mprintf("Combination %d (out of %d).\n",k+1,combinations);
		   reorder_set(re_type,k,trainset,trainsetsize,inputdim);
		   if(interactive)problem_menu(3);
		   algorithm_launcher(ans,TRUE,FALSE,TRUE,IW_ANS_STANDARD);
		   if(ANS_run_success)
			batch_show_and_save(interactive,k,save_classes);
		   }
		  break;

  case 3: weight_initialization=vary_initial_weights_menu();
		  show_reordering_warning();
		  re_type=ordering_info(SRE_NOT_SET,&combinations,trainsetsize,inputdim,TRUE);
		  for(k=0;k<combinations;k++)
		   {
		   mprintf("Combination %d (out of %d).\n",k+1,combinations);
		   reorder_set(re_type,k,trainset,trainsetsize,inputdim);
		   if(interactive)problem_menu(3);
		   algorithm_launcher(ans,TRUE,FALSE,TRUE,weight_initialization);
		   if(ANS_run_success)
			batch_show_and_save(interactive,k,save_classes);
		   }
		  break;

  case 4: if(IS_SUPERVISED_PROBLEM)
		   {
		   mprintf("Invalid option.\n");
		   mprintf("Can not vary output size on a supervised problem!\n");
		   }
		  else
		   {
		   get_bandx_output_ranges(&min_outdim,&max_outdim,&step_outdim,&repeat);
		   show_reordering_warning();
		   re_type=ordering_info(SRE_NOT_SET,&combinations,trainsetsize,inputdim,TRUE);

		   for(v_outdim=min_outdim;v_outdim<=max_outdim;v_outdim+=step_outdim)
		   for(v_repeat=0;v_repeat<repeat;v_repeat++)
			{
			outputdim=v_outdim;

			if(output!=NULL)       /* if an old output set is malloced ...  */
			 {
			 FreeOutput();         /* free it and ....                      */
			 CreateOutput();       /* create a new with the new outputdim.  */
			 }

			for(k=0;k<combinations;k++)
			 {
			 mprintf(" \n");
			 mprintf("Next:running batch number %d.\n",batchrunnum);
			 mprintf("Output size: %d.\n",outputdim);
			 mprintf("Re-ordering Combination: %d (out of %d).\n",k+1,combinations);
			 reorder_set(re_type,k,trainset,trainsetsize,inputdim);
			 if(interactive)problem_menu(3);
			 algorithm_launcher(ans,TRUE,FALSE,TRUE,IW_ANS_STANDARD);
			 if(ANS_run_success)
			  {
			  batch_show_and_save(interactive,batchrunnum,save_classes);
			  batchrunnum++;
			  }
			 }
			}
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
		   weight_initialization=vary_initial_weights_menu();
		   show_reordering_warning();
		   re_type=ordering_info(SRE_NOT_SET,&combinations,trainsetsize,inputdim,TRUE);

		   for(v_outdim=min_outdim;v_outdim<=max_outdim;v_outdim+=step_outdim)
		   for(v_repeat=0;v_repeat<repeat;v_repeat++)
			{
			outputdim=v_outdim;

			if(output!=NULL)       /* if an old output set is malloced ...  */
			 {
			 FreeOutput();         /* free it and ....                      */
			 CreateOutput();       /* create a new with the new outputdim.  */
			 }

			for(k=0;k<combinations;k++)
			 {
			 mprintf(" \n");
			 mprintf("Next:running batch number %d.\n",batchrunnum);
			 mprintf("Output size: %d.\n",outputdim);
			 mprintf("Re-ordering Combination: %d (out of %d).\n",k+1,combinations);
			 reorder_set(re_type,k,trainset,trainsetsize,inputdim);
			 if(interactive)problem_menu(3);
			 algorithm_launcher(ans,TRUE,FALSE,TRUE,weight_initialization);
			 if(ANS_run_success)
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

char *menu[]={"",
			  "Batch and Experimentation Menu",
			  "",
			  "0...Return to previous Menu.",
			  "1...One ANS, one problem.",
			  "2...Many ANSs, one problem.",
			  "3...One ANS, many problems.",
			  "4...Many ANSs, many problems."
			 };

while((no_error)&&(msel!=0))
 {
 msel=mmenu(menu,8,3,0,4);
 switch(msel)
  {
  case 0: break;

  case 1: one_ans_one_problem_menu(-1,ans_menu);
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
