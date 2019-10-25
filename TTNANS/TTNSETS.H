#ifndef TTNSETS
#define TTNSETS

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#define IS_SUPERVISED_PROBLEM     ((TGBL desired!=NULL))
#define IS_UNSUPERVISED_PROBLEM   ((TGBL desired==NULL)&&((TGBL testset)!=(TGBL trainset)))
#define IS_CLUSTERING_PROBLEM     ((TGBL desired==NULL)&&((TGBL testset)==(TGBL trainset)))

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

#endif
