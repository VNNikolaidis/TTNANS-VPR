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

extern LAYER * NthLAYER(int n,ANS * ap);
extern LAYER * LAYERWithId(int id,ANS * ap);
extern BOOL    ExistsLAYERWithId(int id,ANS * ap);
extern NODE *  NODEwithId(int id, LAYER * lp);
extern LAYER * NODEsLAYER (ANS * ap,NODE * np);
extern int     NODEsLAYERId (ANS * ap,NODE * np);
extern LAYER * LINKsLAYER (ANS * ap,LINK * lkp);
extern int     LINKsLAYERId (ANS * ap,LINK * lkp);
extern int     NodesInLAYER(LAYER * lp);
extern NODE *  SetNODEFunction(DATA(*funct)(), NODE * np);
extern void    AppendNODE (NODE * np,LAYER * lp);
extern void    AppendNODEto1DLAYER(NODE * np,LAYER * lp);
extern NODE *  NewNODE(int id,int memorysize,ANS * ans);
extern void    EndNODE(NODE * np);
extern NODE *  RemoveNODEFromList(NODE * np, NODE ** nl);
extern void    AppendLINK (LINK * cp, LAYER * lp);
extern LINK *  DoLINK(NODE * np1,NODE * np2,LINK * lp); /* does NOT create np1,np2,lp.*/
extern LINK *  SetLINKWeight(DATA w, LINK * lp);
extern LINK *  SetLINKFunctions(DATA (*pf)(LINK *), DATA (*lf)(LINK *), LINK * lp);
extern LINK *  NewLINK(ANS * ans, int lmsize);
extern void    EndLINK(LINK * lp);
extern LINK *  RemoveLINKFromList(LINK * lp, LINK ** ll);
extern void    AppendLAYER(LAYER * lp, ANS * ap);
extern LAYER * NewLAYER(int id,int dim,int buffsize);
extern LAYER * FullSetupNew1DLAYER(int dim,int layerid,int buffsize,
				   DATA(*outfunct)(NODE *,int),int stmsize,ANS * ap);
extern void    EndLAYER(LAYER * lp);
extern LAYER * RemoveLAYERFromList(LAYER * lp, LAYER ** ll);
extern void    AppendANS(ANS * ap, ANS ** al);
extern ANS *   NewANS(int ins,int outs,int buffsize);
extern void    EndANS(ANS * ap);
extern ANS *   RemoveANSFromList(ANS * ap, ANS ** al);
extern void    ShowLINK(LINK * cp, ANS * ap);
extern void    ShowNODE(NODE * np,LAYER * lp, ANS * ap);
extern void    ShowLAYER(LAYER * lp, ANS * ap);
extern void    ShowANS(ANS * ap);
extern void    LinkLog(LAYER * lp);

#endif
