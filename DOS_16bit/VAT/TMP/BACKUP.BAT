@echo off

if NOT %1=="" goto full

echo MUST PROVIDE A FILENAME WITHOUT EXTENSION

goto end

:full

Backing up files....

pkzip %1 *.c
pkzip %1 *.h
pkzip %1 *.txt
move %1.zip d:/backups/tcproj/vat

:end

