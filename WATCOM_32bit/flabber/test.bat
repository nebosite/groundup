@wcho off

call flab.bat
if errorcode 10 goto ECODE10
if errorcode 9 goto ECODE9
if errorcode 8 goto ECODE8
if errorcode 7 goto ECODE7
if errorcode 6 goto ECODE6
if errorcode 5 goto ECODE5
if errorcode 4 goto ECODE4
if errorcode 3 goto ECODE3
if errorcode 2 goto ECODE2
if errorcode 1 goto ECODE1





:ECODE0
echo error code 0
goto end
:ECODE1
echo error code 1
goto end
:ECODE2
echo error code 2
goto end
:ECODE3
echo error code 3
goto end
:ECODE4
echo error code 4
goto end
:ECODE5
echo error code 5
goto end
:ECODE6
echo error code 6
goto end
:ECODE7
echo error code 7
goto end
:ECODE8
echo error code 8
goto end
:ECODE9
echo error code 9
goto end
:ECODE10
echo error code 10
goto end


:END

