@echo off

IF NOT %1D==D goto full

dir e:\backups\watcom\flabber

goto end

:full

Backing up files....

pkzip %1 *.c
pkzip %1 *.h
pkzip %1 *.txt
pkzip %1 *.prj
pkzip %1 MAKEFILE
move %1.zip e:\backups\watcom\flabber

:end

