#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
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

#include "./rtree/rtree.h"
#include "./rtree/rtnode.h"
#include "./rtree/entry.h"
#include "./blockfile/blk_file.h"
#include "./blockfile/cache.h"
#include "./linlist/linlist.h"
#include "./rtree/rtree_cmd.h"
#include "./rtree/distance.h"
#include "./his/histogram.h"
#include "./global.h"
#include "./func/gendef.h"
#include "mvq.h"

using namespace std;
MVQ::MVQ() { 
	/*strcpy(f, "H:\\Study\\Others\\Visibility\ Query\\3D\\Executable\\3D\\3D\\db\\");
	strcpy(queryPath, "H:\\Study\\Others\\Visibility\ Query\\3D\\Executable\\3D\\3D\\db\\");
	strcpy(Outpath, "H:\\Study\\Others\\Visibility\ Query\\3D\\Executable\\3D\\3D\\db\\");*/
	strcpy(f, "");
	strcpy(queryPath, "");
	strcpy(Outpath, "");
	T.a = Point3D(-5, -5, -5); T.b = Point3D(5, 5, 5); 
}

map< int, double > MVQ::dstFromTar;


void MVQ::draw_axis(){
	// glColor3f(0, 1, 0);
	// glBegin(GL_LINES); {
	// 	glVertex3f(0, -150, 0);
	// 	glVertex3f(0, 150, 0);
	// }glEnd();
	// glColor3f(1, 0, 0);
	// glBegin(GL_LINES); {
	// 	glVertex3f(-150, 0, 0);
	// 	glVertex3f(150, 0, 0);
	// }glEnd();
	// glColor3f(0, 0, 1);
	// glBegin(GL_LINES); {
	// 	glVertex3f(0, 0, -150);
	// 	glVertex3f(0, 0, 150);
	// }glEnd();
	// glColor3f(0.5, 0.5, 0.5);
	// glBegin(GL_LINES); {
	// 	for (int i = -150; i <= 150; i += 10){
	// 		glVertex3f(i, -150, 0);
	// 		glVertex3f(i, 150, 0);
	// 	}
	// 	for (int i = -150; i <= 150; i += 10){
	// 		glVertex3f(-150, i, 0);
	// 		glVertex3f(150, i, 0);
	// 	}
	// }glEnd();

}



