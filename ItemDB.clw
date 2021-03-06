; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRealmView
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ItemDB.h"
LastPage=0

ClassCount=9
Class1=CItemDBApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class2=CChildView
Class5=CRealmView
Class6=CCharView
Class7=CGraphicView
Class8=CReportView
Class9=CGenericView
Resource2=IDD_ABOUTBOX

[CLS:CItemDBApp]
Type=0
HeaderFile=ItemDB.h
ImplementationFile=ItemDB.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=ItemDB.cpp
ImplementationFile=ItemDB.cpp
Filter=D

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
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[CLS:CRealmView]
Type=0
HeaderFile=RealmView.h
ImplementationFile=RealmView.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CRealmView

[CLS:CCharView]
Type=0
HeaderFile=CharView.h
ImplementationFile=CharView.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[CLS:CGraphicView]
Type=0
HeaderFile=GraphicView.h
ImplementationFile=GraphicView.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[CLS:CReportView]
Type=0
HeaderFile=ReportView.h
ImplementationFile=ReportView.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[CLS:CGenericView]
Type=0
HeaderFile=GenericView.h
ImplementationFile=GenericView.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

