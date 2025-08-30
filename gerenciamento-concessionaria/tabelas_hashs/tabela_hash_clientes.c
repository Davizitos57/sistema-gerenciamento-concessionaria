#ifndef TABELAHASHCLIENTES_C
#define TABELAHASHCLIENTES_C

#include "..\cabecalho\tabela_hash_clientes.h"
#include "..\entidades\clientes.c"
#include "..\arquivos.c"
#include "tabela_hash_geral.c"

void inserirClienteHash(FILE *tabelaHash, FILE *listaEncadeada, TCliente *cliente) {
    int hashlocalizacao = FuncaoHash(cliente->codigo);

    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento;
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if (ponteiroCompartimento == -1) {
        TNoHashClientes NoHashNovo;
        NoHashNovo.cliente = *cliente;
        NoHashNovo.proximo = -1;
        NoHashNovo.ocupado = true;

        fseek(listaEncadeada, 0, SEEK_END);
        int posicaoNovoNo = ftell(listaEncadeada) / sizeof(TNoHashClientes);
        fwrite(&NoHashNovo, sizeof(TNoHashClientes), 1, listaEncadeada);

        fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
        fwrite(&posicaoNovoNo, sizeof(int), 1, tabelaHash);
    } 
    else {
        int posicaoAtual = ponteiroCompartimento;
        TNoHashClientes noHashAtual;

        while (posicaoAtual != -1) {
            fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
            fread(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);

            if(!noHashAtual.ocupado){
                cliente->codigo = noHashAtual.cliente.codigo;
                noHashAtual.cliente = *cliente;
                noHashAtual.ocupado = true;
                fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
                fwrite(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);
                return;
            }

            if (noHashAtual.proximo == -1) {
                break;
            }
            posicaoAtual = noHashAtual.proximo;
        }

        TNoHashClientes NoHashNovo;
        NoHashNovo.cliente = *cliente;
        NoHashNovo.proximo = -1;
        NoHashNovo.ocupado = true;

        fseek(listaEncadeada, 0, SEEK_END);
        int posicaoNovoNo = ftell(listaEncadeada) / sizeof(TNoHashClientes);
        fwrite(&NoHashNovo, sizeof(TNoHashClientes), 1, listaEncadeada);

        noHashAtual.proximo = posicaoNovoNo;
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
        fwrite(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);
    }

    fflush(tabelaHash);
    fflush(listaEncadeada);
}

void inicializaTabelaHashCliente(FILE *tabelaHash, FILE *listaEncadeada, FILE *clientes){
    
    CriaTabelaHashVazia(tabelaHash);
    rewind(clientes);

    TCliente *cliente;
    while((cliente = leitura_arquivo_cliente(clientes))!=NULL){
        inserirClienteHash(tabelaHash, listaEncadeada, cliente);
        free(cliente);
    }
}

void imprimirTabelaHashCliente(FILE *tabelaHash, FILE *listaEncadeada){
    rewind(tabelaHash);

    printf("--------------------------------------------------------------------------------\n");
    printf("                              Tabela Hash de Clientes                           \n");
    printf("--------------------------------------------------------------------------------\n");

    for(int i = 0; i<TAMANHO_HASH; i++){
        int ponteiroCompartimento;
        fseek(tabelaHash, i*sizeof(int), SEEK_SET);
        fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

        printf("\nCompartimento [%d]: ", i);

        if(ponteiroCompartimento == -1){
            printf("Compartimento Vazio.\n");
        }
        else{
            printf("Compartimento Ocupado.\n");

            int posicaoAtual = ponteiroCompartimento;
            while(posicaoAtual != -1){
                TNoHashClientes noHashAtual;
                fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
                fread(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);
                
                if(noHashAtual.ocupado){
                    printf("\n| Nome do cliente: %s\n| CPF do cliente: %s\n| Telefone do cliente: %s\n", noHashAtual.cliente.nome, noHashAtual.cliente.cpf, noHashAtual.cliente.telefone);
                    printf("| Codigo do cliente: %d\n", noHashAtual.cliente.codigo);
                    if(noHashAtual.proximo != -1){
                        printf("| Proximo (Posicao): %d\n\n", noHashAtual.proximo);
                    }
                    else{
                        printf("| Proximo (Posicao): %d (NULL)\n\n", noHashAtual.proximo);
                    }
                }

                posicaoAtual = noHashAtual.proximo;
            }
        }
        printf("--------------------------------------------------------------------------------\n");
    }
    printf("\n");
}

TCliente *buscaClienteHash(FILE *tabelaHash, FILE *listaEncadeada, int codigo){
    int hashlocalizacao = FuncaoHash(codigo);

    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento; 
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if(ponteiroCompartimento == -1){
        printf("\nEsse compartimento [%d] encontra-se vazio.\n\n", hashlocalizacao);
        return NULL;
    }

    int posicaoAtual = ponteiroCompartimento;
    while(posicaoAtual != -1){
        TNoHashClientes noHashAtual;
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
        fread(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);

        if(noHashAtual.cliente.codigo == codigo){
            if(noHashAtual.ocupado){
                TCliente *clienteAchado = (TCliente *)malloc(sizeof(TCliente));
                *clienteAchado = noHashAtual.cliente;
                return clienteAchado;
            }
            else{
                return NULL;
            }
        }

        posicaoAtual = noHashAtual.proximo;
    }

    return NULL;
}

bool deletarClienteHash(FILE *tabelaHash, FILE *listaEncadeada, FILE *clientes, int codigo){
    int hashlocalizacao = FuncaoHash(codigo);

    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento; 
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if(ponteiroCompartimento == -1){
        printf("\nEsse compartimento [%d] encontra-se vazio.\n\n", hashlocalizacao);
        return NULL;
    }

    int posicaoAtual = ponteiroCompartimento;
    TNoHashClientes noHashAtual;

    while(posicaoAtual != -1){
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
        fread(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);

        if(noHashAtual.cliente.codigo == codigo && noHashAtual.ocupado){
            noHashAtual.ocupado = false;
            fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashClientes), SEEK_SET);
            fwrite(&noHashAtual, sizeof(TNoHashClientes), 1, listaEncadeada);

            TCliente clienteAchado;
            rewind(clientes);
            while(fread(&clienteAchado, sizeof(TCliente), 1, clientes) == 1){
                if(clienteAchado.codigo == codigo){
                    clienteAchado.ocupado = false;
                    fseek(clientes, -sizeof(TCliente), SEEK_CUR);
                    fwrite(&clienteAchado, sizeof(TCliente), 1, clientes);
                    fflush(clientes);
                    break;
                }
            }
            return true;
        }
        posicaoAtual = noHashAtual.proximo;
    }
    return false;
}

#endif