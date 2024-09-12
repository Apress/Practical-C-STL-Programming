#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch15_01/Ch15_01
$BDIR/Ch15_02/Ch15_02
$BDIR/Ch15_03/Ch15_03
$BDIR/Ch15_04/Ch15_04
$BDIR/Ch15_05/Ch15_05
