; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VPR.h"
LastPage=0

ClassCount=16
Class1=CVPRApp
Class2=CVPRDoc
Class3=CVPRView
Class4=CMainFrame

ResourceCount=27
Resource1=IDD_SD_REQSTRING (Greek)
Resource2=IDD_SP_COPYRIGHT (Greek)
Class5=CAboutDlg
Resource3=IDR_MAINFRAME (English (U.S.))
Resource4=IDD_SD_HINT
Class6=CVSDrqstr
Resource5=IDD_SD_DATASET
Class7=CVSDmenu
Class8=CVSDfname
Resource6=IDD_SD_OPTIONS
Class9=CVSDsplash
Resource7=IDD_SP_PAGE_1
Class10=CVSDprogress
Resource8=IDD_SP_RICHEDIT (Greek)
Class11=CVSPcright
Resource9=IDD_SD_MENU (Greek)
Resource10=IDD_SD_MENU
Resource11=IDD_SP_PAGE_1 (Greek)
Resource12=IDD_SD_PROGRESS (Greek)
Resource13=IDD_SD_OPTIONS (Greek)
Resource14=IDD_SD_SPLASH (Greek)
Resource15=IDD_ABOUTBOX
Resource16=IDD_SD_SPLASH
Class12=CVSPpage1
Class13=CVSDhint
Resource17=IDD_SD_MACRO (Greek)
Resource18=IDD_SD_PROGRESS
Resource19=IDR_HINTMENU (Greek)
Resource20=IDR_MAINFRAME
Resource21=IDR_HINTMENU
Class14=CVSDdataset
Resource22=IDD_SD_REQSTRING
Class15=CVSDoptions
Resource23=IDD_SP_COPYRIGHT
Class16=CVSDmacro
Resource24=IDD_ABOUTBOX (English (U.S.))
Resource25=IDD_SD_HINT (Greek)
Resource26=IDD_SD_DATASET (Greek)
Resource27=IDD_SD_MACRO

[CLS:CVPRApp]
Type=0
HeaderFile=VPR.h
ImplementationFile=VPR.cpp
Filter=N
LastObject=CVPRApp

[CLS:CVPRDoc]
Type=0
HeaderFile=VPRDoc.h
ImplementationFile=VPRDoc.cpp
Filter=N
LastObject=CVPRDoc
BaseClass=CDocument
VirtualFilter=DC