bool MVQ::Mov_exp3D(int upperk, vector<QueryPoint3D> &q, Point3D *cp) {

	puts("*** running MVQ ***");

	k_ans.clear();
	if (dbLoaded && qpLoaded) {
		int ITR_NUM = 1;

		int page, obstacle_considered;  page = obstacle_considered = 0;
		int k = 10;

		float avg = 0.0;
		float overallAvgTime = 0.0;
		float overallAvgPage = 0.0;
		float overallAvgObstacle = 0.0;
		int count = 0;

		Point3D cornerPoints[8];

		float minx,miny,minz, maxx,maxy,maxz;

		minx= min(T.a.x, T.b.x);
		maxx = max(T.a.x, T.b.x);

		miny = min(T.a.y, T.b.y);
		maxy = max(T.a.y, T.b.y);

		minz = min(T.a.z, T.b.z);
		maxz = max(T.a.z, T.b.z);
		Box2 target(Point3D(minx,maxy,minz),Point3D(maxx,miny,maxz));	// why change maxy and miny?
		// find 8 cornerpoints from 2
		cornerPoints[0]=target.a;
		cornerPoints[1] = Point3D(target.b.x,target.a.y,target.a.z);
		cornerPoints[2] = Point3D(target.b.x,target.b.y,target.a.z);
		cornerPoints[3] = Point3D(target.a.x,target.b.y,target.a.z);
		cornerPoints[4] = Point3D(target.a.x,target.a.y,target.b.z);
		cornerPoints[5] = Point3D(target.b.x,target.a.y,target.b.z);
		cornerPoints[6] = target.b;
		cornerPoints[7] = Point3D(target.a.x,target.b.y,target.b.z);

		for (int ind=0;ind<8;++ind) {
			cp[ind] = cornerPoints[ind];
		}

		// debug

		for (int ind=0;ind<8;++ind) {
			cornerPoints[ind].print();
		}

		for (int k_val = 1; k_val <= 1; k_val++)
		{
			count = 0; avg = 0.0;
			/*k = (int)pow(2.0, k_val);
			if (k>i - 1)break;*/
			k = upperk;

			while (count++<ITR_NUM)
			{
				
				for (int l = 0; l<numOfQueryPoints; l++)
				{
					queryPoints[l].obstacleList = new Heap();
					queryPoints[l].obstacleList->init(3);
					queryPoints[l].visiblePlanes.clear();
				}

				page = 0; obstacle_considered = 0;

				/*if (alternate_approach == 1)
				{
				r->tree->Alternate_approach3D(q, i - 1, T, k, k_ans, page, obstacle_considered);
				}
				else if (alternate_approach == 0)
				r->tree->MOV3D(q, i - 1, T, k, k_ans, page, obstacle_considered);
				else if (alternate_approach == 2)*/
				// debug: 
				k = numOfQueryPoints;
				r->tree->MOV_obs3D(queryPoints, numOfQueryPoints, T, k, k_ans, page, obstacle_considered, cornerPoints);

				/*else if (alternate_approach == 3)
				r->tree->naiveMOV3D(q, i - 1, T, k, k_ans, page, obstacle_considered);*/

				for (int l = 0; l<numOfQueryPoints; l++)
				{
					delete queryPoints[l].obstacleList;

				}

			}


		}

		// ofstream out;
		// out.open("output.txt");
		stringstream out;
		for (int i = 0; i < numOfQueryPoints; ++i){
			out << "position: " << queryPoints[i].position.x << " " << queryPoints[i].position.y << " " << queryPoints[i].position.z << endl;
			out << "visibility: " << queryPoints[i].total_visibility << endl;
			out << "visible planes: " << queryPoints[i].visiblePlanes.size() << endl;

//			cout << "position: " << queryPoints[i].position.x << " " << queryPoints[i].position.y << " " << queryPoints[i].position.z << endl;
//			cout << "visibility: " << queryPoints[i].total_visibility << endl;
//			cout << "visible planes: " << queryPoints[i].visiblePlanes.size() << endl;

			for (int j = 0; j < queryPoints[i].visiblePlanes.size(); ++j) {
				out << "plane;;" << endl;
				out << "planeid: " << queryPoints[i].visiblePlanes[j].planeId << endl;
				out << queryPoints[i].visiblePlanes[j].boundary.p1.x << " " << queryPoints[i].visiblePlanes[j].boundary.p1.y << " " << queryPoints[i].visiblePlanes[j].boundary.p1.z << endl;
				out << queryPoints[i].visiblePlanes[j].boundary.p2.x << " " << queryPoints[i].visiblePlanes[j].boundary.p2.y << " " << queryPoints[i].visiblePlanes[j].boundary.p2.z << endl;
				out << queryPoints[i].visiblePlanes[j].boundary.p3.x << " " << queryPoints[i].visiblePlanes[j].boundary.p3.y << " " << queryPoints[i].visiblePlanes[j].boundary.p3.z << endl;
				out << queryPoints[i].visiblePlanes[j].boundary.p4.x << " " << queryPoints[i].visiblePlanes[j].boundary.p4.y << " " << queryPoints[i].visiblePlanes[j].boundary.p4.z << endl;
				
				out << "invisible parts: " << queryPoints[i].visiblePlanes[j].invisible_parts.size() << endl;

//				cout << "plane;;" << endl;
//				cout << "planeid: " << queryPoints[i].visiblePlanes[j].planeId << endl;
//				cout << queryPoints[i].visiblePlanes[j].boundary.p1.x << " " << queryPoints[i].visiblePlanes[j].boundary.p1.y << " " << queryPoints[i].visiblePlanes[j].boundary.p1.z << endl;
//				cout << queryPoints[i].visiblePlanes[j].boundary.p2.x << " " << queryPoints[i].visiblePlanes[j].boundary.p2.y << " " << queryPoints[i].visiblePlanes[j].boundary.p2.z << endl;
//				cout << queryPoints[i].visiblePlanes[j].boundary.p3.x << " " << queryPoints[i].visiblePlanes[j].boundary.p3.y << " " << queryPoints[i].visiblePlanes[j].boundary.p3.z << endl;
//				cout << queryPoints[i].visiblePlanes[j].boundary.p4.x << " " << queryPoints[i].visiblePlanes[j].boundary.p4.y << " " << queryPoints[i].visiblePlanes[j].boundary.p4.z << endl;
//
//				cout << "invisible parts: " << queryPoints[i].visiblePlanes[j].invisible_parts.size() << endl;
				
				for (list<polygon>::iterator it = queryPoints[i].visiblePlanes[j].invisible_parts.begin(); it != queryPoints[i].visiblePlanes[j].invisible_parts.end(); ++it) {
					out << "inv_plane;;" << endl;
//					cout << "inv_plane;;" << endl;
					for (int k = 0; k < it->sides.size(); ++k) {
						out << it->sides[k].a.x << " " << it->sides[k].a.y << " " << it->sides[k].a.z << endl;
//						cout << it->sides[k].a.x << " " << it->sides[k].a.y << " " << it->sides[k].a.z << endl;
					}
					out << ";;inv_plane" << endl;
//					cout << ";;inv_plane" << endl;
				}

				out << ";;plane" << endl;
//				cout << ";;plane" << endl;
			}
		}
		// out.close();

		//cout << out.str();

		q = queryPoints;

		/*
		for(int l=0;l<k;l++)
		{
		printf("points (%f,%f), visibility = %f\n",k_ans[l].position.x,k_ans[l].position.y,k_ans[l].total_visibility);
		}
		*/

		return true;
		//return out.str();
	}
	//return false;
	return false;
	
}

