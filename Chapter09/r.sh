#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch09_01/Ch09_01
$BDIR/Ch09_02/Ch09_02
$BDIR/Ch09_03/Ch09_03
$BDIR/Ch09_04/Ch09_04
$BDIR/Ch09_05/Ch09_05
