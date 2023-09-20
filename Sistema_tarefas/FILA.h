#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "Tarefa.h"

/* FUN��ES DE MANIPULA��O DE PFILA
Fila* CriaFila()  CRIA A FILA
int VaziaFila (Fila* f) VERIFICA SE A FILA EST� VAIZA
void InsereFila (Fila* f, int v) INSER��O
int RetiraFila (Fila* f) REMO��O
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
    if (fim != NULL) /* verifica se lista n�o estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila(Fila* f){
    f->fim = ins_fim(f->fim);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

No* retira_ini (No* ini){
    No* p = ini->prox;
    free(ini);
    return p;
}

Tarefa RetiraFila(Fila* f){
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
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox){
//        printf("%d - ",q->info);
    }
    printf("\n");
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

#endif // FILA_H_INCLUDED
