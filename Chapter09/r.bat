@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch09_01\%CONFIG%\Ch09_01
%BDIR%\Ch09_02\%CONFIG%\Ch09_02
%BDIR%\Ch09_03\%CONFIG%\Ch09_03
%BDIR%\Ch09_04\%CONFIG%\Ch09_04
%BDIR%\Ch09_05\%CONFIG%\Ch09_05
