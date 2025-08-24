#include "headers\assinaturas_gerais.h"
#include "headers\assinaturas_automoveis.h"
#include "headers\assinaturas_funcionarios.h"
#include "headers\assinaturas_clientes.h"

//Função para calcular o tamanho de um automóvel
int tamanho_automovel(){
    return ((sizeof(char) * 50) + (sizeof(char) * 20) + (sizeof(char) * 20) + (sizeof(int)) + (sizeof(double)) + 
    (sizeof(TFuncionario)) + (sizeof(TCliente)) + (sizeof(int)));
}

//Função para calcular o tamanho do arquivo de automóveis
int tamanho_arquivo_automovel(FILE *out){
    fseek(out, 0, SEEK_END);
    int tamanho = ftell(out) / sizeof(TCarros);
    return tamanho;
}

//Função para ler um automóvel do arquivo
TCarros *leitura_arquivo_carros(FILE *in){
    TCarros *carro = (TCarros *) malloc(sizeof(TCarros));

    if(fread(carro, sizeof(TCarros), 1, in) != 1){
        free(carro);
        return NULL;
    }

    if(carro->funcionario.nome[0] == '\0'){
        strcpy(carro->funcionario.nome, " - ");
    }
    if(carro->cliente.nome[0] == '\0'){
        strcpy(carro->cliente.nome, " - ");
    }

    return carro;
}

//Função para salvar um automóvel no arquivo
void salvarAutomoveis(TCarros *carro, FILE *out){
    fwrite(carro, sizeof(TCarros), 1, out);
    fflush(out);
}

//Função para criar um automóvel manualmente
TCarros *criaAutomoveisManual(TCarros *carro, FILE *out){

    if(carro == NULL){
        carro = (TCarros *)malloc(sizeof(TCarros)); 
        if(carro == NULL){
            printf("Erro ao alocar memoria para cliente.\n");
            exit(1);
        }
    }

    strcpy(carro->funcionario.nome, " - ");
    strcpy(carro->cliente.nome, " - ");

    while(getchar() != '\n'); 

    printf("\nDigite o nome do automovel: ");
    fgets(carro->nome, sizeof(carro->nome), stdin);
    carro->nome[strcspn(carro->nome, "\n")] = '\0';

    printf("\nDigite a marca do automovel: ");
    fgets(carro->marca_veiculo, sizeof(carro->marca_veiculo), stdin);
    carro->marca_veiculo[strcspn(carro->marca_veiculo, "\n")] = '\0';

    printf("\nDigite o modelo do automovel: ");
    fgets(carro->modelo_veiculo, sizeof(carro->modelo_veiculo), stdin);
    carro->modelo_veiculo[strcspn(carro->modelo_veiculo, "\n")] = '\0';

    printf("\nDigite o codigo do automovel: ");
    scanf("%d", &carro->codigo);
    getchar(); 

    printf("\nDigite o preco do automovel: ");
    scanf("%lf", &carro->preco);
    getchar(); 

    carro->funcionario.codigo = 0;
    carro->cliente.codigo = 0;
    carro->situacao = DISPONIVEL;

    if(out != NULL){
        fseek(out, 0, SEEK_END);
        salvarAutomoveis(carro, out);
    }
    return carro;

}

TCarros *criaAutomoveis(char *nome, char *marca, char *modelo, int codigo, double preco){

    TCarros *carro = (TCarros*)malloc(sizeof(TCarros));

    if(carro == NULL){
        printf("Erro ao alocar memoria para automoveis.");
        exit(1);
    }
    
    strcpy(carro -> nome, nome);
    strcpy(carro -> marca_veiculo, marca);
    strcpy(carro -> modelo_veiculo, modelo);
    carro -> codigo = codigo;
    carro -> preco = preco;
    memset(&carro->funcionario, 0, sizeof(TFuncionario));
    memset(&carro->cliente, 0, sizeof(TCliente));
    carro -> situacao = DISPONIVEL;

    return carro;
}

