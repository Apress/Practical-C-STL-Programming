#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch18_01/Ch18_01
$BDIR/Ch18_02/Ch18_02
$BDIR/Ch18_03/Ch18_03
$BDIR/Ch18_04/Ch18_04
$BDIR/Ch18_05/Ch18_05
