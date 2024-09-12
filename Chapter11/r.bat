@echo off
if "%1" == "" (set BDIR=build-msvc) else (set BDIR=%1)
if "%2" == "" (set CONFIG=Release) else (set CONFIG=%2)

%BDIR%\Ch11_01\%CONFIG%\Ch11_01
%BDIR%\Ch11_02\%CONFIG%\Ch11_02
%BDIR%\Ch11_03\%CONFIG%\Ch11_03
%BDIR%\Ch11_04\%CONFIG%\Ch11_04
%BDIR%\Ch11_05\%CONFIG%\Ch11_05
%BDIR%\Ch11_06\%CONFIG%\Ch11_06
%BDIR%\Ch11_07\%CONFIG%\Ch11_07
%BDIR%\Ch11_08\%CONFIG%\Ch11_08
