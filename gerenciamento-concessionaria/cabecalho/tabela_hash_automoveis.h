#ifndef TABELAHASHAUTOMOVEIS_H_INCLUDED
#define TABELAHASHAUTOMOVEIS_H_INCLUDED

#include "assinaturas_gerais.h"
#include "tabela_hash_geral.h"
#include "assinaturas_automoveis.h"

typedef struct{
    TCarros carro;
    int proximo; 
    bool ocupado;
} TNoHashAutomoveis;

TCarros *buscaAutomovelHash(FILE *tabelaHash, FILE *listaEncadeada, int codigo);
void inserirAutomovelHash(FILE *tabelaHash, FILE *listaEncadeada, TCarros *carro);
void inicializaTabelaHashAutomoveis(FILE *tabelaHash, FILE *listaEncadeada, FILE *automoveis);
void imprimirTabelaHash(FILE *tabelaHash, FILE *listaEncadeada);
bool deletarAutomovelHash(FILE *tabelaHash, FILE *listaEncadeada, FILE *automoveis, int codigo);

#endif