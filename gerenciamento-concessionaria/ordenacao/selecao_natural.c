#ifndef SELECAONATURAL_C
#define SELECAONATURAL_C

#include "..\cabecalho\selecao_natural.h"
#include "..\arquivos.c"
#include "..\entidades\automoveis.c"
#include "..\entidades\clientes.c"
#include "..\entidades\funcionarios.c"

int SelecaoNaturalAutomoveis(FILE *Arquivo, int TAMPART, FILE *ArquivoLOGSN){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TEMP_INICIAL = clock(); 

    int contador = 0;
    int reg = 0; 
    int TamArq = tamanho_arquivo_automovel(Arquivo); 
    int NP = 0; 
    TCarros *registro[TAMPART]; 
    char nomeParticao[30];

    TCarros *anterior = NULL; 

    rewind(Arquivo);

    FILE *Reservatorio;
    if ((Reservatorio = fopen("ReservatorioAutomoveis.dat", "w+b")) == NULL) {
        printf("Erro ao criar arquivo de saída do reservatório\n");
        return -1;
    }

    printf("\nGerando particoes...\n\n");
    for (int i = 0; i < TAMPART; i++) {
        registro[i] = leitura_arquivo_carros(Arquivo);
        if (registro[i] == NULL) {
            reg++;
        }
    }
    do {
        sprintf(nomeParticao, "ParticaoAutomoveis%d.dat", NP + 1);

        printf("Criando a particao %d...\n", NP+1);

        FILE *Particao;
        if ((Particao = fopen(nomeParticao, "w+b")) == NULL) {
            printf("Erro ao criar arquivo de saída");
            return -1; 
        }

        while (tamanho_arquivo_automovel(Reservatorio) < TAMPART && reg < TamArq) {            
            TCarros *menorescolhido = NULL;
            int posicaoMenor = -1;

            for (int k = 0; k < TAMPART; k++) {
                if (registro[k] != NULL) {
                    contador++; 
                    if (menorescolhido == NULL || registro[k]->codigo < menorescolhido->codigo) {
                        menorescolhido = registro[k];
                        posicaoMenor = k;
                    }
                }
            }
            
            if(menorescolhido == NULL){
                break;
            }
            
            anterior = menorescolhido;
            salvarAutomoveis(menorescolhido, Particao);

            TCarros *Proximoverificado = leitura_arquivo_carros(Arquivo);
            
            if (Proximoverificado == NULL) {
                registro[posicaoMenor] = NULL;
            } 
            else if (Proximoverificado->codigo < anterior->codigo) {
                salvarAutomoveis(Proximoverificado, Reservatorio);
                registro[posicaoMenor] = NULL;
            } 
            else {
                registro[posicaoMenor] = Proximoverificado;
                reg++;
            }
        }

        fclose(Particao);

        if (tamanho_arquivo_automovel(Reservatorio) == 0) {
            printf("\nReservatorio esta vazio, encerrando o loop...\n");
            break;
        }

        rewind(Reservatorio);
        for (int j = 0; j < TAMPART; j++) {
            registro[j] = leitura_arquivo_carros(Reservatorio);
        }

        fclose(Reservatorio);
        Reservatorio = fopen("ReservatorioAutomoveis.dat", "w+b");
        NP++;
    } 
    while (reg < TamArq || tamanho_arquivo_automovel(Reservatorio));

    fclose(Reservatorio);

    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INICIAL) / CLOCKS_PER_SEC;
    Salvar_LOG_Particoes(ArquivoLOGSN, contador, TEMP_EXECUCAO);

    return NP;
}

