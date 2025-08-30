#ifndef BUSCASSEQUENCIAL_H_INCLUDED
#define BUSCASSEQUENCIAL_H_INCLUDED

#include "assinaturas_gerais.h"
#include "assinaturas_automoveis.h"
#include "assinaturas_funcionarios.h"
#include "assinaturas_clientes.h"

TFuncionario *BuscaSequencialFuncionario(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial);
TFuncionario *BuscaSequencialEditarFunc(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial, TFuncionario **funcionario);
TCarros *BuscaSequencialAutomovel(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial);
TCarros *BuscaSequencialEditarCarro(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial, TCarros **carro);
TCliente *BuscaSequencialCliente(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial);
TCliente *BuscaSequencialEditarCliente(FILE *arquivo, int chave, FILE *ArquivoLOGSequencial, TCliente **cliente);

#endif