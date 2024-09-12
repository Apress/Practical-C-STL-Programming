#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch19_01/Ch19_01
$BDIR/Ch19_02/Ch19_02
$BDIR/Ch19_03/Ch19_03
$BDIR/Ch19_04/Ch19_04
$BDIR/Ch19_05/Ch19_05
