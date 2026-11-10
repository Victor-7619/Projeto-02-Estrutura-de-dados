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

int main(){
    SetConsoleOutputCP(CP_UTF8);

    Arv *L = criaArv();
    Eqp *hash[101];
    inicializaHash(hash);

    menu(L,hash);

    return 0;
}
