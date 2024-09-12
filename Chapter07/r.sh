#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch07_01/Ch07_01
$BDIR/Ch07_02/Ch07_02
$BDIR/Ch07_03/Ch07_03
$BDIR/Ch07_04/Ch07_04
