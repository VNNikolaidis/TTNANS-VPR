/*
    ---------------------
    TTN_ANS:
    TTNFNAME.C   ver.0.01
    ---------------------
    TTN V.Nikolaidis
    ---------------------
    Filename Utilities.
    ---------------------

*/

#ifndef TTNFNAME
#define TTNFNAME

extern int strrpos (char * s, char t);
extern void RemoveFilenameExtention(char * s);
extern void CdAndRemovePathInfo(char * pathfile);
extern void GetFilename(char * title,char * fname,char * filter,BOOL nopath);
extern void GetFileExtention(char * source, char * returned);

#endif
