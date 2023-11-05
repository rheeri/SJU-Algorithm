#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct List {
	struct Node *H;
	int size;
}List;
typedef struct Node {
	struct Node *next;
	int elem;
}Node;

List* initList();
void addElem(List* L, int e);
int removeElem(List* L);
int getElem(List* L);
List* mergeSort(List* L);
void partition(List* L, int k, List** L1, List** L2);
List* merge(List* L1, List* L2);
void printList(List* L);

int main() {
	int n, e;
	List *L = initList();

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &e);
		addElem(L, e);
	}

	L = mergeSort(L);
	printList(L);

	return 0;
}

List* initList() {
	List* L = (List*)malloc(sizeof(List));
	Node* p = (Node*)malloc(sizeof(Node));
	p->next = NULL;
	p->elem = NULL;
	L->size = 0;
	L->H = p;
	return L;
}
void addElem(List* L, int e) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->elem = e;
	newNode->next = NULL;

	Node* p = L->H;
	if (L->size == 0) {
		p->next = newNode;
		L->size++;
		return;
	}

	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newNode;
	L->size++;
	return;
}
int removeElem(List* L) {
	if (L->size == 0) return;

	Node* p = L->H->next;
	int e = p->elem;

	L->H->next = p->next;  //L->H가 아닌 L->H->next임
	L->size--;
	free(p);

	return e;
}
int getElem(List* L) {
	if (L->size == 0) return 0;

	Node* p = L->H->next;
	return p->elem;
}
List* mergeSort(List* L) {
	if (L->size > 1) {
		List *L1, *L2;
		partition(L, (L->size) / 2, &L1, &L2);

		L1 = mergeSort(L1);
		L2 = mergeSort(L2);

		L = merge(L1, L2);
	}
	return L;
}
void partition(List* L, int k, List** L1, List** L2) {
	*L1 = initList();
	*L2 = initList();
	Node* p = L->H->next;

	for (int i = 0; i < k; i++) {
		addElem(*L1, p->elem);
		p = p->next;
	}

	for (int i = k; i < L->size; i++) {
		addElem(*L2, p->elem);
		p = p->next;
	}

}
List* merge(List* L1, List* L2) {
	List* L = initList();
	
	while ((L1->size > 0) && (L2->size > 0)) {
		if (getElem(L1) < getElem(L2)) {
			addElem(L, getElem(L1));
			removeElem(L1);
		}
		else {
			addElem(L, getElem(L2));
			removeElem(L2);
		}
	}
	while (L1->size > 0) {
		addElem(L, getElem(L1));
		removeElem(L1);
	}
	while (L2->size > 0) {
		addElem(L, getElem(L2));
		removeElem(L2);
	}

	return L;
}
void printList(List* L) {
	Node* p = L->H;

	while (p->next != NULL) {
		p = p->next;
		printf(" %d", p->elem);
	}
	printf("\n");
}