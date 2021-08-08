# Microsoft Developer Studio Project File - Name="fl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=fl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fl.mak" CFG="fl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "fl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Misc/fl", XNAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fl - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy release\fl.exe c:\windows\fl.scr
# End Special Build Tool

!ELSEIF  "$(CFG)" == "fl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy debug\fl.exe \apps\purple\program
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "fl - Win32 Release"
# Name "fl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\fl.cpp
# End Source File
# Begin Source File

SOURCE=.\fl.rc
# End Source File
# Begin Source File

SOURCE=.\flDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MyComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\preview.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\verify.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\fl.h
# End Source File
# Begin Source File

SOURCE=.\flDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyButton.h
# End Source File
# Begin Source File

SOURCE=.\MyComboBox.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Bm_logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bm_mlist.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bm_opt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bm_ver.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_awk0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_awk1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_bs0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_bs1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_canc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_done.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_nm0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_nm1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_pm0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_pm1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_psfx0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_psfx1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_qq0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_qq1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_reg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_swm0.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_swm1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Bt_url.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Dialog.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fl.ico
# End Source File
# Begin Source File

SOURCE=.\res\fl.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Preview.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Comic.ttf
# End Source File
# Begin Source File

SOURCE=.\notes.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
