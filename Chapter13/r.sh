#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch13_01/Ch13_01
$BDIR/Ch13_02/Ch13_02
$BDIR/Ch13_03/Ch13_03
$BDIR/Ch13_04/Ch13_04
$BDIR/Ch13_05/Ch13_05
