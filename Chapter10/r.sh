#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch10_01/Ch10_01
$BDIR/Ch10_02/Ch10_02
$BDIR/Ch10_03/Ch10_03
$BDIR/Ch10_04/Ch10_04
$BDIR/Ch10_05/Ch10_05
$BDIR/Ch10_06/Ch10_06
$BDIR/Ch10_07/Ch10_07
$BDIR/Ch10_08/Ch10_08