[CLS:CVPRView]
Type=0
HeaderFile=VPRView.h
ImplementationFile=VPRView.cpp
Filter=C
LastObject=ID_RUN_TTNMENU7
BaseClass=CEditView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=VPR.cpp
ImplementationFile=VPR.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308481
Control7=IDC_STATIC,static,1342308481
Control8=IDC_STATIC,button,1342178055

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_RUN_TTNANS_REC
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_RUN_TTNANS
Command12=ID_RUN_TTNMENU1
Command13=ID_RUN_TTNMENU2
Command14=ID_RUN_TTNMENU3
Command15=ID_RUN_TTNMENU4
Command16=ID_RUN_TTNMENU5
Command17=ID_RUN_TTNMENU6
Command18=ID_RUN_TTNMENU7
Command19=ID_RUN_TTNMENU8
Command20=ID_EDIT_UNDO
Command21=ID_EDIT_CUT
Command22=ID_EDIT_COPY
Command23=ID_EDIT_PASTE
Command24=ID_VIEW_TOOLBAR
Command25=ID_VIEW_STATUS_BAR
Command26=ID_MISC_OPTIONS
Command27=ID_MISC_CLEARSCREEN_ON
Command28=ID_MISC_CLEARSCREEN_OFF
Command29=ID_MISC_MODALDLGS
Command30=ID_MISC_SETSINWIN
Command31=ID_MISC_HINT
Command32=ID_HELP_FINDER
Command33=ID_APP_ABOUT
CommandCount=33

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_RUN_TTNANS
Command5=ID_RUN_TTNMENU1
Command6=ID_RUN_TTNMENU2
Command7=ID_RUN_TTNMENU3
Command8=ID_RUN_TTNMENU4
Command9=ID_RUN_TTNMENU5
Command10=ID_RUN_TTNMENU6
Command11=ID_RUN_TTNMENU7
Command12=ID_RUN_TTNMENU8
Command13=ID_MISC_CLEARSCREEN_NOW
Command14=ID_MISC_CLEARSCREEN_ON
Command15=ID_MISC_CLEARSCREEN_OFF
Command16=ID_MISC_TEXTOUTPUTON
Command17=ID_MISC_TEXTOUTPUTOFF
Command18=ID_MACRO
Command19=ID_EDIT_CUT
Command20=ID_EDIT_COPY
Command21=ID_EDIT_PASTE
Command22=ID_FILE_PRINT
Command23=ID_APP_ABOUT
Command24=ID_CONTEXT_HELP
CommandCount=24

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_RUN_TTNANS_REC
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_RUN_TTNANS
Command12=ID_RUN_TTNMENU1
Command13=ID_RUN_TTNMENU2
Command14=ID_RUN_TTNMENU3
Command15=ID_RUN_TTNMENU4
Command16=ID_RUN_TTNMENU5
Command17=ID_RUN_TTNMENU6
Command18=ID_RUN_TTNMENU7
Command19=ID_RUN_TTNMENU8
Command20=ID_EDIT_UNDO
Command21=ID_EDIT_CUT
Command22=ID_EDIT_COPY
Command23=ID_EDIT_PASTE
Command24=ID_VIEW_TOOLBAR
Command25=ID_VIEW_STATUS_BAR
Command26=ID_MISC_OPTIONS
Command27=ID_MISC_CLEARSCREEN_ON
Command28=ID_MISC_CLEARSCREEN_OFF
Command29=ID_MISC_MODALDLGS
Command30=ID_MISC_SETSINWIN
Command31=ID_MISC_HINT
Command32=ID_HELP_FINDER
Command33=ID_APP_ABOUT
CommandCount=33

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=8
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308481
Control7=IDC_STATIC,static,1342308481
Control8=IDC_STATIC,button,1342178055

[DLG:IDD_SD_REQSTRING]
Type=1
Class=CVSDrqstr
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_TITLE,static,1342312449
Control3=IDC_EDIT1,edit,1350631429

[CLS:CVSDrqstr]
Type=0
HeaderFile=vsdrqstr.h
ImplementationFile=vsdrqstr.cpp
BaseClass=CDialog
LastObject=CVSDrqstr
Filter=D
VirtualFilter=dWC

[DLG:IDD_SD_MENU]
Type=1
Class=CVSDmenu
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC_TITLE,static,1342312448
Control6=IDC_STATIC,button,1342177287
Control7=ID_MISC_HINT,button,1342193664
Control8=ID_MISC_PROPERTIES,button,1342193664
Control9=IDC_CHECK_RSESSION,button,1342242819
Control10=IDC_STATIC,button,1342177287

[CLS:CVSDmenu]
Type=0
HeaderFile=VSDmenu.h
ImplementationFile=VSDmenu.cpp
BaseClass=CDialog
Filter=D
LastObject=CVSDmenu
VirtualFilter=dWC

[CLS:CVSDfname]
Type=0
HeaderFile=VSDfname.h
ImplementationFile=VSDfname.cpp
BaseClass=CFileDialog
Filter=D
VirtualFilter=dWC
LastObject=CVSDfname

[DLG:IDD_SD_SPLASH]
Type=1
Class=CVSDsplash
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342312449
Control5=IDC_STATIC,static,1476526082
Control6=IDC_STATIC_REV,static,1476526080
Control7=IDC_STATIC,static,1342177283

[CLS:CVSDsplash]
Type=0
HeaderFile=VSDsplash.h
ImplementationFile=VSDsplash.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVSDsplash

[DLG:IDD_SD_PROGRESS]
Type=1
Class=CVSDprogress
ControlCount=7
Control1=IDC_PROGRESS1,msctls_progress32,1350565888
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC1,static,1342308353
Control5=ID_MISC_PAUSE,button,1342242816
Control6=ID_MISC_ABORT,button,1342242816
Control7=IDC_STATIC,button,1342177287

[CLS:CVSDprogress]
Type=0
HeaderFile=VSDprogress.h
ImplementationFile=VSDprogress.cpp
BaseClass=CDialog
Filter=D
LastObject=CVSDprogress
VirtualFilter=dWC

