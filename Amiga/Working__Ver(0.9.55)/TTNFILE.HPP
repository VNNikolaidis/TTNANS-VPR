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

extern int file_open_counter;
extern void RewindFile(FHANDLE f);
extern void DeleteFile(char * fname);
extern BOOL FileExists(char * sourcefile);
extern FHANDLE OpenInFile(char * sourcefile);
extern FHANDLE OpenOutFile(char * destfile);
extern void CloseFile(FHANDLE handle);
extern BOOL FileOpenOK (FHANDLE f);
extern BOOL FileEOF (FHANDLE f);
extern BOOL IsEmptyFile(char * fname);
extern DATA ReadDATA(FHANDLE handle);
extern BOOL Read2dDATA(FHANDLE f, DATA ** Array, int rows, int cols);
extern BOOL ReadString(FHANDLE handle,char * s);
extern int ReadInt(FHANDLE handle);
extern void WriteDATA(FHANDLE handle,DATA data);
extern void WriteString(FHANDLE handle,char * s);
extern void WriteInt(FHANDLE handle,int i);
extern BOOL Write2dDATA(FHANDLE f, DATA ** Array, int rows, int cols);
extern int  SeekFirstDATAinFile(FHANDLE f,BOOL show);
extern void GetDataFileDims(char * fname, int * rownum, int * colnum);

#endif
