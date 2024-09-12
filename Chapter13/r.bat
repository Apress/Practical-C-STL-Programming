@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch13_01\%CONFIG%\Ch13_01
%BDIR%\Ch13_02\%CONFIG%\Ch13_02
%BDIR%\Ch13_03\%CONFIG%\Ch13_03
%BDIR%\Ch13_04\%CONFIG%\Ch13_04
%BDIR%\Ch13_05\%CONFIG%\Ch13_05
