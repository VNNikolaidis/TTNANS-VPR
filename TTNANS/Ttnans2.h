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
 void   FullyConnect1DLAYERs(LAYER * src,LAYER * dst,int LINKbuffersize,
				   DATA(*pf)(LINK *),DATA (*lf)(LINK *),ANS * ap);
 void   PresentInputToLayer(DATA * dp,LAYER * lp,int sid);
 void   AddLinkTransferedDataToSTM(LAYER * lp,int stmnum);
 void   UpdateSingleLinkWeight(LINK * cp);
 bool   SnapshotAllLinkWeightsToLinkMems(LAYER * sourcelp, int lmid);
 void   UpdateLinkWeightsAtLayer(LAYER * lp);
 void   ResetAllNodeStmsTo0(LAYER * lp);
 bool   SetAllNodeSpecStm(LAYER * lp, int stmid, DATA value);
 void   ThresholdLayerNodes(LAYER * lp,int from_stm, int to_stm);
 void   AddNodeBiases(LAYER * lp,int deststm);
 void   SortLayerNodeIdsOnStm(LAYER * lp, int stmid);
 void   ShowLayerStms(LAYER * lp, int stmid);
 void   Snapshot1dLayerStms(LAYER * lp, int stmid,DATA * savevector);
 int    Winner1dLayerNodeId(LAYER * lp, int stmid, bool findbigger);
 NODE * Winner1dLayerNode(LAYER * lp, int stmid, bool findbigger);

#endif

