#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
    char name[256];
    char cpf[12];
    int account;
    float amount;
} Client;

int Clients_read(Client*, int);
int Client_print(Client);
int Clients_print(Client*, int);
int find_negative_clients(Client*, int, Client*, int*);

int main() {
    printf("Digite o número de clientes do seu banco: ");
    int number_of_clients = 0;
    scanf("%d", &number_of_clients);
    Client *clients = malloc(number_of_clients * sizeof(Client));

    Clients_read(clients, number_of_clients);
    printf("\nClientes do seu banco: \n\n");
    Clients_print(clients, number_of_clients);

    Client *negative_clients = malloc(number_of_clients * sizeof(Client));
    int number_of_negative_clients = 0;
    find_negative_clients(clients, number_of_clients, negative_clients, &number_of_negative_clients);

    printf("Clientes negativados: \n\n");
    Clients_print(negative_clients, number_of_negative_clients);
}

int Clients_read(Client *clients, int size) {
    for(int i = 0; i < size; i++) {
        char name[256];
        printf("Digite o nome do cliente #%d: ", i + 1);
        scanf("%s", name);

        char cpf[12];
        printf("Digite o número do CPF do cliente %s: ", name);
        scanf("%s", cpf);

        int account = 0;
        printf("Digite o número da conta do cliente %s: ", name);
        scanf("%d", &account);

        float amount = 0;
        printf("Digite a quantia de dinheiro que o cliente %s tem em sua conta: ", name);
        scanf("%f", &amount);

        Client c = {.account = account, .amount = amount};
        strcpy(c.name, name);
        strcpy(c.cpf, cpf);
        clients[i] = c;
    }
}

int Client_print(Client c) {
    printf("Name: %s\n", c.name);
    printf("CPF: %s\n", c.cpf);
    printf("Account: %d\n", c.account);
    printf("Amount: %.2f\n\n", c.amount);
}

int Clients_print(Client *clients, int size) {
    for (int i = 0; i < size; i++) {
        Client_print(clients[i]);
    }
}

int find_negative_clients(Client *clients, int clients_size, Client *negative_clients, int *negative_clients_size) {
    int negative_clients_count = 0;
    for (int i = 0; i < clients_size; i++) {
        Client c = clients[i];
        if (c.amount < 0) {
            negative_clients[negative_clients_count++] = c;
        }
    }
    *negative_clients_size = negative_clients_count;
}