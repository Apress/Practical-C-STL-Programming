#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch11_01/Ch11_01
$BDIR/Ch11_02/Ch11_02
$BDIR/Ch11_03/Ch11_03
$BDIR/Ch11_04/Ch11_04
$BDIR/Ch11_05/Ch11_05
$BDIR/Ch11_06/Ch11_06
$BDIR/Ch11_07/Ch11_07
$BDIR/Ch11_08/Ch11_08
