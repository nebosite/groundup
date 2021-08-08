@echo on
echo [....assembling source code....]
wcl386 -c -l=dos4g %1.c
echo [....updating library....]
wlib %watcom%\lib386\dos\gug.lib -+%1.obj
del  %watcom%\lib386\dos\*.bak
copy ..\gug.h %watcom%\h\*.*
del %1.obj



