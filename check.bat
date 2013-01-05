@echo off
REM Copyright (c) 2013 CIYAM Open Developers

if "%1" == "" goto usage
if not exist "%1" goto error1

copy "%1" "C:\Program Files\ZBar\bin\~check"
pushd "C:\Program Files\ZBar\bin"
zbarimg --raw ~check
del ~check
popd
goto end

:error1
echo Error: File '%1' not found.
goto end

:usage
echo Usage: check [image file name]
goto end

:end