void MVQ::loadQueryPoints() {
	//puts(queryPath);
	queryPoints.clear();
	/*char *t = new char[strlen(queryPath) + 1];
	char *s = queryPath;
	while (*s != '.' && *s != 0)
		*t++ = *s++;
	*t = '\0';
*/
	char QUERYFILE[200] = "";
	float temp; int i = 0;
	FILE *fp; // to read querypoints from file
	FILE *fpDataSetSize;
	//char qfileName[200] = "querypoints";

	//strcpy(QUERYFILE, this->queryPath);
	//itoa(files,qfileName,10);
	//strcat(QUERYFILE, qfileName);
	//strcat(QUERYFILE, ".txt");

	strcat(QUERYFILE, queryPath);
	strcat(QUERYFILE, ".txt");

	printf("Reading query points: ");
	puts(QUERYFILE);

	if ((fp = fopen(QUERYFILE, "r")) == NULL)
	{
		error("Cannot open query text file", TRUE);
		//continue; //try to read next file
	}
	else
	{
		i = 0;
		fscanf(fp, "%f", &temp);	// # of q_points
		//while (!feof(fp))
		while(i<temp)
		{
			QueryPoint3D qu;
			fscanf(fp, "%f %f %f", &(qu.position.x), &(qu.position.y), &(qu.position.z));
			queryPoints.push_back(qu);
			i++; //i is the num of q_points
		}
		qpLoaded = true;
	}
	numOfQueryPoints = i;
	printf("Total querypoints read: %d\n", numOfQueryPoints);
	fclose(fp);

	
}

