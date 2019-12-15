#!/bin/sh

if [ -d "build" ] 
then
    rm -rf build
fi

mkdir build
cd build
cmake ..
make
cd ..
cp small_watch.pgm build/

cd build
./image-test


