# Microsoft Developer Studio Project File - Name="eittris" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=eittris - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "eittris.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "eittris.mak" CFG="eittris - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "eittris - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "eittris - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/games/eittris", ZQAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "eittris - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "c:\dev\msdev\MyProjects\DirectV\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_CONSOLE" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 directv.lib ddraw.lib dinput.lib dxguid.lib dsound.lib winmm.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc.lib" /out:"Release/eitprog.exe" /libpath:"c:\dev\msdev\MyProjects\DirectV\lib"
# SUBTRACT LINK32 /debug /nodefaultlib

!ELSEIF  "$(CFG)" == "eittris - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /I "c:\dev\msdev\MyProjects\DirectV\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_CONSOLE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 directv.lib ddraw.lib dinput.lib dxguid.lib dsound.lib winmm.lib /nologo /subsystem:console /incremental:no /debug /machine:I386 /nodefaultlib:"libcd.lib" /pdbtype:sept /libpath:"c:\dev\msdev\MyProjects\DirectV\lib"

!ENDIF 

# Begin Target

# Name "eittris - Win32 Release"
# Name "eittris - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Computer.cpp
# End Source File
# Begin Source File

SOURCE=.\Defplayr.cpp
# End Source File
# Begin Source File

SOURCE=.\directx.cpp
# End Source File
# Begin Source File

SOURCE=.\DVWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\Egg2.cpp
# End Source File
# Begin Source File

SOURCE=.\eitmain.cpp
# End Source File
# Begin Source File

SOURCE=.\eittris.rc
# End Source File
# Begin Source File

SOURCE=.\Endround.cpp
# End Source File
# Begin Source File

SOURCE=.\Gameseg.cpp
# End Source File
# Begin Source File

SOURCE=.\Hiscore.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\Menus.cpp
# End Source File
# Begin Source File

SOURCE=.\Playgame.cpp
# End Source File
# Begin Source File

SOURCE=.\Plsetup.cpp
# End Source File
# Begin Source File

SOURCE=.\Rconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\Rplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup.cpp
# End Source File
# Begin Source File

SOURCE=.\Sfx.cpp
# End Source File
# Begin Source File

SOURCE=.\Specials.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Utility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DVWnd.h
# End Source File
# Begin Source File

SOURCE=.\Eittris.h
# End Source File
# Begin Source File

SOURCE=.\Hiscore.h
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Agony.wav
# End Source File
# Begin Source File

SOURCE=.\res\Alarmclk.wav
# End Source File
# Begin Source File

SOURCE=.\res\Awwwww.wav
# End Source File
# Begin Source File

SOURCE=.\res\Bigpipe.wav
# End Source File
# Begin Source File

SOURCE=.\res\Bigsmsh.wav
# End Source File
# Begin Source File

SOURCE=.\res\Bing.wav
# End Source File
# Begin Source File

SOURCE=.\res\Camel.wav
# End Source File
# Begin Source File

SOURCE=.\res\Carhorn.wav
# End Source File
# Begin Source File

SOURCE=.\res\Cricket.wav
# End Source File
# Begin Source File

SOURCE=.\res\Dank.wav
# End Source File
# Begin Source File

SOURCE=.\res\Dentdril.wav
# End Source File
# Begin Source File

SOURCE=.\res\Docoe.wav
# End Source File
# Begin Source File

SOURCE=.\res\Dok.wav
# End Source File
# Begin Source File

SOURCE=.\res\Drip.wav
# End Source File
# Begin Source File

SOURCE=.\res\Drop.wav
# End Source File
# Begin Source File

SOURCE=.\res\eittris.ico
# End Source File
# Begin Source File

SOURCE=.\res\eittris.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Hoo.wav
# End Source File
# Begin Source File

SOURCE=.\res\Nelson.wav
# End Source File
# Begin Source File

SOURCE=.\res\Pfffehh.wav
# End Source File
# Begin Source File

SOURCE=.\res\Pmp.wav
# End Source File
# Begin Source File

SOURCE=.\res\RES800.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tap.wav
# End Source File
# Begin Source File

SOURCE=.\res\Thip.wav
# End Source File
# Begin Source File

SOURCE=.\res\Thup.wav
# End Source File
# Begin Source File

SOURCE=.\res\title.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\notes.txt
# End Source File
# End Target
# End Project
