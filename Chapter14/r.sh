#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch14_01/Ch14_01
$BDIR/Ch14_02/Ch14_02
$BDIR/Ch14_03/Ch14_03
$BDIR/Ch14_04/Ch14_04
$BDIR/Ch14_05/Ch14_05
