# Microsoft Developer Studio Generated NMAKE File, Based on Ttnans_console_app.dsp
!IF "$(CFG)" == ""
CFG=ttnans_console_app - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ttnans_console_app - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "ttnans_console_app - Win32 Release" && "$(CFG)" !=\
 "ttnans_console_app - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ttnans_console_app.mak"\
 CFG="ttnans_console_app - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ttnans_console_app - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "ttnans_console_app - Win32 Debug" (based on\
 "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Ttnans_console_app.exe"

!ELSE 

ALL : "$(OUTDIR)\Ttnans_console_app.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ta_conec.obj"
	-@erase "$(INTDIR)\ta_iface.obj"
	-@erase "$(INTDIR)\ta_pe.obj"
	-@erase "$(INTDIR)\Tcon_glo.obj"
	-@erase "$(INTDIR)\Tglobal.obj"
	-@erase "$(INTDIR)\Ttnans.obj"
	-@erase "$(INTDIR)\Ttnans1.obj"
	-@erase "$(INTDIR)\Ttnans2.obj"
	-@erase "$(INTDIR)\Ttnaxum.obj"
	-@erase "$(INTDIR)\Ttnbandx.obj"
	-@erase "$(INTDIR)\Ttnclafi.obj"
	-@erase "$(INTDIR)\Ttncon_f.obj"
	-@erase "$(INTDIR)\Ttncon_u.obj"
	-@erase "$(INTDIR)\ttncust2.obj"
	-@erase "$(INTDIR)\ttncustm.obj"
	-@erase "$(INTDIR)\Ttndafi.obj"
	-@erase "$(INTDIR)\Ttndata1.obj"
	-@erase "$(INTDIR)\Ttndata2.obj"
	-@erase "$(INTDIR)\Ttneigen.obj"
	-@erase "$(INTDIR)\Ttnerror.obj"
	-@erase "$(INTDIR)\Ttnfile.obj"
	-@erase "$(INTDIR)\Ttnfilte.obj"
	-@erase "$(INTDIR)\Ttnfname.obj"
	-@erase "$(INTDIR)\Ttngt.obj"
	-@erase "$(INTDIR)\ttnimage.obj"
	-@erase "$(INTDIR)\Ttnkcn.obj"
	-@erase "$(INTDIR)\Ttnlvqsw.obj"
	-@erase "$(INTDIR)\Ttnmain.obj"
	-@erase "$(INTDIR)\Ttnmath.obj"
	-@erase "$(INTDIR)\Ttnmemor.obj"
	-@erase "$(INTDIR)\Ttnother.obj"
	-@erase "$(INTDIR)\Ttnpca.obj"
	-@erase "$(INTDIR)\Ttnpca_2.obj"
	-@erase "$(INTDIR)\Ttnplbp.obj"
	-@erase "$(INTDIR)\Ttnprb.obj"
	-@erase "$(INTDIR)\Ttnprep2.obj"
	-@erase "$(INTDIR)\Ttnprep3.obj"
	-@erase "$(INTDIR)\Ttnprepr.obj"
	-@erase "$(INTDIR)\Ttnrand.obj"
	-@erase "$(INTDIR)\Ttnreprt.obj"
	-@erase "$(INTDIR)\Ttnreslt.obj"
	-@erase "$(INTDIR)\Ttnsetti.obj"
	-@erase "$(INTDIR)\Ttnthres.obj"
	-@erase "$(INTDIR)\Ttnui.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\Ttnans_console_app.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D\
 "_MBCS" /D "_MY_MIN_AND_MAX_" /D "_MY_RANDOM_"\
 /Fp"$(INTDIR)\Ttnans_console_app.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ttnans_console_app.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:no\
 /pdb:"$(OUTDIR)\Ttnans_console_app.pdb" /machine:I386\
 /out:"$(OUTDIR)\Ttnans_console_app.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ta_conec.obj" \
	"$(INTDIR)\ta_iface.obj" \
	"$(INTDIR)\ta_pe.obj" \
	"$(INTDIR)\Tcon_glo.obj" \
	"$(INTDIR)\Tglobal.obj" \
	"$(INTDIR)\Ttnans.obj" \
	"$(INTDIR)\Ttnans1.obj" \
	"$(INTDIR)\Ttnans2.obj" \
	"$(INTDIR)\Ttnaxum.obj" \
	"$(INTDIR)\Ttnbandx.obj" \
	"$(INTDIR)\Ttnclafi.obj" \
	"$(INTDIR)\Ttncon_f.obj" \
	"$(INTDIR)\Ttncon_u.obj" \
	"$(INTDIR)\ttncust2.obj" \
	"$(INTDIR)\ttncustm.obj" \
	"$(INTDIR)\Ttndafi.obj" \
	"$(INTDIR)\Ttndata1.obj" \
	"$(INTDIR)\Ttndata2.obj" \
	"$(INTDIR)\Ttneigen.obj" \
	"$(INTDIR)\Ttnerror.obj" \
	"$(INTDIR)\Ttnfile.obj" \
	"$(INTDIR)\Ttnfilte.obj" \
	"$(INTDIR)\Ttnfname.obj" \
	"$(INTDIR)\Ttngt.obj" \
	"$(INTDIR)\ttnimage.obj" \
	"$(INTDIR)\Ttnkcn.obj" \
	"$(INTDIR)\Ttnlvqsw.obj" \
	"$(INTDIR)\Ttnmain.obj" \
	"$(INTDIR)\Ttnmath.obj" \
	"$(INTDIR)\Ttnmemor.obj" \
	"$(INTDIR)\Ttnother.obj" \
	"$(INTDIR)\Ttnpca.obj" \
	"$(INTDIR)\Ttnpca_2.obj" \
	"$(INTDIR)\Ttnplbp.obj" \
	"$(INTDIR)\Ttnprb.obj" \
	"$(INTDIR)\Ttnprep2.obj" \
	"$(INTDIR)\Ttnprep3.obj" \
	"$(INTDIR)\Ttnprepr.obj" \
	"$(INTDIR)\Ttnrand.obj" \
	"$(INTDIR)\Ttnreprt.obj" \
	"$(INTDIR)\Ttnreslt.obj" \
	"$(INTDIR)\Ttnsetti.obj" \
	"$(INTDIR)\Ttnthres.obj" \
	"$(INTDIR)\Ttnui.obj"

