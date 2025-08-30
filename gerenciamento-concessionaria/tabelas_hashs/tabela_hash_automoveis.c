#ifndef TABELAHASHAUTOMOVEIS_C
#define TABELAHASHAUTOMOVEIS_C

#include "..\cabecalho\tabela_hash_automoveis.h"
#include "..\entidades\automoveis.c"
#include "..\arquivos.c"
#include "tabela_hash_geral.c"

void inserirAutomovelHash(FILE *tabelaHash, FILE *listaEncadeada, TCarros *carro) {
    int hashlocalizacao = FuncaoHash(carro->codigo);

    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento;
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if (ponteiroCompartimento == -1) {
        TNoHashAutomoveis NoHashNovo;
        NoHashNovo.carro = *carro;
        NoHashNovo.proximo = -1;
        NoHashNovo.ocupado = true;

        fseek(listaEncadeada, 0, SEEK_END);
        int posicaoNovoNo = ftell(listaEncadeada) / sizeof(TNoHashAutomoveis);
        fwrite(&NoHashNovo, sizeof(TNoHashAutomoveis), 1, listaEncadeada);

        fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
        fwrite(&posicaoNovoNo, sizeof(int), 1, tabelaHash);
    } 
    else {
        int posicaoAtual = ponteiroCompartimento;
        TNoHashAutomoveis noHashAtual;

        while (posicaoAtual != -1) {
            fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
            fread(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);

            if(!noHashAtual.ocupado){
                carro->codigo = noHashAtual.carro.codigo;
                noHashAtual.carro = *carro;
                noHashAtual.ocupado = true;
                fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
                fwrite(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);
                return;
            }

            if (noHashAtual.proximo == -1) {
                break;
            }
            posicaoAtual = noHashAtual.proximo;
        }

        TNoHashAutomoveis NoHashNovo;
        NoHashNovo.carro = *carro;
        NoHashNovo.proximo = -1;
        NoHashNovo.ocupado = true;

        fseek(listaEncadeada, 0, SEEK_END);
        int posicaoNovoNo = ftell(listaEncadeada) / sizeof(TNoHashAutomoveis);
        fwrite(&NoHashNovo, sizeof(TNoHashAutomoveis), 1, listaEncadeada);

        noHashAtual.proximo = posicaoNovoNo;
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
        fwrite(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);
    }

    fflush(tabelaHash);
    fflush(listaEncadeada);
}

void inicializaTabelaHashAutomoveis(FILE *tabelaHash, FILE *listaEncadeada, FILE *automoveis){
    
    CriaTabelaHashVazia(tabelaHash);
    rewind(automoveis);

    TCarros *carro;
    while((carro = leitura_arquivo_carros(automoveis))!=NULL){
        inserirAutomovelHash(tabelaHash, listaEncadeada, carro);
        free(carro);
    }
}

void imprimirTabelaHash(FILE *tabelaHash, FILE *listaEncadeada){
    rewind(tabelaHash);

    printf("--------------------------------------------------------------------------------\n");
    printf("                              Tabela Hash de Automoveis                         \n");
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
                TNoHashAutomoveis noHashAtual;
                fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
                fread(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);
                
                if(noHashAtual.ocupado){
                    printf("\n| Nome do automovel: %s\n| Marca do automovel: %s\n| Modelo do automovel: %s\n", noHashAtual.carro.nome, noHashAtual.carro.marca_veiculo, noHashAtual.carro.modelo_veiculo);
                    printf("| Codigo do Automovel: %d\n", noHashAtual.carro.codigo);
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

TCarros *buscaAutomovelHash(FILE *tabelaHash, FILE *listaEncadeada, int codigo){
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
        TNoHashAutomoveis noHashAtual;
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
        fread(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);

        if(noHashAtual.carro.codigo == codigo){
            if(noHashAtual.ocupado){
                TCarros *carroAchado = (TCarros *)malloc(sizeof(TCarros));
                *carroAchado = noHashAtual.carro;
                return carroAchado;
            }
            else{
                return NULL;
            }
        }

        posicaoAtual = noHashAtual.proximo;
    }

    return NULL;
}

bool deletarAutomovelHash(FILE *tabelaHash, FILE *listaEncadeada, FILE *automoveis, int codigo){
    int hashlocalizacao = FuncaoHash(codigo);

    //Posiciona no compartimento correspondente
    fseek(tabelaHash, hashlocalizacao * sizeof(int), SEEK_SET);
    int ponteiroCompartimento; 
    fread(&ponteiroCompartimento, sizeof(int), 1, tabelaHash);

    if(ponteiroCompartimento == -1){
        printf("\nEsse compartimento [%d] encontra-se vazio.\n\n", hashlocalizacao);
        return NULL;
    }

    int posicaoAtual = ponteiroCompartimento;
    TNoHashAutomoveis noHashAtual;

    while(posicaoAtual != -1){
        fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
        fread(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);

        if(noHashAtual.carro.codigo == codigo && noHashAtual.ocupado){
            noHashAtual.ocupado = false;
            fseek(listaEncadeada, posicaoAtual * sizeof(TNoHashAutomoveis), SEEK_SET);
            fwrite(&noHashAtual, sizeof(TNoHashAutomoveis), 1, listaEncadeada);

            TCarros carroAchado;
            rewind(automoveis);
            while(fread(&carroAchado, sizeof(TCarros), 1, automoveis) == 1){
                if(carroAchado.codigo == codigo){
                    carroAchado.ocupado = false;
                    fseek(automoveis, -sizeof(TCarros), SEEK_CUR);
                    fwrite(&carroAchado, sizeof(TCarros), 1, automoveis);
                    fflush(automoveis);
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