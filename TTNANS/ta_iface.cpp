#include "ta_iface.h"

#include "ta_ans.h"
#include "ta_bam.h"
#include "ta_mam.h"

bool Interface_CTa_ans_Algorithm (unsigned selection)
 {
 mhintclear();
 mhintf(false,"Note:\n");
 mhintf(false,"\n");
 mhintf(false,"Interfacing TTNANS with an ANS implemented via the 'CTa_ans' class.    \n");
 mhintf(false,"This is a primitive interface for calling CTa_ans ANSs and may not work\n");
 mhintf(false,"fully especially under Batch-and-Experimentation mode. For example:     \n");
 mhintf(false,"Initial weight settings are currently ignored by CTa_ans ANS objects.\n");
 
 bool ret = false;
 unsigned r,c;
 CTa_environment envir;

 if (envir.Reset (	TGBL trainset,TGBL trainsetsize,TGBL inputdim,
					TGBL testset,TGBL testsetsize,TGBL inputdim,
					TGBL desired,TGBL trainsetsize,TGBL outputdim ) )
  {

#ifdef _DEBUG
envir.Show();
#endif

  switch (selection)
   {
   case CTA_ANS_BAM :	{
						CTa_BAM_ans ans (envir.GetTrainingItem().cols(),
										 envir.GetOutputPrototype().cols());
						ans.GetParameters();
						ret = ans.Run(envir);
						}
						break;

   case CTA_ANS_MAM :	{
						CTa_MAM_ans ans (envir.GetTrainingItem().cols(),
										 envir.GetOutputPrototype().cols());
						ans.GetParameters();
						ret = ans.Run(envir);
						}
						break;

   default:				break;
   }


  // Store results back.

  envir.RestartUsageFromTop();
  if(ret)
   {
   int winner_class;
   DATA t,winner_value;

   mprintf("Copying results and performing winner-takes-all to produce classification...");

   for(r=0;r<TGBL testsetsize;r++)
	{
    winner_class = - 1;
    winner_value = - LARGEDATA;
	for(c=0;c<TGBL outputdim;c++)
     {
     t =  envir.GetOutputItem()[c];
     TGBL output [r][c] = t;
     if( t > winner_value ) 
      {
      winner_value = t;
      winner_class = c;
      }
     }
    TGBL classif [r] = winner_class;
    envir.NextUsageItem();
	}

   mprintf("done.\n");
   }
  }
 return ret;
 }

