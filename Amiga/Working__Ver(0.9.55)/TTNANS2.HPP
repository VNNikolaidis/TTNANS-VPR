/*
  ---------------------
  TTNANS:
  TTNANS2.C    ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  Additional ANS handl.
  ---------------------

*/

#ifndef TTNANS2
#define TTNANS2
extern void   FullyConnect1DLAYERs(LAYER * src,LAYER * dst,int LINKbuffersize,
				   DATA(*pf)(LINK *),DATA (*lf)(LINK *),ANS * ap);
extern void   PresentInputToLayer(DATA * dp,LAYER * lp,int sid);
extern void   AddLinkTransferedDataToSTM(LAYER * lp,int stmnum);
extern void   UpdateSingleLinkWeight(LINK * cp);
extern BOOL   SnapshotAllLinkWeightsToLinkMems(LAYER * sourcelp, int lmid);
extern void   UpdateLinkWeightsAtLayer(LAYER * lp);
extern void   ResetAllNodeStmsTo0(LAYER * lp);
extern BOOL   SetAllNodeSpecStm(LAYER * lp, int stmid, DATA value);
extern void   ThresholdLayerNodes(LAYER * lp,int from_stm, int to_stm);
extern void   AddNodeBiases(LAYER * lp,int deststm);
extern void   SortLayerNodeIdsOnStm(LAYER * lp, int stmid);
extern void   ShowLayerStms(LAYER * lp, int stmid);
extern void   Snapshot1dLayerStms(LAYER * lp, int stmid,DATA * savevector);
extern int    Winner1dLayerNodeId(LAYER * lp, int stmid, BOOL findbigger);
extern NODE * Winner1dLayerNode(LAYER * lp, int stmid, BOOL findbigger);

#endif

