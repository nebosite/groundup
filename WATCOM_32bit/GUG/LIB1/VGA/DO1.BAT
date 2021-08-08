@echo on
rem b %1.c
echo [....assembling source code....]
wcl386 -c -l=dos4g %1.c
echo [....updating library....]
wlib ..\gug.lib -+%1.obj
del %1.obj
