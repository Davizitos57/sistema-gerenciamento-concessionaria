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

#endif