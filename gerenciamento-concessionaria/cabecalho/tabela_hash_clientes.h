#ifndef TABELAHASHCLIENTES_H_INCLUDED
#define TABELAHASHCLIENTES_H_INCLUDED

#include "assinaturas_gerais.h"
#include "tabela_hash_geral.h"
#include "assinaturas_clientes.h"

typedef struct{
    TCliente cliente;
    int proximo; 
    bool ocupado;
} TNoHashClientes;

TCliente *buscaClienteHash(FILE *tabelaHash, FILE *listaEncadeada, int codigo);
void imprimirTabelaHashCliente(FILE *tabelaHash, FILE *listaEncadeada);
void inicializaTabelaHashClientes(FILE *tabelaHash, FILE *listaEncadeada, FILE *clientes);
void inserirClienteHash(FILE *tabelaHash, FILE *listaEncadeada, TCliente *cliente);
bool deletarClienteHash(FILE *tabelaHash, FILE *listaEncadeada, FILE *clientes, int codigo);

#endif