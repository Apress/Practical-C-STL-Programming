#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch02_01/Ch02_01
$BDIR/Ch02_02/Ch02_02
$BDIR/Ch02_03/Ch02_03
$BDIR/Ch02_04/Ch02_04
$BDIR/Ch02_05/Ch02_05
