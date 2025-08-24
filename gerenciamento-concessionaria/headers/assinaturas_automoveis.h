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

#endif