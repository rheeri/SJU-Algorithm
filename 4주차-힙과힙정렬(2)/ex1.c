//������ - ����Ű, �ߺ�Ű ���� �ڵ�
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int H[99];
int n;

void swapElem(int* a, int* b);
void buildHeap();
void downHeap(int i, int last);
void inPlaceHeapSort();
void printHeap();

void main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &H[i]);

	buildHeap();
	inPlaceHeapSort();
	printHeap();
}
void swapElem(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
void buildHeap() {
	for (int i = n / 2; i >= 1; i--) downHeap(i, n);
	return;
}
void downHeap(int i, int last) {
	int left = 2 * i;
	int right = (2 * i) + 1;

	if (left > last) return; //�ܺ� ���

	int bigger = left;
	if (right <= last) {
		if (H[right] > H[bigger]) bigger = right;
	}

	if (H[i] >= H[bigger]) return; //���ĵǾ� ����
	
	swapElem(&H[bigger], &H[i]);
	downHeap(bigger, last);
}
void inPlaceHeapSort() {
	for (int i = n; i >= 2; i--) {
		swapElem(&H[1], &H[i]);
		downHeap(1, i - 1);
	}
	return;
}
void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
	printf("\n");
}