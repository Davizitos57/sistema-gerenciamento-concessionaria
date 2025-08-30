#ifndef ENGINE_C
#define ENGINE_C

#include "cabecalho\engine.h"
#include "entidades\automoveis.c"
#include "entidades\clientes.c"
#include "entidades\funcionarios.c"
#include "buscas\busca_sequencial.c"
#include "buscas\busca_binaria.c"
#include "ordenacao\selection_sort.c"
#include "ordenacao\selecao_natural.c"
#include "ordenacao\intercalacao_otima.c"
#include "menu.c"

void seletor(FILE* automoveis, FILE* clientes, FILE* funcionarios, FILE *ArquivoLOG){

    bool end = true;

    do{

        switch(Menu_Principal()){

            case 1:
                Switch_Automoveis(automoveis, ArquivoLOG);
            break;

            case 2:
                Switch_Clientes(clientes, ArquivoLOG);
            break;

            case 3:
                Switch_Funcionarios(funcionarios, ArquivoLOG);
            break;

            case 4:
                system("cls");
                printf("Encerrando programa...");
                end = false;
            break;      
            
            default:
                printf("\nOpcao invalida, tente novamente\n");        
            break;

        }

    }while(end);
}

void Switch_Automoveis(FILE* carros, FILE *ArquivoLOG){

    system("cls");

    bool end = true;
    int escolha_auto = 0;
    int procuradoA = 0;
    int NP = 0;

    do{

        switch(Menu_Automoveis()){


            case 1:{

                system("cls");
                
                printf("Caso queira criar um automovel novo, certifique-se que a base ja estara criada para a utilizar a busca binaria");
                printf("\nOu caso necessite criar o automovel primeiro, lembre-se de utilizar a busca sequencial\n");
                TCarros *automovel = malloc(sizeof(TCarros));
                criaAutomoveisManual(automovel, carros);
            }
            break;

            case 2:
                printf("\nDe que maneira voce quer procurar um automovel?\n");
                printf("\n[1] Busca Binaria\n[2] Busca Sequencial\n");
                
                printf("Sua escolha: ");
                scanf("%d", &escolha_auto);

                if(escolha_auto == 1){
                    
                    printf("\nInforme qual automovel desejas encontrar. (Utilize o codigo do automovel)");
                    printf("\nOBSERVACAO: Para utilizar essa busca certifique-se que sua base esta ordenada");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoA);

                    printf("\nBuscando binariamente...\n");
                    BuscaBinariaCarro(procuradoA, carros, ArquivoLOG);
                }
                else if(escolha_auto == 2){

                    printf("\nInforme qual automovel desejas encontrar. (Utilize o codigo do automovel)");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoA);

                    printf("\nBuscando sequencialmente...\n");
                    BuscaSequencialAutomovel(carros, procuradoA, ArquivoLOG);
                }
                else {
                    printf("\nOpcao invalida, tente novamente\n");
                }
            break;

            case 3:
                printf("\nInforme qual automovel, voce deseja mudar as informacoes. (Utilize o codigo do automovel)");
                printf("\nEscolha: ");
                scanf("%d", &procuradoA);

                TCarros *c = NULL;
                int posicao = (int)BuscaSequencialEditarCarro(carros, procuradoA, NULL, &c);
                int alterar = 0;

                if(posicao != -1){
                    if(c->situacao == ALUGADO || c->situacao == VENDIDO){
                        printf("O automovel se encontra na situacao de %s.\nDeseja alterar todos os dados ou manter o cliente, funcionario e situacao respectiva desse automovel?\n\n", c->situacao == ALUGADO ? "alugado" : "vendido");
                        printf("[1] Desejo alterar todos os dados.\n[2] Desejo alterar os dados, mas manter a situacao, funcionario e cliente associado.\n");
                        printf("Escolha: ");
                        scanf("%d", &alterar);
                        
                        if(alterar == 1){
                            criaAutomoveisManual(c, NULL);
                        }
                        else if(alterar == 2){
                            printf("\nDigite o nome do automovel: ");
                            while(getchar() != '\n'); 
                            fgets(c->nome, sizeof(c->nome), stdin);
                            c->nome[strcspn(c->nome, "\n")] = '\0';

                            printf("\nDigite a marca do automovel: ");
                            fgets(c->marca_veiculo, sizeof(c->marca_veiculo), stdin);
                            c->marca_veiculo[strcspn(c->marca_veiculo, "\n")] = '\0';

                            printf("\nDigite o modelo do automovel: ");
                            fgets(c->modelo_veiculo, sizeof(c->modelo_veiculo), stdin);
                            c->modelo_veiculo[strcspn(c->modelo_veiculo, "\n")] = '\0';

                            printf("\nDigite o preco do automovel: ");
                            scanf("%lf", &c->preco);
                            getchar(); 
                        }
                        else{
                            printf("\nOpcao invalida, por favor, tente novamente\n");
                        }
                    }
                    else{
                        criaAutomoveisManual(c, NULL);
                    }
                    fseek(carros, posicao * sizeof(TCarros), SEEK_SET);
                    salvarAutomoveis(c, carros); 

                    imprimirCarro(c);
                }
            break;
            
            case 4:
                imprimirBaseCarrosAlugados(carros);
            break;
            
            case 5:
                imprimirBaseCarrosVendidos(carros);
            break;

            case 6:
                imprimirBaseCarros(carros);
            break;

            case 7:
                printf("Ordenando base de dados...");
                Selection_Sort_Automoveis_Disco(carros, ArquivoLOG);
                system("cls");
                printf("Base de dados ordenada\n");
            break;

            case 8:
                system("cls");
                printf("Informe quantos registros do arquivo serao lidos para a memoria.\n");
                printf("Sua escolha: ");
                scanf("%d", &NP);

                int NPcriadas = SelecaoNaturalAutomoveis(carros, NP, ArquivoLOG);
                printf("Numero de particoes criadas: %d\n", NPcriadas+1);

                printf("\nComecando a parte da intercalacao otima...\n");
                IntercalacaoOtimaAutomovel(NPcriadas, "Automoveis.dat", ArquivoLOG);
                printf("\nClassificacao Externa Finalizada\n");
            break;

            case 9:
                system("cls");
                printf("Saindo do setor de Automoveis...");
                printf("\n------------------------------------------------------------------------------------------------------\n");
                end = false;
            break;

            default:
                printf("\nOpcao invalida, tente novamente\n");        
            break;

        }

    }while(end);
}

