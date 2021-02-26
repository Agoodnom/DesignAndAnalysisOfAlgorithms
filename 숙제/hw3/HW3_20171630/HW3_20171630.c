#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
	unsigned long long int weight;
	int u;
	int v;
}edge;

typedef struct {
	int V;
	unsigned long long int E;
	unsigned long long int Max;
}Graph;

typedef struct {
	int parent;
	int rank;
	unsigned long long int vertex_num;
	unsigned long long int weight;
}set;

Graph g;
unsigned long long int heap_size = 0;
unsigned long long int sel_edge = 0;
int kscanned = 0;
void make_heap(edge* heap);
edge delete_heap(edge* heap);
void adjust(edge* heap, int root, int n);
void set_init(set *x);
int set_find(set *x, int v);
void set_union(set *x, int u, int v, unsigned long long int w);
void kruskal(set *x, edge* heap);

int main() {
	FILE* commandfp;
	FILE* infp;
	FILE* outfp;
	char str[255];
	edge* min_heap;
	int num = 0, j = 0;
	clock_t start, end1, end2;
	float res1, res2;
	set* result;
	commandfp = fopen("commands.txt", "r");
	if (commandfp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}

	fscanf(commandfp, "%s", str);
	infp = fopen(str, "r");
	if (infp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}

	fscanf(commandfp, "%s", str);
	outfp = fopen(str, "w");
	if (outfp == NULL) {
		printf("The input file dose not exist.\n");
		exit(1);
	}

	fclose(commandfp);

	fscanf(infp, "%d %lld %lld", &g.V, &g.E, &g.Max);
	min_heap = (edge*)malloc(sizeof(edge)*(g.E + 1));

	set* v = (set*)malloc(sizeof(set) * g.V);

	for (int i = 0; i < g.E; i++) {	//O(lEl)
		edge e;
		fscanf(infp, "%d %d %lld", &e.u, &e.v, &e.weight);
		min_heap[i + 1] = e;
		heap_size++;
	}
	start = clock();
	make_heap(min_heap);	//O(lEl)
	end1 = clock();
	set_init(v);
	kruskal(v, min_heap);	//O(lElloglVl)
	num = g.V - sel_edge;
	result = (set*)malloc(sizeof(set)*num);
	for (int i = 0; i < g.V; i++) {	//O(lVl)
		if (v[i].parent == i) {
			result[j].vertex_num = v[i].vertex_num;
			result[j].weight = v[i].weight;
			j++;
			if (j == num)
				break;
		}
	}
	end2 = clock();

	res1 = (float)(end1 - start) / CLOCKS_PER_SEC;
	res2 = (float)(end2 - start) / CLOCKS_PER_SEC;
	printf("kscanned: %d\nsel_edge: %d\ng.V %d\n", kscanned, sel_edge, g.V);
	printf("%.3f(%.3f)\n%d\n", res2, res1, num);

	fprintf(outfp, "%d\n", num);
	for (int i = 0; i < num; i++) {	//O(lVl);
		fprintf(outfp, "%lld %lld\n", result[i].vertex_num, result[i].weight);
		printf("%lld %lld\n", result[i].vertex_num, result[i].weight);

	}

	free(min_heap);
	free(v);
	free(result);
	fclose(outfp);
	fclose(infp);

	return 0;
}

void make_heap(edge* heap) {
	for (int i = heap_size / 2; i > 0; i--) {
		adjust(heap, i, heap_size);
	}
}

edge delete_heap(edge* heap) {
	edge temp;
	edge e;
	e.u = heap[1].u;
	e.v = heap[1].v;
	e.weight = heap[1].weight;

	temp = heap[1];
	heap[1] = heap[heap_size];
	heap[heap_size] = temp;
	heap_size--;
	adjust(heap, 1, heap_size);

	return e;
}

void adjust(edge* heap, int i, int n) {
	int child, rootkey;
	edge e;
	e = heap[i];
	rootkey = heap[i].weight;
	child = 2 * i;
	while (child <= n) {
		if ((child < n) && (heap[child].weight > heap[child + 1].weight))
			child++;
		if (rootkey <= heap[child].weight)
			break;
		else {
			heap[child / 2] = heap[child];
			child *= 2;
		}
	}
	heap[child / 2] = e;
}

void set_init(set *x) {
	for (int i = 0; i < g.V; i++) {
		x[i].parent = i;
		x[i].rank = 0;
		x[i].vertex_num = 1;
		x[i].weight = 0;
	}
}
int set_find(set *x, int v) {
	if (x[v].parent != v)
		x[v].parent = set_find(x, x[v].parent);

	return x[v].parent;
}
void set_union(set *x, int u, int v, unsigned long long int w) {
	if (u == v)
		return;

	if (x[u].rank < x[v].rank) {
		x[u].parent = v;
		x[v].vertex_num += x[u].vertex_num;
		x[v].weight += x[u].weight + w;
	}
	else if (x[u].rank > x[v].rank) {
		x[v].parent = u;
		x[u].vertex_num += x[v].vertex_num;
		x[u].weight += x[v].weight + w;
	}
	else {
		x[v].parent = u;
		x[u].rank++;
		x[u].vertex_num += x[v].vertex_num;
		x[u].weight += x[v].weight + w;
	}
}

void kruskal(set *x, edge* heap) {
	int u, v;
	sel_edge = 0; //선택된 edge의 수
	edge e;
	while (sel_edge < g.V - 1) {
		kscanned++;	
		e = delete_heap(heap);	//O(log(lEl))->O(log(lVl))
		u = set_find(x, e.u);	//O(α(lVl))
		v = set_find(x, e.v);	//O(α(lVl))
		if (u != v) {
			set_union(x, u, v, e.weight);
			sel_edge++;
		}
		if (heap_size == 0)
			break;
	}
}