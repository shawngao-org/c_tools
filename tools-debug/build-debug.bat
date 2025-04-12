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
cmake -G "MinGW Makefiles" ..
echo Making...
mingw32-make.exe -j 2
if %errorlevel% equ 0 (
  echo Build Successful!
) else (
  echo Build Failed!
  exit /b 1
)
.\tools_debug.exe
if %errorlevel% equ 0 (
  echo Tests Successful!
) else (
  echo Tests Failed!
  exit /b 1
)
