@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch15_01\%CONFIG%\Ch15_01
%BDIR%\Ch15_02\%CONFIG%\Ch15_02
%BDIR%\Ch15_03\%CONFIG%\Ch15_03
%BDIR%\Ch15_04\%CONFIG%\Ch15_04
%BDIR%\Ch15_05\%CONFIG%\Ch15_05
