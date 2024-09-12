@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch02_01\%CONFIG%\Ch02_01
%BDIR%\Ch02_02\%CONFIG%\Ch02_02
%BDIR%\Ch02_03\%CONFIG%\Ch02_03
%BDIR%\Ch02_04\%CONFIG%\Ch02_04
%BDIR%\Ch02_05\%CONFIG%\Ch02_05
