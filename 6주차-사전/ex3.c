#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main() {
	int a, b, cnt;
	scanf("%d %d %d", &a, &b, &cnt);

	char* str = (char*)malloc(sizeof(char)*(cnt + 1));
	scanf("%s", str);

	for (int i = 0; i < cnt; i++) {
		int m = (a + b) / 2;

		if (str[i] == 'Y') {
			a = m + 1;
		}
		else {
			b = m;
		}
	}
	printf("%d", a);
	free(str);
}