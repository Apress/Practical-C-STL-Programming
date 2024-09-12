#!/bin/bash

if [ "$1" = "" ]; then
    BDIR="build"
else
    BDIR=$1
fi

$BDIR/Ch06_01/Ch06_01
$BDIR/Ch06_02/Ch06_02
$BDIR/Ch06_03/Ch06_03
