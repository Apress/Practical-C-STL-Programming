#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch21_01/Ch21_01
$BDIR/Ch21_02/Ch21_02
$BDIR/Ch21_03/Ch21_03
$BDIR/Ch21_04/Ch21_04
$BDIR/Ch21_05/Ch21_05
