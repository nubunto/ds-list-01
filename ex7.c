#include <stdio.h>
#include <stdlib.h>

int read_grades(float*, int);
float calculate_avg(float*, int);

int main() {
    int count = 5;
    float *grades = malloc(count * sizeof(float));
    read_grades(grades, count);
    float avg = calculate_avg(grades, count);
    printf("Media das notas: %2.f\n", avg);
}

int read_grades(float *grades, int size) {
    for (int i = 0; i < size; i++) {
        float grade = 0;
        printf("Digite a nota #%d: ", i + 1);
        scanf("%f", &grade);
        grades[i] = grade;
    }
}

float calculate_avg(float *grades, int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += grades[i];
    }
    return sum / size;
}