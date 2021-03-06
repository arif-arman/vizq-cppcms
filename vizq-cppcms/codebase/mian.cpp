#pragma warning  ( disable : 4786)
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <queue>
#include <cassert>

#include "macros.h"
#include "./gpc/gpc.h"
#include "monotone.h"
// #include "text3d.h"
#include "vcm.h"
#include "mvq.h"

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
#include "tinyfiledialogs.h"

using namespace std;

#define INTRO 0
#define MVQ_S 1
#define VCM_S 2
#define TXT_S 3

int mode = 1;

VCM vcm;
MVQ mvq;

int vr = 0;

int main(int argc, char **argv) {

	cout << "Program starting" << endl;

	if (strcmp(argv[1], "mvq") == 0) {
		if (argc < 5) {
			cout << "Too few arguments" << endl;
			return 0;
		}
		strcat(mvq.f, "../webapp/ob/");
		strcat(mvq.queryPath, "../webapp/qp/");
		strcat(mvq.f, argv[2]);
		strcat(mvq.queryPath, argv[3]);
		//strcat(mvq.f, ".txt");
		// FILE *fp;
		// fp = fopen(mvq.f, "r");
		// if (fp == NULL) {
		// 	cout << "Null" << endl;
		// }
		// fclose(fp);

		vector<QueryPoint3D> q;
		Point3D cp[8];

		mvq.setup();
		mvq.loadQueryPoints();
		mvq.Mov_exp3D(atoi(argv[4]), q, cp);

		for (int i = 0; i < q.size(); ++i) {
			cout << "*** Rank: " << (i + 1) << "***" << endl;
			q[i].print();
		}

	} else if (strstr(argv[1], "vcm")) {
		if (argc < 10) {
			cout << "Too few arguments" << endl;
			return 0;
		}
		//VCM vcm;
		strcpy(vcm.f, "../webapp/ob/");
		strcat(vcm.f, argv[2]); // obstacle set
		double x1 = atoi(argv[3]);
		double y1 = atoi(argv[4]);
		double z1 = atoi(argv[5]);
		double x2 = atoi(argv[6]);
		double y2 = atoi(argv[7]);
		double z2 = atoi(argv[8]);
		vcm.fontsize = atoi(argv[9]);
		if (vcm.fontsize != -1)
			vcm.argContainsText = true;
		vcm.setup();
		Box b(Vector3(x1, y1, z1), Vector3(x2, y2, z2));
		vcm.setTarget(b);
		//vcm.target = b;
		//vcm.target.setPlanes();

		vcm.run2(atoi(argv[3]));	// direction
	} else if (strcmp(argv[1], "cmvq") == 0) {
		puts("CMVQ running");
		puts(argv[2]);
	}

	return 0;
}
