#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include "Tarefa.h"

/* FUNCOES DE MANIPULACAO DE PFILA
Fila* CriaFila()                            CRIA A FILA
int VaziaFila (Fila* f)                     VERIFICA SE A FILA ESTA VAIZA
void InsereFila (Fila* f, int v)            INSERCAO
int RetiraFila (Fila* f)                    REMOCAO
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
    p->info = novaTarefa(); //chama esta funcao para guardar infos da tarefa
    p->prox = NULL;
    if (fim != NULL)
    fim->prox = p;
    return p;
}

void InsereFila(Fila* f){
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

void imprimeFila (Fila* f){
    No* q;
    for (q=f->ini; q!=NULL; q=q->prox){
        imprimirTarefa(q->info); //funcao para imprimir as infos da tarefa
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
    // cria um novo no para cada informacao salva no arquivo
    while(fread(&T, sizeof(Tarefa), 1, arq) == 1){
        //fread(local aonde vai ser guardado a informacao lida, tamanho da informacao a ser lida, quantas informacoes vao ser lidas, daonde vai ser lido)
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL) {
            printf("Erro ao alocar memoria para n0 da fila.\n");
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
        //fwrite(o que sera armazenado, qual o tamanho da infoi a ser salva, quantas infos serao salvas, aonde sera salvo
        q = q->prox;
    }
    fclose(arq);
}

void editaFila(Fila* f){
    int code =0;
    printf("/n/tDigite o codigo da tarefa que deseja editar:");
    scanf("%d",&code);
    No* aux = f->ini;
    while (aux->info.cod != code)
    {
        if (aux==NULL)
        {
            printf("Tarefa nao existe");
            return;
        };
        aux=aux->prox; 
    }
    aux->info = editarTarefa(aux->info);
}

#endif // FILA_H_INCLUDED
