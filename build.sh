#!/bin/bash
mkdir build
cmake --build ./build --target all
cd ./build || exit
cmake .

