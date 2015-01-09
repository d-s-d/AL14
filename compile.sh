#!/bin/sh
g++ -o a.out -O2 -std=c++11 -I/usr/local/include/ -m64 -g -Wall $@ 
