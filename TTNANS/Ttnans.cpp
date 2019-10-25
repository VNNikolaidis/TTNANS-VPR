/*
   --------------------
   TTNANS:
   TTNANS.C    ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   ANS Launcher & menus.
   --------------------

*/

#include "ttndef.h"
#include "ttndef_s.h"
#include "ttnmain.h"
#include "ttnui.h"
#include "ttnerror.h"
#include "ttnkcn.h"
#include "ttnlvqsw.h"
#include "ttnplbp.h"
#include "ta_iface.h"

/*-----------------------------------------------------------------------*/

int ans_menu(int preselect,               /* -1 = Show menu              */
             bool take_action,            /* Don't just select an ANS.   */
             bool get_ans_parameters,     /* Ask for ANS parameters too. */
             bool run_ANS,                /* and run it                  */
             int wim)                     /* Weight Initialization Mode  */
{
int msel=preselect;

char mtitle[]="   A.N.S.   M e n u  ";
char *menu[]={"0...No more processing - Go to previous menu.",
              "1...Kohonen Clustering Net (Autoassociative,Clustering).",
              "2...Learning Vector Quantization (LVQ,Autoassociative,Clustering).",
              "3...Back Propagation Perceptron (BP,Heteroassociative).",
			  "4...Discrete Bidirectional Associative Memory (BAM,Heteroassociative,CTa_ans).",
			  "5...Matrix Associative Memory (MAM,Heteroassociative,CTa_ans)."
             };

TGBL ANS_run_success=false;
if(TGBL no_error)
 {
 if(preselect<0) msel=mmenu(mtitle,menu,6,5);

 if(take_action)
 switch(msel)
  {
  case 0: break;

  case 1:
          if(wim==IW_ANS_STANDARD)wim=IW_ZERO_TO_ONE;
          TGBL ANS_run_success=mainKCN_i(get_ans_parameters,run_ANS,wim,TGBL inputdim,
										TGBL outputdim,TGBL trainset,TGBL trainsetsize,
										TGBL testset,TGBL testsetsize,TGBL output,TGBL classif);
          break;
  case 2:
          if(wim==IW_ANS_STANDARD)wim=IW_ZERO_TO_ONE;
          TGBL ANS_run_success=mainLVQSWU_i(get_ans_parameters,run_ANS,wim,TGBL inputdim,
										TGBL outputdim,TGBL trainset,TGBL trainsetsize,
										TGBL testset,TGBL testsetsize,TGBL output,TGBL classif);
          break;
  case 3:
		  if(wim==IW_ANS_STANDARD)wim=IW_MINUS_ONE_TO_ONE;
		  TGBL ANS_run_success=mainPLBP_i(get_ans_parameters,run_ANS,wim,TGBL inputdim,
										TGBL outputdim,TGBL trainset,TGBL desired,
										TGBL trainsetsize,TGBL testset,TGBL output,
										TGBL testsetsize,TGBL classif);
		  break;
  case 4: TGBL ANS_run_success=Interface_CTa_ans_Algorithm (CTA_ANS_BAM);
		  break;

  case 5: TGBL ANS_run_success=Interface_CTa_ans_Algorithm (CTA_ANS_MAM);
		  break;

  default:break;
  }
 }
mbeep();
return(msel);
}

/*-----------------------------------------------------------------------*/
