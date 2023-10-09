//삽입식 힙 생성
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int H[99];
int n = 0;

void insertItem(int key);
int parent(int i);
void swapElem(int* a, int* b);
void upHeap(int i);
void downHeap(int i, int last);
int removeMax();
void printHeap();

int main() {
	char cmmd;
	int key;

	while (1) {
		scanf("%c", &cmmd);
		getchar();

		if (cmmd == 'i') {
			scanf("%d", &key);
			insertItem(key);
			printf("0\n");
			getchar();
		}
		else if (cmmd == 'd') {
			printf("%d\n", removeMax());
		}
		else if (cmmd == 'p') {
			printHeap();
		}
		else {
			exit(0);
		}
	}
}

void insertItem(int key) {
	n += 1;
	H[n] = key;
	upHeap(n);
	return;
}
int parent(int i) {
	return i / 2;
}
void swapElem(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
void upHeap(int i) {
	if (i == 1) return; //루트노드
	if (H[parent(i)] > H[i]) return; //정렬되어 있는 경우

	swapElem(&H[i], &H[parent(i)]);
	upHeap(parent(i));
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

	swapElem(&H[i], &H[bigger]);
	downHeap(bigger, last);
}
int removeMax() {
	int root = H[1];
	H[1] = H[n];
	n -= 1; //루트에 저장된 키 삭제

	downHeap(1, n);
	return root;
}
void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
	printf("\n");
	return;
}