@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch05_01\%CONFIG%\Ch05_01
%BDIR%\Ch05_02\%CONFIG%\Ch05_02
%BDIR%\Ch05_03\%CONFIG%\Ch05_03
%BDIR%\Ch05_04\%CONFIG%\Ch05_04
%BDIR%\Ch05_05\%CONFIG%\Ch05_05
%BDIR%\Ch05_06\%CONFIG%\Ch05_06
