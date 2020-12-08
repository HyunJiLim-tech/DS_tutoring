#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 8
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] =
{ {0,3,INF,INF,INF,INF,INF,14},
{3,0,8,INF,INF,INF,INF,10},
{INF,8,0,15,2,INF,INF,INF},
{INF,INF,15,0,INF,INF,INF,INF},
{INF,INF,2,INF,0,9,4,5},
{INF,INF,INF,INF,9,0,INF,INF},
{INF,INF,INF,INF,4,INF,0,6},
{14,10,INF,INF,5,INF,6,0} };

int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

typedef struct element {
	int v, d;
}element;

//child������ �����ϴ� sibling�� �߰�
typedef struct TreeNode {
	int vertex, distance;
	struct TreeNode* child, * sibling, * parent;
}TreeNode;

typedef struct TreeType {
	TreeNode* tree;
}TreeType;

typedef struct {
	element* heap;
	int heap_size;
}HeapType;

element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].d > h->heap[child + 1].d))
			child++;
		if (temp.d <= h->heap[child].d)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void build_min_heap(HeapType* h) {
	int i, j;
	int parent, child;
	int flag = 0;
	element temp;
	flag = h->heap_size / 2;

	for (j = flag; j >= 1; j--) {
		parent = j;
		child = j * 2;
		while (child <= h->heap_size) {
			if ((parent * 2 + 1) <= h->heap_size) {
				if ((child < h->heap_size) && (h->heap[child].d > h->heap[child + 1].d))
					child++;
			}
			if (h->heap[parent].d <= h->heap[child].d)
				break;
			temp = h->heap[parent];
			h->heap[parent] = h->heap[child];
			h->heap[child] = temp;
			parent = child;
			child *= 2;
		}
	}
}

void decrease_key_min_heap(HeapType* h, int v, int key) {
	int point, j;
	for (j = 1; j <= h->heap_size; j++) {
		if (h->heap[j].v == v) {
			point = j;
			break;
		}
	}
	element temp;
	if (key >= h->heap[point].d) {
		printf("error : new key is not smaller than current key\n");
	}
	h->heap[point].d = key;
	int i = point;
	while ((i != 1) && (h->heap[i].d < h->heap[i / 2].d)) {
		temp = h->heap[i];
		h->heap[i] = h->heap[i / 2];
		h->heap[i / 2] = temp;
		i /= 2;
	}
}

//�����͸� �ܼ������ϰ� �ѹ��� build_min_heap���� sort����
void insert_all_vertices(HeapType* h, int n) {
	h->heap_size = 0;
	int v;
	int i = 1;
	for (v = 0; v < n; v++) {
		h->heap_size++;
		h->heap[i].v = v;
		h->heap[i].d = dist[v];
		i++;
	}
	build_min_heap(h);
}

void print_prim(TreeNode* root) {
	//root�� �ڽ����� �̵�
	//root = root->child;
	if (root) {
		printf("Vertex %d -> %d\t edge : %d\n", root->parent->vertex, root->vertex, root->distance);
		print_prim(root->child);
		print_prim(root->sibling);
	}
}

void prim(int s, int n) {
	TreeType* t = (TreeType*)malloc(sizeof(TreeType));
	t->tree = (TreeNode*)malloc(sizeof(TreeNode) * (MAX_VERTICES + 1));
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	h->heap = (element*)malloc(sizeof(element) * (MAX_VERTICES + 1));
	element e;
	//Tree �ʱ�ȭ
	for (int k = 0; k < MAX_VERTICES; k++) {
		t->tree[k].vertex = NULL;
		t->tree[k].distance = NULL;
		t->tree[k].child = NULL;
		t->tree[k].sibling = NULL;
		t->tree[k].parent = NULL;
	}
	int i, u, v;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = false;
	}
	dist[s] = 0;
	//min_heap ����
	insert_all_vertices(h, MAX_VERTICES);
	for (i = 0; i < n; i++) {
		e = delete_min_heap(h);
		u = e.v;
		selected[u] = true;
		if (e.d == INF)
			return;
		//Ʈ���� vertex, distance ���� ����
		t->tree[u].vertex = u;
		t->tree[u].distance = e.d;
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF) {
				if (!selected[v] && (weight[u][v] < dist[v])) {
					dist[v] = weight[u][v];
					decrease_key_min_heap(h, v, weight[u][v]);
					//Ʈ���� ���� �θ� ������ �ִ��� Ȯ���ϰ� �ִٸ� �� ������ ����
					if (t->tree[v].parent != NULL) {
						TreeNode* e, * f;
						e = t->tree[v].parent;
						int x, y;
						x = e->child->vertex;
						y = t->tree[v].vertex;
						//�θ��� �ڽ����� ����Ǿ� �־ �ٷ� ����
						if (x == y)
							e->child = NULL;
						//�θ��� �ڽ��� ������ ����Ǿ� �־ ��ġ�� ã�� �� ����
						else {
							e = t->tree[v].parent->child;
							while (true) {
								f = e->sibling;
								x = f->vertex;
								if (x == y) {
									e->sibling = NULL;
									break;
								}
								e = e->sibling;
							}
						}
					}
					//�θ𿡰� �ڽ��� ���ٸ� �ڽ����� ����
					if (t->tree[u].child == NULL) {
						t->tree[u].child = &t->tree[v];
					}
					//�θ𿡰� �ڽ��� �ִٸ� �� �ڽ��� ������ ����(insert_last)
					else {
						TreeNode* j;
						j = t->tree[u].child;
						while (j->sibling) {
							j = j->sibling;
						}
						j->sibling = &t->tree[v];
					}
					//�θ� ������ ����
					t->tree[v].parent = &t->tree[u];
				}
			}
		}
	}
	TreeNode* node = &t->tree[s];
	TreeNode* noded = node->child;
	print_prim(noded);
}

void main() {
	prim(0, MAX_VERTICES);
}