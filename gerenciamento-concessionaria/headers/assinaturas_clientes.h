#ifndef ASSINATURASCLIENTES_H_INCLUDED
#define ASSINATURASCLIENTES_H_INCLUDED

#include "assinaturas_gerais.h"

typedef struct {

    NOME nome;
    CPF cpf;
    TELEFONE telefone;
    ENDERECO endereco;
    int codigo;
    
} TCliente;

//Declarações de Funções
int tamanho_cliente();
int tamanho_arquivo_clientes(FILE *out);

TCliente *leitura_arquivo_cliente(FILE *in);
TCliente *criaCliente(char *nome, char *cpf, char *telefone, char *endereco, int codigo);
TCliente *criaClienteManual (TCliente *cliente, FILE *out);

void criarBaseOrdenadaCliente(FILE *out, int tamanho);
void criarBaseEmbaralhadaCliente(FILE *out, int tamanho);
void salvarCliente(TCliente *cliente, FILE *out);
void imprimecliente(TCliente *c);
void imprimirBaseClientes (FILE *out);
void AlugarAutomovelCliente (FILE *carros, FILE *clientes, FILE *funcionarios);
void ComprarAutomovelCliente (FILE *carros, FILE *clientes, FILE *funcionarios);
void DevolverAutomovelCliente(FILE *carros, FILE *clientes);

#endif