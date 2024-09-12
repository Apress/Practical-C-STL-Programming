@echo off
rem usage:  cm-win
rem         cm-win sdir
rem         cm-win sdir bdir
rem         cm-win sdir bdir platform
rem         cm-win sdir bdir platform config
rem
rem         arguments with spaces not supported
rem
rem var         description
rem ===========================================
rem sdir        cmake -S directory
rem bdir        cmake -B directory
rem platform    x64 | Win32
rem config      Debug | Release

if "%1" == "" (set SDIR=.) else (set SDIR=%1)
if "%2" == "" (set BDIR=build-msvc) else (set BDIR=%2)
if "%3" == "" (set PLATFORM=x64) else (set PLATFORM=%3)
if "%4" == "" (set CONFIG=Release) else (set CONFIG=%4)

echo.
echo SDIR       %SDIR%
echo BDIR       %BDIR%
echo PLATFORM   %PLATFORM%
echo CONFIG     %CONFIG%

rem --- generate build system
cmake --fresh -S %SDIR% -B %BDIR% -A %PLATFORM%

rem -- build targets
cmake --build %BDIR% --config=%CONFIG%
