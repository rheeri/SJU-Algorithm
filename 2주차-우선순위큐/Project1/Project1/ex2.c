#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int* inPlaceInsertionSort(int* arr, int n);
void print(int* arr, int n);

int main() {
	int n;
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

	arr = inPlaceInsertionSort(arr, n);
	print(arr, n);
	free(arr);
	return 0;
}

int* inPlaceInsertionSort(int* arr, int n) {
	for (int i = 1; i < n; i++) {
		int now = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > now) {
			arr[j + 1] = arr[j];
			j -= 1;
		}
		arr[j + 1] = now;
	}
	return arr;
}
void print(int* arr, int n) {
	for (int i = 0; i < n; i++) printf(" %d", arr[i]);
	printf("\n");
	return;
}