void Switch_Clientes(FILE* clientes, FILE *ArquivoLOG){

    system("cls");

    FILE *carros = fopen("Automoveis.dat", "r+b");
    FILE *funcionarios = fopen("Funcionarios.dat", "r+b");
    
    if (carros == NULL) {
        printf("Erro ao abrir o arquivo Automoveis.dat\n");
        return;
    }
    if (funcionarios == NULL) {
        printf("Erro ao abrir o arquivo Funcionarios.dat\n");
        return;
    }
    
    bool end = true;
    int escolha_cliente = 0;
    int procuradoAC = 0;
    int NP = 0;

    do{

       switch(Menu_Cliente()){

            case 1:
                AlugarAutomovelCliente(carros, clientes, funcionarios);
            break;

            case 2:
                ComprarAutomovelCliente(carros, clientes, funcionarios);
            break;

            case 3:
                printf("\nDe que maneira voce quer procurar um automovel?\n");
                printf("\n[1] Busca Binaria\n[2] Busca Sequencial\n");
                
                printf("Sua escolha: ");
                scanf("%d", &escolha_cliente);

                if(escolha_cliente == 1){


                    printf("\nInforme qual automovel desejas encontrar. (Utilize o codigo do automovel)");
                    printf("\nOBSERVACAO: Para utilizar essa busca certifique-se que sua base esta ordenada");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoAC);

                    system("cls");
                    printf("Buscando binariamente...\n");
                    BuscaBinariaCarro(procuradoAC, carros, ArquivoLOG);
                }
                else if(escolha_cliente == 2){


                    printf("\nInforme qual automovel desejas encontrar. (Utilize o codigo do automovel)");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoAC);

                    system("cls");
                    printf("Buscando sequencialmente...\n");
                    BuscaSequencialAutomovel(carros, procuradoAC, ArquivoLOG);
                }
                else {
                    printf("\nOpcao invalida, tente novamente\n");
                }
            break;

            case 4:
                DevolverAutomovelCliente(carros, clientes);
            break;

            case 5:
                imprimirBaseClientes(clientes);
            break;

            case 6:
                printf("Ordenando base de dados...");
                Selection_Sort_Clientes_Disco(clientes, ArquivoLOG);
                system("cls");
                printf("Base de dados ordenada\n");
            break;

            case 7:
                system("cls");
                printf("Informe quantos registros do arquivo serao lidos para a memoria.\n");
                printf("Sua escolha: ");
                scanf("%d", &NP);

                int NPcriadas = SelecaoNaturalCliente(clientes, NP, ArquivoLOG);
                printf("Numero de particoes criadas: %d\n", NPcriadas+1);

                printf("\nComecando a parte da intercalacao otima...\n");
                IntercalacaoOtimaCliente(NPcriadas, "Clientes.dat", ArquivoLOG);
                printf("\nClassificacao Externa Finalizada\n");
            break;

            case 8:
                system("cls");
                printf("Saindo da area destinada a Clientes...");
                printf("\n------------------------------------------------------------------------------------------------------\n");
                end = false;
            break;
            
            default:
                printf("\nOpcao invalida, tente novamente\n");        
            break;

        }

    }while(end);

    fclose(carros);
    fclose(funcionarios);

}

