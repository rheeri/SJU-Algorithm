#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int key;
}node;

struct node* root;
node* makeRoot();
int isInternal(node* w);
int isExternal(node* w);
node* treeSearch(node* v, int k);
void insertItem(int k);
node* expandExternal(node* v);
void findElem(int key);
void removeElem(int k);
void reduceExternal(node* w, node* z);
node* inOrderSucc(node* w);
node* sibling(node* w);
void print();

int main() {
	int key;
	char cmmd;
	root = makeRoot();

	while (1) {
		scanf("%c", &cmmd);
		getchar();

		if (cmmd == 'i') {
			scanf("%d", &key);
			getchar();
			insertItem(key);
		}
		else if (cmmd == 'd') {
			scanf("%d", &key);
			getchar();
			removeElem(key);
		}
		else if (cmmd == 's') {
			scanf("%d", &key);
			getchar();
			findElem(key);
		}
		else if (cmmd == 'p') {
			print();
			printf("\n");
		}
		else {
			exit(1);
		}
	}
}
node* makeRoot() {
	node* root = (node*)malloc(sizeof(node));
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;
	return;
}
int isInternal(node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	return 0;
}
int isExternal(node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	return 0;
}
node* treeSearch(node* v, int k) {
	if (isExternal(v)) return v;

	if (v->key == k) return v;
	else if (v->key > k) return treeSearch(v->lChild, k);
	else return treeSearch(v->rChild, k);
}
void insertItem(int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w)) return;
	else {
		w->key = k;
		w = expandExternal(w);
		return;
	}
}
node* expandExternal(node* v) {
	node* left = (node*)malloc(sizeof(node));
	node* right = (node*)malloc(sizeof(node));

	left->lChild = NULL;
	left->rChild = NULL;
	left->parent = v;

	right->lChild = NULL;
	right->rChild = NULL;
	right->parent = v;

	v->lChild = left;
	v->rChild = right;

	return v;
}
void findElem(int key) {
	node* w = treeSearch(root, key);
	if (isExternal(w)) printf("X\n");
	else if (w->key != key) printf("X\n");
	else printf("%d\n", w->key);
	return;
}
void removeElem(int k) {
	node* w = treeSearch(root, k);
	if (isExternal(w)) {
		printf("X\n");
		return;
	}

	int key = w->key;
	node* z = w->lChild;
	if (!isExternal(z)) z = w->rChild;

	if (isExternal(z)) {
		reduceExternal(w, z);
	}
	else { //내부노드만을 자식으로 가지는 경우
		node* y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(y, z);
	}

	printf("%d\n", key);
}
void reduceExternal(node* w, node* z) {
	node* zs = sibling(z);
	if (w->parent == NULL) {
		root = zs;
		zs->parent = NULL;
		return;
	}

	node* p = w->parent;
	zs->parent = p;
	if (p->lChild == w) p->lChild = zs;
	else p->rChild = zs;

	free(w);
	free(z);
}
node* inOrderSucc(node* w) { //중위순회계승자 y찾기
	w = w->rChild;
	if (isExternal(w)) return;

	while (!isExternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}
node* sibling(node* w) {
	if (w->parent == NULL) return;
	if (w->parent->lChild == w) return w->parent->rChild;
	else return w->parent->lChild;
}
void print() {
	if (isExternal(root)) {
		return;
	}

	printf(" %d", root->key);
	print(root->lChild);
	print(root->rChild);
}