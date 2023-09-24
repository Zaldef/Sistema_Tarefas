#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "Tarefa.h"

/* FUN��ES DE MANIPULA��O DE PFILA
Fila* CriaFila()                            CRIA A FILA
int VaziaFila (Fila* f)                     VERIFICA SE A FILA EST� VAIZA
void InsereFila (Fila* f, int v)            INSER��O
int RetiraFila (Fila* f)                    REMO��O
Fila* liberaFila (Fila* f)                  LIBERA A FILA
void imprimeFila (Fila* f)                  IMPRIME A FILA
void carregarFila(const char *n,Fila* f)    CARREGA UMA FILA SALVADA EXTERNAMENTE
void salvarFila(const char *n,Fila* f)      SALVA UMA FILA EM ARQUIVO EXTERNO
*/

typedef struct nos{
    Tarefa info;
    struct nos *prox;
}No;

typedef struct fila{
    No * ini;
    No * fim;
} Fila;

int VaziaFila(Fila* f){
    if (f->ini==NULL) return 1;
    return 0;
}

Fila* CriaFila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No* fim){
    No* p = (No*) malloc(sizeof(No));
    p->info = novaTarefa(); //chama est� fun��o para guardar infos da tarefa
    p->prox = NULL;
    if (fim != NULL)
    fim->prox = p;
    return p;
}

void inserirFila(Fila* f){
    f->fim = ins_fim(f->fim);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Fila* liberaFila (Fila* f){
    No* q = f->ini;
    while (q!=NULL){
        No* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

No* retira_ini (No* ini){
    No* p = ini->prox;
    free(ini);
    return p;
}

Tarefa retiraFila(Fila* f){
    Tarefa v;
    if (VaziaFila(f)){
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL){
       f->fim = NULL;
    }
    return v;

}

void imprimirFila (Fila* f){
    No* q;
    for (q=f->ini; q!=NULL; q=q->prox){
        imprimirTarefa(q->info); //fun��o para imprimir as infos da tarefa
        printf("\n");
    }

}

void carregarFila(const char *n,Fila* f){
    FILE *arq = fopen(n, "r");
    // FILE *arq, ponteiro do tipo file que vai percorrer o arquivo
    // fopen(arquivo a ser aberto, r- read_only);
    Tarefa T;
    // Verificando se o arquivo foi aberto corretamente
    if (arq == NULL){
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    // cria um novo n� para cada informa��o salva no arquivo
    while(fread(&T, sizeof(Tarefa), 1, arq) == 1){
        //fread(local aonde vai ser guardado a informa��o lida, tamanho da informa��o a ser lida, quantas informa�oes v�o ser lidas, daonde vai ser lido)
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
            printf("Erro ao alocar mem�ria para n� da fila.\n");
            exit(1);
        }

        novoNo->info = T;
        novoNo->prox = NULL;

        if (f->ini == NULL) {
            f->ini = novoNo;
            f->fim = novoNo;
        } else {
            f->fim->prox = novoNo;
            f->fim = novoNo;
        }
    }
    // fecha o arquivo pois nao necessita mais ser usado
    fclose(arq);
}

void salvarFila(const char *n,Fila* f){
    FILE *arq;
    arq = fopen(n, "wt");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    No* q = f->ini;
    while(q!=NULL){
        fwrite(&q->info,sizeof(Tarefa),1,arq);
        //fwrite(o que ser� armazenado, qual o tamanho da infoi a ser salva, quantas infos serao salvas, aonde sera salvo
        q = q->prox;
    }
    fclose(arq);
}

void editarFila(Fila* f){
    int code =0;
    int check = 1;

    do{
        if (check == 0){
            printf("\tFalha na leitura do codigo tente novamente.");
        }
        printf("\n\tCaso deseje sair, digite 0");
        printf("\n\tDigite o codigo da tarefa que deseja editar:");
        fflush(stdin);
        check = scanf("%d",&code);
    }while(check == 0);
    if (code == 0){
        return;
    }

    No* aux = f->ini;
    while (aux->info.cod != code)
    {
        if (aux->prox == NULL)
        {
            printf("Tarefa não existe");
            return;
        };
        aux=aux->prox;
    }
    aux->info = editarTarefa(aux->info);
}

#endif // FILA_H_INCLUDED
