#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<locale.h>
#include<string.h>

// STRUCT'S
typedef struct noArvore{
    int numIdem;
    int codeEqpArv;
    int gravLevel;
    struct noArvore *esq;
    struct noArvore *dir;
}noArv;

typedef struct baseArv{
    noArv *raiz;
}Arv;

typedef struct infosEquipamento{
    int codeEqp;
    char nicknameEqp[11];
    struct infosEquipamento *prox;
}Eqp;


// INICIALIZAÇAO/LIBERAÇAO DE LISTA E HASH
Arv *criaArv() {
    Arv *aux = (Arv*)malloc(sizeof(Arv));
    aux -> raiz = NULL;
    return aux;
}

void inicializaHash(Eqp *hash[]){
    for(int i = 0; i < 101; i++){
        hash[i] = NULL;
    }
}


//AUXILIARES
void pause(){
    printf("\n\n");
    system("pause");
    system("cls");
}

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

char *printaGrav(int grav)
{
    switch (grav) {
        case 1:
            return "baixa";

        case 2:
            return "media";

        case 3:
            return "alta";
    }
}


//INSERIR NA ARVORE
int arvVazia(Arv *p){
    if(p -> raiz == NULL){
        return 1;
    }
    return 0;
}

noArv *auxInsereArv(Arv *arvore, noArv *novo){
    noArv *pai = arvore -> raiz;

    if(arvVazia(arvore)){
        return novo;
    }

    while(1){
        if(novo -> numIdem > pai -> numIdem){
            if(pai -> dir == NULL){
                pai -> dir = novo;
                return arvore -> raiz;
            }
            else{
                pai = pai -> dir;
            }
        }
        else{
            if(pai -> esq == NULL){
                pai -> esq = novo;
                return arvore -> raiz;
            }
            else{
                pai = pai -> esq;
            }
        }
    }
}

int insereArv(Arv *arv, noArv *novo){
    int boolean;
    arv -> raiz = auxInsereArv(arv, novo,&boolean);
    return boolean;
}

int confereNumIdemArv(Arv *p,int code){
    noArv *pai = p -> raiz;

    if(pai == NULL)
    {
        return 0;
    }

    while(1){
        if(pai -> numIdem == code){
            return 1;
        }
        if(pai -> numIdem > code){
            if(pai -> esq == NULL){
                return 0;
            }
            pai = pai -> esq;
        }
        else{
            if(pai -> dir == NULL){
                return 0;
            }
            pai = pai -> dir;
        }
    }
}


//CADASTRO DE EQUIPAMENTO
//hash
int confereLista(Eqp *inicio,int codeEqp){
    while(inicio != NULL){
        if(inicio -> codeEqp == codeEqp){
            return 1;
        }
        inicio = inicio -> prox;
    }
    return 0;
}

int funcHash(int code){
    return code%101;
}

void insereHash(Eqp *hash[], Eqp *novo){
    int pos = funcHash(novo -> codeEqp);

    if(hash[pos] == NULL){
        hash[pos] = novo;
    }
    else{
        novo -> prox = hash[pos];
        hash[pos]= novo;
    }
}


//inserção de informações
int confereNumIdemHash(Eqp *hash[], int code){
    int pos = funcHash(code);

    if(confereLista(hash[pos],code)){
        return 1;
    }
    return 0;
}

void insereNumIdem(Eqp *hash[], Eqp *novo){
    int entrada,verifica;
    do
    {
        entrada = 1;
        verifica = 0;

        printf("\n  [01/02] NÚMERO DE IDENTIFICAÇÃO DO EQUIPAMENTO\n");
        printf("  > Informe o código (1000 a 9999): ");

        scanf("%d",&entrada);
        limpar_buffer();

        if(entrada < 1000 || entrada > 9999)
        {
            verifica = 1;
            printf("\n  [ERRO] O código deve conter 4 dígitos.\n");
            pause();
        }
        else
        {
            novo -> codeEqp = entrada;
            if(confereNumIdemHash(hash,novo -> codeEqp))
            {
                verifica = 1;
                printf("\n  [ERRO] Código já cadastrado.\n");
                pause();
            }
        }
    }while(verifica == 1);

}

void insereNicknameEqp(Eqp *hash[], Eqp *novo){
    char entrada[100];
    do
    {
        printf("\n  [02/02] NOME DO EQUIPAMENTO\n");
        printf("  > Informe o nome (máximo 10 caracteres): ");
        fgets(entrada,sizeof(entrada),stdin);

        if(strlen(entrada) > 11)
        {
            printf("\n  [ERRO] O nome deve conter no máximo 10 caracteres.\n");
            pause();
        }
    }while(strlen(entrada) > 11);

    entrada[strcspn(entrada, "\n")] = '\0';
    strcpy(novo -> nicknameEqp, entrada);
}


