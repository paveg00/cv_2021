#!/bin/bash

rm -rf ./libbin
mkdir libbin
g++ -fPIC -shared -o ./libbin/MedianFilterLib.so lib/MedianFilter.cpp