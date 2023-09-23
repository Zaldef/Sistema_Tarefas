#include <stdlib.h>
#include <stdio.h>
#include "FILA.h"
#include "TAREFA.h"
#include<stdbool.h>
#include <time.h>

#define NUM_CHAR 30

void menu();

int main(){
    Fila *F1 = CriaFila();
    bool end = false;
    while(end == false){
        menu();
        int opcao = 0;
        scanf("%d", &opcao);
        system("cls");
        InsereFilaTeste(F1);
        InsereFilaTeste(F1);
        InsereFilaTeste(F1);
        switch(opcao){
        case 1:
            printf("Adicionar uma nova tarefa\n");
            InsereFila(F1);
            break;
        case 2:
            printf("Modificar uma tarefa\n");
            editaFila(F1);
            break;
        case 3:
            printf("Concluir uma tarefa\n");
            break;
        case 4:
            printf("Atualizacao do status da tarefa\n");
            break;
        case 5:
            printf("Listar tarefas pendentes\n");
            ImprimeFila(F1);
            break;
        case 6:
            printf("Listar tarefas concluidas\n");
            break;
        case 7:
            printf("Listar tarefas concluidas com e sem atraso\n");
            break;
        case 8:
            printf("Sair do programa\n");
            end = true;
            break;
        default:
            printf("Opcao invalida\n");
            break;
}
    }
    return 0;
}

void menu(){
    printf("\n\t1 - Adicionar uma nova tarefa");
    printf("\n\t2 - Modificar uma tarefa");
    printf("\n\t3 - Concluir uma tarefa");
    printf("\n\t4 - Atualizacao do status de uma tarefa");
    printf("\n\t5 - Listar tarefas pendentes");
    printf("\n\t6 - Listar tarefas concluidas");
    printf("\n\t7 - Listar tarefas concluidas com e sem atraso");
    printf("\n\t8 - Sair do programa\n");
}

