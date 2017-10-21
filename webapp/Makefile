all: vizq

vizq: prevSource.o monotone.o blk_file.o cache.o functions.o heap.o histogram.o linlist.o distance.o entry.o gpc.o rtnode.o rtree.o rtree_cmd.o vector3.o mvq.o vcm.o mian.o 
	g++ -w prevSource.o monotone.o blk_file.o cache.o functions.o heap.o histogram.o linlist.o distance.o entry.o gpc.o rtnode.o rtree.o rtree_cmd.o vector3.o mvq.o vcm.o mian.o -o vizq

mian.o: ./codebase/mian.cpp
	g++ -c -w ./codebase/mian.cpp

monotone.o: ./codebase/monotone.cpp
	g++ -c -w ./codebase/monotone.cpp

prevSource.o: ./codebase/prevSource.cpp
	g++ -c -w ./codebase/prevSource.cpp

blk_file.o: ./codebase//blockfile/blk_file.cpp
	g++ -c -w ./codebase/blockfile/blk_file.cpp

cache.o: ./codebase/blockfile/cache.cpp
	g++ -c -w ./codebase/blockfile/cache.cpp

functions.o: ./codebase/func/functions.cpp
	g++ -c -w ./codebase/func/functions.cpp

heap.o: ./codebase/heap/heap.cpp
	g++ -c -w ./codebase/heap/heap.cpp

histogram.o: ./codebase/his/histogram.cpp
	g++ -c -w ./codebase/his/histogram.cpp

linlist.o: ./codebase/linlist/linlist.cpp
	g++ -c -w ./codebase/linlist/linlist.cpp

distance.o: ./codebase/rtree/distance.cpp
	g++ -c -w ./codebase/rtree/distance.cpp

entry.o: ./codebase/rtree/entry.cpp
	g++ -c -w ./codebase/rtree/entry.cpp

gpc.o: ./codebase/rtree/gpc.cpp
	g++ -c -w ./codebase/rtree/gpc.cpp

rtnode.o: ./codebase/rtree/rtnode.cpp
	g++ -c -w ./codebase/rtree/rtnode.cpp

rtree.o: ./codebase/rtree/rtree.cpp
	g++ -c -w ./codebase/rtree/rtree.cpp

rtree_cmd.o: ./codebase/rtree/rtree_cmd.cpp
	g++ -c -w ./codebase/rtree/rtree_cmd.cpp

mvq.o: ./codebase/mvq.cpp
	g++ -c -w ./codebase/mvq.cpp

vcm.o: ./codebase/vcm.cpp ./codebase/vector3.h
	g++ -c -w ./codebase/vcm.cpp 

vector3.o: ./codebase/vector3.cpp
	g++ -c -w ./codebase/vector3.cpp



clean: 
	rm -rf *o vizq





