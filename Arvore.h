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

typedef struct listaIDs{
    int ID;
    struct listaIDs *prox;
}IDs;

typedef struct infosEquipamento{
    int codeEqp;
    char nicknameEqp[11];
    struct infosEquipamento *prox;
    IDs *inicioID;
}Eqp;


// INICIALIZAÇAO/LIBERAÇAO DE LISTA E HASH
Arv *criaArv() {
    Arv *aux = (Arv*)malloc(sizeof(Arv));
    aux -> raiz = NULL;
    return aux;
}

void inicializaHash(Eqp *hash[]){
    for(int i = 0; i < 43; i++){
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
    return code%43;
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
    novo -> inicioID = NULL;

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
int arvVazia(Arv *L){
    if(L -> raiz == NULL){
        return 1;
    }
    return 0;
}

noArv *auxInsereArv(Arv *L, noArv *novo){
    noArv *pai = L -> raiz;

    if(arvVazia(L)){
        return novo;
    }

    while(1){
        if(novo -> numIdem > pai -> numIdem){
            if(pai -> dir == NULL){
                pai -> dir = novo;
                return L -> raiz;
            }
            else{
                pai = pai -> dir;
            }
        }
        else{
            if(pai -> esq == NULL){
                pai -> esq = novo;
                return L -> raiz;
            }
            else{
                pai = pai -> esq;
            }
        }
    }
}

void insereArv(Arv *L, noArv *novo){
    L -> raiz = auxInsereArv(L,novo);
}

int confereNumIdemArv(Arv *L,int code){
    noArv *pai = L -> raiz;

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
void insereNumIdemInc(Arv *L, noArv *novo){
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
            if(confereNumIdemArv(L,novo -> numIdem))
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
void insereIDHash(Eqp *hash[],noArv *novo){
    IDs *novoID = (IDs*)malloc(sizeof(IDs));
    novoID -> prox = NULL;
    novoID -> ID = novo -> numIdem;

    int pos = funcHash(novo -> codeEqpArv);
    Eqp *aux = hash[pos];

    while(aux -> codeEqp != novo -> codeEqpArv){
        aux = aux -> prox;
    }

    IDs *aux2 = aux -> inicioID;

    if(aux2 == NULL){
        aux -> inicioID = novoID;
    }
    else{
        while(aux2 -> prox != NULL){
            aux2 = aux2 -> prox;
        }
        aux2 -> prox = novoID;
    }
}

void editaInfoInc(Eqp *hash[],Arv *L,noArv *novo)
{
    int escolha, verifica = 0;

    do
    {
        escolha = -1;
        printf("\n");
        printf("  ╔══════════════════════════════════════════════════════╗\n");
        printf("  ║                                                      ║\n");
        printf("  ║              EDITAR DADOS DO INCIDENTE               ║\n");
        printf("  ║         Selecione o campo que deseja editar          ║\n");
        printf("  ║                                                      ║\n");
        printf("  ╠══════════════════════════════════════════════════════╣\n");
        printf("  ║    [1]  Número de identificação                      ║\n");
        printf("  ║    [2]  Código do equipamento                        ║\n");
        printf("  ║    [3]  Nível de gravidade                           ║\n");
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
                insereNumIdemInc(L,novo);
                printf("\n  [OK] Número de identificação editado com sucesso.\n");
                pause();
                break;

            case 2:
                insereCodeEqp(hash,novo);
                printf("\n  [OK] Nome(apelido) editado com sucesso.\n");
                pause();
                break;

            case 3:
                insereGravLevel(novo);
                printf("\n  [OK] Gravidade editada com sucesso.\n");
                pause();
                break;

            case 0:
                verifica = 1;
                break;

            default:
                printf("\n  [ERRO] Opção inválida. Escolha um valor entre 0 e 3.\n");
                pause();
                break;
        }
    }while(verifica == 0);
}

void cadastroInc(Eqp *hash[], Arv *L){
    int verifica,escolha;
    noArv *novo = (noArv*)malloc(sizeof(noArv));
    novo -> esq = NULL;
    novo -> dir = NULL;

    insereNumIdemInc(L,novo);
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
        printf("  ║  Código do equipamento  : %-28d║\n", novo -> codeEqpArv);
        printf("  ║  Nível de gravidade     : %-28s║\n", printaGrav(novo -> gravLevel));
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
                insereArv(L,novo);
                insereIDHash(hash,novo);
                printf("\n  [OK] Solicitação cadastrada com sucesso.\n");
                pause();
                break;

            case 2:
                pause();
                editaInfoInc(hash,L,novo);
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

//IMPRESSÃO SOLICITAÇÃO E INCIDENTES

noArv *buscaArv(Arv *L, int ID) {
    noArv *aux = L -> raiz;
    while(aux != NULL) {
        if(aux -> numIdem != ID) {
            if(aux -> numIdem < ID) {
                aux = aux -> dir;
            }
            else {
                aux = aux -> esq;
            }
        }
        else {
            return aux;
        }
    }
    return NULL;
}

void imprimeHash(Eqp *hash[], Arv *L) {
    noArv *aux;
    Eqp *auxEqp;
    IDs *auxID;
    for(int i = 0; i<43;i++) {
            auxEqp = hash[i];
            while(auxEqp != NULL) {
                    printf("código de identificação do equipamento: %d \n" "Nome do equipamento: %s \n",auxEqp -> codeEqp, auxEqp -> nicknameEqp);
                    auxID = auxEqp->inicioID;
                    while(auxID != NULL) {
                        aux = buscaArv(L, auxID -> ID);
                        if(aux != NULL) {
                            printf("Numero de identificação do incidente: %d \n" "gravidade: %s \n",aux -> numIdem, printaGrav(aux->gravLevel));
                            printf("\n");
                        }
                        auxID = auxID->prox;
                    }
                auxEqp = auxEqp -> prox;
            }
    }
}






#endif // ARVORE_H_INCLUDED