//Função para criar uma base ordenada de automóveis
void criarBaseOrdenadaCarros(FILE *out, int tamanho){
    
    int vet[tamanho];
    TCarros *cr;

    for(int i=0;i<tamanho;i++)
        vet[i] = i+1;

    printf("\nGerando a base de dados de automoveis...");

    for (int i=0;i<tamanho;i++){
        cr = criaAutomoveis("Automovel Ficticio", "Marca Ficticia", "Modelo Ficticio", vet[i], 10000*(i+1));
        salvarAutomoveis(cr, out);
    }

    free(cr);
}

//Função para criar uma base embaralhada de automóveis
void criarBaseEmbaralhadaCarros(FILE *out, int tamanho){
    
    int vet[tamanho];
    TCarros *cr;

    for(int i=0;i<tamanho;i++)
        vet[i] = i+1;

    embralhabases(vet, tamanho);

    printf("\nGerando a base de dados de automoveis...");

    for (int i=0;i<tamanho;i++){
        cr = criaAutomoveis("Automovel Ficticio", "Marca Ficticia", "Modelo Ficticio", vet[i], 10000*(i+1));
        salvarAutomoveis(cr, out);
    }

    free(cr);
}

//Função para imprimir os dados de um automóvel
void imprimirCarro(TCarros *carro){
    
    printf("\n| Nome do automovel: %s\n| Marca do automovel: %s\n| Modelo do automovel: %s\n", carro->nome, carro->marca_veiculo,carro->modelo_veiculo);
    printf("| Preco: %.2f\n| Funcionario Responsavel: %s\n", carro->preco, carro->funcionario.nome);
    printf("| Codigo do Funcionario: %d\n", carro->funcionario.codigo);
    printf("| Cliente: %s\n", carro->cliente.nome);
    printf("| Codigo do cliente: %d\n", carro->cliente.codigo);

    if(carro->situacao == 0){
        printf("| Situacao: DISPONIVEL\n");
    }
    else if(carro->situacao > 0){
        printf("| Situacao: VENDIDO\n");
    }
    else{
        printf("| Situacao: ALUGADO\n");
    }
    printf("| Codigo do Automovel: %d", carro->codigo);

    printf("\n\n==============================================================================\n\n");  
}

//Função para imprimir a base de dados dos automóveis
void imprimirBaseCarros(FILE *out){
    system("cls");
    
    printf("Dados referentes aos carros\n\n");

    rewind(out);

    TCarros *carro;
    while((carro = leitura_arquivo_carros(out)) != NULL){
        imprimirCarro(carro);
        free(carro);
    }
    free(carro);
}

//Função para imprimir a base de dados de automóveis alugados
void imprimirBaseCarrosAlugados(FILE *out){
    system("cls");

    printf("Imprimindo todas os dados referentes aos carros alugados no nosso sistema.\n");

    rewind(out);
    
    TCarros *carro;
    while((carro = leitura_arquivo_carros(out)) != NULL){
        if(carro->situacao == ALUGADO){
            imprimirCarro(carro);
        }
        free(carro);
    }
}

// Função para imprimir a base de dados de automóveis vendidos
void imprimirBaseCarrosVendidos(FILE *out){
    system("cls");

    printf("Imprimindo todas os dados referentes aos carros vendidos no nosso sistema.\n");

    rewind(out);
    
    TCarros *carro;
    while((carro = leitura_arquivo_carros(out)) != NULL){
        if(carro->situacao == VENDIDO){
            imprimirCarro(carro);
        }
        free(carro);
    }
}

void imprimirBaseCarrosDisponiveis(FILE *out){
    system("cls");

    printf("Imprimindo todas os dados referentes aos carros disponiveis no nosso sistema.\n");

    rewind(out);
    
    TCarros *carro;
    while((carro = leitura_arquivo_carros(out)) != NULL){
        if(carro->situacao == DISPONIVEL){
            imprimirCarro(carro);
        }
        free(carro);
    }
}