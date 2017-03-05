#include <stdio.h>
#include <stdlib.h>

void LeVetor(int* vec, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("Digite um numero (faltam %d): ", (5 - i));
        int v = 0;
        scanf("%d", &v);
        vec[i] = v;
    }
}

void EscreveVetor(int* vec, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

void MultiplicaVetor(int* orig_vec, int* new_vec, int count) {
    printf("Digite um multiplicador: ");
    int m = 0;
    scanf("%d", &m);

    int i = 0;
    for (i = 0; i < count; i++) {
        new_vec[i] = orig_vec[i] * m;
    }
}

int main() {
    int count = 5;
    int* orig = malloc(count * sizeof(int));
    int* multiplied = malloc(count * sizeof(int));

    LeVetor(orig, count);
    MultiplicaVetor(orig, multiplied, count);
    EscreveVetor(orig, count);
    EscreveVetor(multiplied, count);
}