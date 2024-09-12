@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch14_01\%CONFIG%\Ch14_01
%BDIR%\Ch14_02\%CONFIG%\Ch14_02
%BDIR%\Ch14_03\%CONFIG%\Ch14_03
%BDIR%\Ch14_04\%CONFIG%\Ch14_04
%BDIR%\Ch14_05\%CONFIG%\Ch14_05