"$(OUTDIR)\Ttnans_console_app.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Ttnans_console_app.exe" "$(OUTDIR)\Ttnans_console_app.bsc"

!ELSE 

ALL : "$(OUTDIR)\Ttnans_console_app.exe" "$(OUTDIR)\Ttnans_console_app.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ta_conec.obj"
	-@erase "$(INTDIR)\ta_conec.sbr"
	-@erase "$(INTDIR)\ta_iface.obj"
	-@erase "$(INTDIR)\ta_iface.sbr"
	-@erase "$(INTDIR)\ta_pe.obj"
	-@erase "$(INTDIR)\ta_pe.sbr"
	-@erase "$(INTDIR)\Tcon_glo.obj"
	-@erase "$(INTDIR)\Tcon_glo.sbr"
	-@erase "$(INTDIR)\Tglobal.obj"
	-@erase "$(INTDIR)\Tglobal.sbr"
	-@erase "$(INTDIR)\Ttnans.obj"
	-@erase "$(INTDIR)\Ttnans.sbr"
	-@erase "$(INTDIR)\Ttnans1.obj"
	-@erase "$(INTDIR)\Ttnans1.sbr"
	-@erase "$(INTDIR)\Ttnans2.obj"
	-@erase "$(INTDIR)\Ttnans2.sbr"
	-@erase "$(INTDIR)\Ttnaxum.obj"
	-@erase "$(INTDIR)\Ttnaxum.sbr"
	-@erase "$(INTDIR)\Ttnbandx.obj"
	-@erase "$(INTDIR)\Ttnbandx.sbr"
	-@erase "$(INTDIR)\Ttnclafi.obj"
	-@erase "$(INTDIR)\Ttnclafi.sbr"
	-@erase "$(INTDIR)\Ttncon_f.obj"
	-@erase "$(INTDIR)\Ttncon_f.sbr"
	-@erase "$(INTDIR)\Ttncon_u.obj"
	-@erase "$(INTDIR)\Ttncon_u.sbr"
	-@erase "$(INTDIR)\ttncust2.obj"
	-@erase "$(INTDIR)\ttncust2.sbr"
	-@erase "$(INTDIR)\ttncustm.obj"
	-@erase "$(INTDIR)\ttncustm.sbr"
	-@erase "$(INTDIR)\Ttndafi.obj"
	-@erase "$(INTDIR)\Ttndafi.sbr"
	-@erase "$(INTDIR)\Ttndata1.obj"
	-@erase "$(INTDIR)\Ttndata1.sbr"
	-@erase "$(INTDIR)\Ttndata2.obj"
	-@erase "$(INTDIR)\Ttndata2.sbr"
	-@erase "$(INTDIR)\Ttneigen.obj"
	-@erase "$(INTDIR)\Ttneigen.sbr"
	-@erase "$(INTDIR)\Ttnerror.obj"
	-@erase "$(INTDIR)\Ttnerror.sbr"
	-@erase "$(INTDIR)\Ttnfile.obj"
	-@erase "$(INTDIR)\Ttnfile.sbr"
	-@erase "$(INTDIR)\Ttnfilte.obj"
	-@erase "$(INTDIR)\Ttnfilte.sbr"
	-@erase "$(INTDIR)\Ttnfname.obj"
	-@erase "$(INTDIR)\Ttnfname.sbr"
	-@erase "$(INTDIR)\Ttngt.obj"
	-@erase "$(INTDIR)\Ttngt.sbr"
	-@erase "$(INTDIR)\ttnimage.obj"
	-@erase "$(INTDIR)\ttnimage.sbr"
	-@erase "$(INTDIR)\Ttnkcn.obj"
	-@erase "$(INTDIR)\Ttnkcn.sbr"
	-@erase "$(INTDIR)\Ttnlvqsw.obj"
	-@erase "$(INTDIR)\Ttnlvqsw.sbr"
	-@erase "$(INTDIR)\Ttnmain.obj"
	-@erase "$(INTDIR)\Ttnmain.sbr"
	-@erase "$(INTDIR)\Ttnmath.obj"
	-@erase "$(INTDIR)\Ttnmath.sbr"
	-@erase "$(INTDIR)\Ttnmemor.obj"
	-@erase "$(INTDIR)\Ttnmemor.sbr"
	-@erase "$(INTDIR)\Ttnother.obj"
	-@erase "$(INTDIR)\Ttnother.sbr"
	-@erase "$(INTDIR)\Ttnpca.obj"
	-@erase "$(INTDIR)\Ttnpca.sbr"
	-@erase "$(INTDIR)\Ttnpca_2.obj"
	-@erase "$(INTDIR)\Ttnpca_2.sbr"
	-@erase "$(INTDIR)\Ttnplbp.obj"
	-@erase "$(INTDIR)\Ttnplbp.sbr"
	-@erase "$(INTDIR)\Ttnprb.obj"
	-@erase "$(INTDIR)\Ttnprb.sbr"
	-@erase "$(INTDIR)\Ttnprep2.obj"
	-@erase "$(INTDIR)\Ttnprep2.sbr"
	-@erase "$(INTDIR)\Ttnprep3.obj"
	-@erase "$(INTDIR)\Ttnprep3.sbr"
	-@erase "$(INTDIR)\Ttnprepr.obj"
	-@erase "$(INTDIR)\Ttnprepr.sbr"
	-@erase "$(INTDIR)\Ttnrand.obj"
	-@erase "$(INTDIR)\Ttnrand.sbr"
	-@erase "$(INTDIR)\Ttnreprt.obj"
	-@erase "$(INTDIR)\Ttnreprt.sbr"
	-@erase "$(INTDIR)\Ttnreslt.obj"
	-@erase "$(INTDIR)\Ttnreslt.sbr"
	-@erase "$(INTDIR)\Ttnsetti.obj"
	-@erase "$(INTDIR)\Ttnsetti.sbr"
	-@erase "$(INTDIR)\Ttnthres.obj"
	-@erase "$(INTDIR)\Ttnthres.sbr"
	-@erase "$(INTDIR)\Ttnui.obj"
	-@erase "$(INTDIR)\Ttnui.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\Ttnans_console_app.bsc"
	-@erase "$(OUTDIR)\Ttnans_console_app.exe"
	-@erase "$(OUTDIR)\Ttnans_console_app.ilk"
	-@erase "$(OUTDIR)\Ttnans_console_app.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE"\
 /D "_MBCS" /D "_MY_MIN_AND_MAX_" /D "_MY_RANDOM_" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\Ttnans_console_app.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ttnans_console_app.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ta_conec.sbr" \
	"$(INTDIR)\ta_iface.sbr" \
	"$(INTDIR)\ta_pe.sbr" \
	"$(INTDIR)\Tcon_glo.sbr" \
	"$(INTDIR)\Tglobal.sbr" \
	"$(INTDIR)\Ttnans.sbr" \
	"$(INTDIR)\Ttnans1.sbr" \
	"$(INTDIR)\Ttnans2.sbr" \
	"$(INTDIR)\Ttnaxum.sbr" \
	"$(INTDIR)\Ttnbandx.sbr" \
	"$(INTDIR)\Ttnclafi.sbr" \
	"$(INTDIR)\Ttncon_f.sbr" \
	"$(INTDIR)\Ttncon_u.sbr" \
	"$(INTDIR)\ttncust2.sbr" \
	"$(INTDIR)\ttncustm.sbr" \
	"$(INTDIR)\Ttndafi.sbr" \
	"$(INTDIR)\Ttndata1.sbr" \
	"$(INTDIR)\Ttndata2.sbr" \
	"$(INTDIR)\Ttneigen.sbr" \
	"$(INTDIR)\Ttnerror.sbr" \
	"$(INTDIR)\Ttnfile.sbr" \
	"$(INTDIR)\Ttnfilte.sbr" \
	"$(INTDIR)\Ttnfname.sbr" \
	"$(INTDIR)\Ttngt.sbr" \
	"$(INTDIR)\ttnimage.sbr" \
	"$(INTDIR)\Ttnkcn.sbr" \
	"$(INTDIR)\Ttnlvqsw.sbr" \
	"$(INTDIR)\Ttnmain.sbr" \
	"$(INTDIR)\Ttnmath.sbr" \
	"$(INTDIR)\Ttnmemor.sbr" \
	"$(INTDIR)\Ttnother.sbr" \
	"$(INTDIR)\Ttnpca.sbr" \
	"$(INTDIR)\Ttnpca_2.sbr" \
	"$(INTDIR)\Ttnplbp.sbr" \
	"$(INTDIR)\Ttnprb.sbr" \
	"$(INTDIR)\Ttnprep2.sbr" \
	"$(INTDIR)\Ttnprep3.sbr" \
	"$(INTDIR)\Ttnprepr.sbr" \
	"$(INTDIR)\Ttnrand.sbr" \
	"$(INTDIR)\Ttnreprt.sbr" \
	"$(INTDIR)\Ttnreslt.sbr" \
	"$(INTDIR)\Ttnsetti.sbr" \
	"$(INTDIR)\Ttnthres.sbr" \
	"$(INTDIR)\Ttnui.sbr"

