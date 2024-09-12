@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch03_01\%CONFIG%\Ch03_01
%BDIR%\Ch03_02\%CONFIG%\Ch03_02
%BDIR%\Ch03_03\%CONFIG%\Ch03_03
