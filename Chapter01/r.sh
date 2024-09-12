#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch01_01/Ch01_01
$BDIR/Ch01_02/Ch01_02
$BDIR/Ch01_03/Ch01_03
$BDIR/Ch01_04/Ch01_04
$BDIR/Ch01_05/Ch01_05
$BDIR/Ch01_06/Ch01_06
$BDIR/Ch01_07/Ch01_07

# Ch01_08 requires keyboard input - run directly from command line
# ./$BDIR/Ch01_08/Ch01_08
