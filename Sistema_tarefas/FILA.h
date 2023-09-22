#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "Tarefa.h"

/* FUNÇÕES DE MANIPULAÇÃO DE PFILA
Fila* CriaFila()  CRIA A FILA
int VaziaFila (Fila* f) VERIFICA SE A FILA ESTÁ VAIZA
void InsereFila (Fila* f, int v) INSERÇÃO
int RetiraFila (Fila* f) REMOÇÃO
Fila* liberaFila (Fila* f) LIBERA A FILA
void imprimeFila (Fila* f)IMPRIME A FILA
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
    p->info = novaTarefa();
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila(Fila* f){
    f->fim = ins_fim(f->fim);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

void carregarFila(const char *n,Fila* f){
    FILE *arquivo;
    arquivo = fopen(n, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    Tarefa T;
    while (fread(&T, sizeof(Tarefa), 1, arquivo) == 1) {
        No *novoNo = (No *)malloc(sizeof(No));

        if (novoNo == NULL) {
            printf("Erro ao alocar memória para nó da fila.\n");
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
    fclose(arquivo);
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

void imprimeFila (Fila* f){
    No* q;
    for (q=f->ini; q!=NULL; q=q->prox){
        imprimirTarefa(q->info);
        printf("\n");
    }

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

void salvarFila(const char *n,Fila* f){
    FILE *arquivo;
    arquivo = fopen(n, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    No* q = f->ini;
    while(q!=NULL){
        salvarTarefa(arquivo,q->info);
        q = q->prox;
    }
    fclose(arquivo);
}


#endif // FILA_H_INCLUDED