[CLS:CVSPcright]
Type=0
HeaderFile=vspcright.h
ImplementationFile=vspcright.cpp
BaseClass=CPropertyPage
LastObject=CVSPcright

[DLG:IDD_SP_COPYRIGHT]
Type=1
Class=CVSPcright
ControlCount=4
Control1=IDC_STATIC,static,1342308353
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308353

[DLG:IDD_SP_COPYRIGHT (Greek)]
Type=1
Class=CVSPcright
ControlCount=4
Control1=IDC_STATIC,static,1342308353
Control2=IDC_STATIC,static,1342308353
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308353

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_RUN_TTNANS
Command5=ID_RUN_TTNMENU1
Command6=ID_RUN_TTNMENU2
Command7=ID_RUN_TTNMENU3
Command8=ID_RUN_TTNMENU4
Command9=ID_RUN_TTNMENU5
Command10=ID_RUN_TTNMENU6
Command11=ID_RUN_TTNMENU7
Command12=ID_RUN_TTNMENU8
Command13=ID_MISC_CLEARSCREEN_NOW
Command14=ID_MISC_CLEARSCREEN_ON
Command15=ID_MISC_CLEARSCREEN_OFF
Command16=ID_MISC_TEXTOUTPUTON
Command17=ID_MISC_TEXTOUTPUTOFF
Command18=ID_MACRO
Command19=ID_EDIT_CUT
Command20=ID_EDIT_COPY
Command21=ID_EDIT_PASTE
Command22=ID_FILE_PRINT
Command23=ID_APP_ABOUT
Command24=ID_CONTEXT_HELP
CommandCount=24

[DLG:IDD_SD_REQSTRING (Greek)]
Type=1
Class=CVSDrqstr
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_TITLE,static,1342312449
Control3=IDC_EDIT1,edit,1350631429

[DLG:IDD_SD_MENU (Greek)]
Type=1
Class=CVSDmenu
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC_TITLE,static,1342312448
Control6=IDC_STATIC,button,1342177287
Control7=ID_MISC_HINT,button,1342193664
Control8=ID_MISC_PROPERTIES,button,1342193664
Control9=IDC_CHECK_RSESSION,button,1342242819
Control10=IDC_STATIC,button,1342177287

[DLG:IDD_SD_SPLASH (Greek)]
Type=1
Class=CVSDsplash
ControlCount=7
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342312449
Control5=IDC_STATIC,static,1476526082
Control6=IDC_STATIC_REV,static,1476526080
Control7=IDC_STATIC,static,1342177283

[DLG:IDD_SD_PROGRESS (Greek)]
Type=1
Class=CVSDprogress
ControlCount=7
Control1=IDC_PROGRESS1,msctls_progress32,1350565888
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC1,static,1342308353
Control5=ID_MISC_PAUSE,button,1342242816
Control6=ID_MISC_ABORT,button,1342242816
Control7=IDC_STATIC,button,1342177287

[DLG:IDD_SP_RICHEDIT (Greek)]
Type=1
Class=?
ControlCount=1
Control1=IDC_RICHEDIT1,RICHEDIT,1350631556

[DLG:IDD_SP_PAGE_1]
Type=1
Class=CVSPpage1
ControlCount=2
Control1=IDC_LIST3,listbox,1350652161
Control2=IDC_STATIC,static,1342308352

[CLS:CVSPpage1]
Type=0
HeaderFile=VSPpage1.h
ImplementationFile=VSPpage1.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=CVSPpage1
VirtualFilter=idWC

[DLG:IDD_SD_HINT]
Type=1
Class=CVSDhint
ControlCount=1
Control1=IDC_LIST,listbox,1484800257

[CLS:CVSDhint]
Type=0
HeaderFile=vsdhint.h
ImplementationFile=vsdhint.cpp
BaseClass=CDialog
LastObject=CVSDhint
Filter=D
VirtualFilter=dWC

[MNU:IDR_HINTMENU]
Type=1
Class=?
Command1=ID_MISC_SELECTFONT
Command2=ID_MISC_WWRAP
CommandCount=2

