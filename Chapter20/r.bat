@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch20_01\%CONFIG%\Ch20_01
%BDIR%\Ch20_02\%CONFIG%\Ch20_02
%BDIR%\Ch20_03\%CONFIG%\Ch20_03
%BDIR%\Ch20_04\%CONFIG%\Ch20_04
%BDIR%\Ch20_05\%CONFIG%\Ch20_05
