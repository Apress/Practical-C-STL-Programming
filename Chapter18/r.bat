@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch18_01\%CONFIG%\Ch18_01
%BDIR%\Ch18_02\%CONFIG%\Ch18_02
%BDIR%\Ch18_03\%CONFIG%\Ch18_03
%BDIR%\Ch18_04\%CONFIG%\Ch18_04
%BDIR%\Ch18_05\%CONFIG%\Ch18_05