"$(OUTDIR)\Ttnans_console_app.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:console /incremental:yes\
 /pdb:"$(OUTDIR)\Ttnans_console_app.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\Ttnans_console_app.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ta_conec.obj" \
	"$(INTDIR)\ta_iface.obj" \
	"$(INTDIR)\ta_pe.obj" \
	"$(INTDIR)\Tcon_glo.obj" \
	"$(INTDIR)\Tglobal.obj" \
	"$(INTDIR)\Ttnans.obj" \
	"$(INTDIR)\Ttnans1.obj" \
	"$(INTDIR)\Ttnans2.obj" \
	"$(INTDIR)\Ttnaxum.obj" \
	"$(INTDIR)\Ttnbandx.obj" \
	"$(INTDIR)\Ttnclafi.obj" \
	"$(INTDIR)\Ttncon_f.obj" \
	"$(INTDIR)\Ttncon_u.obj" \
	"$(INTDIR)\ttncust2.obj" \
	"$(INTDIR)\ttncustm.obj" \
	"$(INTDIR)\Ttndafi.obj" \
	"$(INTDIR)\Ttndata1.obj" \
	"$(INTDIR)\Ttndata2.obj" \
	"$(INTDIR)\Ttneigen.obj" \
	"$(INTDIR)\Ttnerror.obj" \
	"$(INTDIR)\Ttnfile.obj" \
	"$(INTDIR)\Ttnfilte.obj" \
	"$(INTDIR)\Ttnfname.obj" \
	"$(INTDIR)\Ttngt.obj" \
	"$(INTDIR)\ttnimage.obj" \
	"$(INTDIR)\Ttnkcn.obj" \
	"$(INTDIR)\Ttnlvqsw.obj" \
	"$(INTDIR)\Ttnmain.obj" \
	"$(INTDIR)\Ttnmath.obj" \
	"$(INTDIR)\Ttnmemor.obj" \
	"$(INTDIR)\Ttnother.obj" \
	"$(INTDIR)\Ttnpca.obj" \
	"$(INTDIR)\Ttnpca_2.obj" \
	"$(INTDIR)\Ttnplbp.obj" \
	"$(INTDIR)\Ttnprb.obj" \
	"$(INTDIR)\Ttnprep2.obj" \
	"$(INTDIR)\Ttnprep3.obj" \
	"$(INTDIR)\Ttnprepr.obj" \
	"$(INTDIR)\Ttnrand.obj" \
	"$(INTDIR)\Ttnreprt.obj" \
	"$(INTDIR)\Ttnreslt.obj" \
	"$(INTDIR)\Ttnsetti.obj" \
	"$(INTDIR)\Ttnthres.obj" \
	"$(INTDIR)\Ttnui.obj"

