#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch03_01/Ch03_01
$BDIR/Ch03_02/Ch03_02
$BDIR/Ch03_03/Ch03_03
