#!/bin/bash

# usage:  cm-lin
#         cm-lin sdir
#         cm-lin sdir bdir
#         cm-lin sdir bdir cxxflag
#
# var     description
#===========================================
# sdir      cmake -S directory
# bdir      cmake -B directory
# cxxflag   flag added to CMAKE_CXX_FLAGS (e.g., -m32 or -m64)
#
# Notes:
#
# When using -m32 or -m64 to overwrite default memory
# model, appropriate libraries must be installed.

if [ "$1" = "" ]; then
    SDIR="."
else
    SDIR=$1
fi

if [ "$2" = "" ]; then
    BDIR="build"
else
    BDIR=$2
fi

CXXFLAG=$3

echo "cmake source dir: '$SDIR'"
echo "cmake build dir:  '$BDIR'"
echo "cmake cxx flag:   '$CXXFLAG'"

cmake --fresh -DCXX_FLAG=$CXXFLAG -S $SDIR -B $BDIR
cmake --build $BDIR
