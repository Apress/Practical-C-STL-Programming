#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch05_01/Ch05_01
$BDIR/Ch05_02/Ch05_02
$BDIR/Ch05_03/Ch05_03
$BDIR/Ch05_04/Ch05_04
$BDIR/Ch05_05/Ch05_05
$BDIR/Ch05_06/Ch05_06
