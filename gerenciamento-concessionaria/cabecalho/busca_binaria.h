#ifndef BUSCASBINARIAS_H_INCLUDED
#define BUSCASBINARIAS_H_INCLUDED

#include "assinaturas_gerais.h"
#include "assinaturas_automoveis.h"
#include "assinaturas_funcionarios.h"
#include "assinaturas_clientes.h"

TFuncionario *BuscaBinariaFunc(int chave, FILE *arquivo, FILE *ArquivoLOGBinario);
TCarros *BuscaBinariaCarro(int chave, FILE *arquivo, FILE *ArquivoLOGBinario);
TCliente *BuscaBinariaCliente(int chave, FILE *arquivo, FILE *ArquivoLOGBinario);

#endif