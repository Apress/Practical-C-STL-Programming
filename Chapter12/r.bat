@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch12_01\%CONFIG%\Ch12_01
%BDIR%\Ch12_02\%CONFIG%\Ch12_02
%BDIR%\Ch12_03\%CONFIG%\Ch12_03
%BDIR%\Ch12_04\%CONFIG%\Ch12_04
