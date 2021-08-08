@echo off

IF NOT %1D==D goto full

dir e:\backups\tcproj\vatfree

goto end

:full

Backing up files....

pkzip %1 *.c
pkzip %1 *.h
pkzip %1 *.txt
move %1.zip e:\backups\tcproj\vatfree

:end

