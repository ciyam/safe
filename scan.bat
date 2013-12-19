@echo off
REM Copyright (c) 2013 CIYAM Developers

setlocal

if "%1" == "" goto usage
if exist "%1" goto error1

set input_file=%cd%\%2

pushd "C:\Program Files\ZBar\bin"

if "%2" == "" goto use_cam
zbarimg --raw -Sdisable -Sqrcode.enable %input_file%>~scan.txt
goto next

:use_cam
zbarcam --raw -Sdisable -Sqrcode.enable>~scan.txt

:next
popd
move "C:\Program Files\ZBar\bin\~scan.txt" %1
type %1
goto end

:usage
echo Usage: scan [output file] [[input file]]
goto end

:error1
echo Error: File '%1' already exists.
goto end

:end
endlocal

