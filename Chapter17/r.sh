#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch17_01/Ch17_01
$BDIR/Ch17_02/Ch17_02
$BDIR/Ch17_03/Ch17_03
$BDIR/Ch17_04/Ch17_04
