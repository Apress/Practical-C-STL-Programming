@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch06_01\%CONFIG%\Ch06_01
%BDIR%\Ch06_02\%CONFIG%\Ch06_02
%BDIR%\Ch06_03\%CONFIG%\Ch06_03
