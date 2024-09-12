#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch04_01/Ch04_01
$BDIR/Ch04_02/Ch04_02
$BDIR/Ch04_03/Ch04_03
$BDIR/Ch04_04/Ch04_04
