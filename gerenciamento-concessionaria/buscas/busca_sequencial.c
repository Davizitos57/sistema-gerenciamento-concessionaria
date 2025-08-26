#ifndef BUSCASEQUENCIAL_C
#define BUSCASEQUENCIAL_C

#include "..\headers\busca_sequencial.h"
#include "..\entidades\automoveis.c"
#include "..\entidades\clientes.c"
#include "..\entidades\funcionarios.c"
#include "..\arquivos.c"

//Função para realizar busca sequencial em funcionários
TFuncionario *BuscaSequencialFuncionario(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial){

    clock_t clock(void);
    
    double TEMP_INCIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TFuncionario *procurado;
    
    int contador = 0;
    
    bool flag = false;

    TEMP_INCIAL = clock(); 

    rewind(arquivo); 

    while((procurado = leitura_arquivo_funcionario(arquivo)) != NULL){
        contador++;
        if(procurado->codigo == chave){
            flag = true;
            break;
        }
    }
    
    TEMP_FINAL = clock(); 
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INCIAL)/CLOCKS_PER_SEC;
 
    //Salva o log da busca sequencial
    Salvar_LOG_S(ArquivoLOGSequencial,contador, TEMP_EXECUCAO);

    if(flag){
        imprimefuncionario(procurado);
        return procurado;
    }
    else{
        printf("\nFuncionario nao foi encontrado, tem certeza que esse codigo %d existe?\n", chave);
        free(procurado);
        return NULL;    
    }
}

TFuncionario *BuscaSequencialEditarFunc(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial, TFuncionario **funcionario){

    clock_t clock(void);
    
    double TEMP_INCIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TFuncionario *procurado = NULL;
    
    int contador = 0;
    int posicao = 0;

    bool flag = false;

    TEMP_INCIAL = clock();

    rewind(arquivo);

    while((procurado = leitura_arquivo_funcionario(arquivo)) != NULL){
        contador++;
        if(procurado->codigo == chave){
            flag = true;
            *funcionario = procurado;
            break;
        }
        posicao++;
    }
    
    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INCIAL)/CLOCKS_PER_SEC;

    Salvar_LOG_S(ArquivoLOGSequencial,contador, TEMP_EXECUCAO);

    if(flag){
        return posicao; 
    }
    else{
        printf("\nFuncionario nao foi encontrado, tem certeza que esse codigo %d existe?\n", chave);
        free(procurado);
        return -1;
    }
}

//Função para realizar busca sequencial em automóveis
TCarros *BuscaSequencialAutomovel(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial){

    system("cls");

    clock_t clock(void);
    
    double TEMP_INCIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TCarros *procurado;
    
    int contador = 0;
    
    bool flag = false;
    TEMP_INCIAL = clock(); 
    rewind(arquivo); 

    while((procurado = leitura_arquivo_carros(arquivo)) != NULL){
        contador++;
        if(procurado->codigo == chave){
            flag = true;
            break;
        }
    }

    TEMP_FINAL = clock(); 
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INCIAL)/CLOCKS_PER_SEC;

    //Salva o log da busca sequencial
    Salvar_LOG_S(ArquivoLOGSequencial,contador, TEMP_EXECUCAO);

    if(flag){
        imprimirCarro(procurado);
        return procurado;
    }
    else{
        printf("\nAutomovel nao foi encontrado, tem certeza que esse codigo %d existe?\n", chave);
        free(procurado);
        return NULL;
    }
}

TCarros *BuscaSequencialEditarCarro(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial, TCarros **carro){

    system("cls");

    clock_t clock(void);
    
    double TEMP_INCIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TCarros *procurado = NULL;
    
    int contador = 0;
    int posicao = 0;

    bool flag = false;

    TEMP_INCIAL = clock();

    rewind(arquivo);

    while((procurado = leitura_arquivo_carros(arquivo)) != NULL){
        contador++;
        if(procurado->codigo == chave){
            flag = true;
            *carro = procurado;
            break;
        }
        posicao++;
    }
    
    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INCIAL)/CLOCKS_PER_SEC;

    Salvar_LOG_S(ArquivoLOGSequencial,contador, TEMP_EXECUCAO);

    if(flag){
        return posicao; 
    }
    else{
        printf("\nAutomovel nao foi encontrado, tem certeza que esse codigo %d existe?\n", chave);
        free(procurado);
        return -1;
    }
}

//Função para realizar busca sequencial em clientes
TCliente *BuscaSequencialCliente(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial){
    clock_t clock(void);

    double TEMP_INICIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TCliente *procuradoC;

    int contador = 0;
    bool flag = false;
    TEMP_INICIAL = clock(); 

    rewind(arquivo);  

    while((procuradoC = leitura_arquivo_cliente(arquivo)) != NULL){
        contador++;
        if(procuradoC->codigo == chave){
            flag = true;
            break;
        }
    }

    TEMP_FINAL = clock();  
    TEMP_EXECUCAO = (TEMP_FINAL-TEMP_INICIAL)/CLOCKS_PER_SEC;

    //Salva o log da busca sequencial
    Salvar_LOG_S(ArquivoLOGSequencial, contador, TEMP_EXECUCAO);

    if(flag){
        imprimecliente(procuradoC);
        return procuradoC;
    }
    else{
        printf("\nCliente nao foi encontrado, tem certeza que o codigo %d existe?\n", chave);
        free(procuradoC);
        return NULL;
    }
}

TCliente *BuscaSequencialEditarCliente(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial, TCliente **cliente){

    clock_t clock(void);
    
    double TEMP_INCIAL, TEMP_FINAL;
    double TEMP_EXECUCAO;

    TCliente *procurado = NULL;
    
    int contador = 0;
    int posicao = 0;

    bool flag = false;

    TEMP_INCIAL = clock();

    rewind(arquivo);

    while((procurado = leitura_arquivo_cliente(arquivo)) != NULL){
        contador++;
        if(procurado->codigo == chave){
            flag = true;
            *cliente = procurado;
            break;
        }
        posicao++;
    }
    
    TEMP_FINAL = clock();
    TEMP_EXECUCAO = (TEMP_FINAL - TEMP_INCIAL)/CLOCKS_PER_SEC;

    Salvar_LOG_S(ArquivoLOGSequencial,contador, TEMP_EXECUCAO);

    if(flag){
        return posicao; 
    }
    else{
        printf("\nCliente nao foi encontrado, tem certeza que esse codigo %d existe?\n", chave);
        free(procurado);
        return -1;
    }
}
#endif