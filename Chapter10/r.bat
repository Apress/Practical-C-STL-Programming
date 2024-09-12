@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch10_01\%CONFIG%\Ch10_01
%BDIR%\Ch10_02\%CONFIG%\Ch10_02
%BDIR%\Ch10_03\%CONFIG%\Ch10_03
%BDIR%\Ch10_04\%CONFIG%\Ch10_04
%BDIR%\Ch10_05\%CONFIG%\Ch10_05
%BDIR%\Ch10_06\%CONFIG%\Ch10_06
%BDIR%\Ch10_07\%CONFIG%\Ch10_07
%BDIR%\Ch10_08\%CONFIG%\Ch10_08
