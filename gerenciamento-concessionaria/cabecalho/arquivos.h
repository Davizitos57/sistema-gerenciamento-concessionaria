#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "assinaturas_gerais.h"
#include "assinaturas_clientes.h"
#include "assinaturas_funcionarios.h"
#include "assinaturas_automoveis.h"


bool arquivos_vazios(FILE* automoveis, FILE* clientes, FILE* funcionarios);
void abre_arquivos(FILE** automoveis, FILE** clientes, FILE** funcionarios);
void abre_arquivos_hash(FILE **tabelaHashAuto, FILE **listaEncadeadaAuto, FILE **tabelaHashCliente, FILE **listaEncadeadaCliente, FILE **tabelaHashFunc, FILE **listaEncadeadaFunc);
void embralhabases(int *vet, int TAM);
void criarBasesOrdenadasGeral (FILE *automoveis, FILE *clientes, FILE *funcionarios, int tamanho);
void criarBasesEmbaralhadasGeral (FILE *automoveis, FILE *clientes, FILE *funcionarios, int tamanho);
void Salvar_LOG_S(FILE *LOG, int contador, double TEMP_EXECUCAO);
void Salvar_LOG_B(FILE *LOG, int contador, double TEMP_EXECUCAO);
void Salvar_LOG_SS(FILE *LOG, int contador, double TEMP_EXECUCAO);
void Salvar_LOG_Particoes(FILE *LOG, int contador, double TEMP_EXECUCAO);
void Salvar_LOG_IntercalacaoOtima(FILE *LOG, int contador, double TEMP_EXECUCAO);

#endif