int SelecaoNaturalCliente(FILE *Arquivo, int TAMPART, FILE *ArquivoLOGSN){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TEMP_INICIAL = clock();

    int contador = 0;
    int reg = 0; 
    int TamArq = tamanho_arquivo_clientes(Arquivo);
    int NP = 0; 
    TCliente *registro[TAMPART]; 
    char nomeParticao[30];

    TCliente *anterior = NULL; 

    rewind(Arquivo);

    FILE *Reservatorio;
    if ((Reservatorio = fopen("ReservatorioCliente.dat", "w+b")) == NULL) {
        printf("Erro ao criar arquivo de saída do reservatório\n");
        return -1;
    }

    printf("\nGerando particoes...\n\n");
    for (int i = 0; i < TAMPART; i++) {
        registro[i] = leitura_arquivo_cliente(Arquivo);
        if (registro[i] == NULL) {
            reg++;
        }
    }
    do {
        sprintf(nomeParticao, "ParticaoCliente%d.dat", NP + 1);

        printf("Criando a particao %d...\n", NP+1);

        FILE *Particao;
        if ((Particao = fopen(nomeParticao, "w+b")) == NULL) {
            printf("Erro ao criar arquivo de saída");
            return -1; 
        }

        while (tamanho_arquivo_clientes(Reservatorio) < TAMPART && reg < TamArq) {
            TCliente *menorescolhido = NULL;
            int posicaoMenor = -1;

            for (int k = 0; k < TAMPART; k++) {
                if (registro[k] != NULL) {
                    contador++;
                    if (menorescolhido == NULL || registro[k]->codigo < menorescolhido->codigo) {
                        menorescolhido = registro[k];
                        posicaoMenor = k;
                    }
                }
            }
            
            if(menorescolhido == NULL){
                break;
            }
            
            anterior = menorescolhido;
            salvarCliente(menorescolhido, Particao);

            TCliente *Proximoverificado = leitura_arquivo_cliente(Arquivo);

            if (Proximoverificado == NULL) {
                registro[posicaoMenor] = NULL;    
            } 

            else if (Proximoverificado->codigo < anterior->codigo) {
                salvarCliente(Proximoverificado, Reservatorio);
                registro[posicaoMenor] = NULL;
            } 

            else {
                registro[posicaoMenor] = Proximoverificado;
                reg++;
            }
        }

        fclose(Particao);

        if (tamanho_arquivo_clientes(Reservatorio) == 0) {
            printf("\nReservatorio esta vazio, encerrando o loop...\n");
            break;
        }

        rewind(Reservatorio);
        for (int j = 0; j < TAMPART; j++) {
            registro[j] = leitura_arquivo_cliente(Reservatorio);
        }

        fclose(Reservatorio);
        Reservatorio = fopen("ReservatorioCliente.dat", "w+b");
        NP++;
    } 
    while (reg < TamArq || tamanho_arquivo_clientes(Reservatorio));

    fclose(Reservatorio);

    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INICIAL) / CLOCKS_PER_SEC;
    Salvar_LOG_Particoes(ArquivoLOGSN, contador, TEMP_EXECUCAO);

    return NP;
}

int SelecaoNaturalFuncionario(FILE *Arquivo, int TAMPART, FILE *ArquivoLOGSN){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TEMP_INICIAL = clock();

    int contador = 0;
    int reg = 0; 
    int TamArq = tamanho_arquivo_funcionarios(Arquivo); 
    int NP = 0; 
    TFuncionario *registro[TAMPART]; 
    char nomeParticao[30];

    TFuncionario *anterior = NULL; 

    rewind(Arquivo);

    FILE *Reservatorio;
    if ((Reservatorio = fopen("ReservatorioFuncionario.dat", "w+b")) == NULL) {
        printf("Erro ao criar arquivo de saída do reservatório\n");
        return -1;
    }

    printf("\nGerando particoes...\n\n");
    for (int i = 0; i < TAMPART; i++) {
        registro[i] = leitura_arquivo_funcionario(Arquivo);
        if (registro[i] == NULL) {
            reg++;
        }
    }
    do {
        sprintf(nomeParticao, "ParticaoFuncionario%d.dat", NP + 1);

        printf("Criando a particao %d...\n", NP+1);

        FILE *Particao;
        if ((Particao = fopen(nomeParticao, "w+b")) == NULL) {
            printf("Erro ao criar arquivo de saída");
            return -1; 
        }

        while (tamanho_arquivo_funcionarios(Reservatorio) < TAMPART && reg < TamArq) {
            TFuncionario *menorescolhido = NULL;
            int posicaoMenor = -1;

            for (int k = 0; k < TAMPART; k++) {
                if (registro[k] != NULL) {
                    contador++;
                    if (menorescolhido == NULL || registro[k]->codigo < menorescolhido->codigo) {
                        menorescolhido = registro[k];
                        posicaoMenor = k;
                    }
                }
            }
            
            if(menorescolhido == NULL){
                break;
            }

            anterior = menorescolhido;
            salvarFuncionario(menorescolhido, Particao);

            TFuncionario *Proximoverificado = leitura_arquivo_funcionario(Arquivo);

            if (Proximoverificado == NULL) {
                registro[posicaoMenor] = NULL;
            } 
            else if (Proximoverificado->codigo < anterior->codigo) {
                salvarFuncionario(Proximoverificado, Reservatorio);
                registro[posicaoMenor] = NULL;
            } 
            else {
                registro[posicaoMenor] = Proximoverificado;
                reg++;
            }
        }

        fclose(Particao);

        if (tamanho_arquivo_funcionarios(Reservatorio) == 0) {
            printf("\nReservatorio esta vazio, encerrando o loop...\n");
            break;
        }
        
        rewind(Reservatorio);
        for (int j = 0; j < TAMPART; j++) {
            registro[j] = leitura_arquivo_funcionario(Reservatorio);
        }

        fclose(Reservatorio);
        Reservatorio = fopen("ReservatorioFuncionario.dat", "w+b");
        NP++;
    } 
    while (reg < TamArq || tamanho_arquivo_funcionarios(Reservatorio));

    fclose(Reservatorio);

    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INICIAL) / CLOCKS_PER_SEC;
    Salvar_LOG_Particoes(ArquivoLOGSN, contador, TEMP_EXECUCAO);

    return NP;
}

#endif