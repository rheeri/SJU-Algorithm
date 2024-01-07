#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main() {
	int n, k, *arr, ans, l, r;

	scanf("%d %d", &n, &k);
	arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

	l = 0, r = n - 1;
	ans = n;
	while (1) {
		if (l > r) {
			ans = l;
			break;
		}

		int mid = (l + r) / 2;
		if (arr[mid] == k) {
			ans = mid;
			break;
		}
		else if (arr[mid] > k) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}

	printf("%d", ans);
}