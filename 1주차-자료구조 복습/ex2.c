#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	int id;
	struct node* left;
	struct node* right;
}node;

node* getNode(int id) {
	node* p = (node*)malloc(sizeof(node));
	p->id = id;
	p->left = NULL;
	p->right = NULL;
}
void findID(node* root, int id, node** p) {
	if (root->id == id) *p = root;

	if (root->left != NULL) findID(root->left, id, p);
	if (root->right != NULL) findID(root->right, id, p);
}
node* treeBuild(int n) {
	int flag = 1, x, y, z;
	node* root = NULL;

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &x, &y, &z);

		if (flag == 1) {
			root = getNode(x);
			if (y != 0) {
				root->left = getNode(y);
			}
			if (z != 0) {
				root->right = getNode(z);
			}
			flag = 0;
		}

		else {
			node* p;
			findID(root, x, &p);

			if (y != 0) {
				p->left = getNode(y);
			}
			if (z != 0) {
				p->right = getNode(z);
			}
		}
	}

	return root;
}
void preOrder(node* root) {
	printf(" %d", root->id);

	if (root->left != NULL) preOrder(root->left);
	if (root->right != NULL) preOrder(root->right);
}
int main() {
	int n;
	char cmmd[100];
	scanf("%d", &n);

	node* root = treeBuild(n);


	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", cmmd);
		node* p = root;

		printf(" %d", p->id);
		for (int j = 0; j < strlen(cmmd); j++) {
			if (cmmd[j] == 'R') {
				p = p->right;
				printf(" %d", p->id);
			}
			else {
				p = p->left;
				printf(" %d", p->id);
			}
		}
		printf("\n");
	}
	return 0;
}