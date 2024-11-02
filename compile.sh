#!/bin/bash

gcc dbConnect.c $(pkg-config --cflags --libs libmongoc-1.0)
