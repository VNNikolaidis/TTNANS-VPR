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
#include "ttndef.hpp"

#include "TTNDATA1.HPP"
#include "TTNERROR.HPP"
#include "TTNFNAME.HPP"
#include "TTNFILE.HPP"
#include "TTNPREPR.HPP"
#include "TTNPREP3.HPP"
#include "TTNMEMOR.HPP"

/*-----------------------------------------------------------------------*/

void DataFileUtility(void)
{
if((no_error)&&
   (mrequest_yn("Proceed with data file utility?")))
 {
 DATA ** data;
 int rows;
 int cols;
 int possible_reorderings;
 char datafilename[FILENAMELENGTH];
 FHANDLE datafile;

 GetFilename("Select data file to be processed.",datafilename,"*.*",TRUE);

 if(!FileExists(datafilename))
  {
  mprintf("File does not exist.\n");
  return;
  }

 GetDataFileDims(datafilename,&rows,&cols);

 datafile=OpenInFile(datafilename);
 if(FileOpenOK(datafile))
  {
  data=MMalloc2dDATA(rows,cols);
  if(no_error)
   Read2dDATA(datafile,data,rows,cols);

  CloseFile(datafile);

  if(no_error)
   {
   if(mrequest_yn("Show data set?"))
    Show2dDataSet(data,rows,cols);
   preprocess(-1,"data",data,rows,cols);
   if(mrequest_yn("Reorder data set?"))
    reorder_set(ordering_info(SRE_NOT_SET,&possible_reorderings,rows,cols,TRUE),
		0,data,rows,cols);
   if(mrequest_yn("Show modified data set?"))
    Show2dDataSet(data,rows,cols);
   if(mrequest_yn("Save to file?"))
    {
    GetFilename("Select file to output to.",datafilename,"*.*",TRUE);
    datafile=OpenOutFile(datafilename);
    if(FileOpenOK(datafile))
     {
     Write2dDATA(datafile,data,rows,cols);
     CloseFile(datafile);
     }
    }
   }
  MFree2dDATA(data,rows);
  }
 }
}

/*-----------------------------------------------------------------------*/

