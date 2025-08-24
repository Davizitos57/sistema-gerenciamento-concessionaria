#include "headers\assinaturas_gerais.h"

int Menu_Principal(){
    int escolha = 0;

    printf("                   Sistema de Gerenciamento de uma Concessionaria               \n");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("\n[1] Servicos Automoveis.\n[2] Servicos Clientes.\n[3] Servicos Funcionarios.\n[4] Sair da Concessionaria.\n\n");
    
    printf("Escolha: ");
    scanf("%d", &escolha);

    return escolha;
}

int Menu_Automoveis(){
    int escolha = 0;

    printf("--------------------------------------------------------------------------------\n");
    printf("                      Seja Bem-vindo ao Setor de Automoveis                     \n");
    printf("--------------------------------------------------------------------------------\n");

    printf("\n[1] Registrar um Automovel.\n[2] Buscar um Automovel.\n[3] Editar um Automovel.\n[4] Verificar os Automoveis alugados.\n");
    printf("[5] Verificar os Automoveis vendidos.\n[6] Sair do Setor de Automoveis.\n\n");

    printf("Escolha: ");
    scanf("%d", &escolha);

    return escolha;
}

int Menu_Funcionarios(){
    int escolha = 0;

    printf("--------------------------------------------------------------------------------\n");
    printf("                Seja Bem-vindo(a) a area destinada a Funcionarios               \n");
    printf("--------------------------------------------------------------------------------\n");

    printf("\n[1] Registrar Funcionario.\n[2] Buscar Funcionario.\n[3] Editar Funcionario.\n[4] Buscar Cliente cadastrado.\n[5] Editar Cliente.\n");
    printf("[6] Sair da area destinada a Funcionarios.\n\n");

    printf("Escolha: ");
    scanf("%d", &escolha);

    return escolha;

}

int Menu_Cliente(){
    int escolha = 0;

    printf("--------------------------------------------------------------------------------\n");
    printf("               Seja Bem-vindo(a) a area destinada a Clientes                    \n");
    printf("--------------------------------------------------------------------------------\n");

    printf("\n[1] Alugar um Automovel.\n[2] Comprar um Automovel.\n[3] Buscar um Automovel.\n[4] Devolver Automovel alugado.\n");
    printf("[5] Sair da area destinada a Clientes.\n\n");

    printf("Escolha: ");
    scanf("%d", &escolha);

    return escolha;

}