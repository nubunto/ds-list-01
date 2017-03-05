#include <stdio.h>
#include <stdlib.h>

void switcher(int *a, int *b, int *c) {
	int largest = *a;
	if (largest < *b) {
		largest = *b;
	}
	if (largest < *c) {
		largest = *c;
	}
	int min = *a;
	if (min > *b) {
		min = *b;
	}
	if (min > *c) {
		min = *c;
	}
	int middle = 0;
	if (*a < largest && *a > min) {
		middle = *a;
	} else if (*b < largest && *b > min) {
		middle = *b;
	} else if (*c < largest && *b > min) {
		middle = *b;
	}
	*a = largest;
	*b = middle;
	*c = min;
}

int main() {
	int *a, *b, *c;
	a = malloc(sizeof(int));
	b = malloc(sizeof(int));
	c = malloc(sizeof(int));
	printf("Digite A: ");
	scanf("%d", a);
	printf("Digite B: ");
	scanf("%d", b);
	printf("Digite C: ");
	scanf("%d", c);
	switcher(a, b, c);
	printf("A: %d  B: %d  C: %d\n", *a, *b, *c);
}
