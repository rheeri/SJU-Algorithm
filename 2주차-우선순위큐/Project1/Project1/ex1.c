//제자리 선택정렬
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void swapElem(int* a, int* b);
int* inPlaceSelectionSort(int* arr, int n);
void print(int* arr, int n);

int main() {
	int n, *arr;
	
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

	arr = inPlaceSelectionSort(arr, n);
	print(arr, n);
	free(arr);
}

void swapElem(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
int* inPlaceSelectionSort(int* arr, int n) {
	for (int i = n - 1; i > 0; i--) {
		int max = i;

		for (int j = i - 1; j >= 0; j--) {
			if (arr[j] > arr[max]) max = j;
		}
		swapElem(&arr[i], &arr[max]);
	}
	return arr;
}
void print(int* arr, int n) {
	for (int i = 0; i < n; i++) printf(" %d", arr[i]);
	printf("\n");
}