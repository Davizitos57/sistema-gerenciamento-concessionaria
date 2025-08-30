#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "assinaturas_gerais.h"
#include "assinaturas_clientes.h"
#include "assinaturas_funcionarios.h"
#include "assinaturas_automoveis.h"
#include "busca_binaria.h"
#include "busca_sequencial.h"
#include "tabela_hash_geral.h"
#include "tabela_hash_automoveis.h"
#include "tabela_hash_clientes.h"
#include "tabela_hash_funcionarios.h"
#include "menu.h"

void seletor(FILE* automoveis, FILE* clientes, FILE* funcionarios, FILE *ArquivoLOG);
void Switch_Automoveis(FILE* carros, FILE *ArquivoLOG);
void Switch_Clientes(FILE* clientes, FILE *ArquivoLOG);
void Switch_Funcionarios(FILE* func, FILE *ArquivoLOG);
void Switch_TabelaHash(FILE *tabelaHashAuto, FILE *tabelaHashCliente, FILE *tabelaHashFunc, FILE *listaEncadeadaAuto, FILE *listaEncadeadaCliente, FILE *listaEncadeadaFunc);

#endif