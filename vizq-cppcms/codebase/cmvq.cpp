
#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <cstring>

#include "cmvq.h"

using namespace std;

void CMVQ::generateRandColors() {
	for (int i = 0; i < 1000; ++i) {
		colors[i][0] = rand() % 255;
		colors[i][1] = rand() % 255;
		colors[i][2] = rand() % 255;
		//printf("%f %f %f\n", colors[i][0], colors[i][1], colors[i][2]);
	}
}


void CMVQ::readQueryPoints(char c[]){
	//printf("Reading query points set from %s ... \n", c);
	freopen(c, "r", stdin);

	//printf("%d", errno);
	int n, i;

	scanf("%d", &n);
	QueryPoint *qp;
	for (i = 0; i < n; i++)
	{

		qp = new QueryPoint();
		//allPointers.push_back(qp);
		qp->readQueryPoint();
		queryPoints.push_back((*qp));
	}

	/*for (i = 0; i < n; i++)
	{

		queryPoints[i].vr.print();
	}*/
	//printf("Read finished. \n");
	FILE *fp = fopen("VizQ\\qpointdb.txt", "w");
	for (i = 0; i < n; ++i) {
		fprintf(fp, "qid: %d\n", i);
		fprintf(fp, "position: %f %f,\n", queryPoints[i].coord.x, queryPoints[i].coord.y);
		fprintf(fp, "vr: %f %f %f %f %f %f\n", queryPoints[i].vr.a.x, queryPoints[i].vr.a.y, queryPoints[i].vr.b.x, queryPoints[i].vr.b.y, queryPoints[i].vr.c.x, queryPoints[i].vr.c.y);
		//fprintf(fp, "QP: %d, POS: {%f,%f}, VR: {%f,%f},{%f,%f},{%f,%f}\n", i, queryPoints[i].coord.x, queryPoints[i].coord.y, queryPoints[i].vr.a.x, queryPoints[i].vr.a.y, queryPoints[i].vr.b.x, queryPoints[i].vr.b.y, queryPoints[i].vr.c.x, queryPoints[i].vr.c.y);

	}

	fclose(fp);
}

void CMVQ::generateVRMBRFile(){
	printf("Generating VR MBR file ... \n");
	char s[1000] = "VizQ\\VRMBR.txt";
	// strcpy(s, "VizQ\\"); strcat(s, "VRMBR.txt");
	FILE *fpVRMBR = fopen(s,"w");

	fprintf(fpVRMBR,"%d\n",queryPoints.size());

	MBR mbr;
	for (int i = 0; i < queryPoints.size(); i++)
	{
		mbr = queryPoints[i].vr.getMBR();
		fprintf(fpVRMBR,"%g %g 0 %g %g 0\n",mbr.bottomLeft.x,mbr.bottomLeft.y,mbr.topRight.x,mbr.topRight.y);
	}

	fclose(fpVRMBR);
	printf("File generated\n");
}

void CMVQ::readObstacles(char c[]){

	printf("Reading obstacle set from %s ... \n", c);

	freopen(c, "r", stdin);

	int N, i;
	scanf("%d", &N);

	MBR *mbr;

	for (i = 0; i < N; i++)
	{
		mbr = new MBR();
		//allPointers.push_back(mbr);
		mbr->readMBR();
		obstacles.push_back((*mbr));

	}
	printf("Reading finished.\n");
}

void CMVQ::readTargetPath(){
	freopen("TargetPath.txt", "r", stdin);

	int N, i;
	scanf("%d", &N);

	Coordinate *coordinate;

	for (i = 0; i < N; i++)
	{
		coordinate = new Coordinate();
		coordinate->scan();
		targetPath.push_back((*coordinate));

	}

}

void CMVQ::buildTree(const char *path, const char *DATAFILENAME, const char *Outpath,int choice)
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


	int blocksize = 256;//1024;
	int b_length = 256;//1024;


	int dimension = 3;

	char OUTFILE[200] = "";

	r = new RTreeCmdIntrpr();
	printf("%s\n", DATAFILE);
	r->build_tree(TREEFILE, DATAFILE, b_length, dimension, 0);

	if(choice==1) rtree = r->tree;
	if (choice == 2) rtreeVR = r->tree;
	if (choice == 3) rtreeAVR = r->tree;



	//rtree->reductionInPosX(1,target);


	return;
}

void CMVQ::createRtreeFromData(char a[100],int choice)//1 for obstacle  , 2 for mbrofvr , 3 for mbrforAVR
{
	//char *Inpath = "H:\\UIU\\Drive\\Research\\VizQ\ February\ 2017\\CMVQ\\CMVQ\\VizQ\\";
	char Inpath[200] = "";
	if (choice == 1) strcat(Inpath, "ob\\");
	else strcat(Inpath, "VizQ\\");
	//char *Outpath = "H:\\UIU\\Drive\\Research\\VizQ\ February\ 2017\\CMVQ\\CMVQ\\VizQ\\";
	char Outpath[200] = "VizQ\\";

	//char *DATAFILENAME = "cityGml_british_3D_normalize";
	char *DATAFILENAME = a;

	//int NumOfObstacles = 3;
	RTree *tTree;

	buildTree(Inpath, DATAFILENAME, Outpath, choice);

	return;
}

