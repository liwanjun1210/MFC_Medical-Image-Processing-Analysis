; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=2
ResourceCount=2
NewFileInclude1=#include "stdafx.h"
Class1=CMedianFiltDlg
LastClass=SharpeningFilter
LastTemplate=CDialog
Resource1=IDD_ENHANCE_MEDIANFILT
Class2=SharpeningFilter
Resource2=IDD_SHARPENING_FILTER

[DLG:IDD_ENHANCE_MEDIANFILT]
Type=1
Class=CMedianFiltDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_MEDFILT_CHANGETOSIZE3,button,1342177289
Control5=IDC_MEDFILT_CHANGETOSIZE5,button,1342177289
Control6=IDC_MEDFILT_CHANGETOSIZE7,button,1342177289
Control7=IDC_MEDFILT_CHANGETOSIZE9,button,1342177289

[CLS:CMedianFiltDlg]
Type=0
HeaderFile=MedianFiltDlg.h
ImplementationFile=MedianFiltDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MEDFILT_CHANGETOSIZE9

[DLG:IDD_SHARPENING_FILTER]
Type=1
Class=SharpeningFilter
ControlCount=13
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,button,1342177287
Control5=IDC_SHARP_COEF_00,edit,1350631552
Control6=IDC_SHARP_COEF_01,edit,1350631552
Control7=IDC_SHARP_COEF_03,edit,1350631552
Control8=IDC_SHARP_COEF_04,edit,1350631552
Control9=IDC_SHARP_COEF_05,edit,1350631552
Control10=IDC_SHARP_COEF_02,edit,1350631552
Control11=IDC_SHARP_COEF_06,edit,1350631552
Control12=IDC_SHARP_COEF_07,edit,1350631552
Control13=IDC_SHARP_COEF_08,edit,1350631552

[CLS:SharpeningFilter]
Type=0
HeaderFile=SharpeningFilter.h
ImplementationFile=SharpeningFilter.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SHARP_COEF_00
VirtualFilter=dWC

