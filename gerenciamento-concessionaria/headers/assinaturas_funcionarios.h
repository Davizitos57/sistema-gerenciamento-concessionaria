#ifndef ASSINATURASFUNCIONARIO_H_INCLUDED
#define ASSINATURASFUNCIONARIO_H_INCLUDED

#include "assinaturas_gerais.h"

typedef struct {

    NOME nome;
    CPF cpf;
    TELEFONE telefone;
    ENDERECO endereco;
    int codigo;
    double salario;
    
} TFuncionario;

//Declarações de Funções
TFuncionario *criaFuncionarios(char *nome, char *cpf, char *telefone, char *endereco, int codigo, double salario);
TFuncionario *criaFuncionariosManual(TFuncionario *func, FILE *out);
TFuncionario *leitura_arquivo_funcionario(FILE *in);

int tamanho_funcionario();
int tamanho_arquivo_funcionarios(FILE *out);

void salvarFuncionario(TFuncionario *func, FILE *out);
void criarBaseOrdenadaFuncionario(FILE *out, int tamanho);
void criarBaseEmbaralhadaFuncionario(FILE *out, int tamanho);
void imprimirBaseFuncionarios(FILE *out);
void imprimefuncionario(TFuncionario *f);

#endif