@echo off

IF NOT %1D==D goto full

dir e:\backups\watcom\gug

goto end

:full

Backing up files....

pkzip -r -p %1 *.*
move %1.zip e:\backups\watcom\gug

:end