void Switch_Funcionarios(FILE* func, FILE *ArquivoLOG){

    system("cls");

    bool end = true;
    int escolha_func = 0;
    int procuradoF = 0; 
    int escolha_cli = 0;
    int procuradoC = 0;
    int NP = 0;

    FILE *clientes = fopen("Clientes.dat", "r+b");
    if (clientes == NULL) {
        printf("Erro ao abrir o arquivo Clientes.dat\n");
        return;
    }

    FILE *carros = fopen("Automoveis.dat", "r+b");
    if(carros == NULL){
        printf("Erro ao abrir o arquivo Automoveis.dat\n");
        return;
    }

    do{

        switch(Menu_Funcionarios()){

            case 1:{

                system("cls");
                printf("Caso queira criar um funcionario novo, certifique-se que a base ja estara criada para a utilizar a busca binaria");
                printf("\nOu caso necessite criar o funcionario primeiro, lembre-se de utilizar a busca sequencial\n");
                TFuncionario *f = (TFuncionario*)malloc(sizeof(TFuncionario));
                criaFuncionariosManual(f, func);
            }
            break;

            case 2:
                printf("\nDe que maneira voce quer procurar um funcionario?\n");
                printf("\n[1] Busca Binaria\n[2] Busca Sequencial\n");
                
                printf("Sua escolha: ");
                scanf("%d", &escolha_func);
                
                if(escolha_func == 1){

                    printf("\nInforme qual funcionario desejas encontrar. (Utilize o codigo do funcionario)");
                    printf("\nOBSERVACAO: Para utilizar essa busca certifique-se que sua base esta ordenada");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoF);

                    system("cls");
                    printf("\nBuscando binariamente...\n");
                    BuscaBinariaFunc(procuradoF, func, ArquivoLOG);
                }
                else if(escolha_func == 2){

                    printf("\nInforme qual funcionario desejas encontrar. (Utilize o codigo do funcionario)");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoF);

                    system("cls");
                    printf("\nBuscando sequencialmente...\n");
                    BuscaSequencialFuncionario(func, procuradoF, ArquivoLOG);
                }
                else {
                    printf("\nOpcao invalida, tente novamente\n"); 
                }
            break;

            case 3:

                printf("Informe qual funcionario, voce deseja mudar as informacoes. (Utilize o codigo do funcionario)");
                printf("\nEscolha: ");
                scanf("%d", &procuradoF);

                TFuncionario *p = NULL;
                int posicao = (int)BuscaSequencialEditarFunc(func, procuradoF, NULL, &p);

                if(posicao != -1){
                    criaFuncionariosManual(p, NULL); 
                    fseek(func, posicao * sizeof(TFuncionario), SEEK_SET); 
                    salvarFuncionario(p, func); 
                    imprimefuncionario(p);

                    rewind(carros); 
                    TCarros *carro;
                    while((carro = leitura_arquivo_carros(carros)) != NULL){
                        if(carro->funcionario.codigo == procuradoF){
                            carro->funcionario = *p;
                            fseek(carros, -sizeof(TCarros), SEEK_CUR);
                            salvarAutomoveis(carro, carros);
                        }
                        free(carro);
                    }
                    free(carro);
                }

            break;

            case 4:
                printf("\nDe que maneira voce quer procurar um cliente cadastrado?\n");
                printf("\n[1] Busca Binaria\n[2] Busca Sequencial\n");

                printf("Sua escolha: ");
                scanf("%d", &escolha_cli);

                if(escolha_cli == 1){

                    printf("\nInforme qual cliente desejas encontrar. (Utilize o codigo do cliente)");
                    printf("\nOBSERVACAO: Para utilizar essa busca certifique-se que sua base esta ordenada");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoC);

                    system("cls");
                    printf("Buscando binariamente...\n");
                    BuscaBinariaCliente(procuradoC, clientes, ArquivoLOG);
                }
                else if(escolha_cli == 2){

                    printf("\nInforme qual cliente desejas encontrar. (Utilize o codigo do cliente)");
                    printf("\nEscolha: ");
                    scanf("%d", &procuradoC);

                    system("cls");
                    printf("Buscando sequencialmente...\n");
                    BuscaSequencialCliente(clientes, procuradoC, ArquivoLOG);
                }
                else {
                    printf("\nOpcao invalida, tente novamente\n"); 
                }
            break;

            case 5: {
                printf("\nInforme qual cliente, voce deseja mudar as informacoes. (Utilize o codigo do cliente)");
                printf("\nEscolha: ");
                scanf("%d", &procuradoC);

                TCliente *cli = NULL;
                int posicao = (int)BuscaSequencialEditarCliente(clientes, procuradoC, NULL, &cli);

                if(posicao != -1){
                    criaClienteManual(cli, NULL); 
                    fseek(clientes, posicao * sizeof(TCliente), SEEK_SET); 
                    salvarCliente(cli, clientes); 
                    imprimecliente(cli);

                    rewind(carros);
                    TCarros *carro;
                    while((carro = leitura_arquivo_carros(carros)) != NULL){
                        if(carro->cliente.codigo == procuradoC){
                            carro->cliente = (*cli);
                            fseek(carros, -sizeof(TCarros), SEEK_CUR);
                            salvarAutomoveis(carro, carros);
                        }
                        free(carro);
                    }
                    free(carro);
                }
            }
            break;

            case 6:
                imprimirBaseFuncionarios(func);
            break;

            case 7:
                printf("Ordenando base de dados...");
                Selection_Sort_Funcionario_Disco(func, ArquivoLOG);
                system("cls");
                printf("Base de dados ordenada\n");
            break;

            case 8:
                system("cls");
                printf("Informe quantos registros do arquivo serao lidos para a memoria.\n");
                printf("Sua escolha: ");
                scanf("%d", &NP);

                int NPcriadas = SelecaoNaturalFuncionario(func, NP, ArquivoLOG);
                printf("Numero de particoes criadas: %d\n", NPcriadas+1);

                printf("\nComecando a parte da intercalacao otima...\n");
                IntercalacaoOtimaFuncionario(NPcriadas,"Funcionarios.dat", ArquivoLOG);
                printf("\nClassificacao Externa Finalizada\n");
            break;

            case 9:
                system("cls");
                printf("Saindo da area destinada a Funcionarios...");
                printf("\n------------------------------------------------------------------------------------------------------\n");
                end = false;
            break;

            default:
                printf("\nOpcao invalida, tente novamente\n");        
            break;

        }

    }while(end);
    
    fclose(clientes);

}
#endif