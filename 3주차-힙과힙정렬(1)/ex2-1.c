//재귀적으로 상향식 힙 생성
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int H[99];
int n = 0;

void swapElem(int* a, int* b);
void downHeap(int i, int last);
void rBuildHeap(int i);
void printHeap();

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}
	rBuildHeap(1);
	printHeap();
	return 0;
}
void swapElem(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
void downHeap(int i, int last) {
	int left = 2 * i;
	int right = (2 * i) + 1;

	if (left > last) return; //외부 노드

	int bigger = left;
	if (right <= last) {
		if (H[right] > H[bigger]) bigger = right;
	}

	if (H[i] >= H[bigger]) return; //정렬되어 있는 경우
	swapElem(&H[bigger], &H[i]);
	downHeap(bigger, last);
}
void rBuildHeap(int i) {
	if (i > n) return; //외부 노드

	int left = 2 * i;
	int right = (2 * i) + 1;

	rBuildHeap(left);
	rBuildHeap(right);
	downHeap(i, n);
}
void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
	printf("\n");
	return;
}