void CMVQ::computeBS(){

	/*char opEx[1000];
	strcpy(opEx, c);
	strcat(opEx, "BlockingSet.txt");*/
	/*strcpy(opEx, outputPath);
	strcat(opEx, varyWhatOutput);
	strcat(opEx, varyAlgo);
	strcat(opEx, "precomputeBS");
	strcat(opEx, curPrefix);
	strcat(opEx, "ET");
	strcat(opEx, "_");
	strcat(opEx, iterString);
	strcat(opEx, isDebug == 0 ? "" : debugString);
	strcat(opEx, ".txt");
*/
	/*FILE *fp = fopen(opEx, "w");*/
	double time = 0;
	printf("BS computation started ... \n");
	for (int i = 0; i < queryPoints.size(); i++)
	{

		if (i % 10 == 0)
		{
			for (int j = 0; j < 79; j++)  //clear a line
				printf("\b");

			printf("No. of Query Points Handled:%d\n", i);

		}
		//Stopwatch sw;

		//sw.start();
		MBR mbrOfVR = queryPoints[i].vr.getMBR();
		while (!qRtreeNodes.empty())qRtreeNodes.pop();
		int count = 0;
		float *mbr = new float[2 * rtree->dimension];
		//allPointers.push_back(mbr);
		mbr[0] = mbrOfVR.bottomLeft.x;
		mbr[1] = mbrOfVR.topRight.x;
		mbr[2] = mbrOfVR.bottomLeft.y;
		mbr[3] = mbrOfVR.topRight.y;
		mbr[4] = mbrOfVR.bottomLeft.z;
		mbr[5] = mbrOfVR.topRight.z;

		/*for (int i = 0; i < 6; i++)
		{
			printf("%g ", mbr[i]);
		}
		printf("\n");
		*/
		qRtreeNodes.push(rtree->root);
		Pair *pair;

		while (!qRtreeNodes.empty()){
			int rtNodeId = qRtreeNodes.front();
			qRtreeNodes.pop();
			RTNode rtn(rtree, rtNodeId);
			for (int j = 0; j < rtn.num_entries; j++)
			{
				Entry &entry = rtn.entries[j];


				if (entry.intersectsMBR(mbr)){
					pair = new Pair(rtNodeId,j);
					//allPointers.push_back(pair);
					if (!rtn.level){
						BS[i][(*pair)]=entry.son;
						count++;
					}//pushtoBS
					else qRtreeNodes.push(entry.son);

				}
			}
		}
		//sw.stop();
		//fprintf(fp, "%d\n", sw.getDiff());
	}
	//fclose(fp);

	printf("BS computation finished.\n");

	FILE *fp = fopen("VizQ\\bsdb.txt", "w");
	map<Pair, int, ComparePair>::iterator mapIt;
	for (int i = 0; i < queryPoints.size(); ++i) {
		fprintf(fp, "qid: %d\n", i);
		for (mapIt = BS[i].begin(); mapIt != BS[i].end(); mapIt++) {
			fprintf(fp, "%d %d %d\n", mapIt->first.blockNo, mapIt->first.entryNo, mapIt->second);
		}
	}
	fclose(fp);
	/*for (int i = 0; i < queryPoints.size(); i++)
	{
		//printf("querypoint:%d\n", i);
		for (map<Pair, int, ComparePair>::iterator it = BS[i].begin(); it != BS[i].end(); ++it)
		{
			RTNode rtn(rtree, it->first.blockNo);
			//printf("%d ",rtn.entries[it->first.entryNo].son);
		}
		//printf("\n");

		//printf("\n");
	}*/
}

//priority_queue<QueryPoint, vector<QueryPoint>, decltype(&comparatorForPQ)> pq(&comparatorForPQ);
//priority_queue<int, vector<int>, decltype(&comparatorForPQ)> pq(&comparatorForPQ);

