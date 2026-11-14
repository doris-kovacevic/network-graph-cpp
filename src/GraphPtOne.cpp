#include <iostream>
#include <string>
#include <fstream>
#include "../h/GraphPtOne.h"
using namespace std;

#define SIZE 10

int getIndex(Graph* graph, string id)
{
	for (int i = 0; i < graph->n; i++)
	{
		if (graph->arr[i]->id == id)
			return i;
		if (graph->arr[i]->id > id)
			break;
	}
	return -1;
}
void resizeArray(HeaderNode**& arr, int& arr_size, int n)
{
	HeaderNode** new_arr = new HeaderNode * [arr_size + SIZE];
	for (int i = 0; i < n; i++)
	{
		new_arr[i] = new HeaderNode();
		new_arr[i] = arr[i];
	}
	delete[] arr;
	arr = new_arr;
	arr_size += SIZE;
}
bool addNode(Graph* graph, string id)
{
	int insert = 0;
	while (insert < graph->n && graph->arr[insert]->id < id)
	{
		insert++;
	}
	if (insert < graph->n && graph->arr[insert]->id == id)
	{
		cout << "Korisnik je vec u sistemu" << endl;
		return false;
	}
	if (graph->n >= graph->arr_size)
	{
		resizeArray(graph->arr, graph->arr_size, graph->n);
	}
	for (int i = graph->n; i > insert; i--)
		graph->arr[i] = graph->arr[i - 1];
	graph->arr[insert] = new HeaderNode();
	graph->arr[insert]->id = id;
	graph->arr[insert]->adjacent_nodes = nullptr;
	graph->n++;
	return true;
}

bool deleteNode(Graph* graph, string id)
{
	int k = getIndex(graph, id);
	if (k == -1)
	{
		cout << "Korisnik koji nije u sistemu se ne moze obrisati" << endl;
		return false;
	}
	HeaderNode* tmp = graph->arr[graph->n - 1];
	for (int i = 0; i < graph-> n ;i++)
	{
		if (i != k)
			deleteBranch(graph, graph->arr[i]->id, id);
		if (i >= k && i < graph->n - 1)
			graph->arr[i] = graph->arr[i + 1];

	}
	graph->n--;
	return true;
}

bool addBranch(Graph* graph, string id1, string id2, double weight)
{
	if (weight < 0 || weight > 1)
	{
		cout << "Tezina grane je van opsega granica" << endl;
	}
	int i = getIndex(graph, id1);
	int j = getIndex(graph, id2);
	if (i == -1)
	{
		cout << "Korisnik " << id1 << " nije u sistemu" << endl;
		return false;
	}
	else if (j == -1)
	{
		cout << "Korisnik " << id2 << " nije u sistemu" << endl;
		return false;
	}
	AdjacentNode* p = graph->arr[i]->adjacent_nodes;
	AdjacentNode* prev = nullptr;
	while (p)
	{
		if (p->id == id2)
		{
			cout << "Veza izmedju " << id1 << " i " << id1 << " vec postoji" << endl;
			return false;
		}
		else if (p->id > id2)
			break;
		prev = p;
		p = p->next;
	}
	AdjacentNode* x = new AdjacentNode();
	x->id = id2;
	x->weight = weight;
	if (!prev)
	{
		graph->arr[i]->adjacent_nodes = x;
	}
	else
		prev->next = x;
	x->next = p;
	return true;
}

bool deleteBranch(Graph* graph, string id1, string id2)
{
	int i = getIndex(graph, id1);
	if (i == -1)
	{
		cout << "Korisnik " << id1 << " nije u sistemu" << endl;
		return false;
	}
	AdjacentNode* p = graph->arr[i]->adjacent_nodes;
	AdjacentNode* prev = nullptr;
	while (p)
	{
		if (p->id == id2)
		{
			if (prev)
				prev->next = p->next;
			else
				graph->arr[i]->adjacent_nodes = p->next; 
			delete p;
			return true;
		}
		else if (p->id > id2)
			return false;
		prev = p;
		p = p->next;
	}
	return false;
}

Graph* createGraph(string name)
{
	ifstream file;
	file.open(name);
	if (!file.is_open())
	{
		cout << "Fajl pod nazivom " << name << " ne postoji" << endl;
		return nullptr;
	}
	Graph* graph = new Graph();
	int n, e;
	file >> n;
	file >> e;
	graph->n = n;
	graph->arr_size = n;
	graph->arr = new HeaderNode * [n];
	string id1, id2;
	for (int i = 0; i < n; i++)
	{
		file >> id1;
		graph->arr[i] = new HeaderNode();
		graph->arr[i]->id = id1;
		graph->arr[i]->adjacent_nodes = nullptr;
	}
	if (e == 0)
		return graph;

	double weight;
	int i = 1;

	file >> id1;
	file >> id2;
	file >> weight;
	int j = getIndex(graph, id1);
	AdjacentNode* x = new AdjacentNode();
	x->id = id2;
	x->weight = weight;
	x->next = nullptr;
	graph->arr[j]->adjacent_nodes = x;

	while( i < e )
	{
		AdjacentNode* p = graph->arr[j]->adjacent_nodes;
		while (i < e)
		{
			i++;
			file >> id1;
			file >> id2;
			file >> weight;
			if (graph->arr[j]->id != id1)
				break;
			AdjacentNode* x = new AdjacentNode();
			x->id = id2;
			x->weight = weight;
			x->next = nullptr;
			p->next = x;
			p = p->next;
		}
		if (graph->arr[j]->id != id1)
		{
			while (true)
			{
				if (graph->arr[j]->id == id1)
					break;
				j++;
			}
			AdjacentNode* x = new AdjacentNode();
			x->id = id2;
			x->weight = weight;
			x->next = nullptr;
			graph->arr[j]->adjacent_nodes = x;
		}
	}
	return graph;
}

void printGraph(Graph* graph)
{
	int j = 0;
	for (int i = 0; i < graph->n; i++)
	{
		cout << graph->arr[i]->id;
		AdjacentNode* p = graph->arr[i]->adjacent_nodes;
		while (p)
		{
			cout << " -> (" << p->id << ", " << p->weight << ")";
			p = p->next;
		}
		cout << endl;
	}
}

void deleteGraph(Graph* graph)
{
	if (graph == nullptr)
		return;
	for (int i = 0; i < graph->n; i++)
	{
		AdjacentNode* p = graph->arr[i]->adjacent_nodes;
		while (p)
		{
			AdjacentNode* tmp = p;
			p = p->next;
			delete(tmp);
		}
		delete(graph->arr[i]);
	}
	delete[] graph->arr;
	delete graph;
	graph = nullptr;
}

