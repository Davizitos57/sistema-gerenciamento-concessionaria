#ifndef INTERCALACAOOTIMA_C
#define INTERCALACAOOTIMA_C

#include "..\headers\intercalacao_otima.h"
#include "..\arquivos.c"
#include "..\entidades\automoveis.c"
#include "..\entidades\clientes.c"
#include "..\entidades\funcionarios.c"

void IntercalacaoOtimaAutomovel(int NP, char *ArquivoFinalOrdenado, FILE *ArquivoLOG_IntecalacaoOtima){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    int contador = 0;
    int F = 3; 

    TEMP_INICIAL = clock();

    FILE **particoes = (FILE **)malloc(NP * sizeof(FILE*)); 
    TCarros ** registros = (TCarros **)malloc(NP * sizeof(TCarros*));

    for(int i = 0; i<NP; i++){
        char nomeParticao[30];
        sprintf(nomeParticao, "ParticaoAutomoveis%d.dat", i+1);
        particoes[i] = fopen(nomeParticao, "r+b");
        if(particoes[i] == NULL){
            printf("Erro ao abrir a particao %d\n", i+1);
            return;
        }
        registros[i] = leitura_arquivo_carros(particoes[i]);
    }

    FILE *ParticaoTotalAutomoveis = fopen("ParticaoTotalAutomoveis.dat", "w+b");
    if(ParticaoTotalAutomoveis == NULL){
        printf("Erro ao criar o arquivo ParticaoTotalAutomoveis.\n");
        return;
    }

    while(NP>0){
        int NPIntercaladas = (NP<F) ? NP : F;

        TCarros **RegistrosIntercalados = (TCarros **)malloc(NPIntercaladas * sizeof(TCarros*));
        FILE **ParticoesIntercaladas = (FILE **)malloc(NPIntercaladas * sizeof(FILE*));

        for(int i = 0; i<NPIntercaladas; i++){
            ParticoesIntercaladas[i] = particoes[i];
            RegistrosIntercalados[i] = registros[i];
        }
        while(true){
            int menor = -1;
            int menorcodigo = INT_MAX; 

            for(int j = 0; j<NPIntercaladas; j++){
                contador++;
                if(RegistrosIntercalados[j] != NULL && RegistrosIntercalados[j]->codigo < menorcodigo){
                    menorcodigo = RegistrosIntercalados[j]->codigo;
                    menor = j;
                }
            }

            if(menor == -1){
                break;
            }

            salvarAutomoveis(RegistrosIntercalados[menor], ParticaoTotalAutomoveis);
            RegistrosIntercalados[menor] = leitura_arquivo_carros(ParticoesIntercaladas[menor]);
        }

        for(int a = 0; a<NPIntercaladas; a++){
            fclose(ParticoesIntercaladas[a]);
            free(RegistrosIntercalados[a]);
        }
        free(RegistrosIntercalados);
        free(ParticoesIntercaladas);

        NP -= NPIntercaladas;

        for(int i = 0; i<NPIntercaladas; i++){
            particoes[i] = particoes[i+NPIntercaladas];
            registros[i] = registros[i+NPIntercaladas];
        }

        fseek(ParticaoTotalAutomoveis, 0, SEEK_SET);
        TCarros **TR = NULL;
        int NTodosRegs = 0;

        TCarros *registro; 
        while((registro = leitura_arquivo_carros(ParticaoTotalAutomoveis))!=NULL){
            TR = (TCarros **)realloc(TR, (NTodosRegs + 1) * sizeof(TCarros*));
            TR[NTodosRegs] = registro;
            NTodosRegs++;
        }

        for(int i = 0; i<NTodosRegs-1; i++){
            for(int j = i+1; j<NTodosRegs; j++){
                if(TR[i]->codigo > TR[j]->codigo){
                    TCarros *temporario = TR[i];
                    TR[i] = TR[j];
                    TR[j] = temporario;
                }
            }
        }

        fseek(ParticaoTotalAutomoveis, 0, SEEK_SET);
        for(int i = 0; i<NTodosRegs; i++){
            salvarAutomoveis(TR[i], ParticaoTotalAutomoveis);
            free(TR[i]);
        }
        free(TR);
    }

    fclose(ParticaoTotalAutomoveis);

    ParticaoTotalAutomoveis = fopen("ParticaoTotalAutomoveis.dat", "r+b");
    if(ParticaoTotalAutomoveis == NULL){
        printf("Erro ao abrir a ParticaoTotalAutomoveis.\n");
        return;
    }

    FILE *ArquivoFinal = fopen(ArquivoFinalOrdenado, "w+b");
    if(ArquivoFinal == NULL){
        printf("Erro ao abrir o Arquivo de Automoveis.dat\n");
        fclose(ParticaoTotalAutomoveis);
        return;
    }

    TCarros *RegFinal;
    while((RegFinal = leitura_arquivo_carros(ParticaoTotalAutomoveis)) != NULL){
        salvarAutomoveis(RegFinal, ArquivoFinal);
        free(RegFinal);
    }

    fclose(ParticaoTotalAutomoveis);
    fclose(ArquivoFinal);

    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL-TEMP_INICIAL)/CLOCKS_PER_SEC;
    Salvar_LOG_IntercalacaoOtima(ArquivoLOG_IntecalacaoOtima, contador, TEMP_EXECUCAO);

    return;
}