//Cadastro e edição
void editaInfoEqp(Eqp *hash[],Eqp *novo)
{
    int escolha, verifica = 0;

    do
    {
        escolha = -1;
        printf("\n");
        printf("  ╔══════════════════════════════════════════════════════╗\n");
        printf("  ║                                                      ║\n");
        printf("  ║             EDITAR DADOS DO EQUIPAMENTO              ║\n");
        printf("  ║         Selecione o campo que deseja editar          ║\n");
        printf("  ║                                                      ║\n");
        printf("  ╠══════════════════════════════════════════════════════╣\n");
        printf("  ║    [1]  Número de identificação                      ║\n");
        printf("  ║    [2]  Nome (apelido)                               ║\n");
        printf("  ╠══════════════════════════════════════════════════════╣\n");
        printf("  ║    [0]  Retornar                                     ║\n");
        printf("  ╚══════════════════════════════════════════════════════╝\n");
        printf("\n  >> Opção escolhida: ");

        scanf("%d",&escolha);
        limpar_buffer();

        pause();

        switch(escolha)
        {
            case 1:
                insereNumIdem(hash,novo);
                printf("\n  [OK] Número de identificação editado com sucesso.\n");
                pause();
                break;

            case 2:
                insereNicknameEqp(hash,novo);
                printf("\n  [OK] Nome(apelido) editado com sucesso.\n");
                pause();
                break;

            case 0:
                verifica = 1;
                break;

            default:
                printf("\n  [ERRO] Opção inválida. Escolha um valor entre 0 e 2.\n");
                pause();
                break;
        }
    }while(verifica == 0);
}

void cadastroEqp(Eqp *hash[]){
    int verifica, escolha;;

    Eqp *novo = (Eqp*)malloc(sizeof(Eqp));
    novo -> prox = NULL;

    insereNumIdem(hash,novo);
    insereNicknameEqp(hash,novo);

    pause();
    do
    {
        verifica = 0;
        escolha = -1;

        printf("\n");
        printf("  ╔═══════════════════════════════════════════════════════╗\n");
        printf("  ║                                                       ║\n");
        printf("  ║                   NOVA INSERÇÃO                       ║\n");
        printf("  ║         Confira os dados antes de confirmar           ║\n");
        printf("  ║                                                       ║\n");
        printf("  ╠═══════════════════════════════════════════════════════╣\n");
        printf("  ║  Número  de identificação:%-28d║\n", novo -> codeEqp);
        printf("  ║  Nome (apelido)       :  %-28s ║\n", novo -> nicknameEqp);
        printf("  ╠═══════════════════════════════════════════════════════╣\n");
        printf("  ║  [1]  Confirmar cadastro                              ║\n");
        printf("  ║  [2]  Editar Informações do equipamento               ║\n");
        printf("  ║  [3]  Cancelar cadastro                               ║\n");
        printf("  ╚═══════════════════════════════════════════════════════╝\n");
        printf("\n  >> Opção escolhida: ");
        scanf("%d",&escolha);
        limpar_buffer();

        switch(escolha)
        {
            case 1:
                insereHash(hash,novo);
                printf("\n  [OK] Solicitação cadastrada com sucesso.\n");
                pause();
                break;

            case 2:
                pause();
                editaInfoEqp(hash,novo);
                verifica = 1;
                break;

            case 3:
                free(novo);
                printf("\n  [AVISO] Solicitação cancelada.\n");
                pause();
                break;

            default:
                printf("\n  [ERRO] Opção inválida. Escolha entre 1 e 3.\n");
                pause();
                verifica = 1;
                break;
        }
    }while(verifica == 1);

}


//REGISTRO DE INCIDENTE
//Árvore
int arvVazia(Arv *p){
    if(p -> raiz == NULL){
        return 1;
    }
    return 0;
}

noArv *auxInsereArv(Arv *arvore, noArv *novo){
    noArv *pai = arvore -> raiz;

    if(arvVazia(arvore)){
        return novo;
    }

    while(1){
        if(novo -> numIdem > pai -> numIdem){
            if(pai -> dir == NULL){
                pai -> dir = novo;
                return arvore -> raiz;
            }
            else{
                pai = pai -> dir;
            }
        }
        else{
            if(pai -> esq == NULL){
                pai -> esq = novo;
                return arvore -> raiz;
            }
            else{
                pai = pai -> esq;
            }
        }
    }
}

void insereArv(Arv *arv, noArv *novo){
    arv -> raiz = auxInsereArv(arv, novo,&boolean);
}

int confereNumIdemArv(Arv *p,int code){
    noArv *pai = p -> raiz;

    if(pai == NULL)
    {
        return 0;
    }

    while(1){
        if(pai -> numIdem == code){
            return 1;
        }
        if(pai -> numIdem > code){
            if(pai -> esq == NULL){
                return 0;
            }
            pai = pai -> esq;
        }
        else{
            if(pai -> dir == NULL){
                return 0;
            }
            pai = pai -> dir;
        }
    }
}


