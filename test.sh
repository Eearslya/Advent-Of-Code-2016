#!/bin/bash

cd $1
make tests
cp INPUT-example INPUT
./test
gcovr -r src
make clean
