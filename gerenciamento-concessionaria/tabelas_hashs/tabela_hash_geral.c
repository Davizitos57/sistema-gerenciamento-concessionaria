#ifndef TABELAHASHGERAL_C
#define TABELAHASHGERAL_C

#include "..\cabecalho\assinaturas_gerais.h"
#include "..\cabecalho\tabela_hash_geral.h"

int FuncaoHash(int codigo){
    return codigo % TAMANHO_HASH;
}

void CriaTabelaHashVazia(FILE *tabelaHash){
    int ponteiroVazio = -1;

    rewind(tabelaHash);
    for(int i = 0; i<TAMANHO_HASH; i++){
        fwrite(&ponteiroVazio, sizeof(int), 1, tabelaHash);
    }
    fflush(tabelaHash);
}

#endif