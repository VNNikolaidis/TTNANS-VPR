/*
  ---------------------
  TTNANS:
  TTNFILE.C    ver.0.01
  ---------------------
  Vasilis.N.Nikolaidis
  ---------------------
  ANSI File Utilities.
  ---------------------

*/

#ifndef TTNFILE
#define TTNFILE

 int get_file_open_counter();

 void file_guard_init();
 void file_guard_end();

 void RewindFile(FHANDLE f);
 void DeleteFile(char * fname);
 bool FileExists(char * sourcefile);
 FHANDLE OpenInFile(char * sourcefile);
 FHANDLE OpenOutFile(char * destfile);
 void CloseFile(FHANDLE handle);
 bool FileOpenOK (FHANDLE f);
 bool FileEOF (FHANDLE f);
 bool IsEmptyFile(char * fname);
 DATA ReadDATA(FHANDLE handle);
 bool Read2dDATA(FHANDLE f, DATA ** Array, int rows, int cols);
 bool ReadString(FHANDLE handle,char * s);
 int  ReadInt(FHANDLE handle); 
 void WriteDATA(FHANDLE handle,DATA data);
 void WriteString(FHANDLE handle,const char * s); 
 void WriteStringNL(FHANDLE handle,const char * s);
 void WriteInt(FHANDLE handle,int i);
 void WriteIntNL(FHANDLE handle,int i);
 bool Write2dDATA(FHANDLE f, DATA ** Array, int rows, int cols);
 int  SeekFirstDATAinFile(FHANDLE f,bool show);
 void GetDataFileDims(char * fname, int * rownum, int * colnum);

#endif
