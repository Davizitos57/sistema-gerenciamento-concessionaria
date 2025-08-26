#include "headers\assinaturas_gerais.h"
#include "headers\assinaturas_automoveis.h"
#include "headers\assinaturas_funcionarios.h"
#include "headers\assinaturas_clientes.h"
#include "headers\busca_sequencial.h"

int tamanho_cliente(){    
    return ((sizeof(char) * 50) + (sizeof(char) * 20) + (sizeof(char) * 20) + (sizeof(char) * 50));
}

//Função para calcular o tamanho do arquivo de clientes
int tamanho_arquivo_clientes(FILE *out){
    fseek(out, 0, SEEK_END);
    int tamanho = ftell(out) / sizeof(TCliente);
    return tamanho;
}

//Função para ler um cliente do arquivo
TCliente *leitura_arquivo_cliente(FILE *in) {
    TCliente *cliente = (TCliente *)malloc(sizeof(TCliente));
    if (fread(cliente, sizeof(TCliente), 1, in) != 1) {
        free(cliente);
        return NULL;
    }
    return cliente;
}

//Função para salvar um cliente no arquivo
void salvarCliente(TCliente *cliente, FILE *out) {
    fwrite(cliente, sizeof(TCliente), 1, out);
    fflush(out);
}

//Função para criar um cliente manualmente
TCliente *criaClienteManual (TCliente *cliente, FILE *out){

    if(cliente == NULL){
        cliente = (TCliente *)malloc(sizeof(TCliente)); 
        if(cliente == NULL){
            printf("Erro ao alocar memoria para cliente.\n");
            exit(1);
        }
    }

    while(getchar() != '\n');

    printf("\nDigite o nome do cliente: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';

    printf("\nDigite o CPF do cliente: ");
    fgets(cliente->cpf, sizeof(cliente->cpf), stdin);
    cliente->cpf[strcspn(cliente->cpf, "\n")] = '\0';

    while(getchar() != '\n');

    printf("\nDigite o telefone do cliente: ");
    fgets(cliente->telefone, sizeof(cliente->telefone), stdin);
    cliente->telefone[strcspn(cliente->telefone, "\n")] = '\0';

    printf("\nDigite o endereco do cliente: ");
    fgets(cliente->endereco, sizeof(cliente->endereco), stdin);
    cliente->endereco[strcspn(cliente->endereco, "\n")] = '\0';

    printf("\nDigite o codigo do cliente: ");
    scanf("%d", &cliente->codigo);
    getchar(); 

    if(out != NULL){
        fseek(out, 0, SEEK_END);
        salvarCliente(cliente, out);
    }
    return cliente;

}

//Função para criar um cliente com parâmetros
TCliente *criaCliente(char *nome, char *cpf, char *telefone, char *endereco, int codigo){

    TCliente *c = (TCliente *)malloc(sizeof(TCliente));
    if(c == NULL){
        printf("\nErro ao alocar memoria para cliente.\n");
        exit(1);
    }

    strcpy(c->nome, nome);
    strcpy(c->cpf, cpf);
    strcpy(c->telefone, telefone);
    strcpy(c->endereco, endereco);
    c->codigo = codigo;

    return c;
}

//Função para criar uma base ordenada de clientes
void criarBaseOrdenadaCliente(FILE *out, int tamanho){
    
    int vet[tamanho];
    TCliente *c;

    for(int i = 0; i < tamanho; i++){
        vet[i] = i+1;
    }

    printf("\nGerando a base de dados de clientes...");

    for(int i = 0; i < tamanho; i++){
        c = criaCliente("Cliente Ficticio", "222.222.222-22", "11 91234-1234", "Cidade ABC - Bairro DEF - Rua GHI", vet[i]);
        salvarCliente(c,out);
    }

    free(c);
}

//Função para criar uma base embaralhada de clientes
void criarBaseEmbaralhadaCliente(FILE *out, int tamanho){
    
    int vet[tamanho];
    TCliente *c;

    for(int i = 0; i < tamanho; i++){
        vet[i] = i+1;
    }

    embralhabases(vet, tamanho);

    printf("\nGerando a base de dados de clientes...");

    for(int i = 0; i < tamanho; i++){
        c = criaCliente("Cliente Ficticio", "222.222.222-22", "11 91234-1234", "Cidade ABC - Bairro DEF - Rua GHI", vet[i]);
        salvarCliente(c,out);
    }

    free(c);
}

// Função para imprimir um cliente
void imprimecliente(TCliente *c) {
    printf("\n| Nome do cliente: %s\n| CPF: %s\n| Telefone: %s\n", c->nome, c->cpf , c->telefone);
    printf("| Endereco: %s\n", c->endereco); 
    printf("| Codigo do cliente: %d\n", c->codigo);
    printf("\n\n==============================================================================\n\n");  

}

//Função para imprimir a base de um cliente
void imprimirBaseClientes (FILE *out){
    system("cls");
    
    printf("\tDados referentes aos clientes\n\n");

    rewind(out);

    TCliente *c;

    while((c = leitura_arquivo_cliente(out)) != NULL){
        imprimecliente(c);
    }
    free(c);
}

//Função para alugar um automóvel para um cliente
void AlugarAutomovelCliente (FILE *carros, FILE *clientes, FILE *funcionarios){

    system("cls");
    imprimirBaseCarrosDisponiveis(carros);

    int codigoAutomovel, codigoFunc;

    TCarros *carro = NULL;
    TFuncionario *funcionario = NULL;
    TCliente *cliente = (TCliente *)malloc(sizeof(TCliente));

    if(cliente == NULL){
        printf("Erro ao alocar memoria para cliente.\n");
        exit(1);
    }

    criaClienteManual(cliente, clientes);

    printf("\nDigite o codigo do automovel: ");
    scanf("%d", &codigoAutomovel);

    carro = BuscaSequencialAutomovel(carros, codigoAutomovel, NULL);
    if(carro == NULL){
        printf("Automovel nao encontrado.\n");
        free(cliente);
        return;
    }

    if (carro->situacao == ALUGADO) {
        printf("\nAutomovel ja esta alugado por outro cliente.\n");
        free(cliente);
        free(carro);
        return;
    }

    if(carro->situacao == VENDIDO){
        printf("\nAutomovel ja foi vendido para outro cliente.\n");
        free(cliente);
        free(carro);
        return;
    }

    printf("\nDigite o codigo do funcionario responsavel pelo aluguel do automovel: ");
    scanf("%d", &codigoFunc);

    funcionario = BuscaSequencialFuncionario(funcionarios, codigoFunc, NULL);
    if(funcionario == NULL){
        printf("Funcionario nao encontrado.\n");
        free(cliente);
        return;
    }

    carro->cliente = *cliente;
    carro->funcionario = *funcionario;
    carro->situacao = -1;

    // Salvar automóvel atualizado
    fseek(carros, -sizeof(TCarros), SEEK_CUR);
    salvarAutomoveis(carro, carros);

    printf("Automovel associado ao cliente com sucesso.\n");

    free(cliente);
    free(carro);
    free(funcionario);
}

// Função para vender um automóvel para um cliente
void ComprarAutomovelCliente (FILE *carros, FILE *clientes, FILE *funcionarios){

    system("cls");
    imprimirBaseCarrosDisponiveis(carros);

    int codigoAutomovel, codigoFunc;

    TCarros *carro = NULL;
    TFuncionario *funcionario = NULL;
    TCliente *cliente = (TCliente *)malloc(sizeof(TCliente));

    if(cliente == NULL){
        printf("Erro ao alocar memoria para cliente.\n");
        exit(1);
    }

    criaClienteManual(cliente, clientes);

    printf("\nDigite o codigo do automovel: ");
    scanf("%d", &codigoAutomovel);

    carro = BuscaSequencialAutomovel(carros, codigoAutomovel, NULL);
    if(carro == NULL){
        printf("Automovel nao encontrado.\n");
        free(cliente);
        return;
    }

    if (carro->situacao == ALUGADO) {
        printf("\nAutomovel ja esta alugado por outro cliente.\n");
        free(cliente);
        free(carro);
        return;
    }

    if (carro->situacao == VENDIDO) {
        printf("\nAutomovel ja foi vendido para outro cliente.\n");
        free(cliente);
        free(carro);
        return;
    }

    printf("\nDigite o codigo do funcionario responsavel pela venda do automovel: ");
    scanf("%d", &codigoFunc);

    funcionario = BuscaSequencialFuncionario(funcionarios, codigoFunc, NULL);
    if(funcionario == NULL){
        printf("Funcionario nao encontrado.\n");
        free(cliente);
        return;
    }

    carro->cliente = *cliente;
    carro->funcionario = *funcionario;
    carro->situacao = 1;

    // Salvar automóvel atualizado
    fseek(carros, -sizeof(TCarros), SEEK_CUR);
    salvarAutomoveis(carro, carros);

    printf("Automovel associado ao cliente com sucesso.\n");

    free(cliente);
    free(carro);
    free(funcionario);
}

//Função para fazer a devolução de um automóvel alugado por um cliente
void DevolverAutomovelCliente(FILE *carros, FILE *clientes) {
    
    int codigo_cliente = 0;
    int codigo_automovel = 0;
    TCarros *carro = NULL;
    TCliente *cliente = NULL;

    printf("\nPor favor, para devolver o automovel alugado, insira algumas informacoes.");
    printf("\nDigite o codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    // Buscar cliente
    rewind(clientes);
    while ((cliente = leitura_arquivo_cliente(clientes)) != NULL) {
        if (cliente->codigo == codigo_cliente) {
            break;
        }
        free(cliente);
        cliente = NULL;
    }

    if (cliente == NULL) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("\nDigite o codigo do automovel: ");
    scanf("%d", &codigo_automovel);

    // Buscar automóvel
    rewind(carros);
    while ((carro = leitura_arquivo_carros(carros)) != NULL) {
        if (carro->codigo == codigo_automovel) {
            break;
        }
        free(carro);
        carro = NULL;
    }

    if (carro == NULL) {
        printf("Automovel nao encontrado.\n");
        free(cliente);
        return;
    }

    if (carro->situacao == ALUGADO && carro->cliente.codigo == codigo_cliente) {
        // Atualizar a situação do carro para disponível
        carro->situacao = DISPONIVEL;
        memset(&carro->cliente, 0, sizeof(TCliente));
        memset(&carro->funcionario, 0, sizeof(TFuncionario));

        // Salvar carro atualizado
        fseek(carros, -sizeof(TCarros), SEEK_CUR);
        salvarAutomoveis(carro, carros);

        printf("Carro devolvido com sucesso.\n");
    } else if (carro->situacao == VENDIDO) {
        printf("Esse carro foi vendido e nao pode ser devolvido.\n");
    } else {
        printf("Esse carro nao foi alugado por esse cliente.\n");
    }

    free(cliente);
    free(carro);
}