#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void rFE(int* arr, int k, int l, int r);

int main() {
	int n, k, *arr;

	scanf("%d %d", &n, &k);
	arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	rFE(arr, k, 0, n-1);

	
	free(arr);
}

void rFE(int* arr, int k, int l, int r) {
	if (arr[r] < k) {
		printf("%d", r); return;
	}
	if (arr[l] > k) {
		printf("%d", l-1); return;
	}

	int mid = (l + r) / 2;
	if (arr[mid] == k) {
		printf("%d\n", mid);
		return;
	}
	else if (arr[mid] > k) rFE(arr, k, l, mid - 1);
	else rFE(arr, k, mid + 1, r);
}