#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch16_01/Ch16_01
$BDIR/Ch16_02/Ch16_02
$BDIR/Ch16_03/Ch16_03
$BDIR/Ch16_04/Ch16_04
$BDIR/Ch16_05/Ch16_05
