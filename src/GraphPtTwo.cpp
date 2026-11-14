#include "../h/GraphPtTwo.h"
#include "../h/GraphPtOne.h"

DeQueue* init()
{
	DeQueue* x = new DeQueue();
	x->last_added = new Node();
	x->first_added = new Node();
	x->last_added = nullptr;
	x->first_added = nullptr;
	return x;
}

bool Empty(DeQueue* stack)
{
	if (stack->last_added)
		return false;
	return true;
}

void stackPush(DeQueue* stack, int i, double weight)
{
	Node* a = new Node();
	a->index = i;
	a->weight = weight;
	a->next = stack->last_added;
	if (Empty(stack))
	{
		stack->last_added = a;
		stack->first_added = a;
		return;
	}
	stack->last_added = a;
}

Node* stackPop(DeQueue* stack)
{
	if (Empty(stack))
		return nullptr;
	Node* p = stack->last_added;
	stack->last_added = stack->last_added->next;
	return p;
}

void stackDelete(DeQueue* stack)
{
	if (!stack) return; 
	Node* p = stack->last_added; 
	while (p) {
		Node* tmp = p->next; 
		delete p;            
		p = tmp;           
	}
	delete stack; 
}

void queueInsert(DeQueue* queue, int i, double weight)
{
	Node* a = new Node();
	a->index = i;
	a->weight = weight;
	a->next = nullptr;
	if (!queue->first_added)
	{
		queue->first_added = a;
		queue->last_added = a;
		return;
	}
	queue->last_added->next = a;
	queue->last_added = a;
	return;
}

Node* queueDelete(DeQueue* queue)
{
	if (!queue->first_added)
		return nullptr;
	Node* x = queue->first_added;
	queue->first_added = queue->first_added->next;
	if (!queue->first_added)
		queue->last_added = nullptr;
	return x;
}

void pqInsert(DeQueue* pq, int i, double weight)
{
	Node* x = new Node();
	x->index = i;
	x->weight = weight;

	if (Empty(pq))
	{
		x->next = nullptr;
		pq->first_added = x;
		pq->last_added = x;
	}
	else
	{
		Node* p = pq->first_added;
		Node* prev = nullptr;
		while (p && p->weight > weight)
		{
			prev = p;
			p = p->next;
		}
		if (!prev)
		{
			x->next = pq->first_added;
			pq->first_added = x;
		}
		else 
		{
			prev->next = x;
			x->next = p;
		}
		if (!p)
			pq->last_added = x;
	}
}

Node* pqDelete(DeQueue* pq)
{
	return queueDelete(pq);
}

void Like(Graph* graph, string id1, string id2)
{
	if (id1 == id2)
		return;
	int i = getIndex(graph, id1);
	int j = getIndex(graph, id2);
	if (i == -1)
	{
		cout << "Korisnik " << id1 << " nije u sistemu" << endl;
		return;
	}
	if (j == -1)
	{
		cout << "Korisnik " << id2 << " nije u sistemu" << endl;
		return;
	}
	AdjacentNode* p = graph->arr[i]->adjacent_nodes;
	AdjacentNode* prev = nullptr;
	while (p)
	{
		if (p->id > id2)
			break;
		if (p->id == id2)
		{
			p->weight += 0.1;
			if (p->weight > 1)
				p->weight = 1;
			return;
		}
		prev = p;
		p = p->next;
	}
	AdjacentNode* x = new AdjacentNode();
	x->id = id2;
	x->weight = 0.1;
	if (!prev)
	{
		graph->arr[i]->adjacent_nodes = x;
	}
	else
		prev->next = x;
	x->next = p;
}

