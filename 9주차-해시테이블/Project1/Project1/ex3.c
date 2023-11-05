#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int M, q, *Table;
void findElem(int key);
void insertItem(int key);
int getNextBucket(int key, int v, int i);
void initBucketArray();
int hash1(int x);
int hash2(int x);
int doubleHashing(int b, int i);
void print();

int main() {
	char c;
	int n, key;
	scanf("%d %d %d", &M, &n, &q);
	getchar();

	Table = (int*)malloc(sizeof(int)*M);
	initBucketArray();

	while (1) {
		scanf("%c", &c);
		getchar();

		if (c == 'i') {
			scanf("%d", &key); getchar();
			insertItem(key);
		}
		else if (c == 's') {
			scanf("%d", &key); getchar();
			findElem(key);
		}
		else if (c == 'p') {
			print();
		}
		else {
			print();
			exit(1);
		}
	}
	return 0;
}
void findElem(int key) {
	int v = hash1(key);
	int i = 0;

	while (i < M) {
		int b = getNextBucket(key, v, i);
		if (Table[b] == 0) {
			printf("-1\n");
			return;
		}
		else if (key == Table[b]) {
			printf("%d %d\n", b, Table[b]);
			return;
		}
		else i += 1;
	}
}
void insertItem(int key) {
	int v = hash1(key);
	int i = 0; 

	int b = getNextBucket(key, v, i);
	if (Table[b] != 0) {
		b = doubleHashing(key, 0);
	}

	Table[b] = key;
	printf("%d\n", b);
	return;
}
int getNextBucket(int key, int v, int i) {
	int hash = hash2(key);
	return (v + i * hash) % M;
}
void initBucketArray() {
	for (int i = 0; i < M; i++) {
		Table[i] = 0;
	}
}
int hash1(int x) {
	return x % M;
}
int hash2(int x) {
	return q - (x % q);
}
int doubleHashing(int b, int i) {
	int h1 = hash1(b);
	int h2 = i * hash2(b);
	int idx = (h1 + h2) % M;

	if (Table[idx] == 0) return idx;
	else {
		printf("C");
		return doubleHashing(b, i + 1);
	}
}
void print() {
	for (int i = 0; i < M; i++) {
		printf(" %d", Table[i]);
	}
	printf("\n");
}