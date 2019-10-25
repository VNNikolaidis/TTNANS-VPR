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

#include "TTNDEF.HPP"

#include "TTNMAIN.HPP"
#include "TTNERROR.HPP"
#include "TTNKCN.HPP"
#include "TTNLVQSW.HPP"
#include "TTNPLBP.HPP"

/*-----------------------------------------------------------------------*/

int ans_menu(int preselect,               /* -1 = Show menu              */
             BOOL take_action,            /* Don't just select an ANS.   */
             BOOL get_ans_parameters,     /* Ask for ANS parameters too. */
             BOOL run_ANS,                /* and run it                  */
             int wim)                     /* Weight Initialization Mode  */
{
int msel=preselect;

char *menu[]={"---------------------",
              "   A.N.S.   M e n u  ",
              "---------------------",
              "Select:              ",
              "0...No more processing - Go to previous menu.",
              "1...Kohonen Clustering Net.",
              "2...Learning Vector Quantization.",
              "3...Back Propagation Perceptron."
             };

ANS_run_success=FALSE;
if(no_error)
 {
 if(preselect<0) msel=mmenu(menu,8,4,0,3);

 if(take_action)
 switch(msel)
  {
  case 0: break;

  case 1:
          if(wim==IW_ANS_STANDARD)wim=IW_ZERO_TO_ONE;
          ANS_run_success=mainKCN_i(get_ans_parameters,run_ANS,wim,inputdim,outputdim,
                                    trainset,trainsetsize,testset,testsetsize,output,classif);
          break;
  case 2:
          if(wim==IW_ANS_STANDARD)wim=IW_ZERO_TO_ONE;
          ANS_run_success=mainLVQSWU_i(get_ans_parameters,run_ANS,wim,inputdim,outputdim,
                                       trainset,trainsetsize,testset,testsetsize,output,classif);
          break;
  case 3:
          if(wim==IW_ANS_STANDARD)wim=IW_MINUS_ONE_TO_ONE;
          ANS_run_success=mainPLBP_i(get_ans_parameters,run_ANS,wim,inputdim,outputdim,
                                     trainset,desired,trainsetsize,testset,output,testsetsize,classif);
          break;

  default:break;
  }
 }
mbeep();
return(msel);
}

/*-----------------------------------------------------------------------*/