void IntercalacaoOtimaCliente(int NP, char *ArquivoFinalOrdenado, FILE *ArquivoLOG_IntecalacaoOtima){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    int contador = 0;
    int F = 3; 

    TEMP_INICIAL = clock();

    FILE **particoes = (FILE **)malloc(NP * sizeof(FILE*)); 
    TCliente ** registros = (TCliente **)malloc(NP * sizeof(TCliente*)); 
    for(int i = 0; i<NP; i++){
        char nomeParticao[30];
        sprintf(nomeParticao, "ParticaoCliente%d.dat", i+1);
        particoes[i] = fopen(nomeParticao, "r+b");
        if(particoes[i] == NULL){
            printf("Erro ao abrir a particao %d\n", i+1);
            return;
        }
        registros[i] = leitura_arquivo_cliente(particoes[i]);
    }

    FILE *ParticaoTotalClientes = fopen("ParticaoTotalClientes.dat", "w+b");
    if(ParticaoTotalClientes == NULL){
        printf("Erro ao criar o arquivo ParticaoTotalClientes.\n");
        return;
    }

    while(NP>0){
        int NPIntercaladas = (NP<F) ? NP : F; 

        TCliente **RegistrosIntercalados = (TCliente **)malloc(NPIntercaladas * sizeof(TCliente*));
        FILE **ParticoesIntercaladas = (FILE **)malloc(NPIntercaladas * sizeof(FILE*));

        for(int i = 0; i<NPIntercaladas; i++){
            ParticoesIntercaladas[i] = particoes[i];
            RegistrosIntercalados[i] = registros[i];
        }

        while(true){
            int menor = -1; 
            int menorcodigo = INT_MAX; 

            for(int j = 0; j<NPIntercaladas; j++){
                contador++;
                if(RegistrosIntercalados[j] != NULL && RegistrosIntercalados[j]->codigo < menorcodigo){
                    menorcodigo = RegistrosIntercalados[j]->codigo;
                    menor = j;
                }
            }

            if(menor == -1){
                break;
            }

            salvarCliente(RegistrosIntercalados[menor], ParticaoTotalClientes);
            RegistrosIntercalados[menor] = leitura_arquivo_cliente(ParticoesIntercaladas[menor]);
        }

        for(int a = 0; a<NPIntercaladas; a++){
            fclose(ParticoesIntercaladas[a]);
            free(RegistrosIntercalados[a]);
        }
        free(RegistrosIntercalados);
        free(ParticoesIntercaladas);

        NP -= NPIntercaladas;

        for(int i = 0; i<NPIntercaladas; i++){
            particoes[i] = particoes[i+NPIntercaladas];
            registros[i] = registros[i+NPIntercaladas];
        }

        fseek(ParticaoTotalClientes, 0, SEEK_SET);
        TCliente **TR = NULL;
        int NTodosRegs = 0;

        TCliente *registro; 
        while((registro = leitura_arquivo_cliente(ParticaoTotalClientes))!=NULL){
            TR = (TCliente **)realloc(TR, (NTodosRegs + 1) * sizeof(TCliente*));
            TR[NTodosRegs] = registro;
            NTodosRegs++;
        }

        for(int i = 0; i<NTodosRegs-1; i++){
            for(int j = i+1; j<NTodosRegs; j++){
                if(TR[i]->codigo > TR[j]->codigo){
                    TCliente *temporario = TR[i];
                    TR[i] = TR[j];
                    TR[j] = temporario;
                }
            }
        }

        fseek(ParticaoTotalClientes, 0, SEEK_SET);
        for(int i = 0; i<NTodosRegs; i++){
            salvarCliente(TR[i], ParticaoTotalClientes);
            free(TR[i]);
        }
        free(TR);
    }

    fclose(ParticaoTotalClientes);

    ParticaoTotalClientes = fopen("ParticaoTotalClientes.dat", "r+b");
    if(ParticaoTotalClientes == NULL){
        printf("Erro ao abrir a ParticaoTotalClientes.\n");
        return;
    }

    FILE *ArquivoFinal = fopen(ArquivoFinalOrdenado, "w+b");
    if(ArquivoFinal == NULL){
        printf("Erro ao abrir o Arquivo de Automoveis.dat\n");
        fclose(ParticaoTotalClientes);
        return;
    }

    TCliente *RegFinal;
    while((RegFinal = leitura_arquivo_cliente(ParticaoTotalClientes)) != NULL){
        salvarCliente(RegFinal, ArquivoFinal);
        free(RegFinal);
    }

    fclose(ParticaoTotalClientes);
    fclose(ArquivoFinal);

    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL-TEMP_INICIAL)/CLOCKS_PER_SEC;
    Salvar_LOG_IntercalacaoOtima(ArquivoLOG_IntecalacaoOtima, contador, TEMP_EXECUCAO);

    return;
}