"$(OUTDIR)\Ttnans_console_app.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "ttnans_console_app - Win32 Release" || "$(CFG)" ==\
 "ttnans_console_app - Win32 Debug"
SOURCE=..\Ttnans\ta_conec.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TA_CO=\
	"..\Ttnans\Ta_ans.h"\
	"..\Ttnans\Ta_conec.h"\
	"..\Ttnans\Ta_envir.h"\
	"..\Ttnans\Ta_layer.h"\
	"..\Ttnans\Ta_pe.h"\
	"..\Ttnans\Ta_store.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ta_conec.obj" : $(SOURCE) $(DEP_CPP_TA_CO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TA_CO=\
	"..\StdAfx.h"\
	"..\Ttnans\Ta_ans.h"\
	"..\Ttnans\Ta_conec.h"\
	"..\Ttnans\Ta_envir.h"\
	"..\Ttnans\Ta_layer.h"\
	"..\Ttnans\Ta_pe.h"\
	"..\Ttnans\Ta_store.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\ta_conec.obj"	"$(INTDIR)\ta_conec.sbr" : $(SOURCE) $(DEP_CPP_TA_CO)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\ta_iface.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TA_IF=\
	"..\Ttnans\Ta_ans.h"\
	"..\Ttnans\Ta_bam.h"\
	"..\Ttnans\Ta_conec.h"\
	"..\Ttnans\Ta_envir.h"\
	"..\Ttnans\ta_iface.h"\
	"..\Ttnans\Ta_layer.h"\
	"..\Ttnans\Ta_mam.h"\
	"..\Ttnans\Ta_pe.h"\
	"..\Ttnans\Ta_store.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ta_iface.obj" : $(SOURCE) $(DEP_CPP_TA_IF) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TA_IF=\
	"..\StdAfx.h"\
	"..\Ttnans\Ta_ans.h"\
	"..\Ttnans\Ta_bam.h"\
	"..\Ttnans\Ta_conec.h"\
	"..\Ttnans\Ta_envir.h"\
	"..\Ttnans\ta_iface.h"\
	"..\Ttnans\Ta_layer.h"\
	"..\Ttnans\Ta_mam.h"\
	"..\Ttnans\Ta_pe.h"\
	"..\Ttnans\Ta_store.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\ta_iface.obj"	"$(INTDIR)\ta_iface.sbr" : $(SOURCE) $(DEP_CPP_TA_IF)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\ta_pe.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TA_PE=\
	"..\Ttnans\Ta_pe.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ta_pe.obj" : $(SOURCE) $(DEP_CPP_TA_PE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TA_PE=\
	"..\Ttnans\Ta_pe.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ta_pe.obj"	"$(INTDIR)\ta_pe.sbr" : $(SOURCE) $(DEP_CPP_TA_PE)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Tcon_glo.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TCON_=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef_o.h"\
	

"$(INTDIR)\Tcon_glo.obj" : $(SOURCE) $(DEP_CPP_TCON_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TCON_=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Tcon_glo.obj"	"$(INTDIR)\Tcon_glo.sbr" : $(SOURCE) $(DEP_CPP_TCON_)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Tglobal.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"


"$(INTDIR)\Tglobal.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TGLOB=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRrevision.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Tglobal.obj"	"$(INTDIR)\Tglobal.sbr" : $(SOURCE) $(DEP_CPP_TGLOB)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnans.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNAN=\
	"..\Ttnans\ta_iface.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnkcn.h"\
	"..\Ttnans\Ttnlvqsw.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnplbp.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnans.obj" : $(SOURCE) $(DEP_CPP_TTNAN) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNAN=\
	"..\StdAfx.h"\
	"..\Ttnans\ta_iface.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnkcn.h"\
	"..\Ttnans\Ttnlvqsw.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnplbp.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnans.obj"	"$(INTDIR)\Ttnans.sbr" : $(SOURCE) $(DEP_CPP_TTNAN)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnans1.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNANS=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnans1.obj" : $(SOURCE) $(DEP_CPP_TTNANS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNANS=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnans1.obj"	"$(INTDIR)\Ttnans1.sbr" : $(SOURCE) $(DEP_CPP_TTNANS)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnans2.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNANS2=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnans2.obj" : $(SOURCE) $(DEP_CPP_TTNANS2) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNANS2=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnans2.obj"	"$(INTDIR)\Ttnans2.sbr" : $(SOURCE) $(DEP_CPP_TTNANS2)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnaxum.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNAX=\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnaxum.obj" : $(SOURCE) $(DEP_CPP_TTNAX) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNAX=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnclafi.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnaxum.obj"	"$(INTDIR)\Ttnaxum.sbr" : $(SOURCE) $(DEP_CPP_TTNAX)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnbandx.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNBA=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep3.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnbandx.obj" : $(SOURCE) $(DEP_CPP_TTNBA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNBA=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep3.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnbandx.obj"	"$(INTDIR)\Ttnbandx.sbr" : $(SOURCE) $(DEP_CPP_TTNBA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnclafi.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNCL=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnclafi.obj" : $(SOURCE) $(DEP_CPP_TTNCL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNCL=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnclafi.obj"	"$(INTDIR)\Ttnclafi.sbr" : $(SOURCE) $(DEP_CPP_TTNCL)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttncon_f.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNCO=\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttncon_f.obj" : $(SOURCE) $(DEP_CPP_TTNCO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNCO=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	
NODEP_CPP_TTNCO=\
	"..\Ttnans\ttngui0.h"\
	"..\Ttnans\ttnident.h"\
	

"$(INTDIR)\Ttncon_f.obj"	"$(INTDIR)\Ttncon_f.sbr" : $(SOURCE) $(DEP_CPP_TTNCO)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttncon_u.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNCON=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnbool.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnreprt.h"\
	

"$(INTDIR)\Ttncon_u.obj" : $(SOURCE) $(DEP_CPP_TTNCON) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNCON=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnbool.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnreprt.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttncon_u.obj"	"$(INTDIR)\Ttncon_u.sbr" : $(SOURCE) $(DEP_CPP_TTNCON)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\ttncust2.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNCU=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ttncust2.obj" : $(SOURCE) $(DEP_CPP_TTNCU) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNCU=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\ttncust2.obj"	"$(INTDIR)\ttncust2.sbr" : $(SOURCE) $(DEP_CPP_TTNCU)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\ttncustm.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNCUS=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ttncustm.obj" : $(SOURCE) $(DEP_CPP_TTNCUS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNCUS=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\ttncustm.obj"	"$(INTDIR)\ttncustm.sbr" : $(SOURCE) $(DEP_CPP_TTNCUS)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttndafi.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNDA=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfilte.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep3.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttndafi.obj" : $(SOURCE) $(DEP_CPP_TTNDA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNDA=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfilte.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep3.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttndafi.obj"	"$(INTDIR)\Ttndafi.sbr" : $(SOURCE) $(DEP_CPP_TTNDA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttndata1.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNDAT=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttndata1.obj" : $(SOURCE) $(DEP_CPP_TTNDAT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNDAT=\
	"..\msflexgrid.h"\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnreprt.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDdataset.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttndata1.obj"	"$(INTDIR)\Ttndata1.sbr" : $(SOURCE) $(DEP_CPP_TTNDAT)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttndata2.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNDATA=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttndata2.obj" : $(SOURCE) $(DEP_CPP_TTNDATA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNDATA=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttndata2.obj"	"$(INTDIR)\Ttndata2.sbr" : $(SOURCE)\
 $(DEP_CPP_TTNDATA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttneigen.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNEI=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttneigen.obj" : $(SOURCE) $(DEP_CPP_TTNEI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNEI=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttneigen.obj"	"$(INTDIR)\Ttneigen.sbr" : $(SOURCE) $(DEP_CPP_TTNEI)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnerror.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNER=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnerror.obj" : $(SOURCE) $(DEP_CPP_TTNER) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNER=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnerror.obj"	"$(INTDIR)\Ttnerror.sbr" : $(SOURCE) $(DEP_CPP_TTNER)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnfile.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNFI=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnfile.obj" : $(SOURCE) $(DEP_CPP_TTNFI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNFI=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnfile.obj"	"$(INTDIR)\Ttnfile.sbr" : $(SOURCE) $(DEP_CPP_TTNFI)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnfilte.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNFIL=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnfilte.obj" : $(SOURCE) $(DEP_CPP_TTNFIL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNFIL=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnfilte.obj"	"$(INTDIR)\Ttnfilte.sbr" : $(SOURCE) $(DEP_CPP_TTNFIL)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnfname.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNFN=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnfname.obj" : $(SOURCE) $(DEP_CPP_TTNFN) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNFN=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDfname.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnfname.obj"	"$(INTDIR)\Ttnfname.sbr" : $(SOURCE) $(DEP_CPP_TTNFN)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttngt.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNGT=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttngt.obj" : $(SOURCE) $(DEP_CPP_TTNGT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNGT=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttngt.obj"	"$(INTDIR)\Ttngt.sbr" : $(SOURCE) $(DEP_CPP_TTNGT)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\ttnimage.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNIM=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\ttnimage.obj" : $(SOURCE) $(DEP_CPP_TTNIM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNIM=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\ttnimage.obj"	"$(INTDIR)\ttnimage.sbr" : $(SOURCE) $(DEP_CPP_TTNIM)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnkcn.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNKC=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttnans2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnnets.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnkcn.obj" : $(SOURCE) $(DEP_CPP_TTNKC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNKC=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttnans2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnnets.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnkcn.obj"	"$(INTDIR)\Ttnkcn.sbr" : $(SOURCE) $(DEP_CPP_TTNKC)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnlvqsw.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNLV=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttnans2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnnets.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnthres.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnlvqsw.obj" : $(SOURCE) $(DEP_CPP_TTNLV) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNLV=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttnans2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnnets.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnthres.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnlvqsw.obj"	"$(INTDIR)\Ttnlvqsw.sbr" : $(SOURCE) $(DEP_CPP_TTNLV)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnmain.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNMA=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\ttncustm.h"\
	"..\Ttnans\Ttndafi.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\ttngt.h"\
	"..\Ttnans\ttnimage.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnother.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnreprt.h"\
	"..\Ttnans\Ttnreslt.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnmain.obj" : $(SOURCE) $(DEP_CPP_TTNMA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNMA=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\ttncustm.h"\
	"..\Ttnans\Ttndafi.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndata2.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\ttngt.h"\
	"..\Ttnans\ttnimage.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnother.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnprepr.h"\
	"..\Ttnans\Ttnreprt.h"\
	"..\Ttnans\Ttnreslt.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRrevision.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnmain.obj"	"$(INTDIR)\Ttnmain.sbr" : $(SOURCE) $(DEP_CPP_TTNMA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnmath.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNMAT=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnmath.obj" : $(SOURCE) $(DEP_CPP_TTNMAT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNMAT=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnmath.obj"	"$(INTDIR)\Ttnmath.sbr" : $(SOURCE) $(DEP_CPP_TTNMAT)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnmemor.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNME=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnmemor.obj" : $(SOURCE) $(DEP_CPP_TTNME) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNME=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnmemor.obj"	"$(INTDIR)\Ttnmemor.sbr" : $(SOURCE) $(DEP_CPP_TTNME)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnother.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNOT=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep3.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnother.obj" : $(SOURCE) $(DEP_CPP_TTNOT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNOT=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep3.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnother.obj"	"$(INTDIR)\Ttnother.sbr" : $(SOURCE) $(DEP_CPP_TTNOT)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnpca.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPC=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnpca.obj" : $(SOURCE) $(DEP_CPP_TTNPC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPC=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnpca.obj"	"$(INTDIR)\Ttnpca.sbr" : $(SOURCE) $(DEP_CPP_TTNPC)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnpca_2.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPCA=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnpca_2.obj" : $(SOURCE) $(DEP_CPP_TTNPCA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPCA=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnpca_2.obj"	"$(INTDIR)\Ttnpca_2.sbr" : $(SOURCE) $(DEP_CPP_TTNPCA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnplbp.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPL=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttnans2.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnnets.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnplbp.obj" : $(SOURCE) $(DEP_CPP_TTNPL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPL=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttnans1.h"\
	"..\Ttnans\Ttnans2.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnnets.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsetti.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnplbp.obj"	"$(INTDIR)\Ttnplbp.sbr" : $(SOURCE) $(DEP_CPP_TTNPL)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnprb.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPR=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnprb.obj" : $(SOURCE) $(DEP_CPP_TTNPR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPR=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprb.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnprb.obj"	"$(INTDIR)\Ttnprb.sbr" : $(SOURCE) $(DEP_CPP_TTNPR)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnprep2.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPRE=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnprep2.obj" : $(SOURCE) $(DEP_CPP_TTNPRE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPRE=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnprep2.obj"	"$(INTDIR)\Ttnprep2.sbr" : $(SOURCE) $(DEP_CPP_TTNPRE)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnprep3.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPREP=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep2.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnprep3.obj" : $(SOURCE) $(DEP_CPP_TTNPREP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPREP=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep2.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnprep3.obj"	"$(INTDIR)\Ttnprep3.sbr" : $(SOURCE)\
 $(DEP_CPP_TTNPREP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnprepr.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNPREPR=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpca.h"\
	"..\Ttnans\Ttnpca_2.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnprepr.obj" : $(SOURCE) $(DEP_CPP_TTNPREPR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNPREPR=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpca.h"\
	"..\Ttnans\Ttnpca_2.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnprepr.obj"	"$(INTDIR)\Ttnprepr.sbr" : $(SOURCE)\
 $(DEP_CPP_TTNPREPR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnrand.cpp
DEP_CPP_TTNRA=\
	"..\Ttnans\Ttndef.h"\
	

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"


"$(INTDIR)\Ttnrand.obj" : $(SOURCE) $(DEP_CPP_TTNRA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"


"$(INTDIR)\Ttnrand.obj"	"$(INTDIR)\Ttnrand.sbr" : $(SOURCE) $(DEP_CPP_TTNRA)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnreprt.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNRE=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnreprt.obj" : $(SOURCE) $(DEP_CPP_TTNRE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNRE=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnreprt.obj"	"$(INTDIR)\Ttnreprt.sbr" : $(SOURCE) $(DEP_CPP_TTNRE)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnreslt.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNRES=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttnaxum.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\Ttnclafi.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnreslt.obj" : $(SOURCE) $(DEP_CPP_TTNRES) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNRES=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Tmatrix.h"\
	"..\Ttnans\Ttnaxum.h"\
	"..\Ttnans\Ttnbandx.h"\
	"..\Ttnans\Ttnclafi.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttneigen.h"\
	"..\Ttnans\Ttnerror.h"\
	"..\Ttnans\Ttnfile.h"\
	"..\Ttnans\Ttnfname.h"\
	"..\Ttnans\Ttnmain.h"\
	"..\Ttnans\Ttnmath.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnreslt.obj"	"$(INTDIR)\Ttnreslt.sbr" : $(SOURCE) $(DEP_CPP_TTNRES)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnsetti.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNSE=\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep2.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	

"$(INTDIR)\Ttnsetti.obj" : $(SOURCE) $(DEP_CPP_TTNSE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNSE=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndata1.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnprep2.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnsets.h"\
	"..\Ttnans\Ttnui.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDprop.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnsetti.obj"	"$(INTDIR)\Ttnsetti.sbr" : $(SOURCE) $(DEP_CPP_TTNSE)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnthres.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

DEP_CPP_TTNTH=\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	

"$(INTDIR)\Ttnthres.obj" : $(SOURCE) $(DEP_CPP_TTNTH) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNTH=\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_n.h"\
	"..\Ttnans\Ttndef_o.h"\
	

"$(INTDIR)\Ttnthres.obj"	"$(INTDIR)\Ttnthres.sbr" : $(SOURCE) $(DEP_CPP_TTNTH)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\Ttnans\Ttnui.cpp

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"


"$(INTDIR)\Ttnui.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

DEP_CPP_TTNUI=\
	"..\StdAfx.h"\
	"..\TTNANS\Tglobal.h"\
	"..\Ttnans\Ttndef.h"\
	"..\Ttnans\Ttndef_o.h"\
	"..\Ttnans\Ttndef_s.h"\
	"..\Ttnans\Ttnmemor.h"\
	"..\Ttnans\Ttnpros.h"\
	"..\Ttnans\Ttnreprt.h"\
	"..\VPR.h"\
	"..\VPRDoc.h"\
	"..\VPRView.h"\
	"..\VSDmenu.h"\
	"..\VSDprogress.h"\
	"..\VSDprop.h"\
	"..\VSDrqstr.h"\
	"..\VSPcright.h"\
	"..\VSPpage1.h"\
	

"$(INTDIR)\Ttnui.obj"	"$(INTDIR)\Ttnui.sbr" : $(SOURCE) $(DEP_CPP_TTNUI)\
 "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

