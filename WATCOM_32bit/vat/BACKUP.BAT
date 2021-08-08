@echo off

IF NOT %1D==D goto full

dir e:\backups\watcom\vat

goto end

:full

Backing up files....

pkzip %1 *.c
pkzip %1 *.h
pkzip %1 *.txt
pkzip %1 makefile
move %1.zip e:\backups\watcom\vat

:end