DeQueue* DfsI_finishedTimes(Graph* graph)
{
	int n = graph->n;
	int* visit = new int[n]();
	DeQueue* stack = init();
	//DeQueue* path = init();
	DeQueue* finished_times = init();
	for (int j = 0; j < graph->n; j++)
	{
		if (visit[j] == 0)
		{
			stackPush(stack, j);
		}
		while (!Empty(stack))
		{
			Node* x = stackPop(stack);
			int i = x->index;
			if (visit[i] == 0)
			{
				visit[i] = 1;
				stackPush(stack, i);
				//stackPush(path, i);
				AdjacentNode* p = graph->arr[i]->adjacent_nodes;
				while (p)
				{
					int k = getIndex(graph, p->id);
					if (visit[k] == 0)
					{
						stackPush(stack, k);
					}
					p = p->next;
				}
			}
			else if (visit[i] == 1)
			{
				stackPush(finished_times, i);
				visit[i] = 2;
			}
		}
	}
	stackDelete(stack);
	delete[] visit;
	//stackDelete(path);
	return finished_times;
}

Graph* transposedGraph(Graph* graph)
{
	Graph* gt = new Graph();
	gt->n = graph->n;
	gt->arr = new HeaderNode * [gt->n];
	for (int i = 0; i < graph->n; i++)
	{
		gt->arr[i] = new HeaderNode();
		gt->arr[i]->id = graph->arr[i]->id;
		gt->arr[i]->adjacent_nodes = nullptr;
	}
	for (int i = 0; i < graph->n; i++)
	{
		AdjacentNode* p = graph->arr[i]->adjacent_nodes;
		while (p)
		{
			addBranch(gt, p->id, graph->arr[i]->id, p->weight);
			p = p->next;
		}
	}
	return gt;
}

void MaxComponent(Graph* graph) {
	DeQueue* finished_times = DfsI_finishedTimes(graph);
	Graph* gt = transposedGraph(graph);
	DeQueue* stack = new DeQueue();
	int* visit = new int[graph->n]();
	DeQueue* max = init();
	int maxsize = 0;

	while(!Empty(finished_times)) 
	{
		Node* x = stackPop(finished_times);
		int j = x->index;
		if (visit[j] == 0)
		{
			stackPush(stack, j);
			DeQueue* curr = new DeQueue();
			int currsize = 0;
			while (!Empty(stack)) 
			{
				x = stackPop(stack);
				int u = x->index;
				if (visit[u] == 0) 
				{
					visit[u] = 1;
					stackPush(curr, u);
					currsize++;
					AdjacentNode* p = gt->arr[u]->adjacent_nodes;
					while (p) 
					{
						int k = getIndex(gt, p->id);
						if (visit[k] == 0) 
							stackPush(stack, k);
						p = p->next;
					}
				}
			}
			if (currsize >= maxsize)
			{
				maxsize = currsize;
				stackDelete(max);
				max = curr;
			}
		}
	}
	Node* a = stackPop(max);
	while (!Empty(max))
	{
		cout << graph->arr[a->index]->id << " -> ";
		a = stackPop(max);
	}
	if (a)
		cout << graph->arr[a->index]->id << endl;
	delete[] visit;
	stackDelete(stack);
	stackDelete(finished_times);
	deleteGraph(gt);
	stackDelete(max);
}