void CMVQ::computeVisibility(MBR mbr, int k){

	/*
	map<Pair, int, ComparePair>::iterator mapit;
	RTNode *rtn;
	for (mapit = ABS.begin(); mapit != ABS.end(); mapit++)
	{
		int rtnIndex = blockset[mapit->first.blockNo];
		rtn = (rtns[rtnIndex]);
		//float *f = rtn.entries[mapit->first.entryNo].bounces;
		float f[6];

		for (int i = 0; i < 6; i++){
			f[i] = rtn->entries[mapit->first.entryNo].bounces[i];
		}
		//MBR obstacle(f);


	}
	*/

	//pq = priority_queue<QueryPoint, vector<QueryPoint>, decltype(&comparatorForPQ)>();
	priority_queue<int, vector<int>, decltype(&comparatorForPQ)> pq(&comparatorForPQ);


	SomeRandomRectangle targetRect = mbr.getRectFromMBR();;
	int size = currentPVQS.size();
	set<int>::iterator setIt;
	int i = 0;
	for ( setIt = currentPVQS.begin(); setIt != currentPVQS.end(); setIt++)
	{
		i++;
		queryPoints[(*setIt)].init_visibility(targetRect);
		if (queryPoints[*setIt].total_visibility > .0001)
			//pq.push(queryPoints[(*setIt)]);
			pq.push(*setIt);
		if (i == size)break;
	}

	//QueryPoint q;
	int q;
	int length = entries.size();
	//printf("%d\n",length);
	for (int i = 0; i < length; i++)
	{
		//priority_queue<QueryPoint, vector<QueryPoint>, decltype(&comparatorForPQ)> temp(&comparatorForPQ);
		priority_queue<int, vector<int>, decltype(&comparatorForPQ)> temp(&comparatorForPQ);
		//SomeRandomRectangle obstacleRect;
		Coordinate a(entries[i]->bounces[0], entries[i]->bounces[3]);
		Coordinate b(entries[i]->bounces[1], entries[i]->bounces[2]);

		SomeRandomRectangle obstacleRect(a,b);

		while (!pq.empty()){
			q = pq.top();
			pq.pop();
			if (queryPoints[q].IsInVisibleRegion(obstacleRect)){
				queryPoints[q].update_visibliliyRegion(obstacleRect,targetRect);
			}

			if(queryPoints[q].total_visibility>.0001)temp.push(q);
		}

		pq = temp;
	}

	// debug: zitu
	FILE *fp = fopen("VizQ\\vizresults.txt", "w");
	//printf("\n Writing Visibility results ... \n");
	while (!pq.empty()) {
		q = pq.top();
		printf("%d %f %f %f\n", q, queryPoints[q].coord.x, queryPoints[q].coord.y, queryPoints[q].total_visibility);
		pq.pop();
	}
	fclose(fp);
}
void CMVQ::printAVRlist() {

	//cout << "=== AVR List ===";
	int avrSize = gpavrs.size();
	//cout << avrSize << endl;
	for (int i = 0; i < avrSize; i++) {
		gpc_polygon tmp = *(gpavrs[i].avrPolygon);
		//cout << tmp.contour->num_vertices << " ";
		//printf("%d ", tmp.contour->num_vertices);
		for (int j = 0; j < tmp.contour->num_vertices; j++) {
			//printf("%g,%g ", tmp.contour->vertex[j].x, tmp.contour->vertex[j].y);
			//cout << tmp.contour->vertex[j].x << ", " << tmp.contour->vertex[j].y << " ";
		}
		//printf("\n");
		for (int j = 0; j < gpavrs[i].PVQS.size(); j++) {
			///printf("%d ", gpavrs[i].PVQS[j]);
			//cout << tmp.contour->vertex[j].x << ", " << tmp.contour->vertex[j].y << " ";
		}
		//printf("\n");

		//cout << endl;
	}
	//avrs[i].toString();
}
//
//void markUnion() {
//	gpc_polygon p = uni;
//	//poly = avrs[i];
//	Coordinate c1, c2;
//	for (int i = 0; i < p.num_contours; i++) {
//		for (int j = 0; j < p.contour[i].num_vertices; j++) {
//			c1.x = p.contour[i].vertex[j].x;
//			c1.y = p.contour[i].vertex[j].y;
//			c2.x = p.contour[i].vertex[(j + 1) % p.contour[i].num_vertices].x;
//			c2.y = p.contour[i].vertex[(j + 1) % p.contour[i].num_vertices].y;
//			glColor3f(1, 0, 1);
//			glBegin(GL_LINES); {
//				glVertex3f(c1.x, c1.y, 2);
//				glVertex3f(c2.x, c2.y, 2);
//			}
//			glEnd();
//		}
//	}
//
//}
//
//void markAVRs() {
//	//CPolygon poly;
//	int avrSize = gpavrs.size();
//	//cout << "AVR size " << avrSize;
//
//	for (int i = 0; i < avrSize; i++) {
//		gpc_polygon p = *(gpavrs[i].avrPolygon);
//		//poly = avrs[i];
//		Coordinate c1, c2;
//		for (int j = 0; j < p.contour->num_vertices; j++) {
//			c1.x = p.contour->vertex[j].x;
//			c1.y = p.contour->vertex[j].y;
//			c2.x = p.contour->vertex[(j + 1) % p.contour->num_vertices].x;
//			c2.y = p.contour->vertex[(j + 1) % p.contour->num_vertices].y;
//			//c1.toString();
//			//c2.toString();
//			//c1 = poly.vertices[j];
//			//c2 = poly.vertices[(j+1)%poly.size];
//			glColor3b(colors[i][0], colors[i][1], colors[i][2]);
//			glBegin(GL_LINES); {
//				glVertex3f(c1.x, c1.y, 5);
//				glVertex3f(c2.x, c2.y, 5);
//			}
//			glEnd();
//		}
//	}
//}

void CMVQ::testPrint(gpc_polygon *p) {
	//cout << "Polygon " << endl;
	for (int i = 0; i < p->contour->num_vertices; i++) {
		//cout << p->contour->vertex[i].x << " " << p->contour->vertex[i].y << endl;
	}
}

void CMVQ::printAVR(gpc_polygon &tmp){

	//cout << tmp.contour->num_vertices << " ";

	for (int i = 0; i < tmp.num_contours; i++) {
		printf("%d ", tmp.contour[i].num_vertices);
		for (int j = 0; j < tmp.contour[i].num_vertices; j++) {
			//cout << tmp.contour[i].vertex[j].x << ", " << tmp.contour[i].vertex[j].y << " ";
			printf("%g,%g ", tmp.contour[i].vertex[j].x, tmp.contour[i].vertex[j].y);
		}
		printf("\n");
		//cout << endl;
	}

}

