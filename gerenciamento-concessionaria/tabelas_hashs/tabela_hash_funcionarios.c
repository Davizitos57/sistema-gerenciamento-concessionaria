#ifndef TABELAHASHFUNCIONARIOS_C
#define TABELAHASHFUNCIONARIOS_C

#include "..\cabecalho\tabela_hash_funcionarios.h"
#include "..\entidades\funcionarios.c"
#include "..\arquivos.c"
#include "tabela_hash_geral.c"

void inserirFuncionarioHash(FILE *tabelaHash, FILE *listaEncadeada, TFuncionario *func) {
    int hashlocalizacao = FuncaoHash(func->codigo);

    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento;
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if (ponteiroCompartimento == -1) {
        TNoHashFuncionario NoHashNovo;
        NoHashNovo.funcionario = *func;
        NoHashNovo.proximo = -1;
        NoHashNovo.ocupado = true;

        fseek(listaEncadeada, 0, SEEK_END);
        int posicaoNovoNo = ftell(listaEncadeada) / sizeof(TNoHashFuncionario);
        fwrite(&NoHashNovo, sizeof(TNoHashFuncionario), 1, listaEncadeada);

        fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
        fwrite(&posicaoNovoNo, sizeof(int), 1, tabelaHash);
    } 
    else {
        int posicaoAtual = ponteiroCompartimento;
        TNoHashFuncionario noHashAtual;

        while (posicaoAtual != -1) {
            fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
            fread(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);

            if(!noHashAtual.ocupado){
                func->codigo = noHashAtual.funcionario.codigo;
                noHashAtual.funcionario = *func;
                noHashAtual.ocupado = true;
                fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
                fwrite(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);
                return;
            }

            if (noHashAtual.proximo == -1) {
                break;
            }
            posicaoAtual = noHashAtual.proximo;
        }

        TNoHashFuncionario NoHashNovo;
        NoHashNovo.funcionario = *func;
        NoHashNovo.proximo = -1;
        NoHashNovo.ocupado = true;

        fseek(listaEncadeada, 0, SEEK_END);
        int posicaoNovoNo = ftell(listaEncadeada) / sizeof(TNoHashFuncionario);
        fwrite(&NoHashNovo, sizeof(TNoHashFuncionario), 1, listaEncadeada);

        noHashAtual.proximo = posicaoNovoNo;
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
        fwrite(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);
    }

    fflush(tabelaHash);
    fflush(listaEncadeada);
}

void inicializaTabelaHashFuncionarios(FILE *tabelaHash, FILE *listaEncadeada, FILE *funcionarios){
    
    CriaTabelaHashVazia(tabelaHash);
    rewind(funcionarios);

    TFuncionario *func;
    while((func = leitura_arquivo_funcionario(funcionarios))!=NULL){
        inserirFuncionarioHash(tabelaHash, listaEncadeada, func);
        free(func);
    }
}

void imprimirTabelaHashFunc(FILE *tabelaHash, FILE *listaEncadeada){
    rewind(tabelaHash);

    printf("--------------------------------------------------------------------------------\n");
    printf("                            Tabela Hash de Funcionarios                         \n");
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
                TNoHashFuncionario noHashAtual;
                fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
                fread(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);
                
                if(noHashAtual.ocupado){
                    printf("\n| Nome do funcionario: %s\n| CPF do funcionario: %s\n| Telefone do funcionario: %s\n", noHashAtual.funcionario.nome, noHashAtual.funcionario.cpf, noHashAtual.funcionario.telefone);
                    printf("| Codigo do funcionario: %d\n", noHashAtual.funcionario.codigo);
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

TFuncionario *buscaFuncionarioHash(FILE *tabelaHash, FILE *listaEncadeada, int codigo){
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
        TNoHashFuncionario noHashAtual;
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
        fread(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);

        if(noHashAtual.funcionario.codigo == codigo){
            if(noHashAtual.ocupado){
                TFuncionario *funcAchado = (TFuncionario *)malloc(sizeof(TFuncionario));
                *funcAchado = noHashAtual.funcionario;
                return funcAchado;
            }
            else{
                return NULL;
            }
        }

        posicaoAtual = noHashAtual.proximo;
    }

    return NULL;
}

bool deletarFuncionarioHash(FILE *tabelaHash, FILE *listaEncadeada, FILE *funcionarios, int codigo){
    int hashlocalizacao = FuncaoHash(codigo);

    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento; 
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if(ponteiroCompartimento == -1){
        printf("\nEsse compartimento [%d] encontra-se vazio.\n\n", hashlocalizacao);
        return NULL;
    }

    int posicaoAtual = ponteiroCompartimento;
    TNoHashFuncionario noHashAtual;

    while(posicaoAtual != -1){
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
        fread(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);

        if(noHashAtual.funcionario.codigo == codigo && noHashAtual.ocupado){
            noHashAtual.ocupado = false;
            fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashFuncionario), SEEK_SET);
            fwrite(&noHashAtual, sizeof(TNoHashFuncionario), 1, listaEncadeada);

            TFuncionario funcAchado;
            rewind(funcionarios);
            while(fread(&funcAchado, sizeof(TFuncionario), 1, funcionarios) == 1){
                if(funcAchado.codigo == codigo){
                    funcAchado.ocupado = false;
                    fseek(funcionarios, -sizeof(TFuncionario), SEEK_CUR);
                    fwrite(&funcAchado, sizeof(TFuncionario), 1, funcionarios);
                    fflush(funcionarios);
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