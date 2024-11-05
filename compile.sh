#!/bin/bash
cd ./src
gcc -o ./../a.out main.c $(pkg-config --cflags --libs libmongoc-1.0) -lncurses
