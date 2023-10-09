#include <stdlib.h>
#include <stdio.h>
#include "FILA.h"    // gerenciamento de fila/lista
#include <stdbool.h> // trabalhar com booleanos


#define NUM_CHAR 30

void menu();

int main(){
    Fila *F1 = CriaFila(); // Criando a Fila principal
    No *LP = inicializa(); // ''     Lista de pendentes
    No *LC = inicializa(); // ''     Lista de concluidos

    // carregando data
    const char *Arq_F1 = "database_F1.txt";
    const char *Arq_LP = "database_LP.txt";
    const char *Arq_LC = "database_LC.txt";
    carregarFila(Arq_F1,F1);
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
        verificarStatus(F1); // função que roda s Fila principal atualizando seus status de atrasada

        switch (opcao){

        case 1:
            printf("Adicionar uma nova tarefa\n");
            inserirFila(F1,LC,LP); // a nova tarefa é inserida em F1, mas é passado LC e LP, para verificação de codigo
            break;

        case 2:
            printf("Listar tarefas\n");
            imprimirFila(F1); //imprime lista completa de tarefas
            system("pause");
            break;

        case 3:
            printf("Modificar uma tarefa\n");
            printf("\n\t=========Fila de tarefas==========\n");
            imprimirFila(F1);
            printf("\n\t====Lista de tarefas pendentes====\n");
            imprimirLista(LP);
            editarFila(F1,LP); //modifica alguma tarefa
            break;

        case 4:
            printf("Concluir uma tarefa\n");
            imprimirFila(F1);
            if(F1->ini == NULL){
                system("pause");
            }else{
                LC = ConcluirTarefa(F1,LC);
                F1 = ExcluirTarefaFila(F1,LC);
            }
            break;

        case 5:
            printf("Atualizacao do status da tarefa\n");
            imprimirFila(F1);
            if(F1->ini == NULL){
                system("pause");
            }else{
                LP = TarefaPendente(F1,LP);
                F1 = ExcluirTarefaFila(F1,LP); //exclui todas as tarefas que estão na lista de pendentes da fila
            }
            break;

            case 6:
            printf("Atualizacao do status da tarefa\n");
            imprimirLista(LP);
            if(LP == NULL){
                system("pause");
            }else{
                InsereFilaTarefa(F1,RemoverTarefaPendente(LP));
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

        case 9:
            printf("\n\t=========Fila de tarefas===========\n");
            imprimirFila(F1);
            printf("\n\t====Lista de tarefas pendentes=====\n");
            imprimirLista(LP);
            printf("\n\t====Lista de tarefas concluidas====\n");
            imprimirLista(LC);
            excluir_geral(F1,&LP,&LC);
            break;

        case 10:
            printf("Sair do programa\n");
            // Salvando data
            salvarFila(Arq_F1, F1);
            salvarLista(Arq_LP, LP);
            salvarLista(Arq_LC, LC);
            liberarFila(F1);
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
    printf("\n\t5 - Adicionar tarefa pendente");
    printf("\n\t6 - Remover tarefa pendente");
    printf("\n\t7 - Listar tarefas pendentes");
    printf("\n\t8 - Listar tarefas concluidas");
    printf("\n\t9 - Excluir tarefa");
    printf("\n\t10 - Sair do programa\n");
}
