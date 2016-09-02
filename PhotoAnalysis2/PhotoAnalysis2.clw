; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPhotoAnalysis2View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PhotoAnalysis2.h"
LastPage=0

ClassCount=10
Class1=CPhotoAnalysis2App
Class2=CPhotoAnalysis2Doc
Class3=CPhotoAnalysis2View
Class4=CMainFrame

ResourceCount=7
Resource1=IDR_PHOTOATYPE
Resource2=IDD_DLG_LINERPARA
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_ABOUTBOX
Class7=CSHOWRGB
Resource4=IDD_SHOW_RGB
Class8=CLinerParaDlg
Resource5=IDD_DIALOG_LOGIC_CAL
Class9=CLOGIC_CAL
Resource6=IDR_MAINFRAME
Class10=CREGIONGROWTH
Resource7=IDD_DIALOG_REGIONGROWTH

[CLS:CPhotoAnalysis2App]
Type=0
HeaderFile=PhotoAnalysis2.h
ImplementationFile=PhotoAnalysis2.cpp
Filter=N

[CLS:CPhotoAnalysis2Doc]
Type=0
HeaderFile=PhotoAnalysis2Doc.h
ImplementationFile=PhotoAnalysis2Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPhotoAnalysis2Doc

[CLS:CPhotoAnalysis2View]
Type=0
HeaderFile=PhotoAnalysis2View.h
ImplementationFile=PhotoAnalysis2View.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=ID_REGION_GROW


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=PhotoAnalysis2.cpp
ImplementationFile=PhotoAnalysis2.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_PHOTOATYPE]
Type=1
Class=CPhotoAnalysis2View
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_RGB_TO_HSV
Command18=ID_GRAY_LINAR_STRETCH
Command19=ID_GRAY_PIECEWISE
Command20=ID_HISTOGRAM_EQUALIZE
Command21=ID_HISTOGRAM_MATCHING
Command22=ID_ENHANCE_MIDIANFILTER
Command23=ID_ENHANCE_MAXFILTER
Command24=ID_ENHANCE_MINFILTER
Command25=ID_ENHANCE_EQUALIZEFILTER
Command26=ID_ENHANCE_SHARPENINGFILTER
Command27=ID_GRAY_TO_COLOR
Command28=ID_COLOR_TO_GRAY
Command29=ID_TRANSFORM_MIRROR_X
Command30=ID_TRANSFORM_MIRROR_Y
Command31=ID_ZOOM
Command32=ID_IMAGE_CAL
Command33=ID_INVERSE
Command34=ID_FFT
Command35=ID_IFFT
Command36=ID_IDEAL_LPF
Command37=ID_IDEAL_HPF
Command38=ID_BUTTER_LPF
Command39=ID_BUTTER_HPF
Command40=ID_HOMOMORPHIC_FILTER
Command41=ID_MORPHOLOGY
Command42=ID_DEGENERATE
Command43=ID_INVERSE_FILTER
Command44=ID_MENUITEM32807
Command45=ID_THRESHOLD
Command46=ID_REGION_GROW
Command47=ID_REGION_DIVANDCON
Command48=ID_WINDOW_NEW
Command49=ID_WINDOW_CASCADE
Command50=ID_WINDOW_TILE_HORZ
Command51=ID_WINDOW_ARRANGE
Command52=ID_APP_ABOUT
CommandCount=52

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
CommandCount=14

[DLG:IDD_SHOW_RGB]
Type=1
Class=CSHOWRGB
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_POINT_X,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_POINTX,edit,1350631552
Control6=IDC_EDIT_POINTY,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[CLS:CSHOWRGB]
Type=0
HeaderFile=SHOWRGB.h
ImplementationFile=SHOWRGB.cpp
BaseClass=CDialog
Filter=D
LastObject=CSHOWRGB

[DLG:IDD_DLG_LINERPARA]
Type=1
Class=CLinerParaDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_A,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_B,edit,1350631552
Control8=IDC_COORD,static,1342308352

[CLS:CLinerParaDlg]
Type=0
HeaderFile=LinerParaDlg.h
ImplementationFile=LinerParaDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLinerParaDlg

[DLG:IDD_DIALOG_LOGIC_CAL]
Type=1
Class=CLOGIC_CAL
ControlCount=7
Control1=IDC_RADIO_ADD,button,1342308361
Control2=IDC_RADIO_SUB,button,1342177289
Control3=IDC_RADIO_MUL,button,1342177289
Control4=IDC_RADIO_DIV,button,1342177289
Control5=IDOK,button,1342242816
Control6=IDC_RADIO_AND,button,1342177289
Control7=IDC_RADIO_OR,button,1342177289

[CLS:CLOGIC_CAL]
Type=0
HeaderFile=LOGIC_CAL.h
ImplementationFile=LOGIC_CAL.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO_OR
VirtualFilter=dWC

[DLG:IDD_DIALOG_REGIONGROWTH]
Type=1
Class=CREGIONGROWTH
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_POINTX,edit,1350631552
Control7=IDC_EDIT_POINTY,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_THRE,edit,1350631552

[CLS:CREGIONGROWTH]
Type=0
HeaderFile=REGIONGROWTH.h
ImplementationFile=REGIONGROWTH.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

