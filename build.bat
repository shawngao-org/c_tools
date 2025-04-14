@echo off

set DIRECTORY=build
echo Check if the %DIRECTORY% directory exists...
if exist "%DIRECTORY%" (
  echo The %DIRECTORY% directory already exists. Deleting %DIRECTORY% directory...
  rmdir /s /q "%DIRECTORY%"
)
echo Creating directory and enter %DIRECTORY%
mkdir "%DIRECTORY%"
cd "%DIRECTORY%"
echo CMaking...
@REM If you are using MinGW, use the following command instead:
@REM cmake -G "MinGW Makefiles" ..
@REM If you are using Cygwin, use the following command instead:
cmake -G "Unix Makefiles" ..
echo Making...
make.exe -j 2
if %errorlevel% equ 0 (
  echo Build Successful!
) else (
  echo Build Failed!
  exit /b 1
)
echo Testing...
make.exe test
