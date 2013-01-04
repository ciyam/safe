@echo off

if "%1" == "" goto usage
if exist "%1" goto error1

pushd "C:\Program Files\ZBar\bin"
zbarcam --raw -Sdisable -Sqrcode.enable>~send.txt
popd
move "C:\Program Files\ZBar\bin\~send.txt" %1
type %1
goto end

:usage
echo Usage: scan [output file name]
goto end

:error1
echo Error: File '%1' already exists.
goto end

:end
