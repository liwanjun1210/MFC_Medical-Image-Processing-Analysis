; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=5
ResourceCount=5
NewFileInclude1=#include "stdafx.h"
Class1=CIdealFilter
LastClass=CInverseFilterRadius
LastTemplate=CDialog
Resource1=IDD_DEGENERATE
Class2=CButterworthFilter
Resource2=IDD_IDEAL_FILTER
Class3=CHomomorphicFilter
Resource3=IDD_HOMOMORPHIC_FILTER
Class4=CDegenerateModel
Resource4=IDD_BUTTERWORTH_FILTER
Class5=CInverseFilterRadius
Resource5=IDD_INVERSEFILTER_RADIUS

[DLG:IDD_IDEAL_FILTER]
Type=1
Class=CIdealFilter
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_IDEAL_CUTOFF_FREQ,edit,1350631552

[CLS:CIdealFilter]
Type=0
HeaderFile=IdealFilter.h
ImplementationFile=IdealFilter.cpp
BaseClass=CDialog
Filter=D
LastObject=CIdealFilter
VirtualFilter=dWC

[DLG:IDD_BUTTERWORTH_FILTER]
Type=1
Class=CButterworthFilter
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_BW_CUTOFF_FREQ,edit,1350631552
Control6=IDC_BW_ORDER,edit,1350631552

[CLS:CButterworthFilter]
Type=0
HeaderFile=ButterworthFilter.h
ImplementationFile=ButterworthFilter.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CButterworthFilter

[DLG:IDD_HOMOMORPHIC_FILTER]
Type=1
Class=CHomomorphicFilter
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GAMMAH,edit,1350631552
Control7=IDC_GAMMAL,edit,1350631552
Control8=IDC_CUTOFF_FREQ,edit,1350631552

[CLS:CHomomorphicFilter]
Type=0
HeaderFile=HomomorphicFilter.h
ImplementationFile=HomomorphicFilter.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHomomorphicFilter

[DLG:IDD_DEGENERATE]
Type=1
Class=CDegenerateModel
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342308359
Control4=IDC_ATMOSPHERIC_TURBULENCE,button,1342308361
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1_k,edit,1484849280
Control7=IDC_STATIC,button,1342177287
Control8=IDC_MOTION_DEGENERATE,button,1342308361
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT2_a,edit,1484849280
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT2_T,edit,1484849280
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT2_b,edit,1484849280
Control15=IDC_STATIC,button,1342177287
Control16=IDC_REGENETATED_IMAGE,button,1342308361

[CLS:CDegenerateModel]
Type=0
HeaderFile=DegenerateModel.h
ImplementationFile=DegenerateModel.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDegenerateModel

[DLG:IDD_INVERSEFILTER_RADIUS]
Type=1
Class=CInverseFilterRadius
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO4,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_EDIT2,edit,1350631552

[CLS:CInverseFilterRadius]
Type=0
HeaderFile=InverseFilterRadius.h
ImplementationFile=InverseFilterRadius.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT2
VirtualFilter=dWC