[MNU:IDR_HINTMENU (Greek)]
Type=1
Class=?
Command1=ID_MISC_SELECTFONT
Command2=ID_MISC_WWRAP
CommandCount=2

[DLG:IDD_SP_PAGE_1 (Greek)]
Type=1
Class=CVSPpage1
ControlCount=2
Control1=IDC_LIST3,listbox,1350652161
Control2=IDC_STATIC,static,1342308352

[DLG:IDD_SD_HINT (Greek)]
Type=1
Class=CVSDhint
ControlCount=1
Control1=IDC_LIST,listbox,1484800257

[DLG:IDD_SD_DATASET]
Type=1
Class=CVSDdataset
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control3=ID_DATASET_SCALE,button,1342242817
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DATASET_PROGRESS,msctls_progress32,1350565888
Control6=ID_DATASET_SAVE,button,1342242817
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_ROWS,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_COLS,edit,1350633600

[CLS:CVSDdataset]
Type=0
HeaderFile=VSDdataset.h
ImplementationFile=VSDdataset.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CVSDdataset

[CLS:CVSDoptions]
Type=0
HeaderFile=VSDoptions.h
ImplementationFile=VSDoptions.cpp
BaseClass=CDialog
Filter=D
LastObject=CVSDoptions
VirtualFilter=dWC

[DLG:IDD_SD_OPTIONS]
Type=1
Class=CVSDoptions
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=ID_MISC_CLEARSCREEN_OFF,button,1342242816
Control5=ID_MISC_CLEARSCREEN_ON,button,1342242816
Control6=ID_MISC_HINT,button,1342242816
Control7=ID_MISC_MODALDLGS,button,1342242816
Control8=ID_MISC_SELECTFONT,button,1342242816
Control9=ID_MISC_TEXTOUTPUTOFF,button,1342242816
Control10=ID_MISC_TEXTOUTPUTON,button,1342242816
Control11=ID_MISC_WWRAP,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=ID_MISC_OLDFILEREQ,button,1342242816
Control14=ID_MISC_SETHCDELAY,button,1342242816

[DLG:IDD_SD_MACRO]
Type=1
Class=CVSDmacro
ControlCount=7
Control1=IDCANCEL,button,1342242816
Control2=IDC_BUTTON_REC,button,1342242944
Control3=IDC_BUTTON_PLAY,button,1342242944
Control4=IDC_BUTTON_STOP,button,1342242944
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[CLS:CVSDmacro]
Type=0
HeaderFile=VSDmacro.h
ImplementationFile=VSDmacro.cpp
BaseClass=CDialog
Filter=D
LastObject=CVSDmacro
VirtualFilter=dWC

[DLG:IDD_SD_DATASET (Greek)]
Type=1
Class=?
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDC_MSFLEXGRID1,{6262D3A0-531B-11CF-91F6-C2863C385E30},1342242816
Control3=ID_DATASET_SCALE,button,1342242817
Control4=IDC_STATIC,button,1342177287
Control5=IDC_DATASET_PROGRESS,msctls_progress32,1350565888
Control6=ID_DATASET_SAVE,button,1342242817
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_ROWS,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_COLS,edit,1350633600

[DLG:IDD_SD_OPTIONS (Greek)]
Type=1
Class=?
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=ID_MISC_CLEARSCREEN_OFF,button,1342242816
Control5=ID_MISC_CLEARSCREEN_ON,button,1342242816
Control6=ID_MISC_HINT,button,1342242816
Control7=ID_MISC_MODALDLGS,button,1342242816
Control8=ID_MISC_SELECTFONT,button,1342242816
Control9=ID_MISC_TEXTOUTPUTOFF,button,1342242816
Control10=ID_MISC_TEXTOUTPUTON,button,1342242816
Control11=ID_MISC_WWRAP,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=ID_MISC_OLDFILEREQ,button,1342242816
Control14=ID_MISC_SETHCDELAY,button,1342242816

[DLG:IDD_SD_MACRO (Greek)]
Type=1
Class=?
ControlCount=7
Control1=IDCANCEL,button,1342242816
Control2=IDC_BUTTON_REC,button,1342242944
Control3=IDC_BUTTON_PLAY,button,1342242944
Control4=IDC_BUTTON_STOP,button,1342242944
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

