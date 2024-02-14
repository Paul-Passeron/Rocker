#!/bin/bash

set -xe
clear
var="examples/main.rkr"
make
echo "$#"
if [ $# -ge 2 ]; then
  ./main $1 $2
else
  if [ $# -eq 1 ]; then
    ./main $var output.c
  fi
fi
./format.sh
