@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch08_01\%CONFIG%\Ch08_01
%BDIR%\Ch08_02\%CONFIG%\Ch08_02
%BDIR%\Ch08_03\%CONFIG%\Ch08_03
%BDIR%\Ch08_04\%CONFIG%\Ch08_04
