#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<locale.h>

// STRUCT'S
typedef struct noArvore{
    int numIdem;
    int codeEqp;
    int gravLevel;
    struct noArv *esq;
    struct noArv *dir;
}noArv;

typedef struct baseArv{
    noArv *raiz;
}Arv;

// INICIALIZAÇAO/LIBERAÇAO DE LISTA
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

//AUXILIARES
void pause()
{
    printf("\n\n");
    system("pause");
    system("cls");
}
void limpar_buffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}



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


#endif // ARVORE_H_INCLUDED
