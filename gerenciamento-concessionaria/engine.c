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
#include "tabelas_hashs\tabela_hash_geral.c"
#include "tabelas_hashs\tabela_hash_automoveis.c"
#include "tabelas_hashs\tabela_hash_clientes.c"
#include "tabelas_hashs\tabela_hash_funcionarios.c"
#include "menu.c"

void seletor(FILE* automoveis, FILE* clientes, FILE* funcionarios, FILE *ArquivoLOG){

    bool end = true;

    FILE *tabelaHashAuto = fopen("TabelaHashAuto.dat", "r+b");
    FILE *listaEncadeadaAuto = fopen("ListaEncadeadaAuto.dat", "r+b");

    FILE *tabelaHashCliente = fopen("TabelaHashCliente.dat", "r+b");
    FILE *listaEncadeadaCliente = fopen("ListaEncadeadaCliente.dat", "r+b");
        
    FILE *tabelaHashFunc = fopen("TabelaHashFunc.dat", "r+b");
    FILE *listaEncadeadaFunc = fopen("ListaEncadeadaFunc.dat", "r+b");

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
                Switch_TabelaHash(tabelaHashAuto, tabelaHashCliente, tabelaHashFunc, listaEncadeadaAuto, listaEncadeadaCliente, listaEncadeadaFunc);
            break;

            case 5:
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

void Switch_TabelaHash(FILE *tabelaHashAuto, FILE *tabelaHashCliente, FILE *tabelaHashFunc, FILE *listaEncadeadaAuto, FILE *listaEncadeadaCliente, FILE *listaEncadeadaFunc){

    system("cls");

    bool end = true;
    bool end2 = true;
    int escolha = 0;
    int acharHash = 0;

    FILE *carros = fopen("Automoveis.dat", "r+b");
    FILE *clientes = fopen("Clientes.dat", "r+b");
    FILE *funcionarios = fopen("Funcionarios.dat", "r+b");

    if(carros == NULL){
        printf("Erro ao abrir o arquivo Automoveis.dat\n");
        return;
    }

    if(clientes == NULL){
        printf("Erro ao abrir o arquivo Clientes.dat\n");
        return;
    }

    if(funcionarios == NULL){
        printf("Erro ao abrir o arquivo Funcionarios.dat\n");
        return;
    }

    inicializaTabelaHashFuncionarios(tabelaHashFunc, listaEncadeadaFunc, funcionarios);
    inicializaTabelaHashCliente(tabelaHashCliente, listaEncadeadaCliente, clientes);
    inicializaTabelaHashAutomoveis(tabelaHashAuto, listaEncadeadaAuto, carros);

    do{
        switch(Menu_TabelaHash()){

            case 1:
                system("cls");
                
                do{

                    printf("--------------------------------------------------------------------------------\n");
                    printf("          Seja Bem-vindo(a) a area destinada a Tabela Hash Automoveis           \n");
                    printf("--------------------------------------------------------------------------------\n\n");
            

                    printf("[1] Adicionar Automovel na Tabela Hash.\n[2] Buscar Automovel na Tabela Hash.\n[3] Deletar Automovel na Tabela Hash.\n");
                    printf("[4] Imprime a Tabela Hash de Automoveis.\n[5] Sair da area destinada a Tabela Hash Automoveis.\n\n");

                    printf("Sua escolha: ");
                    scanf("%d", &escolha);

                    if(escolha == 1){
                        TCarros *carroNovo = criaAutomoveisManual(NULL, carros);
                        inserirAutomovelHash(tabelaHashAuto, listaEncadeadaAuto, carroNovo);
                        system("cls");
                        printf("Carro adicionado!\n\n");
                    }
                    else if(escolha == 2){
                        printf("\nDigite o codigo do Automovel que desejas buscar.\n");
                        printf("Escolha: ");
                        scanf("%d", &acharHash);

                        TCarros *carroAchado = buscaAutomovelHash(tabelaHashAuto, listaEncadeadaAuto, acharHash);
                        if(carroAchado!=NULL){
                            int hashlocalizacao = FuncaoHash(acharHash);
                            system("cls");
                            printf("Automovel achado na Tabela Hash:\n");
                            imprimirCarro(carroAchado);
                            printf("Esse Automovel se encontra no Compartimento [%d].\n\n", hashlocalizacao);
                            free(carroAchado);
                        }
                        else{
                            system("cls");
                            printf("Automovel nao foi achado na Tabela Hash.\n\n");
                        }
                    }
                    else if(escolha == 3){
                        printf("\nDigite o codigo do Automovel que desejas deletar.\n");
                        printf("Escolha: ");
                        scanf("%d", &acharHash);

                        if(deletarAutomovelHash(tabelaHashAuto, listaEncadeadaAuto, carros, acharHash)){
                            system("cls");
                            printf("Automovel com codigo %d foi removido com sucesso.\n\n", acharHash);
                        }
                        else{
                            system("cls");
                            printf("Automovel com codigo %d nao foi encontrado na Tabela Hash.\n\n", acharHash);
                        }
                    }
                    else if(escolha == 4){
                        imprimirTabelaHash(tabelaHashAuto, listaEncadeadaAuto);
                    }
                    else if(escolha == 5){
                        system("cls");
                        printf("Saindo da area destinada a Tabela Hash Automoveis...\n");
                        end2 = false;
                    }
                    else{
                        printf("\nOpcao invalida, tente novamente\n");   
                    }
                }
                while(end2);

            break;

            case 2:
                system("cls");
                
                do{

                    printf("--------------------------------------------------------------------------------\n");
                    printf("          Seja Bem-vindo(a) a area destinada a Tabela Hash Clientes             \n");
                    printf("--------------------------------------------------------------------------------\n\n");
            

                    printf("[1] Adicionar Clientes na Tabela Hash.\n[2] Buscar Clientes na Tabela Hash.\n[3] Deletar Clientes na Tabela Hash.\n");
                    printf("[4] Imprime a Tabela Hash de Clientes.\n[5] Sair da area destinada a Tabela Hash Clientes.\n\n");

                    printf("Sua escolha: ");
                    scanf("%d", &escolha);

                    if(escolha == 1){
                        TCliente *clienteNovo = criaClienteManual(NULL, clientes);
                        inserirClienteHash(tabelaHashCliente, listaEncadeadaCliente, clienteNovo);
                        system("cls");
                        printf("Cliente adicionado!\n\n");
                    }
                    else if(escolha == 2){
                        printf("\nDigite o codigo do Cliente que desejas buscar.\n");
                        printf("Escolha: ");
                        scanf("%d", &acharHash);

                        TCliente *clienteAchado = buscaClienteHash(tabelaHashCliente, listaEncadeadaCliente, acharHash);
                        if(clienteAchado!=NULL){
                            int hashlocalizacao = FuncaoHash(acharHash);
                            system("cls");
                            printf("Cliente achado na Tabela Hash:\n");
                            imprimecliente(clienteAchado);
                            printf("Esse Cliente se encontra no Compartimento [%d].\n\n", hashlocalizacao);
                            free(clienteAchado);
                        }
                        else{
                            system("cls");
                            printf("Cliente nao foi achado na Tabela Hash.\n\n");
                        }
                    }
                    else if(escolha == 3){
                        printf("\nDigite o codigo do Cliente que desejas deletar.\n");
                        printf("Escolha: ");
                        scanf("%d", &acharHash);

                        if(deletarClienteHash(tabelaHashCliente, listaEncadeadaCliente, clientes, acharHash)){
                            system("cls");
                            printf("Cliente com codigo %d foi removido com sucesso.\n\n", acharHash);
                        }
                        else{
                            system("cls");
                            printf("Cliente com codigo %d nao foi encontrado na Tabela Hash.\n\n", acharHash);
                        }
                    }
                    else if(escolha == 4){
                        imprimirTabelaHashCliente(tabelaHashCliente, listaEncadeadaCliente);
                    }
                    else if(escolha == 5){
                        system("cls");
                        printf("Saindo da area destinada a Tabela Hash Cliente...\n");
                        end2 = false;
                    }
                    else{
                        printf("\nOpcao invalida, tente novamente\n");   
                    }
                }
                while(end2);
            break;

            case 3:
                system("cls");

                do{

                    printf("--------------------------------------------------------------------------------\n");
                    printf("          Seja Bem-vindo(a) a area destinada a Tabela Hash Funcionarios          \n");
                    printf("--------------------------------------------------------------------------------\n\n");
            

                    printf("[1] Adicionar Funcionario na Tabela Hash.\n[2] Buscar Funcionario na Tabela Hash.\n[3] Deletar Funcionario na Tabela Hash.\n");
                    printf("[4] Imprime a Tabela Hash de Funcionario.\n[5] Sair da area destinada a Tabela Hash Funcionario.\n\n");

                    printf("Sua escolha: ");
                    scanf("%d", &escolha);

                    if(escolha == 1){
                        TFuncionario *funcNovo = criaFuncionariosManual(NULL, funcionarios);
                        inserirFuncionarioHash(tabelaHashFunc, listaEncadeadaFunc, funcNovo);
                        system("cls");
                        printf("Funcionario adicionado!\n\n");
                    }
                    else if(escolha == 2){
                        printf("\nDigite o codigo do Funcionario que desejas buscar.\n");
                        printf("Escolha: ");
                        scanf("%d", &acharHash);

                        TFuncionario *funcAchado = buscaFuncionarioHash(tabelaHashFunc, listaEncadeadaFunc, acharHash);
                        if(funcAchado!=NULL){
                            int hashlocalizacao = FuncaoHash(acharHash);
                            system("cls");
                            printf("Funcionario achado na Tabela Hash:\n");
                            imprimefuncionario(funcAchado);
                            printf("Esse Funcionario se encontra no Compartimento [%d].\n\n", hashlocalizacao);
                            free(funcAchado);
                        }
                        else{
                            system("cls");
                            printf("Funcionario nao foi achado na Tabela Hash.\n\n");
                        }
                    }
                    else if(escolha == 3){
                        printf("\nDigite o codigo do Funcionario que desejas deletar.\n");
                        printf("Escolha: ");
                        scanf("%d", &acharHash);

                        if(deletarFuncionarioHash(tabelaHashFunc, listaEncadeadaFunc, funcionarios, acharHash)){
                            system("cls");
                            printf("Funcionario com codigo %d foi removido com sucesso.\n\n", acharHash);
                        }
                        else{
                            system("cls");
                            printf("Funcionario com codigo %d nao foi encontrado na Tabela Hash.\n\n", acharHash);
                        }
                    }
                    else if(escolha == 4){
                        imprimirTabelaHashFunc(tabelaHashFunc, listaEncadeadaFunc);
                    }
                    else if(escolha == 5){
                        system("cls");
                        printf("Saindo da area destinada a Tabela Hash Funcionario...\n");
                        end2 = false;
                    }
                    else{
                        printf("\nOpcao invalida, tente novamente\n");   
                    }
                }
                while(end2);
            break;

            case 4:
                system("cls");
                printf("Saindo da area destinada a Tabela Hash...");
                printf("\n------------------------------------------------------------------------------------------------------\n");
                end = false;
            break;

            default:
                printf("\nOpcao invalida, tente novamente\n");        
            break;
        }
    }
    while(end);
}
#endif