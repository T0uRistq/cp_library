#!/bin/bash

g++ -std=c++17 -Wshadow -Wall -O2 -Wno-unused-result -o $1 $1.cpp
