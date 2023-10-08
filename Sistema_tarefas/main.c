#include <stdlib.h>
#include <stdio.h>
#include "FILA.h"    // gerenciamento de fila/lista
#include <stdbool.h> // trabalhar com booleanos
#include <time.h>    // utilizar hora

#define NUM_CHAR 30

void menu();

int main(){
    Fila *F1 = CriaFila(); // Criando a Fila prioridade alta
    Fila *F2 = CriaFila(); // Criando a Fila prioridade media
    Fila *F3 = CriaFila(); // Criando a Fila prioridade baixa

    No *LP = inicializa(); // ''     Lista de pendentes
    No *LC = inicializa(); // ''     Lista de concluidos
    // carregando data
    const char *Arq_F3 = "database_F3.txt";
    const char *Arq_LP = "database_LP.txt";
    const char *Arq_LC = "database_LC.txt";
    carregarFila(Arq_F3,F3);
    LP = carregarLista(Arq_LP);
    LC = carregarLista(Arq_LC);

    // variaveis do loop principal do program
    int opcao = 0;
    bool end = false;
    // loop principal
    while (end == false){
        menu();
        scanf("%d", &opcao);
        system("cls");

        switch (opcao){

        case 1:
            printf("Adicionar uma nova tarefa\n");
            Tarefa new = novaTarefa(F1,F2,F3,LC,LP);

             if (new.prioridade == 1)
            {
                inserirFila(F1,new);
            }
            else if (new.prioridade == 2)
            {
                inserirFila(F2,new);
            }
            else
            {
                inserirFila(F3,new);
            }
                     
            break;

        case 2:
            printf("Listar tarefas\n");
            imprimirFila(F1);
            imprimirFila(F2);
            imprimirFila(F3);
            system("pause");
            break;

        case 3:
            printf("Modificar uma tarefa\n");
            imprimirFila(F1);
            imprimirFila(F2);
            imprimirFila(F3);

            editarFila(F1,F2,F3);
            break;

        case 4:
            printf("Concluir uma tarefa\n");
            imprimirFila(F1);
            imprimirFila(F2);
            imprimirFila(F3);
           
            LC = ConcluirTarefa(F1,F2,F3,LC);
            ExcluirTarefaFila(F1,F2,F3,LC);
            
            break;

        case 5:
            printf("Atualizacao do status da tarefa\n");
            break;

        case 6:
            printf("Listar tarefas pendentes\n");
            imprimirLista(LP);
            system("pause");
            break;

        case 7:
            imprimirListaConcluidas(LC);
            break;


        case 8:
            printf("Sair do programa\n");
            // Salvando data
            salvarFila(Arq_F3, F3);
            salvarLista(Arq_LP, LP);
            salvarLista(Arq_LC, LC);
            liberaFila(F3);
            liberaLista(LP);
            liberaLista(LC);
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
    system("cls");
    printf("\n\t1 - Adicionar uma nova tarefa");
    printf("\n\t2 - Listar tarefas");
    printf("\n\t3 - Modificar uma tarefa");
    printf("\n\t4 - Concluir uma tarefa");
    printf("\n\t5 - Atualizacao do status de uma tarefa");
    printf("\n\t6 - Listar tarefas pendentes");
    printf("\n\t7 - Listar tarefas concluidas");
    printf("\n\t8 - Sair do programa\n");
}
