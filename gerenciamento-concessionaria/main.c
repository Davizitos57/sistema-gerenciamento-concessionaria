#include "headers\assinaturas_gerais.h"
#include "headers\arquivos.h"
#include "headers\engine.h"

int main(){
    FILE *automoveis = NULL, *clientes = NULL, *funcionarios = NULL;
    FILE *ArquivoLOG = NULL;

    abre_arquivos(&automoveis, &clientes, &funcionarios);

    int tamanho = 1000;
    int escolhainicial = 0; 
    if(arquivos_vazios(automoveis, clientes, funcionarios)){
        do {

            printf("Antes de comecarmos, por favor, informe qual estilo de base de dados deseja utilizar.");
            printf("\n\n[1] Utilizar Bases Ordenadas.\n[2] Utilizar Bases Embaralhadas.\n\n");
            printf("Sua escolha: ");
            scanf("%d", &escolhainicial);
    
            if(escolhainicial == 1){
                criarBasesOrdenadasGeral(automoveis, clientes, funcionarios, tamanho);
            }
            else if(escolhainicial == 2){
                criarBasesEmbaralhadasGeral(automoveis, clientes, funcionarios, tamanho);
            }
            else{
                printf("\nOpcao invalida, tente novamente\n");  
            }
            system("cls");
        }
        while(escolhainicial > 2 || escolhainicial < 1);
    }
    else{
        printf("\nBases de dados ja existentes. Pulando a criacao de novas bases...\n");
    }

    printf("------------------------------------------------------------------------------------------------------\n");
    printf("                                Seja Bem-vindo                                  \n");
    printf("O nosso programa conta com, atualmente, %d automoveis cadastrados, %d clientes e %d funcionarios.\n", tamanho, tamanho/2, tamanho/5);
    seletor(automoveis, clientes, funcionarios, ArquivoLOG);

    return 0;
}