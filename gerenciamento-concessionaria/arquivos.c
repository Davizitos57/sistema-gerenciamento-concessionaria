#include "headers\assinaturas_gerais.h"
#include "headers\assinaturas_clientes.h"
#include "headers\assinaturas_funcionarios.h"
#include "headers\assinaturas_automoveis.h"

void abre_arquivos(FILE **automoveis, FILE **clientes, FILE **funcionarios){
    *automoveis = fopen("Automoveis.dat", "w+b");
    fclose(*automoveis);
    *automoveis = fopen("Automoveis.dat", "r+b");

    *clientes = fopen("Clientes.dat", "w+b");
    fclose(*clientes);
    *clientes = fopen("Clientes.dat", "r+b");

    *funcionarios = fopen("Funcionarios.dat", "w+b");
    fclose(*funcionarios);
    *funcionarios = fopen("Funcionarios.dat", "r+b");

    if(*automoveis == NULL || *clientes == NULL || *funcionarios == NULL){
        printf("Erro ao abrir um dos arquivos!\n");
        exit(1);
    }
}

bool arquivos_vazios(FILE *automoveis, FILE *clientes, FILE *funcionarios){
    fseek(automoveis, 0, SEEK_END);
    fseek(clientes, 0, SEEK_END);
    fseek(funcionarios, 0, SEEK_END);

    long tamanho_automoveis = ftell(automoveis);
    long tamanho_clientes = ftell(clientes);
    long tamanho_funcionarios = ftell(funcionarios);

    rewind(automoveis);
    rewind(clientes);
    rewind(funcionarios);

    return tamanho_automoveis == 0 && tamanho_clientes == 0 && tamanho_funcionarios == 0;
}

void embralhabases(int *vet, int TAM) {
    srand(time(NULL));
    for (int i = TAM - 1; i > 0; i--) {
        int j = rand() % (i+1);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}