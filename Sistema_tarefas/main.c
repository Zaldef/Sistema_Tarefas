#include <stdlib.h>
#include <stdio.h>
#include "FILA.h" // gerenciamento de fila
#include "TAREFA.h" // gerenciamento de tarefa
#include<stdbool.h> // trabalhar com booleanos
#include <time.h> // utilizar hora

#define NUM_CHAR 30

void menu();

int main(){
    Fila *F1 = CriaFila(); //Criando a Fila principal
    Fila *FP = CriaFila(); // ''     Fila de pendentes
    Fila *FC = CriaFila(); // ''     Fila de concluidos
    //carregando data
    const char *Arq_F1 = "database_F1.txt";
    const char *Arq_FP = "database_FP.txt";
    const char *Arq_FC = "database_FC.txt";
    carregarFila(Arq_F1,F1);
    carregarFila(Arq_FP,FP);
    carregarFila(Arq_FC,FC);

    // variaveis do loop principal do program
    int opcao = 0;
    bool end = false;
    //loop principal
    while(end == false){
        menu();
        scanf("%d", &opcao);
        system("cls");

        switch(opcao){
        case 1:
            printf("Adicionar uma nova tarefa\n");
            inserirFila(F1);
            break;
        case 2:
            printf("Modificar uma tarefa\n");
            imprimirFila(F1);
            editarFila(F1);
            break;
        case 3:
            printf("Concluir uma tarefa\n");
            break;
        case 4:
            printf("Atualizacao do status da tarefa\n");
            break;
        case 5:
            printf("Listar tarefas pendentes\n");
            imprimirFila(FP);
            break;
        case 6:
            printf("Listar tarefas concluidas\n");
            imprimirFila(FC);
            break;
        case 7:
            printf("Listar tarefas concluidas com e sem atraso\n");
            break;
        case 8:
            printf("Sair do programa\n");
            // Salvando data
            salvarFila(Arq_F1, F1);
            salvarFila(Arq_FP, FP);
            salvarFila(Arq_FC, FC);
            liberaFila(F1);
            liberaFila(FP);
            liberaFila(FC);
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