//inserção de informações
void insereNumIdemInc(Arv *pai, noArv *novo){
    int entrada,verifica;
    do
    {
        entrada = 1;
        verifica = 0;

        printf("\n  [01/03] NÚMERO DE IDENTIFICAÇÃO DO INCIDENTE\n");
        printf("  > Informe o código (10 a 99: ");

        scanf("%d",&entrada);
        limpar_buffer();

        if(entrada < 10 || entrada > 99)
        {
            verifica = 1;
            printf("\n  [ERRO] O código deve conter 2 dígitos.\n");
            pause();
        }
        else
        {
            novo -> numIdem = entrada;
            if(confereNumIdemArv(pai,novo -> numIdem))
            {
                verifica = 1;
                printf("\n  [ERRO] Código já cadastrado.\n");
                pause();
            }
        }
    }while(verifica == 1);

}

void insereCodeEqp(Eqp *hash[], noArv *novo){
    int entrada,verifica;
    do
    {
        entrada = 1;
        verifica = 0;

        printf("\n  [02/03] NÚMERO DE IDENTIFICAÇÃO DO EQUIPAMENTO RELACIONADO\n");
        printf("  > Informe o código (1000 a 9999: ");

        scanf("%d",&entrada);
        limpar_buffer();

        if(entrada < 1000 || entrada > 9999)
        {
            verifica = 1;
            printf("\n  [ERRO] O código deve conter 4 dígitos.\n");
            pause();
        }
        else
        {
            novo -> codeEqpArv = entrada;
            if(!confereNumIdemHash(hash,novo -> codeEqpArv))
            {
                verifica = 1;
                printf("\n  [ERRO] Equipamento não encontrado.\n");
                pause();
            }
        }
    }while(verifica == 1);
}

void insereGravLevel(noArv *novo){
    int verifica;
    do
    {
        novo -> gravLevel = 1;
        verifica = 0;

        printf("\n  [03/03] GRAVIDADE DO INCIDENTE\n");
        printf("  [1] Baixa gravidade\n");
        printf("  [2] Média gravidade\n");
        printf("  [3] Alta gravidade\n");
        printf("\n  > Informe a gravidade (1 a 3): ");

        scanf("%d",&novo -> gravLevel);
        limpar_buffer();

        if(novo -> gravLevel < 1 || novo -> gravLevel > 3)
        {
            verifica = 1;
            printf("\n  [ERRO] Gravidade inválida. Escolha um valor entre 1 e 3.\n");
            pause();
        }
    }while(verifica == 1);
}


//Cadastro e edição
void cadastroInc(Eqp *hash[], Arv *raiz){
    int verifica,escolha;
    noArv *novo = (noArv*)malloc(sizeof(noArv));
    novo -> esq = NULL;
    novo -> dir = NULL;

    insereNumIdemInc(raiz,novo);
    insereCodeEqp(hash,novo);
    insereGravLevel(novo);

    pause();
    do
    {
        verifica = 0;
        escolha = -1;

        printf("\n");
        printf("  ╔═══════════════════════════════════════════════════════╗\n");
        printf("  ║                                                       ║\n");
        printf("  ║                   NOVO INCIDENTE                      ║\n");
        printf("  ║         Confira os dados antes de confirmar           ║\n");
        printf("  ║                                                       ║\n");
        printf("  ╠═══════════════════════════════════════════════════════╣\n");
        printf("  ║  Número de identificação: %-28d║\n", novo -> numIdem);
        printf("  ║  Código do equipamento : %-28d║\n", novo -> codeEqpArv);
        printf("  ║  Nível de gravidade    : %-28d║\n", printaGrav(novo -> gravLevel));
        printf("  ╠═══════════════════════════════════════════════════════╣\n");
        printf("  ║  [1]  Confirmar cadastro                              ║\n");
        printf("  ║  [2]  Editar informações do incidente                 ║\n");
        printf("  ║  [3]  Cancelar cadastro                               ║\n");
        printf("  ╚═══════════════════════════════════════════════════════╝\n");
        printf("\n  >> Opção escolhida: ");
        scanf("%d",&escolha);
        limpar_buffer();

        switch(escolha)
        {
            case 1:
                insereHash(hash,novo);
                printf("\n  [OK] Solicitação cadastrada com sucesso.\n");
                pause();
                break;

            case 2:
                pause();
                editaInfoEqp(hash,novo);
                verifica = 1;
                break;

            case 3:
                free(novo);
                printf("\n  [AVISO] Solicitação cancelada.\n");
                pause();
                break;

            default:
                printf("\n  [ERRO] Opção inválida. Escolha entre 1 e 3.\n");
                pause();
                verifica = 1;
                break;
        }
    }while(verifica == 1);
}

#endif // ARVORE_H_INCLUDED
