#ifndef TABELAHASHGERAL_H_INCLUDED
#define TABELAHASHGERAL_H_INCLUDED

#include "assinaturas_gerais.h"

#define TAMANHO_HASH 7

int FuncaoHash(int codigo);
void CriaTabelaHashVazia(FILE *tabelaHash);

#endif 