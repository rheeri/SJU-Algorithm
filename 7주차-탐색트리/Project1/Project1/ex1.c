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

int isInternal(node* w) {
	if (w->lChild != NULL && w->rChild != NULL) return 1;
	return 0;
}
int isExternal(node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	return 0;
}
node* inOrderSucc(node* w) {
	w = w->rChild;
	if (isExternal(w)) return;

	while (isInternal(w->lChild)) w = w->lChild;
	return w;
}
node* treeSearch(node* v, int k) {
	if (isExternal(v)) return v;

	if (v->key == k) return v;
	else if ((v->key) > k) return treeSearch(v->lChild, k);
	else return treeSearch(v->rChild, k);
}
void findElem(int key) {
	node* w = treeSearch(root, key);
	if (isExternal(w)) printf("X\n");
	else if (w->key != key) printf("X\n");
	else printf("%d\n", w->key);
	return;
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
void insertItem(int k) {
	node* w = treeSearch(root, k);
	if (isInternal(w)) return;
	else {
		w->key = k;
		w = expandExternal(w);
		return;
	}
}
node* makeRoot() {
	char c;
	int key;

	scanf("%c %d", &c, &key);
	getchar();

	node* v = (node*)malloc(sizeof(node));
	v = expandExternal(v);
	v->key = key;
	v->parent = NULL;

	return v;
}
node* sibling(node* w) {
	if (w->parent == NULL) return;
	if (w->parent->lChild == w) return w->parent->rChild;
	else return w->parent->lChild;
}
void reduceExternal(node* root, node* z) {
	node* w = z->parent;
	node* zs = sibling(z);

	if (w->parent == NULL) {
		root->lChild = zs->lChild;
		root->rChild = zs->rChild;
		root->lChild->parent = zs;
		root->rChild->parent = zs;
		zs->parent = NULL;
	}
	else {
		node* g = w->parent;
		zs->parent = g;
		if (w == g->lChild) {
			g->lChild = zs;
		}
		else if (w == g->rChild) {
			g->rChild = zs;
		}
	}

	free(z);
	free(w);
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

	if (isExternal(z)) reduceExternal(w, z);
	else {
		node* y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(w, z);
	}

	printf("%d\n", key);
}
void print(node* root) {
	if (isExternal(root)) {
		return;
	}

	printf(" %d", root->key);
	print(root->lChild);
	print(root->rChild);
}
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
			print(root);
			printf("\n");
		}
		else {
			exit(1);
		}
	}
}
