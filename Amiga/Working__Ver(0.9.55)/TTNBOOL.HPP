#ifndef TTNBOOL
#define TTNBOOL

#ifdef _MSWINDOWS_
 #include "windows.h"
#else
 #ifndef BOOL
  #define BOOL int
  #define FALSE 0
  #define TRUE 1
 #endif
#endif
#define UNDEFINED -999
#endif
