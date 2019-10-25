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

int strrpos (char * s, char t);
void RemoveFilenameExtension(char * s);
void GetFilename(char * title,char * fname,char * filter,bool nopath);
void GetFileExtension(char * source, char * returned);

#endif