void IntercalacaoOtimaFuncionario(int NP, char *ArquivoFinalOrdenado, FILE *ArquivoLOG_IntecalacaoOtima){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    int contador = 0;
    int F = 3; 

    TEMP_INICIAL = clock();

    FILE **particoes = (FILE **)malloc(NP * sizeof(FILE*)); 
    TFuncionario ** registros = (TFuncionario **)malloc(NP * sizeof(TFuncionario*)); 

    for(int i = 0; i<NP; i++){
        char nomeParticao[30];
        sprintf(nomeParticao, "ParticaoFuncionario%d.dat", i+1);
        particoes[i] = fopen(nomeParticao, "r+b");
        if(particoes[i] == NULL){
            printf("Erro ao abrir a particao %d\n", i+1);
            return;
        }
        registros[i] = leitura_arquivo_funcionario(particoes[i]);
    }

    FILE *ParticaoTotalFuncionarios = fopen("ParticaoTotalFuncionarios.dat", "w+b");
    if(ParticaoTotalFuncionarios == NULL){
        printf("Erro ao criar o arquivo ParticaoTotalFuncionarios.\n");
        return;
    }

    while(NP>0){
        int NPIntercaladas = (NP<F) ? NP : F; //Define se serao intercaladas o numero F de particoes ou em caso de nao houver o suficiente de F, o numero restante de NP

        TFuncionario **RegistrosIntercalados = (TFuncionario **)malloc(NPIntercaladas * sizeof(TFuncionario*));
        FILE **ParticoesIntercaladas = (FILE **)malloc(NPIntercaladas * sizeof(FILE*));

        for(int i = 0; i<NPIntercaladas; i++){
            ParticoesIntercaladas[i] = particoes[i];
            RegistrosIntercalados[i] = registros[i];
        }
        while(true){
            int menor = -1; 
            int menorcodigo = INT_MAX; 
            for(int j = 0; j<NPIntercaladas; j++){
                contador++;
                if(RegistrosIntercalados[j] != NULL && RegistrosIntercalados[j]->codigo < menorcodigo){
                    menorcodigo = RegistrosIntercalados[j]->codigo;
                    menor = j;
                }
            }

            if(menor == -1){
                break;
            }

            salvarFuncionario(RegistrosIntercalados[menor], ParticaoTotalFuncionarios);
            RegistrosIntercalados[menor] = leitura_arquivo_funcionario(ParticoesIntercaladas[menor]);
        }

        for(int a = 0; a<NPIntercaladas; a++){
            fclose(ParticoesIntercaladas[a]);
            free(RegistrosIntercalados[a]);
        }
        free(RegistrosIntercalados);
        free(ParticoesIntercaladas);

        NP -= NPIntercaladas;

        for(int i = 0; i<NPIntercaladas; i++){
            particoes[i] = particoes[i+NPIntercaladas];
            registros[i] = registros[i+NPIntercaladas];
        }

        fseek(ParticaoTotalFuncionarios, 0, SEEK_SET);
        TFuncionario **TR = NULL;
        int NTodosRegs = 0;

        TFuncionario *registro; 
        while((registro = leitura_arquivo_funcionario(ParticaoTotalFuncionarios))!=NULL){
            TR = (TFuncionario **)realloc(TR, (NTodosRegs + 1) * sizeof(TFuncionario*));
            TR[NTodosRegs] = registro;
            NTodosRegs++;
        }

        for(int i = 0; i<NTodosRegs-1; i++){
            for(int j = i+1; j<NTodosRegs; j++){
                if(TR[i]->codigo > TR[j]->codigo){
                    TFuncionario *temporario = TR[i];
                    TR[i] = TR[j];
                    TR[j] = temporario;
                }
            }
        }

        fseek(ParticaoTotalFuncionarios, 0, SEEK_SET);
        for(int i = 0; i<NTodosRegs; i++){
            salvarFuncionario(TR[i], ParticaoTotalFuncionarios);
            free(TR[i]);
        }
        free(TR);
    }

    fclose(ParticaoTotalFuncionarios);

    ParticaoTotalFuncionarios = fopen("ParticaoTotalFuncionarios.dat", "r+b");
    if(ParticaoTotalFuncionarios == NULL){
        printf("Erro ao abrir a ParticaoTotalFuncionarios.\n");
        return;
    }

    FILE *ArquivoFinal = fopen(ArquivoFinalOrdenado, "w+b");
    if(ArquivoFinal == NULL){
        printf("Erro ao abrir o Arquivo de Automoveis.dat\n");
        fclose(ParticaoTotalFuncionarios);
        return;
    }

    TFuncionario *RegFinal;
    while((RegFinal = leitura_arquivo_funcionario(ParticaoTotalFuncionarios)) != NULL){
        salvarFuncionario(RegFinal, ArquivoFinal);
        free(RegFinal);
    }

    fclose(ParticaoTotalFuncionarios);
    fclose(ArquivoFinal);

    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL-TEMP_INICIAL)/CLOCKS_PER_SEC;
    Salvar_LOG_IntercalacaoOtima(ArquivoLOG_IntecalacaoOtima, contador, TEMP_EXECUCAO);

    return;
}

#endif