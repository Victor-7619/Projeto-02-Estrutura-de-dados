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
    int codeEqp;
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

noArv *criaNo(){
    noArv *novo = (noArv*)malloc(sizeof(noArv));
    novo -> esq = NULL;
    novo -> dir = NULL;

    printf("\nDigite Numero de identificação: ");
    scanf("%d",&novo -> numIdem);
    printf("\nDigite Code Equipamento relacionado: ");
    scanf("%d",&novo -> codeEqp);
    printf("\nDigite gravLevel: ");
    scanf("%d",&novo -> gravLevel);

    return novo;
}

int arvVazia(Arv *p){
    if(p -> raiz == NULL){
        return 1;
    }
    return 0;
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



//INSERIR NA ARVORE
noArv *auxInsereArv(Arv *arvore, noArv *novo, int *boolean){
    noArv *pai = arvore -> raiz;

    if(arvVazia(arvore)){
        *boolean = 1;
        return novo;
    }

    int flag = 0;

    while(!flag){
        if(novo -> numIdem == pai -> numIdem){
            *boolean = 0;
            return arvore -> raiz;
        }
        if(novo -> numIdem > pai -> numIdem){
            if(pai -> dir == NULL){
                pai -> dir = novo;
                flag = 1;
            }
            else{
                pai = pai -> dir;
            }
        }
        else{
            if(pai -> esq == NULL){
                pai -> esq = novo;
                flag = 1;
            }
            else{
                pai = pai -> esq;
            }
        }
    }
    *boolean = 1;
    return arvore -> raiz;
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
        if(code < pai -> numIdem){
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
int confereLista(Eqp *inicio,Eqp *novo){
    while(inicio != NULL){
        if(inicio -> codeEqp == novo -> codeEqp){
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


//INSERÇÃO DE INFORMAÇÕES
int confereNumIdemHash(Eqp *hash[], Eqp *novo){
    int pos = funcHash(novo -> codeEqp);

    if(confereLista(hash[pos],novo)){
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

        printf("\n  [01/02] NÚMERO DE IDENTIFICAÇÃO DO INCIDENTE\n");
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
            if(confereNumIdemHash(hash,novo))
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


//Edição
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
        printf("  ║                   NOVA SOLICITAÇÃO                    ║\n");
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

#endif // ARVORE_H_INCLUDED
