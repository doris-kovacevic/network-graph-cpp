#ifndef GRAPHPTONE_H
#define GRAPHPTONE_H

#include <iostream>
#include <string>
#include <fstream>
#include "GraphPtOne.h"
using namespace std;

#define SIZE 10

typedef struct AdjacentNode {
	string id;
	double weight = 0;
	AdjacentNode* next = nullptr;
};

typedef struct HeaderNode {
	string id;
	AdjacentNode* adjacent_nodes = nullptr;
};

typedef struct Graph {
	HeaderNode** arr = nullptr;
	int n = 0, arr_size = 0;
};

int getIndex(Graph* graph, string id);

void resizeArray(HeaderNode**& arr, int& arr_size, int n);

bool addNode(Graph* graph, string id);

bool deleteNode(Graph* graph, string id);

bool addBranch(Graph* graph, string id1, string id2, double weight);

bool deleteBranch(Graph* graph, string id1, string id2);

Graph* createGraph(string name);

void printGraph(Graph* graph);

void deleteGraph(Graph* graph);

#endif
