#ifndef ARVORE_H_INCLUDED
#define ARVORE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<locale.h>

typedef struct noArvore
{
    int info;
    struct noArv *esq;
    struct noArv *dir;
}noArv;

typedef struct Arvore
{
    noArv *raiz;
}


void insereArv(noArv *no,int num)
{
    int flag = 0;
    noArv *pai = no;
    noArv *novo = (*noArv)malloc(sizeof(Noarv));

    novo -> info = num;
    novo -> esq = NULL;
    novo -> dir = NULL;

    if(no == NULL)
    {
        return novo;
    }
    while(!flag)
    {
        if(num > pai -> info)
        {
            if(pai -> dir == NULL)
            {
                pai -> dir = novo;
                flag = 1;
            }
            else
            {
                pai = pai -> dir;
            }
        }
        else
        {
            if(num < pai ->info)
            {
                else
                {
                    if(pai -> esq == NULL)
                    {
                        pai -> esq = novo;
                        flag = 1;
                    }
                    else
                    {
                        pai = pai -> esq;
                    }
                }
            }
            else
            {

            }
        }
    }
}



#endif // ARVORE_H_INCLUDED
