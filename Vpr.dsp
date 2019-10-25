# Microsoft Developer Studio Project File - Name="VPR" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VPR - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Vpr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Vpr.mak" CFG="VPR - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VPR - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VPR - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "VPR - Win32 Release MMX" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VPR - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MY_RANDOM_" /D "_AXUM_COMPATIBLE_" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x408 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x408 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "VPR - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MY_RANDOM_" /D "_AXUM_COMPATIBLE_" /FR /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x408 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x408 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "VPR - Win32 Release MMX"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "VPR___Wi"
# PROP BASE Intermediate_Dir "VPR___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "VPR MMX Release"
# PROP Intermediate_Dir "VPR MMX Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MY_RANDOM_" /D "_AXUM_COMPATIBLE_" /FR /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MY_RANDOM_" /D "_AXUM_COMPATIBLE_" /D "_MMX_" /FR /FD /GM /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x408 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x408 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "VPR - Win32 Release"
# Name "VPR - Win32 Debug"
# Name "VPR - Win32 Release MMX"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_conec.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ta_iface.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_pe.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Tcon_glo.cpp
# End Source File
# Begin Source File

SOURCE=.\TTNANS\Tglobal.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnans.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnans1.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnans2.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnaxum.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnbandx.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnclafi.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttncon_f.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttncon_u.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ttncust2.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ttncustm.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndafi.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndata1.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndata2.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttneigen.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnerror.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnfilte.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnfname.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttngt.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ttnimage.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnkcn.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnlvqsw.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnmain.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnmath.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnmemor.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnother.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnpca.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnpca_2.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnplbp.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprb.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprep2.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprep3.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprepr.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnrand.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnreprt.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnreslt.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnsetti.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnthres.cpp
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnui.cpp
# End Source File
# Begin Source File

SOURCE=.\VPR.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\VPR.hpj

!IF  "$(CFG)" == "VPR - Win32 Release"

USERDEP__VPR_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	
# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Vpr
InputPath=.\hlp\VPR.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "VPR - Win32 Debug"

USERDEP__VPR_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Vpr
InputPath=.\hlp\VPR.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "VPR - Win32 Release MMX"

USERDEP__VPR_H="$(ProjDir)\hlp\AfxCore.rtf"	"$(ProjDir)\hlp\AfxPrint.rtf"	
# Begin Custom Build - Making help file...
OutDir=.\VPR MMX Release
ProjDir=.
TargetName=Vpr
InputPath=.\hlp\VPR.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	call "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VPR.rc
# End Source File
# Begin Source File

SOURCE=.\VPRDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\VPRView.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDdataset.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDfname.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDhint.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDmacro.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDmenu.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDoptions.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDprogress.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDprop.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDrqstr.cpp
# End Source File
# Begin Source File

SOURCE=.\VSDsplash.cpp
# End Source File
# Begin Source File

SOURCE=.\VSPcright.cpp
# End Source File
# Begin Source File

SOURCE=.\VSPpage1.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ta_acont.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_ans.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_bam.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_conec.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_envir.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ta_iface.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_layer.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_mam.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_pe.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ta_store.h
# End Source File
# Begin Source File

SOURCE=.\TTNANS\Tglobal.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Tmatrix.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnans.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnans1.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnans2.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnaxum.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnbandx.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnbool.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnclafi.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ttncustm.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndafi.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndata1.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndata2.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndef.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndef_n.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndef_o.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttndef_s.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttneigen.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnerror.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnfile.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnfilte.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnfname.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ttngt.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\ttnimage.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnkcn.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnlvqsw.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnmain.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnmath.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnmemor.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnnets.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnother.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnpca.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnpca_2.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnplbp.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprb.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprep2.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprep3.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnprepr.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnpros.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnreprt.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnreslt.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnsets.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnsetti.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnthres.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\Ttnui.h
# End Source File
# Begin Source File

SOURCE=.\VPR.h
# End Source File
# Begin Source File

SOURCE=.\VPRDoc.h
# End Source File
# Begin Source File

SOURCE=.\Ttnans\VPRiface.h
# End Source File
# Begin Source File

SOURCE=.\VPRrevision.h
# End Source File
# Begin Source File

SOURCE=.\VPRView.h
# End Source File
# Begin Source File

SOURCE=.\VSDdataset.h
# End Source File
# Begin Source File

SOURCE=.\VSDfname.h
# End Source File
# Begin Source File

SOURCE=.\VSDhint.h
# End Source File
# Begin Source File

SOURCE=.\VSDmacro.h
# End Source File
# Begin Source File

SOURCE=.\VSDmenu.h
# End Source File
# Begin Source File

SOURCE=.\VSDoptions.h
# End Source File
# Begin Source File

SOURCE=.\VSDprogress.h
# End Source File
# Begin Source File

SOURCE=.\VSDprop.h
# End Source File
# Begin Source File

SOURCE=.\VSDrqstr.h
# End Source File
# Begin Source File

SOURCE=.\VSDsplash.h
# End Source File
# Begin Source File

SOURCE=.\VSPcright.h
# End Source File
# Begin Source File

SOURCE=.\VSPpage1.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\qmark.ico
# End Source File
# Begin Source File

SOURCE=.\Res\rec1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\rec2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Untitled.BMP
# End Source File
# Begin Source File

SOURCE=.\res\VPR.ico
# End Source File
# Begin Source File

SOURCE=.\res\VPR.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VPRDoc.ico
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\VPR.cnt
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section VPR : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section VPR : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section VPR : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section VPR : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section VPR : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
