@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch21_01\%CONFIG%\Ch21_01
%BDIR%\Ch21_02\%CONFIG%\Ch21_02
%BDIR%\Ch21_03\%CONFIG%\Ch21_03
%BDIR%\Ch21_04\%CONFIG%\Ch21_04
%BDIR%\Ch21_05\%CONFIG%\Ch21_05
