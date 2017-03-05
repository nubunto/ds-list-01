#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int read_array_size();
int fill_array(int*, int);
int show_array(int*, int);
int already_exists(int*, int, int);

int main() {
    int size = read_array_size();
    int *array = malloc(size * sizeof(int));
    fill_array(array, size);
    show_array(array, size);
}

int read_array_size() {
    srand((unsigned)time(NULL));

    int size = 0;
    printf("Digite o tamanho do array: ");
    scanf("%d", &size);
    return size;
}

int fill_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        int n = rand() % RAND_MAX;
        while(already_exists(array, size, n)) {
            n = rand() % RAND_MAX;
        }
        array[i] = n;
    }
}

int show_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int already_exists(int *array, int size, int n) {
    for (int i = 0; i < size; i++) {
        if (array[i] == n) {
            return 1;
        }
    }
    return 0;
}