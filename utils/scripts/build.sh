#!/bin/bash

g++ -std=c++17 -Wshadow -Wall -g -fsanitize=address -fsanitize=undefined -D GLIBCXX_DEBUG -o $1 $1.cpp
