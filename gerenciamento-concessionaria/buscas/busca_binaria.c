#ifndef BUSCABINARIA_C
#define BUSCABINARIA_C

#include "..\headers\busca_binaria.h"
#include "..\entidades\automoveis.c"
#include "..\entidades\clientes.c"
#include "..\entidades\funcionarios.c"
#include "..\arquivos.c"


//Função para realizar uma busca binária em funcionários
TFuncionario *BuscaBinariaFunc(int chave, FILE *arquivo, FILE *ArquivoLOGBinario) {

    system("cls");

    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TFuncionario *procurado = NULL;
    int inicio = 0;
    int fim = tamanho_arquivo_funcionarios(arquivo) - 1;
    int contador = 0;

    bool flag = false;

    TEMP_INICIAL = clock(); 

    rewind(arquivo); 

    while (inicio <= fim) {
        contador++;

        int meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TFuncionario), SEEK_SET); 
        procurado = leitura_arquivo_funcionario(arquivo); 

        if (procurado->codigo == chave) { 
            flag = true;
            break;
        } else if (procurado->codigo < chave) { 
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    TEMP_FINAL = clock(); //Marca o tempo final
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INICIAL) / CLOCKS_PER_SEC;

    //Salva o log da busca binária
    Salvar_LOG_B(ArquivoLOGBinario, contador, TEMP_EXECUCAO);

    if (flag) {
        imprimefuncionario(procurado);
        return procurado;
    } else {
        printf("\nFuncionario nao foi encontrado, tem certeza que o codigo %d existe?\n", chave);
        free(procurado);
        return NULL;
    }
}

//Função para realizar busca binária em automoveis
TCarros *BuscaBinariaCarro(int chave, FILE *arquivo, FILE *ArquivoLOGBinario) {

    system("cls");
    
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TCarros *procurado = NULL;
    int inicio = 0;
    int fim = tamanho_arquivo_automovel(arquivo) - 1;
    int contador = 0;

    bool flag = false;

    TEMP_INICIAL = clock(); 

    rewind(arquivo); 

    while (inicio <= fim) {
        contador++;

        int meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TCarros), SEEK_SET); 
        procurado = leitura_arquivo_carros(arquivo); 

        if (procurado->codigo == chave) { 
            flag = true;
            break;
        } else if (procurado->codigo < chave) { 
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    TEMP_FINAL = clock(); //Marca o tempo final
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INICIAL) / CLOCKS_PER_SEC;

    //Salva o log da busca binaria
    Salvar_LOG_B(ArquivoLOGBinario, contador, TEMP_EXECUCAO);

    if (flag) {
        imprimirCarro(procurado);
        return procurado;
    } else {
        printf("\nAutomovel nao foi encontrado, tem certeza que o codigo %d existe?\n", chave);
        free(procurado);
        return NULL;
    }
}

//Função para realizar busca binária em clientes
TCliente *BuscaBinariaCliente(int chave, FILE *arquivo, FILE *ArquivoLOGBinario) {

    system("cls");
    
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TCliente *procurado = NULL;
    int inicio = 0;
    int fim = tamanho_arquivo_clientes(arquivo) - 1;
    int contador = 0;

    bool flag = false;

    TEMP_INICIAL = clock(); 

    rewind(arquivo); 

    while (inicio <= fim) {
        contador++;

        int meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(TCliente), SEEK_SET); 
        procurado = leitura_arquivo_cliente(arquivo); 

        if (procurado->codigo == chave) { 
            flag = true;
            break;
        } else if (procurado->codigo < chave) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    TEMP_FINAL = clock(); 
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INICIAL) / CLOCKS_PER_SEC;

    //Salva o log da busca binaria
    Salvar_LOG_B(ArquivoLOGBinario, contador, TEMP_EXECUCAO);

    if (flag) {
        imprimecliente(procurado);
        return procurado;
    } else {
        printf("\nCliente nao foi encontrado, tem certeza que o codigo %d existe?\n", chave);
        free(procurado);
        return NULL;
    }
}
#endif