void MVQ::debug() {
	// draw_axis();
	// glColor3f(0.5, 0.5, 0.5);
	// T.draw();
	// if (showObstacles) {
	// 	for (int i = 0; i < obstacles.size(); ++i)
	// 	{
	// 		/*if (obstacles[i].color.x == 255 && !obstacles[i].color.y && !obstacles[i].color.z) {
	// 		if (showAll) obstacles[i].draw();
	// 		else continue;
	// 		}
	// 		else*/
	// 		glPushMatrix();
	// 		int ind = i%rColor.size();
	// 		glColor3ub(rColor[ind].x, rColor[ind].y, rColor[ind].z);
	// 		obstacles[i].draw();
	// 		glPopMatrix();
	// 	}
	// }
	
	// for (int i = 0; i < queryPoints.size(); ++i) {
	// 	if (i == vr) queryPoints[i].draw(true);
	// 	else queryPoints[i].draw(false);
		
	// }
	// GLfloat ambientColor[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// GLfloat lightColor0[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	// GLfloat lightPos0[] = { -0.5f, 0.5f, 1.0f, 0.0f };
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	// glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

void MVQ::clearTarget() {
	if (isTargetSet) {
		Box2 b(Point3D(0,0,0), Point3D(0,0,0));
		T = b;
	}
}


void MVQ::buildTree(char *path, char *DATAFILENAME, char *Outpath)
{

	char TREEFILE[200];
	strcpy(TREEFILE, path);
	strcat(TREEFILE, DATAFILENAME);
	strcat(TREEFILE, ".tree");

	//input file

	char DATAFILE[200];
	strcpy(DATAFILE, path);
	strcat(DATAFILE, DATAFILENAME);
	strcat(DATAFILE, ".txt");

	//puts(TREEFILE);
	//puts(DATAFILE);

	int blocksize = 1024;
	int b_length = 1024;

	int dimension = 3;

	char OUTFILE[200] = "";

	r = new RTreeCmdIntrpr();

	r->build_tree(TREEFILE, DATAFILE, b_length, dimension, 0);

	rtree = r->tree;


	//rtree->reductionInPosX(1,target);

	return;
}

void MVQ::createRtreeFromData(char *f)
{
	printf("Reading obstacle set from: \n");
	puts(f);
	// home pc directory
	//char *Inpath = "";
	char *Inpath = "";	// for linux codebase
	//char *Outpath = "H:\\Study\\Others\\Visibility\ Query\\3D\\Executable\\3D\\3D\\db\\";
	char Outpath[200];
	strcpy(Outpath, "");
	// uiu pc
	//char *Outpath = "F:\\3D\\3D\\db\\";
	//puts(f);
	//char *t = new char[strlen(f) + 1];
	//char *s = t;
	//while (*f != '.' && *f != 0)
	// while(*f)
	// 	*t++ = *f++;
	// *t = '\0';
	// //char *DATAFILENAME = s;
	char DATAFILENAME[200];
	strcpy(DATAFILENAME, f);
	//puts(t);
	//int NumOfObstacles = 3;
	puts("Input path:");
	puts(Inpath);
	puts("Data file name:");
	puts(DATAFILENAME);
	buildTree(Inpath, DATAFILENAME, Outpath);

	return;
}


float MVQ::DIST(float *bounces) {
	float x1 = (bounces[0] + bounces[1])/2;
	float y1 = (bounces[2] + bounces[3])/2;
	float z1 = (bounces[4] + bounces[5])/2;
	float x2 = (T.a.x + T.b.x)/2;
	float y2 = (T.a.y + T.b.y)/2;
	float z2 = (T.a.z + T.b.z)/2;

	// debug
	printf("DIST: %f %f %f %f %f %f\n", x1, y1, z1, x2, y2, z2);

	return sqrt(pow(x1-x2,2) + pow(y1-y2,2) + pow(z1-z2,2));
}

void MVQ::setup() {
	if (isTargetSet) clearTarget();
	isTargetSet = false; mvqGenerated = false;
	obstacles.clear();
	//initialize();
	printf("\nInitializing world ... \n");
	createRtreeFromData(f);
	generateRandCol();
	priority_queue< int, vector<int>, compare> Q;
	Q.push(rtree->root);
	int cnt = 0, discard = 0;
	while (!Q.empty())
	{
		int v = Q.top();
		//int v=Q.front();
		RTNode *rtn = new RTNode(rtree, v);
		Q.pop();
		for (int e = 0; e<rtn->num_entries; e++)
		{
			Entry u = rtn->entries[e];
			/* debug: zitu */
			for (int ind = 0; ind<6; ++ind)
				printf("%f%c", u.bounces[ind], ind == 5 ? '\n' : ' ');
			if (rtn->level)
			{
				//dstFromTar[u.son] = u.bounces[0]; // need to update later, wouldn't it only apply for +x?
				/* debug: zitu */
				dstFromTar[u.son] = DIST(u.bounces);
				Q.push(u.son);
				continue;
			}
			Point3D v0(u.bounces[0], u.bounces[2], u.bounces[4]);
			Point3D v1(u.bounces[1], u.bounces[3], u.bounces[5]);
			Box2 bu(v0, v1);
			//bu.setPlanes();
			//int i = cnt % rColor.size();
			//bu.color = Vector3(rColor[i].x, rColor[i].y, rColor[i].z);
			obstacles.resize(obstacles.size() + 1);
			obstacles.back() = bu;
			cnt++;
		}
	}
	dbLoaded = true;
}


void MVQ::generateRandCol()
{
	srand(time(NULL));
	for (int i = 0; i < 30; i++) {
		double r, g, b;
		while (1) {
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
			if (!((r == 255 && !g && !b) || (!r && g == 255 && !b) || (!r && !g && b == 255) || (!r && g == 255 && b == 255) || (r == 255 && g == 255 && !b)))
				break;
		}
		rColor.push_back(Point3D(r, g, b));
	}
}
