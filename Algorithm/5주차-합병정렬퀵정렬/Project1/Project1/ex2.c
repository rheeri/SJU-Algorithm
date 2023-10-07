#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

int findPivot(int* L, int l, int r);
void swapElem(int* a, int* b);
void inPlacePartition(int* L, int l, int r, int k, int* pivot);
void inPlaceQuickSort(int* L, int l, int r);
void print(int* L, int n);

int main() {
	srand(time(NULL));

	int n, *L;
	scanf("%d", &n);

	L = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) scanf("%d", &L[i]);

	inPlaceQuickSort(L, 0, n - 1);
	print(L, n);

	free(L);
}
int findPivot(int* L, int l, int r) {
	int pivot = l + rand() % (r - l + 1);

	return pivot;
}
void swapElem(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void inPlacePartition(int* L, int l, int r, int k, int* result) {
	int pivot, i, j;

	pivot = L[k];
	swapElem(&L[k], &L[r]);
	i = l, j = r - 1;

	while (i <= j) {
		while (i <= j && L[i] <= pivot) {
			i += 1;
		}
		while (j >= i && L[j] >= pivot) {
			j -= 1;
		}
		if (i < j) {
			swapElem(&L[i], &L[j]);
		}
	}
	swapElem(&L[i], &L[r]);
	result[0] = j;
	result[1] = i;
}
void inPlaceQuickSort(int* L, int l, int r) {
	if (l >= r) return;

	int k = findPivot(L, l, r);
	int pivot[2];

	inPlacePartition(L, l, r, k, &pivot);
	inPlaceQuickSort(L, l, pivot[0]);
	inPlaceQuickSort(L, pivot[1], r);
}
void print(int* L, int n) {
	for (int i = 0; i < n; i++) printf(" %d", L[i]);
	printf("\n");
}