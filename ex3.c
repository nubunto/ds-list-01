#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Worker {
    char name[256];
    int code;
    float total_sales;
    float salary;
    float bonification;
} Worker;

int read_collaborators(Worker* workers, int size);
int print_workers(Worker* workers, int size);
int Worker_print(Worker);

int main() {
    printf("Entre com o número total de colaboradores: ");
    int total_collaborators = 0;
    scanf("%d", &total_collaborators);

    Worker* collaborators = malloc(total_collaborators * sizeof(Worker));
    read_collaborators(collaborators, total_collaborators);
    print_workers(collaborators, total_collaborators);
}

int read_collaborators(Worker* collaborators, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        Worker w;

        char name[256];
        printf("Digite o nome do colaborador #%d: ", (i + 1));
        scanf("%s", name);
        strcpy(w.name, name);

        int code = 0;
        printf("Digite o codigo do colaborador %s: ", name);
        scanf("%d", &code);
        w.code = code;

        float total_sales = 0;
        printf("Digite o valor total de vendas do colaborador %s: ", name);
        scanf("%f", &total_sales);
        w.total_sales = total_sales;

        float salary = 0;
        printf("Digite o salário do colaborador %s: ", name);
        scanf("%f", &salary);
        w.salary = salary;

        float bonification = 0;
        if (total_sales >= 500 && total_sales < 1000) {
            bonification = 0.05;
        }
        if (total_sales >= 1000 && total_sales < 1500) {
            bonification = 0.10;
        }
        if (total_sales >= 1500) {
            bonification = 0.15;
        }
        w.bonification = salary * bonification;

        collaborators[i] = w;
    }
}

int print_workers(Worker* collaborators, int size) {
    int i = 0;
    for(i = 0; i < size; i++) {
        Worker_print(collaborators[i]);
    }
}

int Worker_print(Worker w) {
    printf("Collaborator %s\n", w.name);
    printf("code: %d\n", w.code);
    printf("total sales: %.2f\n", w.total_sales);
    printf("salary: %.2f\n", w.salary);
    printf("bonification: %.2f\n\n", w.bonification);

}