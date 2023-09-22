#include <stdlib.h>
#include <stdio.h>
#include "FILA.h" // gerenciamento de fila
#include "TAREFA.h" // gerenciamento de tarefa
#include<stdbool.h> // trabalhar com booleanos
#include <time.h> // utilizar hora

#define NUM_CHAR 30

void menu();

int main(){
    //carregando database
    const char *Arquivo = "database.txt";

    Fila *F1 = CriaFila();
    carregarFila(Arquivo,F1);
    int opcao = 0;
    bool end = false;
    while(end == false){
        menu();
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
        case 1:
            printf("Adicionar uma nova tarefa\n");
            InsereFila(F1);
            break;
        case 2:
            printf("Modificar uma tarefa\n");
            break;
        case 3:
            printf("Concluir uma tarefa\n");
            break;
        case 4:
            printf("Atualizacao do status da tarefa\n");
            break;
        case 5:
            printf("Listar tarefas pendentes\n");
            imprimeFila(F1);
            break;
        case 6:
            printf("Listar tarefas concluidas\n");
            break;
        case 7:
            printf("Listar tarefas concluidas com e sem atraso\n");
            break;
        case 8:
            printf("Sair do programa\n");
            salvarFila(Arquivo, F1);
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

