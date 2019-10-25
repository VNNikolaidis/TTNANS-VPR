/*
   --------------------
   TTNANS:
   TTNDAFI.C   ver.0.01
   --------------------
   Vasilis.N.Nikolaidis
   --------------------
   Data File Utilities
   --------------------

*/
#include "ttndef.h"
#include "ttndef_s.h"
#include "ttnmain.h"
#include "ttnui.h"

#include "ttndata1.h"
#include "ttnerror.h"
#include "ttnfname.h"
#include "ttnfile.h"
#include "ttnprepr.h"
#include "ttnprep3.h"
#include "ttnmemor.h"
#include "ttnfilte.h"

/*-----------------------------------------------------------------------*/

void DataFileUtility(void)
{
if((TGBL no_error)&&
   (mrequest_yn("Proceed with data file utility?")))
 {
 DATA ** data;
 int rows;
 int cols;
 int possible_reorderings;
 char datafilename[FILENAMELENGTH];
 FHANDLE datafile;

 GetFilename("Select data file to be processed.",datafilename,"*.*",true);

 if(!FileExists(datafilename))
  {
  mprintf("File does not exist.\n");
  return;
  }

 GetDataFileDims(datafilename,&rows,&cols);

 datafile=OpenInFile(datafilename);
 if(FileOpenOK(datafile))
  {
 
  mprintf("(Opened %s (%d x %d))\n",datafilename,rows,cols);

  data=MMalloc2dDATA(rows,cols);
  if(TGBL no_error)
   Read2dDATA(datafile,data,rows,cols);
  CloseFile(datafile);

  mprintf("(Done reading %s (%d x %d))\n",datafilename,rows,cols);


  if(TGBL no_error)
   {
   int msel=-1;
   char mtitle[]="  Data File Utility Menu   ";
   char * menu[]={"0...Free Data (exit the utility).",
                  "1...Show Data.",
                  "2...Preprocess Data.",
                  "3...Filter Data.",
                  "4...Functional Expantion of Data.",
			      "5...Reorder Data.",
                  "6...Save Data to File."
				  };		

   while ((TGBL no_error) AND (msel!=0))
    {
    msel=mmenu(mtitle,menu,7,6);
   
    switch(msel)
     {
	 case 1:	if(mrequest_yn("Show data set?")) Show2dDataSet(data,rows,cols,"Data Set");
				break;

	 case 2:    preprocess(-1,"data",data,rows,cols);
				break;

	 case 3:	{
				bool filtered_some = false;
				DATA ** ndata = NULL;
				int nrows,ncols;
				filtered_some=filter_set(data,rows,cols,&ndata,&nrows,&ncols);
				if(filtered_some)
				 {
				 if(mrequest_yn("Keep filtered data set?"))
				  {
				  MFree2dDATA(data,rows);
				  data=ndata;
                  rows=nrows;
                  cols=ncols;
                  }
                 }
				}
				break;

	case 4:		if(mrequest_yn("Perform Functional Expansion on data set?"))
				 cols=FunctionalExpansion("File Data",data,rows,cols);
				break;

	case 5:		if(mrequest_yn("Reorder data set?"))
				 {
				 reorder_set(ordering_info(SRE_NOT_SET,&possible_reorderings,rows,cols,true),0,data,rows,cols);
				 }
				break;

    case 6:		if(mrequest_yn("Save to file?"))
				 {
				 GetFilename("Select file to output to.",datafilename,"*.*",true);
				 datafile=OpenOutFile(datafilename);
				 if(FileOpenOK(datafile))
				  {
				  Write2dDATA(datafile,data,rows,cols);
				  CloseFile(datafile);
				  }
				 }
				break;
     } 
    }
   }
  mprintf("Freeing Data (%d x %d).\n",rows,cols);
  MFree2dDATA(data,rows);
  }
 }
}

/*-----------------------------------------------------------------------*/

