#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE *arquivo;


typedef struct{
    char nome[50];
    int cpf;
    int qtd_pet;

}Cliente;

typedef struct{
    char nome[50];
    int idade;
    int tipo;

}Pet;

typedef struct{
    char nome[50];
    float preco;

}Equipamento;

typedef struct{
    Pet *petAtendido;
    Cliente *clienteAtendido;
    Equipamento *equipamentoAtendido;
    char tipoAtendido[50];

}Atendimento;



int main(){
    float *preco = malloc(sizeof(float));
    *preco = 0;
    Atendimento atendimento;

    int opMenu = 1;
    atendimento.clienteAtendido = malloc(sizeof(Cliente));
    atendimento.petAtendido = malloc(sizeof(Pet));
    while(opMenu != 0){
        opMenu = menu();
        switch(opMenu){
            case 1:{
                cadastroCliente(&atendimento, preco);
                break;
            }
            case 2:{
                consultaAtendimento(&atendimento);
                break;
            }

            default:{
                printf("Foi nao");
                break;
            }

        }
    }
    preco = 0;
    free(preco);
    preco = NULL;
    free(atendimento.clienteAtendido);
    atendimento.clienteAtendido = NULL;
    free(atendimento.petAtendido);
    atendimento.petAtendido = NULL;



    return 0;
}

int menu(){
    int op;
    printf("[1]Registrar atendimento\n[2]Consultar atendimento\n>> ");
    scanf("%d", &op);
    return op;
}

void consultaAtendimento(Atendimento *atendimento){
    arquivo = fopen("text.txt", "r");
    char c = fgetc(arquivo);
    if(c == EOF){
        printf("Tem nada nao!\n");
    }
    else{
        while(c != EOF){
            printf("%c", c);
            c = fgetc(arquivo);
        }
    }

}

void cadastroCliente(Atendimento *atendimento, float *preco){
    printf("---------------------------\n");
    printf("Digite o nome do cliente: ");
    scanf("%s", atendimento->clienteAtendido->nome);
    printf("Digite o CPF: ");
    scanf("%d", &atendimento->clienteAtendido->cpf);
    printf("Quantidade de Pets: ");
    scanf("%d", &atendimento->clienteAtendido->qtd_pet);
    cadastroPet(atendimento, preco);



}

void cadastroPet(Atendimento *atendimento, float *preco){
    int qtd_pet_cadastro = atendimento->clienteAtendido->qtd_pet;

    Pet pet[10];
    int op;
    printf("\n- - - -Cadastro do PET - - - -\n");
    for(int i = 0; i < qtd_pet_cadastro; i++){
        printf("Nome do pet %d: ", i + 1);
        scanf("%s", pet[i].nome);
        printf("Idade do pet %d: ", i + 1);
        scanf("%d", &pet[i].idade);
        printf("Tipo: \n[1] Cachorro\n[2] Gato\n[3] Urso\n[4] Jaguatirica\n[5] Hamster\n>> ");
        scanf("%d", &pet[i].tipo);
        printf("- Pet registrado! -\n\n");
    }
    printf("Para qual deseja atendimento: \n");
    for(int i = 0; i < qtd_pet_cadastro; i++){
        printf("(%d)%s\n", i + 1, pet[i].nome);
    }
    printf(">> ");
    scanf("%d", &op);
    atendimento->petAtendido[0] = pet[op-1];
    cadastroAtendimento(atendimento, preco);
}

void cadastroAtendimento(Atendimento *atendimento, float *preco){
    char cliente[50];
    char bicho[50];
    strcpy(cliente, atendimento->clienteAtendido->nome);
    strcpy(bicho, atendimento->petAtendido->nome);



    printf("\nCliente: %s\n", cliente);
    printf("\nBicho: %s\n", bicho);
    tipoServico(atendimento, preco);


}

void tipoServico(Atendimento *atendimento, float *preco){
    int op = 0;
    printf("Qual servico deseja?\n[1] Banho\n[2] Tosa\n[3] Consulta\n>> ");
    scanf("%d", &op);
    if(op == 1){
        printf("Vamo banhar teu bicho\n");
        strcpy(atendimento->tipoAtendido, "Banho - 80R$");
        *preco += 80.00;

    }
    else if(op == 2){
        printf("Vamo rapar e tudo\n");
        strcpy(atendimento->tipoAtendido, "Tosa - 50R$");
        *preco += 50.00;
    }
    else{
        printf("Vamo consultar o bicho\n");
        strcpy(atendimento->tipoAtendido, "Consulta - 300R$");
        *preco += 300.0;

    }

    printArquivo(atendimento, preco);

}

void equipamentos(Atendimento *atendimento , int op, float *preco){
        if(op == 1){
            fprintf(arquivo, "Toalha - 6.00R$\n");
            *preco += 6.0;
        }
        else if(op == 2){
            fprintf(arquivo, "Luva Pelo - 15.00R$\n");
            *preco += 15.0;

        }
        else if(op == 3){
            fprintf(arquivo, "Sabonete - 2.0R$\n");
            *preco += 2.0;
        }
        else{
            fprintf(arquivo, "Coleira - 5.0R$\n");
            *preco += 5.0;
        }


}

printArquivo(Atendimento *atendimento, float *preco){

    int op;
    arquivo = fopen("text.txt", "a");
    fprintf(arquivo, "-------------------------------\n");
    fprintf(arquivo, "Nome do cliente: %s\n", atendimento->clienteAtendido->nome);
    fprintf(arquivo, "Nome do pet: %s\n", atendimento->petAtendido->nome);
    fprintf(arquivo, "Servico solicitado: %s\n", atendimento->tipoAtendido);
    fprintf(arquivo, "Equipamentos: \n");
    do{
        printf("\nQuais equipamentos?");
        printf("\n[1] Toalha descartavel\n[2] Luva Pelo\n[3] Sabonete\n[4] Coleira\n>> ");
        scanf("%d", &op);
        equipamentos(atendimento , op, preco);
        printf("\nMais algum equipamento?\n");
        printf("[0] - Nao\n[1] - Sim\n>>");
        scanf("%d", &op);
    }
    while(op != 0);

    fprintf(arquivo,"Preco: %.2fR$\n-------------------------------\n\n", *preco);
    fclose(arquivo);
}

