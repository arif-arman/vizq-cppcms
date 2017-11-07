#ifndef CMVQ_H
#define CMVQ_H
#define BLACK 0, 0, 0
#define M_PI 3.1415923
#define targetSize 2
#define K 1

#include "./gpc/gpc.h"
//R-tree stuffs
#include "./rtree/rtree.h"
#include "./rtree/rtnode.h"
#include "./rtree/entry.h"
#include "./blockfile/blk_file.h"
#include "./blockfile/cache.h"
#include "./linlist/linlist.h"
#include "./rtree/rtree_cmd.h"
#include "./rtree/distance.h"
#include "./his/histogram.h"
#include "./gpc/gpc.h"
#include "./cmvqinc/AVR.h"
#include "./cmvqinc/QueryPoint.h"
#include "./cmvqinc/MBR.h"
#include "./cmvqinc/Pair.h"
#include "./cmvqinc/Coordinate.h"
#include "./cmvqinc/Rectangle.h"

class CMVQ {
public:
	void precompute(char *, char *);
	void readAVRDB();
	void traverseRTree();
	void readBlockingSetDB(char *);
	void mbrBSApproach();
	void incrementalAVRBSApproach();
	bool isInsidePolygon(gpc_polygon avr, float *mbrf);
	void makeAVRFile();
	void getMBRFromPolygon(gpc_polygon *);
	void writeAVRDB();
	void createAVR();
	void printAVR(gpc_polygon &);
	void testPrint(gpc_polygon *);
	void printAVRlist();
	void computeVisibility(MBR mbr, int k);
	void computeBS();
	void createRtreeFromData(char[], int);
	void buildTree(const char *path, const char *DATAFILENAME,
			const char *Outpath, int choice);
	void readTargetPath();
	void readObstacles(char c[]);
	void generateVRMBRFile();
	void readQueryPoints(char c[]);
	void generateRandColors();

	class ComparePair {
	public:
		bool operator()(const Pair& lhs, const Pair& rhs) const {
			return lhs.blockNo < rhs.blockNo
					|| (lhs.blockNo == rhs.blockNo && lhs.entryNo < rhs.entryNo);
		}
	};

	class CompareQueryPoint {
	public:
		bool operator()(const QueryPoint& lhs, const QueryPoint& rhs) const {
			return lhs.total_visibility > rhs.total_visibility;
		}

	};

	bool comparatorForPQ(int &a, int &b) {
		return queryPoints[a].total_visibility < queryPoints[b].total_visibility;
	}

	set<int> currentPVQS;
	set<int> previousPVQS;
	map<Pair, int, ComparePair> ABS;
	map<int, int> blockset;
	vector<RTNode *> rtns;
	vector<Entry *> entries;
	RTreeCmdIntrpr *r;
	RTree *rtree;
	RTree *rtreeVR;
	RTree *rtreeAVR;
	char obsset_tree[1000] = "ob\\";

	gpc_polygon uni;
	queue<int> qRtreeNodes;
	vector<QueryPoint> queryPoints;
	vector<MBR> obstacles;
	vector<Coordinate> targetPath;
	vector<AVR> gpavrs;
	map<Pair, int, ComparePair> BS[1000];
	vector<Pair> PVQS;

	int canDrawGrid;

	double upX, upY, upZ;
	double cameraForward;
	double cameraAlong;
	double cameraUp;

	vector<void *> allPointers;

	double lookX, lookY, lookZ;

	int nextMBR = 0;
	char iterString[500];
	char varyWhatOutput[500];

	char curPrefix[100];

	FILE *fp;

	int debugPrint = 0;

	double colors[1000][3];

};

#endif
