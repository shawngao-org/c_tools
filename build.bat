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
echo Do you want to install this lib to system? (Y/N) [default in 5s: Y]:
set "REPLY="
set /p "REPLY="

(
    echo Y
    timeout /t 5 /nobreak >nul
) | (
    set /p "REPLY="
)

if "%REPLY%"=="" set "REPLY=Y"

if /i "%REPLY%"=="Y" (
  echo Installing...
  mingw32-make install
  copy libtools.dll "C:/Program Files (x86)/tools/lib/libtools.dll"
  if %errorlevel% equ 0 (
    echo Install Successful!
  ) else (
    echo Install Failed!
    exit /b 1
  )
)
