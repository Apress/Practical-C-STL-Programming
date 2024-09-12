#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch08_01/Ch08_01
$BDIR/Ch08_02/Ch08_02
$BDIR/Ch08_03/Ch08_03
$BDIR/Ch08_04/Ch08_04
