@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch19_01\%CONFIG%\Ch19_01
%BDIR%\Ch19_02\%CONFIG%\Ch19_02
%BDIR%\Ch19_03\%CONFIG%\Ch19_03
%BDIR%\Ch19_04\%CONFIG%\Ch19_04
%BDIR%\Ch19_05\%CONFIG%\Ch19_05
