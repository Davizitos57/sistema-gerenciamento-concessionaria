#ifndef TABELAHASHFUNCIONARIOS_H_INCLUDED
#define TABELAHASHFUNCIONARIOS_H_INCLUDED

#include "assinaturas_gerais.h"
#include "tabela_hash_geral.h"
#include "assinaturas_funcionarios.h"

typedef struct{
    TFuncionario funcionario;
    int proximo; 
    bool ocupado;
} TNoHashFuncionario;

TFuncionario *buscaFuncionarioHash(FILE *tabelaHash, FILE *listaEncadeada, int codigo);
void inserirFuncionarioHash(FILE *tabelaHash, FILE *listaEncadeada, TFuncionario *func);
void inicializaTabelaHashFuncionarios(FILE *tabelaHash, FILE *listaEncadeada, FILE *funcionarios);
void imprimirTabelaHashFunc(FILE *tabelaHash, FILE *listaEncadeada);
bool deletarFuncionarioHash(FILE *tabelaHash, FILE *listaEncadeada, FILE *funcionarios, int codigo);

#endif