#ifndef FUNCIONARIOS_C
#define FUNCIONARIOS_C

#include "..\cabecalho\assinaturas_funcionarios.h"

int tamanho_funcionario(){
    
    return ((sizeof(char) * 50) + (sizeof(char) * 15) + (sizeof(char) * 20) + (sizeof(char) * 50) + (sizeof(int)) + (sizeof(double)));
}

int tamanho_arquivo_funcionarios(FILE *out){
    fseek(out, 0, SEEK_END);
    int tamanho = ftell(out) / sizeof(TFuncionario);
    return tamanho;
}   

TFuncionario *leitura_arquivo_funcionario(FILE *in){
    TFuncionario *func = (TFuncionario *)malloc(sizeof(TFuncionario));
    if(fread(func, sizeof(TFuncionario), 1 ,in) != 1){
        free(func);
        return NULL;
    }

    return func;
}

void salvarFuncionario(TFuncionario *func, FILE *out){
    fwrite(func, sizeof(TFuncionario), 1, out);
    fflush(out);
}

TFuncionario *criaFuncionariosManual(TFuncionario *func, FILE *out){

    if(func == NULL){
        func = (TFuncionario *)malloc(sizeof(TFuncionario)); 
        if(func == NULL){
            printf("Erro ao alocar memoria para cliente.\n");
            exit(1);
        }
    }

    func->ocupado = true;
    
    while(getchar() != '\n'); 

    printf("\nDigite o nome do funcionario: ");
    fgets(func->nome, sizeof(func->nome), stdin);
    func->nome[strcspn(func->nome, "\n")] = '\0';

    printf("\nDigite o CPF do funcionario: ");
    fgets(func->cpf, sizeof(func->cpf), stdin);
    func->cpf[strcspn(func->cpf, "\n")] = '\0';

    while(getchar() != '\n'){};

    printf("\nDigite o telefone do funcionario: ");
    fgets(func->telefone, sizeof(func->telefone), stdin);
    func->telefone[strcspn(func->telefone, "\n")] = '\0';

    printf("\nDigite o endereco do funcionario: ");
    fgets(func->endereco, sizeof(func->endereco), stdin);
    func->endereco[strcspn(func->endereco, "\n")] = '\0'; 

    printf("\nDigite o salario do funcionario: ");
    scanf("%lf", &func->salario);
    getchar(); 

    rewind(out);
    TFuncionario *existeFunc = NULL;

    while((existeFunc = leitura_arquivo_funcionario(out)) != NULL){
        if(!existeFunc->ocupado){
            func->codigo = existeFunc->codigo;
            fseek(out, -sizeof(TFuncionario), SEEK_CUR);
            salvarFuncionario(func, out);
            free(existeFunc);
            return func;
        }
        free(existeFunc);
    }

    fseek(out, 0, SEEK_END);
    func->codigo = tamanho_arquivo_funcionarios(out)+1;
    salvarFuncionario(func, out);
    
    return func;

}

TFuncionario *criaFuncionarios(char *nome, char *cpf, char *telefone, char *endereco, int codigo, double salario){


    TFuncionario *func = (TFuncionario*)malloc(sizeof(TFuncionario));

    if(func == NULL){

        printf("\nErro ao alocar memoria para func.\n");

        exit(1);
    }
    
    strcpy(func -> nome, nome);
    strcpy(func -> cpf, cpf);
    strcpy(func -> telefone, telefone);
    strcpy(func -> endereco, endereco);

    func -> codigo = codigo;
    func -> salario = salario;

    func -> ocupado = true;

    return func;
}

void criarBaseOrdenadaFuncionario(FILE *out, int tamanho){

    int vet[tamanho];
    TFuncionario *f;

    for(int i=0;i<tamanho;i++)
        vet[i] = i+1;

    printf("\nGerando a base de dados de funcionarios...");

    for (int i=0;i<tamanho;i++){

        f = criaFuncionarios("Funcionario Ficticio", "000.000.000-00", "00 90000-0000", "Cidade ZZZ - Bairro YYY - Rua XXX - Numero 000", vet[i], 3000*(i+1));
        salvarFuncionario(f, out);
    }

    free(f);
}

void criarBaseEmbaralhadaFuncionario(FILE *out, int tamanho){


    int vet[tamanho];
    TFuncionario *f;

    for(int i=0;i<tamanho;i++)
        vet[i] = i+1;


    embralhabases(vet, tamanho);

    printf("\nGerando a base de dados de funcionarios...");

    for (int i=0;i<tamanho;i++){

        f = criaFuncionarios("Funcionario Ficticio", "000.000.000-00", "00 90000-0000", "Cidade ZZZ - Bairro YYY - Rua XXX - Numero 000", vet[i], 3000*(i+1));
        salvarFuncionario(f, out);
    }

    free(f);
}

void imprimefuncionario(TFuncionario *f) {

    printf("\n| Nome do funcionario: %s\n| CPF: %s\n| Telefone: %s\n", f->nome, f->cpf , f->telefone);
    printf("| Endereco: %s\n", f->endereco); 
    printf("| Salario: %.2f\n| Codigo do funcionario: %d\n", f->salario, f->codigo);

    printf("\n\n==============================================================================\n\n");  

}

void imprimirBaseFuncionarios(FILE *out){

    system("cls");

    printf("\tDados referentes aos funcionarios\n\n");

    rewind(out);

    TFuncionario *f;

    while((f = leitura_arquivo_funcionario(out)) != NULL){
        imprimefuncionario(f);
    }
    free(f);
}
#endif