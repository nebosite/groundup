@echo on
echo [....assembling source code....]
wasm %1.asm
echo [....updating library....]
wlib e:\gug_dev\lib1\gug.lib -+%1.obj
del %1.obj