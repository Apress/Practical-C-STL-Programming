@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch17_01\%CONFIG%\Ch17_01
%BDIR%\Ch17_02\%CONFIG%\Ch17_02
%BDIR%\Ch17_03\%CONFIG%\Ch17_03
%BDIR%\Ch17_04\%CONFIG%\Ch17_04
