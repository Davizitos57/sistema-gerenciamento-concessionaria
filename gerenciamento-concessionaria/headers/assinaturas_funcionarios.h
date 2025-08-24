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

#endif