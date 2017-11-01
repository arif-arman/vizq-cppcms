#!/bin/bash

export LD_LIBRARY_PATH=/usr/local/lib


c++ -w vizq.cpp -lcppcms ../vizq-cppcms/Debug/codebase/prevSource.o ../vizq-cppcms/Debug/codebase/monotone.o ../vizq-cppcms/Debug/codebase/blockfile/blk_file.o ../vizq-cppcms/Debug/codebase/blockfile/cache.o ../vizq-cppcms/Debug/codebase/func/functions.o ../vizq-cppcms/Debug/codebase/heap/heap.o ../vizq-cppcms/Debug/codebase/his/histogram.o ../vizq-cppcms/Debug/codebase/linlist/linlist.o ../vizq-cppcms/Debug/codebase/rtree/distance.o ../vizq-cppcms/Debug/codebase/rtree/entry.o ../vizq-cppcms/Debug/codebase/gpc/gpc.o ../vizq-cppcms/Debug/codebase/rtree/rtnode.o ../vizq-cppcms/Debug/codebase/rtree/rtree.o ../vizq-cppcms/Debug/codebase/rtree/rtree_cmd.o ../vizq-cppcms/Debug/codebase/vector3.o ../vizq-cppcms/Debug/codebase/mvq.o ../vizq-cppcms/Debug/codebase/vcm.o -o vizq
echo "VizQ compiled"
cppcms_tmpl_cc ./templates/$1.tmpl -o ./templates/$1.cpp
echo "Template compiled"
g++ -w -shared -fPIC ./templates/$1.cpp -o ./templates/lib$1.so -lcppcms -lbooster
g++ -w -rdynamic vizq.cpp ../vizq-cppcms/Debug/codebase/prevSource.o ../vizq-cppcms/Debug/codebase/monotone.o ../vizq-cppcms/Debug/codebase/blockfile/blk_file.o ../vizq-cppcms/Debug/codebase/blockfile/cache.o ../vizq-cppcms/Debug/codebase/func/functions.o ../vizq-cppcms/Debug/codebase/heap/heap.o ../vizq-cppcms/Debug/codebase/his/histogram.o ../vizq-cppcms/Debug/codebase/linlist/linlist.o ../vizq-cppcms/Debug/codebase/rtree/distance.o ../vizq-cppcms/Debug/codebase/rtree/entry.o ../vizq-cppcms/Debug/codebase/gpc/gpc.o ../vizq-cppcms/Debug/codebase/rtree/rtnode.o ../vizq-cppcms/Debug/codebase/rtree/rtree.o ../vizq-cppcms/Debug/codebase/rtree/rtree_cmd.o ../vizq-cppcms/Debug/codebase/vector3.o ../vizq-cppcms/Debug/codebase/mvq.o ../vizq-cppcms/Debug/codebase/vcm.o -o vizq -lcppcms -lbooster
echo "Template loaded"
echo "Running server"
./vizq -c config.js



