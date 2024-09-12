#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch20_01/Ch20_01
$BDIR/Ch20_02/Ch20_02
$BDIR/Ch20_03/Ch20_03
$BDIR/Ch20_04/Ch20_04
$BDIR/Ch20_05/Ch20_05
