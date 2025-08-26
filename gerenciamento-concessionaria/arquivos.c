#ifndef ARQUIVOS_C
#define ARQUIVOS_C

#include "headers\arquivos.h"
#include "entidades\automoveis.c"
#include "entidades\clientes.c"
#include "entidades\funcionarios.c"

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

void criarBasesOrdenadasGeral (FILE *automoveis, FILE *clientes, FILE *funcionarios, int tamanho){

    int tamanhocliente = tamanho/2;
    int tamanhofunc = tamanho/5;

    criarBaseOrdenadaCarros(automoveis, tamanho);
    criarBaseOrdenadaFuncionario(funcionarios, tamanhofunc);
    criarBaseOrdenadaCliente(clientes, tamanhocliente);

    srand(time(NULL));
    for(int i = 0; i < tamanho; i++){
        int autoaletorio = rand() % tamanho;
        fseek(automoveis, autoaletorio *sizeof(TCarros), SEEK_SET);
        TCarros *carro = leitura_arquivo_carros(automoveis);

        int clientealeatorio = rand() % tamanhocliente;
        fseek(clientes, clientealeatorio*sizeof(TCliente), SEEK_SET);
        TCliente *cliente = leitura_arquivo_cliente(clientes);

        int funcaleatorio = rand() % tamanhofunc;
        fseek(funcionarios, funcaleatorio *sizeof(TFuncionario), SEEK_SET);
        TFuncionario *funcionario = leitura_arquivo_funcionario(funcionarios);

        carro->cliente = *cliente;
        carro->funcionario = *funcionario;
        carro->situacao = (rand() % 2 == 0) ? ALUGADO : VENDIDO;

        fseek(automoveis, autoaletorio *sizeof(TCarros), SEEK_SET);
        salvarAutomoveis(carro, automoveis);

        free(carro);
        free(cliente);
        free(funcionario);
    }
}

void criarBasesEmbaralhadasGeral (FILE *automoveis, FILE *clientes, FILE *funcionarios, int tamanho){

    int tamanhocliente = tamanho/2;
    int tamanhofunc = tamanho/5;

    criarBaseEmbaralhadaCarros(automoveis, tamanho);
    criarBaseEmbaralhadaFuncionario(funcionarios, tamanhofunc);
    criarBaseEmbaralhadaCliente(clientes, tamanhocliente);

    srand(time(NULL));
    for(int i = 0; i < tamanho; i++){
        int autoaletorio = rand() % tamanho;
        fseek(automoveis, autoaletorio *sizeof(TCarros), SEEK_SET);
        TCarros *carro = leitura_arquivo_carros(automoveis);
        
        int clientealeatorio = rand() % tamanhocliente;
        fseek(clientes, clientealeatorio*sizeof(TCliente), SEEK_SET);
        TCliente *cliente = leitura_arquivo_cliente(clientes);

        int funcaleatorio = rand() % tamanhofunc;
        fseek(funcionarios, funcaleatorio *sizeof(TFuncionario), SEEK_SET);
        TFuncionario *funcionario = leitura_arquivo_funcionario(funcionarios);

        carro->cliente = *cliente;
        carro->funcionario = *funcionario;
        carro->situacao = (rand() % 2 == 0) ? ALUGADO : VENDIDO;

        fseek(automoveis, autoaletorio *sizeof(TCarros), SEEK_SET);
        salvarAutomoveis(carro, automoveis);

        free(carro);
        free(cliente);
        free(funcionario);
    }
}

void Salvar_LOG_B(FILE *LOG, int contador, double TEMP_EXECUCAO){
    LOG = fopen("ArquivoLOG.txt", "a");
    
    if(LOG == NULL){
        printf("Nao foi possivel abrir o arquivo");
        return;
    }

    fprintf(LOG, "\n---------- BUSCA BINARIA ----------\n");
    fprintf(LOG, "Número de comparações: %d\n", contador);
    fprintf(LOG, "Tempo de execução da busca: %f\n", TEMP_EXECUCAO);


    fclose(LOG);
}

void Salvar_LOG_S(FILE *LOG, int contador, double TEMP_EXECUCAO){
    LOG = fopen("ArquivoLOG.txt", "a");
    
    if(LOG == NULL){
        printf("Nao foi possivel abrir o arquivo");
        return;
    }

    fprintf(LOG, "\n---------- BUSCA SEQUENCIAL ----------\n");
    fprintf(LOG, "Número de comparações: %d\n", contador);
    fprintf(LOG, "Tempo de execução da busca: %f\n", TEMP_EXECUCAO);


    fclose(LOG);
}

void Salvar_LOG_SS(FILE *LOG, int contador, double TEMP_EXECUCAO){
    LOG = fopen("ArquivoLOG_SelectionSort.txt", "a");

    if(LOG == NULL){
        printf("Nao foi possivel abrir o arquivo");
        return;
    }
    fprintf(LOG, "\n---------- SELECTION SORT ----------\n");
    fprintf(LOG, "Numero de comparações: %d\n", contador);
    fprintf(LOG, "Tempo de execucao da ordenacao: %f\n", TEMP_EXECUCAO);

    fclose(LOG);

}

void Salvar_LOG_Particoes(FILE *LOG, int contador, double TEMP_EXECUCAO){
    LOG = fopen("ArquivoLOG_SelecaoNatural.txt", "a");

    if(LOG == NULL){
        printf("Nao foi possivel abrir o arquivo");
        return;
    }
    fprintf(LOG, "\n---------- SELECAO NATURAL ----------\n");
    fprintf(LOG, "Número de comparações: %d\n", contador);
    fprintf(LOG, "Tempo de execucao da criacao de particoes: %f\n", TEMP_EXECUCAO);

    fclose(LOG);
}

void Salvar_LOG_IntercalacaoOtima(FILE *LOG, int contador, double TEMP_EXECUCAO){
    LOG = fopen("ArquivoLOG_IntercalacaoOtima.txt", "a");

    if(LOG == NULL){
        printf("Nao foi possivel abrir o arquivo");
        return;
    }
    fprintf(LOG, "\n---------- INTERCALACAO OTIMA ----------\n");
    fprintf(LOG, "Número de comparações: %d\n", contador);
    fprintf(LOG, "Tempo de execucao da intercalacao: %f\n", TEMP_EXECUCAO);

    fclose(LOG);
}

#endif
