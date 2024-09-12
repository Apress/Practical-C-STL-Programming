@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch04_01\%CONFIG%\Ch04_01
%BDIR%\Ch04_02\%CONFIG%\Ch04_02
%BDIR%\Ch04_03\%CONFIG%\Ch04_03
%BDIR%\Ch04_04\%CONFIG%\Ch04_04
