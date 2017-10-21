#!/bin/bash

export LD_LIBRARY_PATH=/usr/local/lib

c++ testground.cpp -lcppcms -o testground
echo "Testground compiled"
cppcms_tmpl_cc ./templates/$1.tmpl -o ./templates/$1.cpp
echo "Template compiled"
g++ -shared -fPIC ./templates/$1.cpp -o ./templates/lib$1.so -lcppcms -lbooster
g++ -rdynamic testground.cpp -o testground -lcppcms -lbooster
echo "Template loaded"
echo "Running server"
./testground -c config.js