void CMVQ::createAVR() {
	//freopen("output.txt", "w", stdout);
	printf("AVR calculation started ... \n");
	int qSize = queryPoints.size();
	//CPolygon *poly;

	gpc_polygon gp = { 0, NULL, NULL };
	Coordinate *coord;
	QueryPoint qp;

	/*char avrOutputPath[1000];
	strcpy(avrOutputPath, outputPath);
	strcat(avrOutputPath, varyWhatOutput);
	strcat(avrOutputPath,"precomputeAVR");
	strcat(avrOutputPath, curPrefix);
	strcat(avrOutputPath, "ET");
	strcat(avrOutputPath, "_");
	strcat(avrOutputPath, iterString);
	strcat(avrOutputPath, isDebug == 0 ? "" : debugString);
	strcat(avrOutputPath, ".txt");

	FILE *fp = fopen(avrOutputPath, "w");*/

	for (int i = 0; i < queryPoints.size(); i++) {
		vector<AVR> newAvr;
		if (i% 10 == 0)
		{
			for (int i = 0; i < 79; i++)  //clear a line
				printf("\b");

			printf("No. of Query Points Handled:%d\n", i);

		}
		//Stopwatch sw;
		//sw.start();
		qp = queryPoints[i];
		//vector<AVR> *tmpvector= new vector<AVR>();
		gpc_polygon gpcvr = { 0, NULL, NULL };
		gpc_vertex ver[] = { { qp.vr.a.x, qp.vr.a.y }, { qp.vr.b.x, qp.vr.b.y }, { qp.vr.c.x, qp.vr.c.y } };
		gpc_vertex_list vl = { 3, ver };
		gpc_add_contour(&gpcvr, &vl, 0);
		if (!i) {
			coord = new Coordinate[3];
			allPointers.push_back(coord);
			coord[0] = qp.vr.a;
			coord[1] = qp.vr.b;
			coord[2] = qp.vr.c;
			gpc_vertex v[] = { { coord[0].x, coord[0].y }, { coord[1].x, coord[1].y }, { coord[2].x, coord[2].y } };
			gpc_vertex_list vl = { 3, v };
			gpc_add_contour(&gp, &vl, 0);
			AVR *temp = new AVR(&gp);
			allPointers.push_back(temp);
			temp->PVQS.push_back(i);
			gpavrs.push_back((*temp));
			//poly = new CPolygon(3,coord);
			//avrs.push_back(*poly);
		}
		else {
			gpc_polygon un;
			int avrSize = gpavrs.size();
			bool flag = false;
			for (int j = 0; j<avrSize; j++) {
				AVR avr = gpavrs[j];
				//CPolygon avr = avrs[j];
				//avr.toString();
				//vector<gpc_polygon> spawned = clip(&avr, &qp, &gpcvr);
				gpc_polygon child;

				// check intersection
				try{
					gpc_polygon_clip(GPC_INT, avr.avrPolygon, &gpcvr, &child);
				}
				catch (char *c)
				{

				}
				//cout << child.num_contours << endl;
				if (child.num_contours) {
					if (!flag)
						un = *avr.avrPolygon;
					else gpc_polygon_clip(GPC_UNION, avr.avrPolygon, &un, &un);
					flag = true;
					//cout << "Union";
					//printAVR(un);
				}
				for (int m = 0; m < child.num_contours; m++) {
					//cout << child.contour[m].num_vertices << endl;
					gpc_polygon *tmp = new gpc_polygon();
					allPointers.push_back(tmp);
					//cout << result.contour[i].num_vertices << endl;
					gpc_vertex *tv = new gpc_vertex[child.contour[m].num_vertices];
					allPointers.push_back(tv);
					for (int l = 0, n = 0; l < child.contour[m].num_vertices; l++) {
						tv[n].x = child.contour[m].vertex[l].x;
						tv[n++].y = child.contour[m].vertex[l].y;
					}
					gpc_vertex_list tvl = { child.contour[m].num_vertices, tv };
					gpc_add_contour(tmp, &tvl, 0);
					//cout << "INT";
					//printAVR(*tmp);
					AVR* temp = new AVR(tmp);
					allPointers.push_back(temp);
					for (int k = 0; k < avr.PVQS.size(); k++)
					{
						temp->PVQS.push_back(avr.PVQS[k]);
					}
					temp->PVQS.push_back(i);
					newAvr.push_back(*temp);
				}
				// check difference
				gpc_polygon_clip(GPC_DIFF, avr.avrPolygon, &gpcvr, &child);
				//cout << child.num_contours << endl;
				//if (child.num_contours) gpavrs.erase(gpavrs.begin() + j);
				for (int m = 0; m < child.num_contours; m++) {
					//cout << child.contour[m].num_vertices << endl;
					gpc_polygon *tmp = new gpc_polygon();
					allPointers.push_back(tmp);
					//cout << result.contour[i].num_vertices << endl;
					gpc_vertex *tv = new gpc_vertex[child.contour[m].num_vertices];
					allPointers.push_back(tv);
					for (int l = 0, n = 0; l < child.contour[m].num_vertices; l++) {
						tv[n].x = child.contour[m].vertex[l].x;
						tv[n++].y = child.contour[m].vertex[l].y;
					}
					gpc_vertex_list tvl = { child.contour[m].num_vertices, tv };
					gpc_add_contour(tmp, &tvl, 0);
					//cout << "DIFF";
					//printAVR(*tmp);
					AVR* temp = new AVR(tmp);
					allPointers.push_back(temp);
					for (int k = 0; k < avr.PVQS.size(); k++)
					{
						temp->PVQS.push_back(avr.PVQS[k]);
					}
					//temp->PVQS.push_back(i);
					newAvr.push_back(*temp);
				}

				//if (!flag) newAvr.push_back(avr);

				/*
				if (spawned.size()) {
				gpavrs.erase(gpavrs.begin() + j);
				int sS1ize = spawned.size();
				for (int k = 0; k < sSize; k++) {
				gpavrs.push_back(spawned[k]);
				}
				}
				*/
			}
			uni = un;
			gpc_polygon child;
			//printAVR(un);
			gpc_polygon_clip(GPC_DIFF, &gpcvr, &un, &child);
			for (int m = 0; m < child.num_contours; m++) {
				//cout << child.contour[m].num_vertices << endl;
				gpc_polygon *tmp = new gpc_polygon();// { 0, NULL, NULL };
				//cout << result.contour[i].num_vertices << endl;
				gpc_vertex *tv = new gpc_vertex[child.contour[m].num_vertices];
				allPointers.push_back(tmp);
				allPointers.push_back(tv);

				for (int l = 0, n = 0; l < child.contour[m].num_vertices; l++) {
					tv[n].x = child.contour[m].vertex[l].x;
					tv[n++].y = child.contour[m].vertex[l].y;
				}
				gpc_vertex_list tvl = { child.contour[m].num_vertices, tv };
				gpc_add_contour(tmp, &tvl, 0);
				//cout << "DIFF VR";
				//printAVR(*tmp);
				AVR* temp = new AVR(tmp);
				allPointers.push_back(temp);
				temp->PVQS.push_back(i);
				newAvr.push_back(*temp);
			}

			gpavrs.clear();
			for (int i = 0; i < newAvr.size(); i++)
			{
				gpavrs.push_back(newAvr[i]);
			}
			newAvr.clear();

			/*
			//tmpvector->push_back(gpavrs[0]);
			for (int j = 0; j < gpavrs.size(); j++)
			{
				tmpvector->push_back(gpavrs[j]);
			}
			//gpavrs.clear();
			gpavrs.clear();
			for (int j = 0; j < newAvr.size(); j++)
			{
				gpavrs.push_back(newAvr.at(j));
			}
			newAvr.clear();

			for (int j = tmpvector->size() - 1; j >= 0; j--)
			{
				AVR *pointer = &(*tmpvector)[j];
				//free(pointer);
				delete pointer;
			}

			tmpvector = new vector<AVR>();*/


		}
		//int x = -90;
		//printAVRlist();
		//sw.stop();
		//fprintf(fp, "%d\n", sw.getDiff());


	}
	//fclose(fp);

	printf("AVR computation finished.\n");


}

