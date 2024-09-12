@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch01_01\%CONFIG%\Ch01_01
%BDIR%\Ch01_02\%CONFIG%\Ch01_02
%BDIR%\Ch01_03\%CONFIG%\Ch01_03
%BDIR%\Ch01_04\%CONFIG%\Ch01_04
%BDIR%\Ch01_05\%CONFIG%\Ch01_05
%BDIR%\Ch01_06\%CONFIG%\Ch01_06
%BDIR%\Ch01_07\%CONFIG%\Ch01_07

rem Ch01_08 requires keyboard input, run directly from command line
rem %BDIR%\Ch01_08\%CONFIG%\Ch01_08
