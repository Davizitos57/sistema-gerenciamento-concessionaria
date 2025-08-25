#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "assinaturas_gerais.h"

bool arquivos_vazios(FILE* automoveis, FILE* clientes, FILE* funcionarios);
void abre_arquivos(FILE** automoveis, FILE** clientes, FILE** funcionarios);
void embralhabases(int *vet, int TAM);
void criarBasesOrdenadasGeral (FILE *automoveis, FILE *clientes, FILE *funcionarios, int tamanho);
void criarBasesEmbaralhadasGeral (FILE *automoveis, FILE *clientes, FILE *funcionarios, int tamanho);

#endif