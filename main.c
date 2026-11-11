#include"Arvore.h"

void menu(Arv *L, Eqp *hash[]){
    int escolha, verifica = 1;

    do{
        printf("\n");
        printf("  ╔══════════════════════════════════════════════════════╗\n");
        printf("  ║                                                      ║\n");
        printf("  ║               GERENCIAMENTO DE FALHAS                ║\n");
        printf("  ║             Equipamentos e incidentes                ║\n");
        printf("  ║                                                      ║\n");
        printf("  ╠══════════════════════════════════════════════════════╣\n");
        printf("  ║    [1]  Cadastrar equipamento                        ║\n");
        printf("  ║    [2]  Registrar incidente                          ║\n");
        printf("  ║    [3]  Consultar equipamento e incidente            ║\n");
        printf("  ║    [4]  Listar todos os incidentes                   ║\n");
        printf("  ║    [5]  Excluir incidente                            ║\n");
        printf("  ║    [6]  Excluir equipamento                          ║\n");
        printf("  ╠══════════════════════════════════════════════════════╣\n");
        printf("  ║    [0]  Encerrar programa                            ║\n");
        printf("  ╚══════════════════════════════════════════════════════╝\n");

        printf("\n  >> Opção escolhida: ");
        scanf("%d",&escolha);
        limpar_buffer();

        switch(escolha){
            case 1:
                pause();
                cadastroEqp(hash);
                break;

            case 2:
                pause();
                cadastroInc(hash,L);
                break;

            case 3:
                pause();
                imprimeHash(hash,L);
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 0:
                printf("encerrando programa.");
                pause();
                verifica = 0;
                break;
            default:
                printf("\n  [ERRO] Opção inválida. Escolha um valor entre 0 e 6.\n");
                pause();
                break;
            }
    }while(verifica);

}

void insereDadosTeste(Arv *L, Eqp *hash[]) {

    // EQUIPAMENTO 1
    Eqp *eqp1 = malloc(sizeof(Eqp));
    eqp1->codeEqp = 1001;
    strcpy(eqp1->nicknameEqp, "Motor");
    eqp1->prox = NULL;
    eqp1->inicioID = NULL;
    insereHash(hash, eqp1);

    // EQUIPAMENTO 2
    Eqp *eqp2 = malloc(sizeof(Eqp));
    eqp2->codeEqp = 2002;
    strcpy(eqp2->nicknameEqp, "Bomba");
    eqp2->prox = NULL;
    eqp2->inicioID = NULL;
    insereHash(hash, eqp2);

    // EQUIPAMENTO 3
    Eqp *eqp3 = malloc(sizeof(Eqp));
    eqp3->codeEqp = 3003;
    strcpy(eqp3->nicknameEqp, "Sensor");
    eqp3->prox = NULL;
    eqp3->inicioID = NULL;
    insereHash(hash, eqp3);


    // INCIDENTE 1
    noArv *inc1 = malloc(sizeof(noArv));
    inc1->numIdem = 50;
    inc1->codeEqpArv = 1001;
    inc1->gravLevel = 1;
    inc1->esq = NULL;
    inc1->dir = NULL;
    insereArv(L, inc1);
    insereIDHash(hash, inc1);

    // INCIDENTE 2
    noArv *inc2 = malloc(sizeof(noArv));
    inc2->numIdem = 30;
    inc2->codeEqpArv = 2002;
    inc2->gravLevel = 2;
    inc2->esq = NULL;
    inc2->dir = NULL;
    insereArv(L, inc2);
    insereIDHash(hash, inc2);

    // INCIDENTE 3
    noArv *inc3 = malloc(sizeof(noArv));
    inc3->numIdem = 70;
    inc3->codeEqpArv = 1001;
    inc3->gravLevel = 3;
    inc3->esq = NULL;
    inc3->dir = NULL;
    insereArv(L, inc3);
    insereIDHash(hash, inc3);

    // INCIDENTE 4
    noArv *inc4 = malloc(sizeof(noArv));
    inc4->numIdem = 20;
    inc4->codeEqpArv = 1001;
    inc4->gravLevel = 2;
    inc4->esq = NULL;
    inc4->dir = NULL;
    insereArv(L, inc4);
    insereIDHash(hash, inc4);

    // INCIDENTE 5
    noArv *inc5 = malloc(sizeof(noArv));
    inc5->numIdem = 40;
    inc5->codeEqpArv = 2002;
    inc5->gravLevel = 3;
    inc5->esq = NULL;
    inc5->dir = NULL;
    insereArv(L, inc5);
    insereIDHash(hash, inc5);

    // INCIDENTE 6
    noArv *inc6 = malloc(sizeof(noArv));
    inc6->numIdem = 60;
    inc6->codeEqpArv = 3003;
    inc6->gravLevel = 1;
    inc6->esq = NULL;
    inc6->dir = NULL;
    insereArv(L, inc6);
    insereIDHash(hash, inc6);

    // INCIDENTE 7
    noArv *inc7 = malloc(sizeof(noArv));
    inc7->numIdem = 80;
    inc7->codeEqpArv = 1001;
    inc7->gravLevel = 3;
    inc7->esq = NULL;
    inc7->dir = NULL;
    insereArv(L, inc7);
    insereIDHash(hash, inc7);

    // INCIDENTE 8
    noArv *inc8 = malloc(sizeof(noArv));
    inc8->numIdem = 10;
    inc8->codeEqpArv = 3003;
    inc8->gravLevel = 2;
    inc8->esq = NULL;
    inc8->dir = NULL;
    insereArv(L, inc8);
    insereIDHash(hash, inc8);

    // INCIDENTE 9
    noArv *inc9 = malloc(sizeof(noArv));
    inc9->numIdem = 35;
    inc9->codeEqpArv = 1001;
    inc9->gravLevel = 1;
    inc9->esq = NULL;
    inc9->dir = NULL;
    insereArv(L, inc9);
    insereIDHash(hash, inc9);

    // INCIDENTE 10
    noArv *inc10 = malloc(sizeof(noArv));
    inc10->numIdem = 65;
    inc10->codeEqpArv = 2002;
    inc10->gravLevel = 2;
    inc10->esq = NULL;
    inc10->dir = NULL;
    insereArv(L, inc10);
    insereIDHash(hash, inc10);

    printf("\n[OK] Dados de teste inseridos com sucesso!\n");
}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Arv *L = criaArv();
    Eqp *hash[43];
    inicializaHash(hash);

    insereDadosTeste(L, hash);

    menu(L,hash);

    return 0;
}