void CMVQ::writeAVRDB() {
	fp = fopen("VizQ\\avrdb.txt", "w");
	fprintf(fp, "root: %d\n", rtreeAVR->root);
	for (int i = 0; i < gpavrs.size(); ++i) {
		fprintf(fp, "aid: %d\n", i);
		//printf("aid: %d\n", i);
		int n = gpavrs[i].avrPolygon->num_contours;
		fprintf(fp, "contours: %d\n", n);
		//printf("contours: %d\n", n);

		for (int j = 0; j < n; ++j) {
			int m = gpavrs[i].avrPolygon->contour[j].num_vertices;
			fprintf(fp, "vertices: %d\n", m);
			//printf("contour: %d, vertices: %d\n", j, m);
			for (int k = 0; k < m; ++k) {
				fprintf(fp, "%f %f\n", gpavrs[i].avrPolygon->contour[j].vertex[k].x, gpavrs[i].avrPolygon->contour[j].vertex[k].y);
				//printf("%f %f\n", gpavrs[i].avrPolygon->contour[j].vertex[k].x, gpavrs[i].avrPolygon->contour[j].vertex[k].y);
			}
		}
		n = gpavrs[i].PVQS.size();
		fprintf(fp, "PVQS: %d ", n);
		for (int j = 0; j < n; ++j) {
			fprintf(fp, "%d ", gpavrs[i].PVQS[j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

MBR *mbr;
void CMVQ::getMBRFromPolygon(gpc_polygon *temp){

	double maxX, maxY, minX, minY;
	maxX = minX = temp->contour->vertex[0].x;
	minY = maxY = temp->contour->vertex[0].y;
	for (int i = 0; i < temp->contour->num_vertices; i++)
	{
		if (maxX < temp->contour->vertex[i].x)maxX = temp->contour->vertex[i].x;
		if (maxY < temp->contour->vertex[i].y)maxY = temp->contour->vertex[i].y;
		if (minX > temp->contour->vertex[i].x)minX = temp->contour->vertex[i].x;
		if (minY > temp->contour->vertex[i].y)minY = temp->contour->vertex[i].y;
	}

	Coordinate bottomLeft(minX, minY, 0), topRight(maxX, maxY, 0);
	mbr = new MBR(bottomLeft, topRight);
	//allPointers.push_back(mbr);
}

void CMVQ::makeAVRFile(){
	printf("Generating AVR file ... \n");
	char s[1000] = ""; strcat(s, "VizQ\\"); strcat(s, "AVRMBR.txt");
	FILE *fp = fopen(s, "w");
	fprintf(fp, "%d\n", gpavrs.size());
	for (int i = 0; i < gpavrs.size(); i++)
	{
		getMBRFromPolygon(gpavrs[i].avrPolygon);
		fprintf(fp, "%g %g 0 %g %g 0\n", mbr->bottomLeft.x, mbr->bottomLeft.y, mbr->topRight.x, mbr->topRight.y);
		delete mbr;
	}
	fclose(fp);
	printf("AVR file generated.\n");
}
bool CMVQ::isInsidePolygon(gpc_polygon avr, float *mbrf){

	/* zitu: returns true if target overlaps with the avr */

	MBR mbr(mbrf);

	gpc_polygon gpc= {0,NULL,NULL};
	gpc_vertex ver[] = { { mbr.bottomLeft.x, mbr.bottomLeft.y  },
			{ mbr.topLeft.x, mbr.topLeft.y },
			{ mbr.topRight.x, mbr.topRight.y },
			{ mbr.bottomRight.x, mbr.bottomRight.y }
		};
	gpc_vertex_list vl = { 4, ver };

	gpc_add_contour(&gpc, &vl, 0);
	/*printf("AVR: ");
	printAVR(avr);
	printf("Target: ");
	printAVR(gpc);*/
	gpc_polygon intersection = {0,NULL,NULL};
	gpc_polygon_clip(GPC_INT, &gpc, &avr, &intersection);
	/*printf("Intersection: ");
	printAVR(intersection);*/
	if (intersection.num_contours == 0)return false;
	return true;
	/* debug: zitu
		should return true when even some part of target is within an AVR
		not only when target is completely inside AVR

		gpc_polygon_clip(GPC_DIFF, &gpc, &intersection, &intersection);
		printf("Target - Intersection : ");
		printAVR(intersection);
		if (intersection.num_contours == 0)return true;

		return false;
	*/
}

char targetPathString[1000];
float midx, midy, midz;

void CMVQ::incrementalAVRBSApproach(){

	//printf("Running algorithm ... ");

	int n;

	/*FILE *fpTarget = fopen(targetPathString, "r");

	char opEx[1000];
	strcpy(opEx, outputPath);
	strcat(opEx, varyWhatOutput);
	strcat(opEx, "ET");
	strcat(opEx, curPrefix);
	strcat(opEx, "_");
	strcat(opEx, iterString);
	strcat(opEx, isPathVaried);
	strcat(opEx, pathCountString);
	strcat(opEx, isDebug == 0 ? "" : debugString);
	strcat(opEx, ".txt");

	char opIO[1000];
	strcpy(opIO, outputPath);
	strcat(opIO, varyWhatOutput);
	strcat(opIO, "IO");
	strcat(opIO, curPrefix);
	strcat(opIO, "_");
	strcat(opIO, iterString);
	strcat(opIO, isPathVaried);
	strcat(opIO, pathCountString);
	strcat(opIO, isDebug == 0 ? "" : debugString);
	strcat(opIO, ".txt");

	FILE *fpTime = fopen(opEx,"w");
	FILE *fpIO = fopen(opIO, "w");
	fscanf(fpTarget, "%d", &n);
 	*/

	gpc_polygon *boundary = new gpc_polygon();


	//MBR mbr;
	float fmbr[6];
	//int ioCount;
	//Stopwatch sw;
	for (int targetCount = 0; targetCount < 1; targetCount++)
	{

		//if (targetCount % 10 == 0)
		//{
		//	for (int i = 0; i < 79; i++)  //clear a line
		//		printf("\b");

		//	printf("No. of Target Handled:%d\n", targetCount);

		//}
		// scan targets mid points
		//fscanf(fpTarget, "%f %f %f", &midx, &midy, &midz);
		// create MBR from target location
		fmbr[0] = midx - (targetSize / 2);
		fmbr[2] = midy - (targetSize / 2);
		fmbr[4] = 0;
		fmbr[1] = midx + (targetSize / 2);
		fmbr[3] = midy + (targetSize / 2);
		fmbr[5] = 0;


		// boundary is initialized and mbr of target is inside the previous boundary (AVR) then we just compute visibility
		if (boundary->contour!=NULL && isInsidePolygon(*boundary, fmbr) == true && targetCount!=0){

			MBR target(fmbr);
			computeVisibility(target,K);
			///printf("%d %d\n", targetCount, currentPVQS.size());

			//continue;
		}
		else {

			currentPVQS.clear();	// remove PVQS items from previous iteration

			gpc_free_polygon(boundary);	// free boundary of AVR ?

			while (!qRtreeNodes.empty())qRtreeNodes.pop();

			qRtreeNodes.push(rtreeAVR->root);	// Q to hold r-tree nodes
			Pair *pair;

			while (!qRtreeNodes.empty()){
				int rtNodeId = qRtreeNodes.front();
				qRtreeNodes.pop();
				RTNode rtn(rtreeAVR, rtNodeId);
				for (int j = 0; j < rtn.num_entries; j++)
				{
					Entry &entry = rtn.entries[j];
					// debug: zitu
					/*for (int i = 0; i < 6; ++i) printf("%f ", entry.bounces[i]);
					printf("\n");*/
					if (entry.intersectsMBR(fmbr)){	// current entry intersects with target
						pair = new Pair(rtNodeId, j);
						//allPointers.push_back(pair);
						if (!rtn.level && isInsidePolygon(*(gpavrs[entry.son].avrPolygon),fmbr)){
							int size = gpavrs[entry.son].PVQS.size();
							for (int i = 0; i < size; i++)
							{
								currentPVQS.insert(gpavrs[entry.son].PVQS[i]);
								//boundary = gpavrs[entry.son].avrPolygon;
							}
							gpc_polygon_clip(GPC_UNION, gpavrs[entry.son].avrPolygon, boundary, boundary);
						}
						else if(rtn.level>0)qRtreeNodes.push(entry.son);
						//delete pair;
					}
				}
			}

			//printf("%d %d\n",targetCount, currentPVQS.size());

			//qccom=qc intersect qp

			set<int> intersect;
			std::set_intersection(currentPVQS.begin(), currentPVQS.end(), previousPVQS.begin(), previousPVQS.end(),
				std::inserter(intersect, intersect.begin()));


			//qt=qc\qcom
			set<int> differece;
			std::set_difference(currentPVQS.begin(), currentPVQS.end(), intersect.begin(), intersect.end(),
				std::inserter(differece, differece.begin()));


			//for all q in Q t do
			//	Ab = Ab union q.B
			//	end for
			set<int>::iterator setIt;
			set<int>::iterator differenceIt;
			map<Pair, int, ComparePair>::iterator mapIt;
			for (differenceIt = differece.begin(); differenceIt != differece.end(); differenceIt++)
			{
				for (mapIt = BS[*differenceIt].begin(); mapIt != BS[*differenceIt].end(); mapIt++)
				{
					if (ABS.find(mapIt->first) == ABS.end())ABS[mapIt->first] = 1;
					else ABS[mapIt->first] = ABS[mapIt->first] + 1;
					//printf("%d ", mapIt->second);
				}
				//printf("\n");
			}

			//Qt = Qp \ Qcom

			differece.clear();
			std::set_difference(previousPVQS.begin(), previousPVQS.end(), intersect.begin(), intersect.end(),
				std::inserter(differece, differece.begin()));

			/*for all q in Q t do
			UpdateABS(A b, q, Q c)
			end for*/

			for (differenceIt = differece.begin(); differenceIt != differece.end(); differenceIt++)
			{
				for (mapIt = BS[*differenceIt].begin(); mapIt != BS[*differenceIt].end(); mapIt++)
				{
					if (ABS[mapIt->first] == 1) ABS.erase(ABS.find(mapIt->first));
					else if (ABS.find(mapIt->first) != ABS.end())ABS[mapIt->first] = ABS[mapIt->first] - 1;
				}
			}



			rtns.clear();
			blockset.clear();
			entries.clear();
			//int x = 0;
			for (mapIt = ABS.begin(); mapIt != ABS.end(); mapIt++){

				if (blockset.find(mapIt->first.blockNo) == blockset.end()){
					//ioCount++;
					RTNode *rtn = new RTNode(rtree, mapIt->first.blockNo);
					//allPointers.push_back(rtn);
					rtns.push_back(rtn);
					entries.push_back(&rtn->entries[mapIt->first.entryNo]);
					//allPointers.push_back();
					blockset[mapIt->first.blockNo] = rtns.size()-1;
				}

			}

			/*for (int i = 0; i < rtns.size(); i++)
			{
				for (int j = 0; j < rtns[i]->num_entries; j++)
				{
					//printf("%d\n",rtns[i]->block);
					for (int k = 0; k < 6; k++){
						//printf("%g ", rtns[i]->entries[j].bounces[k]);
					}
					//printf("\n");
				}

			}*/

			MBR target(fmbr);
			computeVisibility(target, K);

			//use pq.top to get the queryPoint with maximum visibility

			//previousPVQS = currentPVQS;

			previousPVQS.clear();
			for (setIt = currentPVQS.begin(); setIt != currentPVQS.end(); setIt++)
			{
				previousPVQS.insert(*setIt);
			}

		}

		/*sw.stop();

		int clkCount = sw.getDiff();

		fprintf(fpTime,"%d\n",clkCount);
		fprintf(fpIO, "%d\n", ioCount);*/

	}
	//fclose(fpIO);
	//fclose(fpTime);

}

void CMVQ::mbrBSApproach(){

	int n;


	char targetPath[1000];
	strcpy(targetPath, c);
	strcat(targetPath, varyWhat);
	strcat(targetPath, "Targetpath.txt");

	FILE *fpTarget = fopen(targetPathString, "r");




	//fscanf(fpTarget, "%d", &n);

	int ioCount;


	//FILE *fpTarget = fopen("Targetpath.txt", "r");
	fscanf(fpTarget, "%d", &n);
	float midx, midy, midz;
	//MBR mbr;
	float *mbr = new float[2 * rtree->dimension];
	//allPointers.push_back(mbr);
	for (int targetCount = 0; targetCount < n; targetCount++)
	{

		if (targetCount % 10 == 0)
		{
			for (int i = 0; i < 79; i++)  //clear a line
				printf("\b");

			printf("No. of Target Handled:%d\n", targetCount);

		}

		fscanf(fpTarget, "%f %f %f", &midx, &midy, &midz);
		mbr[0] = midx - (targetSize / 2);
		mbr[2] = midy - (targetSize / 2);
		mbr[4] = 0;
		mbr[1] = midx + (targetSize / 2);
		mbr[3] = midy + (targetSize / 2);
		mbr[5] = 0;

		while (!qRtreeNodes.empty())qRtreeNodes.pop();

		ioCount = 0;

		currentPVQS.clear();

		qRtreeNodes.push(rtreeVR->root);


		Pair *pair;
		while (!qRtreeNodes.empty()){
			int rtNodeId = qRtreeNodes.front();
			qRtreeNodes.pop();
			RTNode rtn(rtreeVR, rtNodeId);
			ioCount++;
			for (int j = 0; j < rtn.num_entries; j++)
			{
				Entry &entry = rtn.entries[j];

				/*for (int k = 0; k < 2*rtreeVR->dimension; k++)
				{
				printf("%f ", entry.bounces[k]);
				}
				printf("\n");*/
				if (entry.intersectsMBR(mbr)){
					pair = new Pair(rtNodeId, j);
					//allPointers.push_back(pair);
					if (!rtn.level){
						PVQS.push_back((*pair));
						currentPVQS.insert(entry.son);
					}//pushtoBS
					else qRtreeNodes.push(entry.son);

				}
			}
		}

		PVQS.clear();


		set<int>::iterator setIt;
		map<Pair, int, ComparePair>::iterator mapIt;

		ABS.clear();
		for (setIt = currentPVQS.begin(); setIt!= currentPVQS.end(); setIt++)
		{
			for (mapIt = BS[*setIt].begin(); mapIt != BS[*setIt].end(); mapIt++)
			{
				ABS[mapIt->first] = 1;
			}
		}


		rtns.clear();
		blockset.clear();
		entries.clear();
		//int x = 0;
		for (mapIt = ABS.begin(); mapIt != ABS.end(); mapIt++){

			if (blockset.find(mapIt->first.blockNo) == blockset.end()){
				ioCount++;
				RTNode *rtn = new RTNode(rtree, mapIt->first.blockNo);
				//allPointers.push_back(rtn);
				rtns.push_back(rtn);
				entries.push_back(&rtn->entries[mapIt->first.entryNo]);
				//allPointers.push_back();
				blockset[mapIt->first.blockNo] = rtns.size() - 1;
			}

		}


		MBR target(mbr);
		computeVisibility(target, K);


	}
}


void CMVQ::readBlockingSetDB(char *dataset) {
	ifstream in("VizQ\\bsdb.txt");
	int qid = -1;
	for (string line; getline(in, line);) {
		if (line.find("qid") != string::npos) {
			qid = atoi(line.substr(5).c_str());
		}
		else {
			int val[3];
			char t[1000];
			int j = 0;
			int k = 0;
			for (int i = 0; i < line.length(); ++i) {
				if (line[i] != ' ') {
					t[k++] = line[i];
				}
				else {
					t[k] = NULL;
					val[j++] = atoi(t);
					k = 0;
				}
			}
			t[k] = NULL;
			val[j] = atoi(t);
			//for (int i = 0; i < 3; ++i)
			//	cout << val[i] << " ";
			//cout << endl;
			Pair *pair = new Pair(val[0], val[1]);
			BS[qid][(*pair)] = val[2];
		}
	}
	r = new RTreeCmdIntrpr();
	char tree_fname[200] = "ob\\";
	strcat(tree_fname, dataset);
	strcat(tree_fname, ".tree");
	if (r->chk_file_exist(tree_fname)) {
		//printf("Loading Obstacle Set R-Tree\n");
		//r->get_blen();
		r->o_blen = 256;
		r->o_csize = 0;
		//r->get_csize();
		r->free_tree();
		r->cache = new Cache(r->o_csize, r->o_blen);
		r->tree = new RTree(tree_fname, r->cache);
		if (r->o_csize > 0 && r->tree->file->get_blocklength() != r->o_blen);
			//printf("Warning: the block length of cache does not agree with the tree!\n");
		//printf("Tree residing in memory.\n");
		rtree = r->tree;
	}
	else {
		//printf("R-Tree file does not exist\n");
	}
	//delete r;
}

void CMVQ::traverseRTree() {
	qRtreeNodes.push(rtreeAVR->root);
	while (!qRtreeNodes.empty()) {
		int rtNodeId = qRtreeNodes.front();
		qRtreeNodes.pop();
		RTNode rtn(rtreeAVR, rtNodeId);
		for (int j = 0; j < rtn.num_entries; j++)
		{
			Entry &entry = rtn.entries[j];
			if (rtn.level) qRtreeNodes.push(entry.son);
			else {
				printf("%d ", entry.son);
			}
		}
	}
}

void CMVQ::readAVRDB() {
	ifstream in("VizQ\\avrdb.txt");
	int aid = -1;
	int contours = -1;
	for (string line; getline(in, line);) {
		//cout << line << endl;
		if (line.find("aid") != string::npos) {
			aid = atoi(line.substr(5).c_str());
		}
		else if (line.find("contours") != string::npos) {
			gpc_polygon *gp = new gpc_polygon();
			//gpc_vertex v[] = { { coord[0].x, coord[0].y }, { coord[1].x, coord[1].y }, { coord[2].x, coord[2].y } };

			contours = atoi(line.substr(10).c_str());
			string t;
			for (int i = 0; i < contours; ++i) {
				getline(in, t);
				//cout << t << endl;
				gpc_vertex *v;
				int vertices;
				if (t.find("vertices") != string::npos) {
					vertices = atoi(t.substr(10).c_str());
					v = new gpc_vertex[vertices];
					for (int j = 0; j < vertices; ++j) {
						string l;
						getline(in, l);
						//cout << l << endl;
						char h[1000];
						double x, y;
						int m = 0;
						for (int k = 0; k < l.length(); ++k) {
							if (l[k] != ' ')
								h[m++] = l[k];
							else {
								h[m] = NULL;
								m = 0;
								x = atof(h);
							}
						}
						h[m] = NULL;
						y = atof(h);
						v[j].x = x;
						v[j].y = y;
					}
				}
				gpc_vertex_list vl = {vertices, v };
				gpc_add_contour(gp, &vl, 0);
			}
			string p;
			getline(in, p);
			if (p.find("PVQS") != string::npos) {
				p = p.substr(6);
				char v[6];
				int num_pvq;
				vector<int> pvq;
				for (int k = 0; k < p.length(); ++k) {
					if (p[k] == ' ') {
						v[k] = NULL;
						num_pvq = atoi(v);
						p = p.substr(k+1);
						break;
					}
					v[k] = p[k];
				}
				for (int k = 0; k < num_pvq; ++k) {
					char v[6];
					for (int l = 0; l < p.length(); ++l) {
						if (p[l] == ' ') {
							v[l] = NULL;
							pvq.push_back(atoi(v));
							p = p.substr(l+1);
							break;
						}
						v[l] = p[l];
					}
				}
				AVR *temp = new AVR(gp);
				temp->PVQS = pvq;
				gpavrs.push_back(*(temp));
			}
			//for (int k = 0; k < gpavrs.size(); ++k) printAVR(*(gpavrs[k].avrPolygon));
		}
	}
	r = new RTreeCmdIntrpr();
	char tree_fname[200] = "VizQ\\AVRMBR.tree";
	if (r->chk_file_exist(tree_fname)) {
		//printf("Loading AVR DB R-Tree\n");
		//r->get_blen();
		r->o_blen = 256;
		r->o_csize = 0;
		//r->get_csize();
		r->free_tree();
		r->cache = new Cache(r->o_csize, r->o_blen);
		r->tree = new RTree(tree_fname, r->cache);
		if (r->o_csize > 0 && r->tree->file->get_blocklength() != r->o_blen);
			//printf("Warning: the block length of cache does not agree with the tree!\n");
		//printf("Tree residing in memory.\n");
		rtreeAVR = r->tree;
	}
	else {
		//printf("R-Tree file does not exist\n");
	}
	//printf("%d\n", rtreeAVR->root);
	//delete r;
	//traverseRTree();	// for debug

}



int main(int argc, char **argv){

	if (argc < 2) {
		printf("Too few arguments\nOption 1: precomputation? obstacle set? query points? \nOption 2: precomputation? target pos?\n");
		return 1;
	}

	if (!strcmp("precompute", argv[1])) {
		//if (argc < 4) return 1;
		char obsset[1000] = "ob\\";
		strcat(obsset, argv[2]);
		//strcat(obsset, "dataset");
		strcat(obsset, ".txt");
		//strcat(obsset, "dataset.txt");
		readObstacles(obsset);
		createRtreeFromData(argv[2], 1);

		// precomputation part begins
		char qset[1000] = "qp\\";
		strcat(qset, argv[3]);
		strcat(qset, ".txt");
		//strcat(qset, "querypoints.txt");
		readQueryPoints(qset);
		//printf("Query points: %d\n", queryPoints.size());

		generateVRMBRFile();
		createRtreeFromData("VRMBR", 2);

		createAVR();
		//printAVRlist();
		makeAVRFile();
		createRtreeFromData("AVRMBR", 3);
		writeAVRDB();

		computeBS();
	}

	else {
		if (argc < 6) return 1;
		// cmvq dataset queryset targetx targety
		strcat(obsset_tree, argv[2]);
		midx = atof(argv[3]);
		midy = atof(argv[4]);
		readBlockingSetDB(argv[2]);
		readAVRDB();
		char qset[1000] = "qp\\";
		strcat(qset, argv[3]);
		strcat(qset, ".txt");
		readQueryPoints(qset);
		//strcpy(targetPathString, "tp\\");
		//strcat(targetPathString, "targetpath.txt");
		incrementalAVRBSApproach();

	}





	return 0;
}

void CMVQ::precompute(char *ob, char *qp) {
	char obsset[1000];
	strcpy(obsset, ob);
	puts("Reading obstacles: ");
	puts(obsset);
	readObstacles(obsset);
	createRtreeFromData(obsset, 1);

	// precomputation part begins
	char qset[1000];
	strcpy(qset, qp);
	readQueryPoints(qset);
	printf("Query points: %d\n", queryPoints.size());

	generateVRMBRFile();
	createRtreeFromData("VRMBR", 2);

//	createAVR();
//	//printAVRlist();
//	makeAVRFile();
//	createRtreeFromData("AVRMBR", 3);
//	writeAVRDB();
//
//	computeBS();
}
