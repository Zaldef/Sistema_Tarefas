#include <stdlib.h>
#include <stdio.h>
#include "OurLibrary.h"

int main(){
    // TADS
    Fila *F1 = inicializarFila();
    Fila *F2 = inicializarFila();
    Fila *F3 = inicializarFila();
    Lista *LP = inicializarLista();
    Lista *LC = inicializarLista();
    // carregando data
    const char *Arq_F1 = "database_F1.txt";
    const char *Arq_F2 = "database_F2.txt";
    const char *Arq_F3 = "database_F3.txt";
    carregarFila(Arq_F1,F1);
    carregarFila(Arq_F2,F2);
    carregarFila(Arq_F3,F3);
    
    // variaveis auxiliares
    Tarefa AuxT;
    No *AuxNo;
    int AuxInt;
    int flag;
    // variaveis do loop principal do program
    int opcao = 0;
    int end = 0;

    void menu();

    while (end == 0){
        menu();
        scanf("%d", &opcao);
        system("cls");
        verificarStatus(F1,F2,F3);
    switch (opcao){

        case 1:
            printf("Adicionar uma nova tarefa\n");
            AuxT = novaTarefa(F1,F2,F3,LP,LC);
            // inserir na fila correta
            if(AuxT.prioridade == 1){
                inserirFila(F1,AuxT);
            }else if(AuxT.prioridade == 2){
                inserirFila(F2,AuxT);
            }else if(AuxT.prioridade == 3){
                inserirFila(F3,AuxT);
            }
            printf("\n\tTarefa adicionada com sucesso!\n\t");
            system("pause");
        break;

        case 2:
            printf("Listar tarefas\n");
            printf("\n==================Fila de tarefas===================\n");
            printf("\n\t=========Prioridade Alta===========\n");
            imprimirFila(F1);
            printf("\n\t=========Prioridade Normal=========\n");
            imprimirFila(F2);
            printf("\n\t=========Prioridade Baixa==========\n");
            imprimirFila(F3);
            system("pause");
        break;

        case 3:
            printf("Modificar uma tarefa\n");
            printf("\n==================Fila de tarefas===================\n");
            printf("\n\t=========Prioridade Alta===========\n");
            imprimirFila(F1);
            printf("\n\t=========Prioridade Normal=========\n");
            imprimirFila(F2);
            printf("\n\t=========Prioridade Baixa==========\n");
            imprimirFila(F3);
            printf("\n==============Lista de tarefas pendentes============\n");
            imprimirLista(LP);
            AuxInt = editar(F1,F2,F3,LP);
            if(AuxInt == -1){
                printf("\n\tTarefa não encontrada\n\t");
                system("pause");
            }
        break;

        case 4:
            printf("Concluir uma tarefa\n");
            printf("\n==================Fila de tarefas===================\n");
            printf("\n\t=========Prioridade Alta===========\n");
            imprimirFila(F1);
            printf("\n\t=========Prioridade Normal=========\n");
            imprimirFila(F2);
            printf("\n\t=========Prioridade Baixa==========\n");
            imprimirFila(F3);

            AuxInt = buscarNoFila(F1, F2, F3, &flag);
            if(AuxInt == -1){
                printf("\n\tTarefa nao encontrada\n\t");
                system("pause");
            }else if(AuxInt >0){
                if(flag == 1){
                    F1 = removerNoFila(F1,AuxInt,&AuxNo);
                    LC = inserirNoListaConcluida(LC,AuxNo);
                }else if(flag == 2){
                    F2 = removerNoFila(F2,AuxInt,&AuxNo);
                    LC = inserirNoListaConcluida(LC,AuxNo);
                }else if(flag == 3){
                    F3 = removerNoFila(F3,AuxInt,&AuxNo);
                    LC = inserirNoListaConcluida(LC,AuxNo);
                }
                system("pause");
            }
        break;

        case 5:
            printf("Adicionar tarefa pendente\n");
            printf("\n==================Fila de tarefas===================\n");
            printf("\n\t=========Prioridade Alta===========\n");
            imprimirFila(F1);
            printf("\n\t=========Prioridade Normal=========\n");
            imprimirFila(F2);
            printf("\n\t=========Prioridade Baixa==========\n");
            imprimirFila(F3);
            AuxInt = buscarNoFila(F1, F2, F3, &flag);
            if(AuxInt == -1){
                printf("\n\tTarefa nao encontrada\n\t");
                system("pause");
            }else if(AuxInt >0){
                if(flag == 1){
                    F1 = removerNoFila(F1,AuxInt,&AuxNo);
                    AuxNo->info.status = -1;
                    LP = inserirNoListaPendente(LP,AuxNo);
                }else if(flag == 2){
                    F2 = removerNoFila(F2,AuxInt,&AuxNo);
                    AuxNo->info.status = -1;
                    LP = inserirNoListaPendente(LP,AuxNo);
                }else if(flag == 3){
                    F3 = removerNoFila(F3,AuxInt,&AuxNo);
                    AuxNo->info.status = -1;
                    LP = inserirNoListaPendente(LP,AuxNo);
                }
                system("pause");
            }
        break;

        case 6:
            printf("Remover tarefa pendente\n");
            imprimirLista(LP);
            AuxInt = buscarNoPendente(LP);
            if(AuxInt == -1){
                printf("\n\tTarefa nao encontrada\n\t");
                system("pause");
            }else if(AuxInt >0){ // remover da lista pendente e inserir na fila correta
                AuxNo = removerNoLista(LP,AuxInt);
                AuxNo->info.status = 0;
                if(AuxNo->info.prioridade == 1){
                    F1 = inserirNoFila(F1,AuxNo);
                }else if(AuxNo->info.prioridade == 2){
                    F2 = inserirNoFila(F2,AuxNo);
                }else if(AuxNo->info.prioridade == 3){
                    F3 = inserirNoFila(F3,AuxNo);
                }
                printf("\n\tTarefa removida com sucesso!\n\t");
                system("pause");
            }
        break;


        case 7:
            printf("Listar tarefas pendentes\n");
            imprimirLista(LP);
            system("pause");
        break;

        case 8:
            imprimirListaConcluidas(LC);
        break;

        case 0:
            salvarFila(Arq_F1, F1);
            salvarFila(Arq_F2, F2);
            salvarFila(Arq_F3, F3);
            liberarFila(F1);
            liberarFila(F2);
            liberarFila(F3);
            liberarLista(LP);
            liberarLista(LC);
            end = 1;
        break;

        default:
            printf("Opcao invalida\n");
        break;

        }
    }
}

void menu(){
    system("cls");
    printf("\n\t1 - Adicionar uma nova tarefa");
    printf("\n\t2 - Listar tarefas");
    printf("\n\t3 - Modificar uma tarefa");
    printf("\n\t4 - Concluir uma tarefa");
    printf("\n\t5 - Adicionar tarefa pendente");
    printf("\n\t6 - Remover tarefa pendente");
    printf("\n\t7 - Listar tarefas pendentes");
    printf("\n\t8 - Listar tarefas concluidas");
    //printf("\n\t9 - Excluir tarefa");
    printf("\n\t0 - Sair do programa\n");
}
