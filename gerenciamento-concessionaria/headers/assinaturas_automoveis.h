#ifndef ASSINATURASAUTOMOVEIS_H_INCLUDED
#define ASSINATURASAUTOMOVEIS_H_INCLUDED

#include "assinaturas_gerais.h"
#include "assinaturas_funcionarios.h"
#include "assinaturas_clientes.h"

typedef struct Carros{

    NOME nome;
    MARCA marca_veiculo;
    MODELO modelo_veiculo;
    int codigo;
    double preco;

    TFuncionario funcionario;
    TCliente cliente;

    int situacao;
    
} TCarros;

//Declarações de Funções
int tamanho_automovel();
int tamanho_arquivo_automovel(FILE *out);

TCarros *leitura_arquivo_carros(FILE *in);
TCarros *criaAutomoveis(char *nome, char *marca, char *modelo, int codigo, double preco);
TCarros *criaAutomoveisManual(TCarros *carro, FILE *out);

void salvarAutomoveis(TCarros *carro, FILE *out);
void criarBaseOrdenadaCarros(FILE *out, int tamanho);
void criarBaseEmbaralhadaCarros(FILE *out, int tamanho);
void imprimirCarro(TCarros *carro);
void imprimirBaseCarros(FILE *out);
void imprimirBaseCarrosAlugados(FILE *out);
void imprimirBaseCarrosVendidos(FILE *out);
void imprimirBaseCarrosDisponiveis(FILE *out);

#endif