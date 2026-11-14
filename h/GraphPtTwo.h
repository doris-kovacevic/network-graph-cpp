#ifndef GRAPHPTTWO_H
#define GRAPHPTTWO_H

#include <iostream>
#include <string>
#include <fstream>
#include "GraphPtOne.h"
using namespace std;
typedef struct Node {
	int index = -1;
	double weight = 2;
	Node* next = nullptr;
};
typedef struct DeQueue{
	Node* last_added;
	Node* first_added;
};

DeQueue* init();

bool Empty(DeQueue* stack);

void stackPush(DeQueue* stack, int i, double weight = 2);

Node* stackPop(DeQueue* stack);

void stackDelete(DeQueue* stack);

void queueInsert(DeQueue* queue, int i, double weight = -1);

Node* queueDelete(DeQueue* queue);

void pqInsert(DeQueue* pq, int i, double weight = -1);

Node* pqDelete(DeQueue* pq);

void Like(Graph* graph, string id1, string id2);

DeQueue* DfsI_finishedTimes(Graph* graph);

Graph* transposedGraph(Graph* graph);

void MaxComponent(Graph* graph);

void MostLikelyPath(Graph* graph, string id1, string id2);

void KthInfluence(Graph* g, int k);

#endif

