#ifndef SELECTIONSORT_C
#define SELECTIONSORT_C

#include "..\headers\selection_sort.h"
#include "..\arquivos.c"
#include "..\entidades\automoveis.c"
#include "..\entidades\clientes.c"
#include "..\entidades\funcionarios.c"

void Selection_Sort_Automoveis_Disco(FILE *out, FILE *ArquivoLogSS){
    clock_t clock(void);
    double temporizador_INICIAL, temporizador_FINAL;
    double tempo_execucao;

    int contador = 0;
    int tamanho = tamanho_arquivo_automovel(out); 

    temporizador_INICIAL = clock();
    
    int i, j, min;
    
    rewind(out); 
    for(i = 1; i<tamanho; i++){
        min = i;
        fseek(out, (i-1)*sizeof(TCarros), SEEK_SET); 
        TCarros *carromin = leitura_arquivo_carros(out); 

        for(j = i+1; j<=tamanho; j++){ 
            fseek(out, (j-1)*sizeof(TCarros), SEEK_SET); 
            TCarros *carroJ = leitura_arquivo_carros(out);

            if(carroJ->codigo < carromin->codigo){
                min = j; 
                free(carromin); 
                carromin = carroJ; 
            }
            else{
                free(carroJ);
            }
            contador++;
        }

        if(min != i){ 
            fseek(out, (i-1)*sizeof(TCarros), SEEK_SET); 
            TCarros *carroI = leitura_arquivo_carros(out); 

            fseek(out, (i-1)*sizeof(TCarros), SEEK_SET); 
            salvarAutomoveis(carromin, out); 

            fseek(out, (min-1)*sizeof(TCarros), SEEK_SET); 
            salvarAutomoveis(carroI, out);

            free(carroI);
        }
        
        free(carromin);

    }
    fflush(out); 

    temporizador_FINAL = clock();
    tempo_execucao = (temporizador_FINAL - temporizador_INICIAL) / CLOCKS_PER_SEC;
    Salvar_LOG_SS(ArquivoLogSS, contador, tempo_execucao);
}

void Selection_Sort_Clientes_Disco(FILE *out, FILE *ArquivoLogSS){
    clock_t clock(void);
    double temporizador_INICIAL, temporizador_FINAL;
    double tempo_execucao;

    int contador = 0;    
    int tamanhocliente = tamanho_arquivo_clientes(out);

    temporizador_INICIAL = clock();
    
    int i, j, min;
    
    rewind(out); 
    for(i = 1; i<tamanhocliente; i++){
        min = i;
        fseek(out, (i-1)*sizeof(TCliente), SEEK_SET);
        TCliente *clientemin = leitura_arquivo_cliente(out); 

        for(j = i+1; j<=tamanhocliente; j++){ 
            fseek(out, (j-1)*sizeof(TCliente), SEEK_SET); 
            TCliente *clienteJ = leitura_arquivo_cliente(out);  

            if(clienteJ->codigo < clientemin->codigo){
                min = j; 
                free(clientemin); 
                clientemin = clienteJ; 
            }
            else{
                free(clienteJ);
            }
            contador++;
        }

        if(min != i){
            fseek(out, (i-1)*sizeof(TCliente), SEEK_SET); 
            TCliente *clienteI = leitura_arquivo_cliente(out); 

            fseek(out, (i-1)*sizeof(TCliente), SEEK_SET); 
            salvarCliente(clientemin, out); 

            fseek(out, (min-1)*sizeof(TCliente), SEEK_SET); 
            salvarCliente(clienteI, out); 
            free(clienteI);
        }

        free(clientemin);

    }
    fflush(out); 

    temporizador_FINAL = clock();
    tempo_execucao = (temporizador_FINAL - temporizador_INICIAL) / CLOCKS_PER_SEC;
    Salvar_LOG_SS(ArquivoLogSS, contador, tempo_execucao);
}

void Selection_Sort_Funcionario_Disco(FILE *out, FILE *ArquivoLogSS){
    clock_t clock(void);
    double temporizador_INICIAL, temporizador_FINAL;
    double tempo_execucao;

    int contador = 0;
    int tamanhofunc = tamanho_arquivo_funcionarios(out); 


    temporizador_INICIAL = clock();
    
    int i, j, min;
    
    rewind(out); 
    for(i = 1; i<tamanhofunc; i++){
        min = i;
        fseek(out, (i-1)*sizeof(TFuncionario), SEEK_SET); 
        TFuncionario *funcionariomin = leitura_arquivo_funcionario(out); 

        for(j = i+1; j<=tamanhofunc; j++){ 
            fseek(out, (j-1)*sizeof(TFuncionario), SEEK_SET);
            TFuncionario *funcionarioJ = leitura_arquivo_funcionario(out);  

            if(funcionarioJ->codigo < funcionariomin->codigo){
                min = j; 
                free(funcionariomin); 
                funcionariomin = funcionarioJ; 
            }
            else{
                free(funcionarioJ);
            }
            contador++;
        }

        if(min != i){ 
            fseek(out, (i-1)*sizeof(TFuncionario), SEEK_SET); 
            TFuncionario *funcionarioI = leitura_arquivo_funcionario(out); 

            fseek(out, (i-1)*sizeof(TFuncionario), SEEK_SET); 
            salvarFuncionario(funcionariomin, out);

            fseek(out, (min-1)*sizeof(TFuncionario), SEEK_SET); 
            salvarFuncionario(funcionarioI, out); 

            free(funcionarioI);
        }
        free(funcionariomin);
    }
    fflush(out); 

    temporizador_FINAL = clock();
    tempo_execucao = (temporizador_FINAL - temporizador_INICIAL) / CLOCKS_PER_SEC;
    Salvar_LOG_SS(ArquivoLogSS, contador, tempo_execucao);
}

#endif