void MostLikelyPath(Graph* graph, string id1, string id2)
{
	int x = getIndex(graph, id1);
	int y = getIndex(graph, id2);
	if (x == -1)
	{
		cout << "Korisnik " << id1 << " nije u sistemu" << endl;
		return;
	}
	if (y == -1)
	{
		cout << "Korisnik " << id2 << " nije u sistemu" << endl;
		return;
	}
	DeQueue* pq_d = init();
	int* t = new int[graph->n];
	for (int i = 0; i < graph->n; i++)
		t[i] = -1;
	double* d = new double[graph->n]();
	int* visit = new int[graph->n]();
	visit[x] = 1;
	d[x] = 1;
	AdjacentNode* p = graph->arr[x]->adjacent_nodes;
	while (p)
	{
		int k = getIndex(graph, p->id);
		pqInsert(pq_d, k, p->weight);
		d[k] = p->weight;
		t[k] = x;
		p = p->next;
	}
	while (!Empty(pq_d))
	{
		Node* a = pqDelete(pq_d);
		int i = a->index;
		visit[i] = 1;
		p = graph->arr[i]->adjacent_nodes;
		while (p)
		{
			int j = getIndex(graph, p->id);
			if (visit[j] == 0)
			{
				if (d[i] * p->weight > d[j])
				{
					d[j] = d[i] * p->weight;
					t[j] = i;
					pqInsert(pq_d, j, d[j]);
				}
			}
			p = p->next;
		}
		
	}
	if (d[y] == 0)
	{
		cout << "Ne postoji put od korisnika " << id1 << " do korisnika " << id2 << " " << endl;
		delete[] t;
		delete[] d;
		delete[] visit;
		pqDelete(pq_d);
		return;
	}
	DeQueue* stack = init();
	int i = y;
	stackPush(stack, i);
	while (i != x && !Empty(stack))
	{
		stackPush(stack, t[i], d[i]);
		i = t[i];
	}
	cout << "Najverovatniji put od " << id1 << " do " << id2 << " je: ";
	Node* a = stackPop(stack);
	while (!Empty(stack)) 
	{
		cout << graph->arr[a->index]->id << " - (" << a->weight << ") -> ";
		a = stackPop(stack);
	}
	cout << graph->arr[a->index]->id << endl;
	//cout << "Verovatnoca puta: " << d[y] << endl;
	if(a)
		delete a;
	delete[] t;
	delete[] d;
	delete[] visit;
	pqDelete(pq_d);
	stackDelete(stack);
}


void KthInfluence(Graph* g, int k)
{
	if (k<1 || k>g->n)
	{
		cout << "Uneli ste nevalidan broj k" << endl;
		return;
	}
	Graph* graph = transposedGraph(g);
	DeQueue* influences = init();
	int* t = new int[graph->n];
	double* d = new double[graph->n];
	int* visit = new int[graph->n]();
	for (int i = 0; i < graph->n; i++)
	{
		for (int j = 0; j < graph->n; j++)
		{
			t[j] = -1;
			d[j] = 0.0;
			visit[j] = 0;
		}
		DeQueue* pq_d = init();
		visit[i] = 1;
		d[i] = 1.0;
		AdjacentNode* p = graph->arr[i]->adjacent_nodes;
		while (p)
		{
			int k = getIndex(graph, p->id);
			pqInsert(pq_d, k, p->weight);
			d[k] = p->weight;
			t[k] = i;
			p = p->next;
		}
		while (!Empty(pq_d))
		{
			Node* a = pqDelete(pq_d);
			int c = a->index;
			visit[c] = 1;
			p = graph->arr[c]->adjacent_nodes;
			while (p)
			{
				int j = getIndex(graph, p->id);
				if (!visit[j])
				{
					double prob = d[c] * p->weight;
					if (prob > d[j])
					{
						d[j] = prob;
						t[j] = c;
						pqInsert(pq_d, j, d[j]);
					}
				}
				p = p->next;
			}
			delete a;
		}
		double prob_sum = 0;
		//pod komentarom su delovi koji se koriste ako se uticaj racuna kao (suma verovatnoca do svih cvorova)/(broj cvorova do kojih objava moze da dodje)
		//van komentara je usvojena situacija gde se uticaj racuna kao (suma verovatnoca do svih cvorova)/(ukupan broj cvorova)
		//double no_connections = 0;
		for (int m = 0; m < graph->n; m++)
		{
			if (m != i)
			{
				prob_sum += d[m];
				//if (t[i][m] != -1)
				//	no_connections++;
			}
		}
		//if(no_connections!=0)
		//	curr_influence = prob_sum/no_connections;
		double curr_influence = prob_sum / graph->n;
		pqInsert(influences, i, curr_influence);
		queueDelete(pq_d);
	}
	Node* a = nullptr;
	for (int i = 0; i < k; i++)
		a = pqDelete(influences);
	cout << "Korisnik sa " << k << ". najvecim uticajem je " << graph->arr[a->index]->id << endl;
	cout << "Uticaj: " << a->weight << endl;
	delete[] visit;
	delete[] d;
	delete[] t;
	pqDelete(influences);
	deleteGraph(graph);
}
