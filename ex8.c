#include <stdio.h>
#include <stdlib.h>

int read_array_size();
int read_array_values(int*, int);
int read_value_to_search();
int find_in(int*, int, int);

int main() {
    int size = read_array_size();    
    int *array = malloc(size * sizeof(int));
    read_array_values(array, size);
    int value_to_search = read_value_to_search();
    int found = find_in(array, size, value_to_search);
    if (found == 1) {
        printf("Valor %d foi encontrado no array\n", value_to_search);
    } else {
        printf("Valor %d nao foi encontrado no array\n", value_to_search);
    }
}

int read_array_size() {
    int size = 0;
    printf("Digite o tamanho do array: ");
    scanf("%d", &size);
    return size;
}

int read_array_values(int *array, int size) {
    for (int i = 0; i < size; i++) {
        int value = 0;
        printf("Digite o numero #%d: ", i + 1);
        scanf("%d", &value);
        array[i] = value;
    }
}

int read_value_to_search() {
    int value = 0;
    printf("Digite o numero a ser pesquisado: ");
    scanf("%d", &value);
    return value;
}

int find_in(int *array, int size, int value_to_search) {
    for (int i = 0; i < size; i++) {
        if (array[i] == value_to_search) {
            return 1;
        }
    }
    return 0;
}