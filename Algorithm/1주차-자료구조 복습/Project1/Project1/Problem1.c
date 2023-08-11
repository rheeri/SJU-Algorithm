#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct list {
	int rank;
	struct node* header;
	struct node* trailer;
}list;
typedef struct node {
	int elem;
	struct node* prev;
	struct node* next;
}node;

list* initList();
void add(list* L);
void delete(list* L);
void get(list* L);
void print(list* L);

int main() {
	int n, r;
	char cmmd, ch;
	list* L = initList();
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &cmmd);

		if (cmmd == 'A') add(L);
		else if (cmmd == 'D') delete(L);
		else if (cmmd == 'G') get(L);
		else print(L);
	}
	return 0;
}

list* initList() {
	list* L = (list*)malloc(sizeof(list));
	node* H = (node*)malloc(sizeof(node));
	node* T = (node*)malloc(sizeof(node));

	H->next = T;
	H->prev = NULL;
	T->next = NULL;
	T->prev = H;

	L->header = H;
	L->trailer = T;
	L->rank = 0;

	return L;
}
void add(list* L) {
	int r;
	char e;
	scanf("%d %c", &r, &e);

	if (r < 1 || r > L->rank + 1) {
		printf("invalid position\n");
		return;
	}

	node* p = L->header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}

	node* newN = (node*)malloc(sizeof(node));
	newN->elem = e;
	newN->prev = p->prev;
	newN->next = p;

	p->prev->next = newN;
	p->prev = newN;

	L->rank = L->rank + 1;
}
void delete(list* L) {
	int r;
	scanf("%d", &r);

	if (r < 1 || r > L->rank) {
		printf("invalid position\n");
		return;
	}

	node* p = L->header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}

	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	L->rank = L->rank - 1;
}
void get(list* L) {
	int r;
	scanf("%d", &r);

	if (r < 1 || r > L->rank) {
		printf("invalid position\n");
		return;
	}

	node* p = L->header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	printf("%c\n", p->elem);
}
void print(list* L) {
	node* p = L->header->next;
	while (p->next != NULL) {
		printf("%c", p->elem);
		p = p->next;
	}
	printf("\n");
}