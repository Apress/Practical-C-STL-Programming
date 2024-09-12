@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch07_01\%CONFIG%\Ch07_01
%BDIR%\Ch07_02\%CONFIG%\Ch07_02
%BDIR%\Ch07_03\%CONFIG%\Ch07_03
%BDIR%\Ch07_04\%CONFIG%\Ch07_04
