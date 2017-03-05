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
	printf("largest: %d\n", largest);

	int min = *a;
	if (min > *b) {
		min = *b;
	}
	if (min > *c) {
		min = *c;
	}
	printf("min: %d\n", min);
	int middle = 0;
	if (*a < largest && *a > min) {
		middle = *a;
	} else if (*b < largest && *b > min) {
		middle = *b;
	} else if (*c < largest && *b > min) {
		middle = *b;
	}
	printf("middle: %d\n", middle);
	*a = largest;
	*b = middle;
	*c = min;
}

int main() {
	int *a, *b, *c;
	a = malloc(sizeof(int));
	b = malloc(sizeof(int));
	c = malloc(sizeof(int));
	*a = 5;
	*b = 21;
	*c = -4;
	switcher(a, b, c);
	printf("A: %d  B: %d  C: %d\n", *a, *b, *c);
}
