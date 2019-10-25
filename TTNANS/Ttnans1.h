/*
  ---------------------
  TTNANS:
  TTNANS1.C    ver.0.02
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Basic ANS handling
  ---------------------
*/

#ifndef TTNANS1
#define  TTNANS1

#include "ttndef_n.h"

 LAYER * NthLAYER(int n,ANS * ap);
 LAYER * LAYERWithId(int id,ANS * ap);
 bool    ExistsLAYERWithId(int id,ANS * ap);
 NODE *  NODEwithId(int id, LAYER * lp);
 LAYER * NODEsLAYER (ANS * ap,NODE * np);
 int     NODEsLAYERId (ANS * ap,NODE * np);
 LAYER * LINKsLAYER (ANS * ap,LINK * lkp);
 int     LINKsLAYERId (ANS * ap,LINK * lkp);
 int     NodesInLAYER(LAYER * lp);
 NODE *  SetNODEFunction(DATA(*funct)(), NODE * np);
 void    AppendNODE (NODE * np,LAYER * lp);
 void    AppendNODEto1DLAYER(NODE * np,LAYER * lp);
 NODE *  NewNODE(int id,int memorysize,ANS * ans);
 void    EndNODE(NODE * np);
 NODE *  RemoveNODEFromList(NODE * np, NODE ** nl);
 void    AppendLINK (LINK * cp, LAYER * lp);
 LINK *  DoLINK(NODE * np1,NODE * np2,LINK * lp); /* does NOT create np1,np2,lp.*/
 LINK *  SetLINKWeight(DATA w, LINK * lp);
 LINK *  SetLINKFunctions(DATA (*pf)(LINK *), DATA (*lf)(LINK *), LINK * lp);
 LINK *  NewLINK(ANS * ans, int lmsize);
 void    EndLINK(LINK * lp);
 LINK *  RemoveLINKFromList(LINK * lp, LINK ** ll);
 void    AppendLAYER(LAYER * lp, ANS * ap);
 LAYER * NewLAYER(int id,int dim,int buffsize);
 LAYER * FullSetupNew1DLAYER(int dim,int layerid,int buffsize,
				   DATA(*outfunct)(NODE *,int),int stmsize,ANS * ap);
 void    EndLAYER(LAYER * lp);
 LAYER * RemoveLAYERFromList(LAYER * lp, LAYER ** ll);
 void    AppendANS(ANS * ap, ANS ** al);
 ANS *   NewANS(int ins,int outs,int buffsize);
 void    EndANS(ANS * ap);
 ANS *   RemoveANSFromList(ANS * ap, ANS ** al);
 void    ShowLINK(LINK * cp, ANS * ap);
 void    ShowNODE(NODE * np,LAYER * lp, ANS * ap);
 void    ShowLAYER(LAYER * lp, ANS * ap);
 void    ShowANS(ANS * ap);
 void    LinkLog(LAYER * lp);

#endif
