@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch16_01\%CONFIG%\Ch16_01
%BDIR%\Ch16_02\%CONFIG%\Ch16_02
%BDIR%\Ch16_03\%CONFIG%\Ch16_03
%BDIR%\Ch16_04\%CONFIG%\Ch16_04
%BDIR%\Ch16_05\%CONFIG%\Ch16_05
