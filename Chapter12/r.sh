#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch12_01/Ch12_01
$BDIR/Ch12_02/Ch12_02
$BDIR/Ch12_03/Ch12_03
$BDIR/Ch12_04/Ch12_04
