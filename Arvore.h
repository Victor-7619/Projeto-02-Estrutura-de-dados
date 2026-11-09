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

int confereNumIdem(Arv *p,int code){
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


//HASH
int confereLista(Eqp *inicio,Eqp *novo){
    while(inicio != NULL){
        if(inicio -> codeEqp == novo -> codeEqp){
            return 0;
        }
        inicio = inicio -> prox;
    }
    return 1;
}

int funcHash(int code){
    return code%101;
}

int inserirHash(Eqp *novo, Eqp *hash[]){
    int pos = funcHash(novo -> codeEqp);

    if(hash[pos] == NULL){
        hash[pos] = novo;
        return 1;
    }
    if(confereLista(hash[pos],novo)){
        novo -> prox = hash[pos];
        hash[pos]= novo;
        return 1;
    }
    return 0;
}


//INSERÇÃO DE INFORMAÇÕES
void insereNumIdem(Arv *p, noArv *novo){
    int entrada;
    do
    {
        entrada = 1;
        verifica = 0;

        printf("\n  [01/05] NÚMERO DE IDENTIFICAÇÃO DO INCIDENTE\n");
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
            novo -> numIdem = entrada;
            if(VerCod(p,entrada))
            {
                verifica = 1;
                printf("\n  [ERRO] Código já cadastrado.\n");
                pause();
            }
        }
    }while(verifica == 1);

}


//CADASTRO DE EQUIPAMENTO


void cadastroEqp(Arv *L){

}

#endif // ARVORE_H_INCLUDED
