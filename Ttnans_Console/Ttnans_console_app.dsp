# Microsoft Developer Studio Project File - Name="ttnans_console_app" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ttnans_console_app - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ttnans_console_app.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ttnans_console_app.mak" CFG="ttnans_console_app - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ttnans_console_app - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ttnans_console_app - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ttnans_console_app - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_MY_MIN_AND_MAX_" /D "_MY_RANDOM_" /YX /FD /c
# ADD BASE RSC /l 0x408 /d "NDEBUG"
# ADD RSC /l 0x408 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ttnans_console_app - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_MY_MIN_AND_MAX_" /D "_MY_RANDOM_" /FR /YX /FD /c
# ADD BASE RSC /l 0x408 /d "_DEBUG"
# ADD RSC /l 0x408 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ttnans_console_app - Win32 Release"
# Name "ttnans_console_app - Win32 Debug"
# Begin Source File

SOURCE=..\Ttnans\TA_ans.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ta_bam.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_conec.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_conec.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_envir.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_iface.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_iface.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_layer.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_pe.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ta_pe.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TA_store.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Tcon_glo.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Tglobal.cpp
# End Source File
# Begin Source File

SOURCE=..\TTNANS\Tglobal.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Tmatrix.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnans.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNANS.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnans1.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNANS1.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnans2.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNANS2.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnaxum.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNAXUM.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnbandx.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNBANDX.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNBOOL.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnclafi.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNCLAFI.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttncon_f.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttncon_u.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ttncust2.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ttncustm.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttndafi.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNDAFI.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttndata1.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttndata1.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttndata2.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNDATA2.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttndef.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNDEF_N.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttndef_o.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNDEF_S.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttneigen.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNEIGEN.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnerror.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNERROR.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnfile.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNFILE.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnfilte.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNFILTE.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnfname.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnfname.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttngt.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ttngt.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\ttnimage.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnkcn.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNKCN.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnlvqsw.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNLVQSW.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnmain.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnmain.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnmath.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNMATH.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnmemor.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNMEMOR.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNNETS.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnother.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNOTHER.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnpca.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPCA.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnpca_2.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPCA_2.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnplbp.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPLBP.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnprb.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPRB.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnprep2.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPREP2.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnprep3.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPREP3.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnprepr.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnprepr.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNPROS.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnrand.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnreprt.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNREPRT.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnreslt.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNRESLT.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNSETS.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnsetti.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNSETTI.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnthres.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\TTNTHRES.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnui.cpp
# End Source File
# Begin Source File

SOURCE=..\Ttnans\Ttnui.h
# End Source File
# Begin Source File

SOURCE=..\Ttnans\VPRiface.h
# End Source File
# End Target
# End Project
