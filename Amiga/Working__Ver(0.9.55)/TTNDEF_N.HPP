/* --------------------
   ANS Def ver.0.3
   --------------------
   Vasilis.N.Nikolaidis
   -------------------- */

#ifndef TTNDEF_N
#define TTNDEF_N

/*-----------------------------------------------------------------------*/

#define NODE  struct NODE_
#define LINK  struct LINK_
#define LAYER struct LAYER_
#define ANS   struct ANS_

/*-----------------------------------------------------------------------*/

ANS;                         /* Incomplete def. of ANS (struct ANS_).    */

NODE                         /* structure declaration of neuron.         */
 {
 int  id;
 int  stmsize;               /* Indicates the node's number in LAYER.    */
 DATA * stm;                 /* short term memory                        */
 DATA bias;                  /* bias                                     */
 DATA (*outfunction)(NODE *, /* PE function acting upon specified stm.   */
                     int);   /* (such as threshold function - optional)  */
 ANS  * ans;                 /* used to access ANS local memory (abuff). */
 NODE * prev;                /* previous NODE in linked list of NODEs.   */
 NODE * next;                /* next NODE in linked list of NODEs.       */
 };

LINK                         /* structure declaration LINK (connection). */
 {
 int  cbuffsize;             /* local memory buffer size. lm is used for */
 DATA * cbuff;               /* storage of other data (eg learnin.rates).*/
 NODE * source;              /* this LINK goes from source to destin.    */
 NODE * destin;
 DATA weight;                /* weight of source to destination LINK.    */
 DATA (*processfunction)     /* function modifying data using weight.    */
                    (LINK *);
 DATA (*learnfunction)       /* function adjusting weights.              */
                    (LINK *);
 ANS  * ans;                 /* ANS * is for optional ans->buff access.  */
 LINK * prev;                /* previous LINK in linked list of LINKs.   */
 LINK * next;                /* next LINK in linked list of LINKs.       */
 };

LAYER                        /* structure declaration of layer.          */
 {
 int id;
 int dim;                    /* Number of dimentions (1,2,etc dim.layer).*/
 int * dims;                 /* Actual size of each dimention            */
 int  lbuffsize;             /* local memory buffer size. lm is used for */
 DATA * lbuff;               /* storage of other data (eg learnin.rates).*/
 NODE  * nodes;              /* linked list of NODEs in layer.           */
 LINK  * links;              /* linked list of LINKs (outgoing).         */
 LAYER * prev;
 LAYER * next;
 };

ANS                          /* structure declaration of neural network. */
 {
 int     inputdim;           /* local size of input  (usualy == global)  */
 int     outputdim;          /* local size of output (usualy == global)  */
 int     numoflayers;
 LAYER * inputlayer;
 LAYER * outputlayer;
 LAYER * layers;             /* linked list of LAYERs(order significant).*/
 DATA    abuffsize;
 DATA  * abuff;              /* a local buffer used to store misc. stuff.*/
 ANS   * prev;               /* prev,next ans are optional, used in case */
 ANS   * next;               /* there are more than one ans's (ans list).*/
 };

/*-----------------------------------------------------------------------*/

#endif
