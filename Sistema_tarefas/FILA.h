#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#define NUM_CHAR 30
#include <time.h>    // utilizar hora
#include <string.h>


// ESTRUTURAS
typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct info{
    int cod;             // codigo da tarefa
    char name[NUM_CHAR]; // nome da tarefa
    char proj[NUM_CHAR]; // qual projeto a tarefa pertence
    Data ini;            // data de inicio
    Data ter;            // data de termino
    int status;          // 1 atrasada e 0 em dia e -1 pendente
}Tarefa;

typedef struct nos{
    Tarefa info;
    struct nos *prox;
}No;

typedef struct fila{
    No *ini;
    No *fim;
}Fila;

// prototipos fila
int VaziaFila (Fila* f);                        //VERIFICA SE A FILA ESTA VAIZA
Fila* CriaFila();                               //CRIA A FILA
No* ins_fim (No* fim, Fila *f, No *lc, No *lp); //função auxiliar para criar uma nova tarefa
No* ins_fim_tarefa (No* fim, No *no);           //função auxiliar para mover uma tarefa ja existente
void InsereFilaTarefa (Fila* f, No *no);        //função para mover entre filas
Fila *ExcluirTarefaFila(Fila *F, No *LC);       //retira uma tarefa da fila
void InserirFila (Fila* f);                     //INSERIR
Fila* liberarFila (Fila* f);                    //LIBERA A FILA
void imprimirFila (Fila* f);                    //IMPRIME A FILA
void carregarFila(const char *n,Fila* f);       //CARREGA UMA FILA SALVADA EXTERNAMENTE
void salvarFila(const char *n,Fila* f);         //SALVA UMA FILA EM ARQUIVO EXTERNO
void editarFila(Fila* f, No *lp);                       //EDITAR ALGUM NÓ NA FILA

// prototipos de lista
No* inicializa();                               //INICIALIZA LISTA
No* inserirLista (No* recebida, Tarefa valor);  //INSERIR
int VaziaLista(No *recebida);                   //VERIFICA SE A LISTA ESTA VAZIA
No* retiraTarefaPendente (No* l, Tarefa t);     //RETIRA TAREFA PENDENTE DA LISTA
void imprimirLista(No* p);                      //IMPRIME A FILA
No* liberaLista(No *receb);                     //LIBERA A LISTA
No* carregarLista(const char *n);               //CARREGA UMA LISTA SALVADA EXTERNAMENTE
void salvarLista(const char *n,No* l);          //SALVA UMA LISTA EM ARQUIVO EXTERNO
No *OrdenarListaData(No * lista);               //ORGANIZA A FILA DE ACORDO COM A DATA TÉRMINO
No* RemoverTarefaPendente(No *LP);              //REMOVER TAREFA DA LISTA DE PENDENTE

// Prototipo Tarefa
int DataValida(int dia, int mes, int ano);          //VERIFICANDO DATA INSERIDA TEM FROMATO VALIDO
Tarefa novaTarefa(Fila* f, No *lc, No *lp);         //CRIA NOVA TAREFA
void imprimirTarefa(Tarefa T);                      //IPRIME TAREFA
Tarefa editarTarefa(Tarefa old);                    //EDITA TAREFA
int verificarCod(Fila *f, No *lc, No *lp, int t);   //VERIFICA CODIGO DA TAREFA SE ELE JA NAO EXISTE EM OUTRA TAREFAS
void verificarStatus(Fila *f);                      //VERIFICA O STATUS DE ATRASADA
Tarefa SelecionarTarefa(Fila* f);                   //BUSCA DE INFORMACOES
No* ConcluirTarefa(Tarefa t, No *LC);               //MUDANÇA DE FILA PARA LISTA DE CONCLUIDAS
No* TarefaPendente(Tarefa t, No *LP);               //MUDANÇA DE STATUS PARA PENDENTE
Tarefa SelecionarTarefaPendente(No* f);             //ESCOLHA DA TAREFA PENDENTE
int comparaData(No *A, No *B);                      //COMPARA DATA DE TERMINO DE DOIS NÓS


int VaziaFila(Fila *f){
    if (f->ini == NULL)
        return 1;
    return 0;
}

Fila *CriaFila(){
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No* fim, Fila *f, No *lc, No *lp){
    // criando novo no
    No* p = (No*) malloc(sizeof(No));
    p->info = novaTarefa(f,lc,lp); //chama esta funcao para guardar infos da tarefa lc e lp passados como parametro apenas para verificar cod
    p->prox = NULL;
    // encadeando na fila
    if (fim != NULL)
        fim->prox = p;
    return p;
}

No* ins_fim_tarefa (No* fim, No *no){
    No* tarefa = no;
    No* p = (No*) malloc(sizeof(No));
    p->info = tarefa->info;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista n�o estava vazia */
    fim->prox = p;
    return p;
}

void InsereFilaTarefa (Fila* f, No *no){
    f->fim = ins_fim_tarefa(f->fim,no);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Fila *ExcluirTarefaFila(Fila *F, No *LC){
    Fila *f = CriaFila();
    No *aux = F->ini;
    int flag = 0;
    while(!flag){
        //verifica se o codigo e igual
        if(aux->info.cod == LC->info.cod){
            aux = aux->prox;
        }else{
            InsereFilaTarefa(f,aux);
            aux = aux->prox;
        }
        if (aux == NULL) flag = 1;
    }
    free(F);
    return f;
}

void inserirFila(Fila* f, No *lc, No *lp){
    f->fim = ins_fim(f->fim, f, lc, lp); //lc e lp passados como parametro apenas para verificar cod
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Fila *liberarFila(Fila *f){
    No *q = f->ini;
    while (q != NULL)
    {
        No *t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

void imprimirFila(Fila *f){
    No *q;
    if (VaziaFila(f))
    {
        printf("\n\n\t\t ==> FILA VAZIA <==\n\n ");
    }
    for (q = f->ini; q != NULL; q = q->prox)
    {
        imprimirTarefa(q->info); // funcao para imprimir as infos da tarefa
        printf("\n");
    }
}

void carregarFila(const char *n, Fila *f){
    FILE *arq = fopen(n, "r");
    // FILE *arq, ponteiro do tipo file que vai percorrer o arquivo
    // fopen(arquivo a ser aberto, r- read_only);
    Tarefa T;
    // Verificando se o arquivo foi aberto corretamente
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    // cria um novo no para cada informacao salva no arquivo
    while (fread(&T, sizeof(Tarefa), 1, arq) == 1)
    {
        // fread(local aonde vai ser guardado a informacao lida, tamanho da informacao a ser lida, quantas informacoes vao ser lidas, daonde vai ser lido)
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL)
        {
            printf("Erro ao alocar memoria para n0 da fila.\n");
            exit(1);
        }

        novoNo->info = T;
        novoNo->prox = NULL;

        if (f->ini == NULL)
        {
            f->ini = novoNo;
            f->fim = novoNo;
        }
        else
        {
            f->fim->prox = novoNo;
            f->fim = novoNo;
        }
    }
    // fecha o arquivo pois nao necessita mais ser usado
    fclose(arq);
}

void salvarFila(const char *n, Fila *f){
    FILE *arq;
    arq = fopen(n, "wt");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    No *q = f->ini;
    while (q != NULL)
    {
        fwrite(&q->info, sizeof(Tarefa), 1, arq);
        // fwrite(o que sera armazenado, qual o tamanho da infoi a ser salva, quantas infos serao salvas, aonde sera salvo
        q = q->prox;
    }
    fclose(arq);
}

void editarFila(Fila *f, No* lp){
    int code = 0;
    int check = 1;

    do{
        if (check == 0)
        {
            printf("\tFalha na leitura do codigo tente novamente.");
        }
        printf("\n\tCaso deseje sair, digite 0");
        printf("\n\tDigite o codigo da tarefa que deseja editar:");
        fflush(stdin);
        check = scanf("%d", &code); // verificaçãod e leitura
    } while (check == 0);
    if(code == 0) return;
    // busca do codigo na fila principal
    No *aux = f->ini;
    check = 0;
    while (check == 0){
        if(aux->info.cod == code){
            check = 1; //achou o codigo
        }else if(aux->prox != NULL){
            aux = aux->prox; //nao achou proxmio
        }else{
            check = -1; //nao achou o codigo
        }
    }
    //chegou ao final da fila, pula pra lista
    if ( check == -1) aux = lp;
    while( check == -1){
        if(aux->info.cod == code){
            check = 1; //achou o codigo
        }else if(aux->prox != NULL){
            aux = aux->prox; //nao achou proxmio
        }else{
            printf("Tarefa nao existe !!!");
            return;
        }
    }
    aux->info = editarTarefa(aux->info);
}

void excluir_geral(Fila *f, No **lp, No **lc){
    int code = 0;
    int check = 1;

    do {
        if (check == 0) {
            printf("\tFalha na leitura do código, tente novamente.");
        }
        printf("\n\tCaso deseje sair, digite 0");
        printf("\n\tDigite o codigo da tarefa que deseja excluir:");
        fflush(stdin);
        check = scanf("%d", &code); // verificação de leitura
    } while (check == 0);
    if (code == 0) return;

    // Busca do código na fila principal
    No *aux = f->ini;
    No *ant = NULL;
    check = 0;

    while (aux != NULL) {
        if (aux->info.cod == code) {
            if (ant == NULL) {
                // É o primeiro nó da lista principal
                f->ini = aux->prox;
            } else {
                // Não é o primeiro nó, ajusta o ponteiro do nó anterior
                ant->prox = aux->prox;
            }
            free(aux);
            check = 1;
            break; // Sai do loop, pois a tarefa foi encontrada e excluída
        }
        ant = aux;
        aux = aux->prox;
    }

    // Se a tarefa não foi encontrada na fila principal, verifica nas listas lp e lc
    if (check == 0) {
        aux = *lp;
        ant = NULL;
        while (aux != NULL) {
            if (aux->info.cod == code) {
                if (ant == NULL) {
                    // É o primeiro nó da lista lp
                    *lp = aux->prox;
                } else {
                    // Não é o primeiro nó, ajusta o ponteiro do nó anterior
                    ant->prox = aux->prox;
                }
                free(aux);
                check = 1;
                break; // Sai do loop, pois a tarefa foi encontrada e excluída
            }
            ant = aux;
            aux = aux->prox;
        }
    }

    // Se a tarefa não foi encontrada na lista lp, verifica na lista lc
    if (check == 0) {
        aux = *lc;
        ant = NULL;
        while (aux != NULL) {
            if (aux->info.cod == code) {
                if (ant == NULL) {
                    // É o primeiro nó da lista lc
                    *lc = aux->prox;
                } else {
                    // Não é o primeiro nó, ajusta o ponteiro do nó anterior
                    ant->prox = aux->prox;
                }
                free(aux);
                check = 1;
                break; // Sai do loop, pois a tarefa foi encontrada e excluída
            }
            ant = aux;
            aux = aux->prox;
        }
    }

    // Se check ainda for 0, a tarefa não foi encontrada em nenhuma das listas
    if (check == 0) {
        printf("Tarefa não encontrada!\n");
    }
}

// Funcoes Lista
No *inicializa(){
    return NULL;
}

No* inserirLista (No* recebida, Tarefa valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->info = valor;
    novo->prox = recebida;
    return novo;
}

int VaziaLista(No *recebida){
 return (recebida == NULL);
}

No* retiraTarefaPendente (No* l, Tarefa t){
    No* ant = inicializa();
    No* p = l;
    while (p != NULL && p->info.cod != t.cod){
        ant = p;
        p = p->prox;
    }
 /* verifica se achou elemento */
    if (p == NULL)
    return l; /* não achou: retorna lista original */
    /* retira elemento */
    if (ant == NULL) {
        l = p->prox; // retira elemento do inicio
    }else{
        ant->prox = p->prox; // retira elemento do meio da lista
    }
    free(p);
    return l;
}

void imprimirLista(No *p){
    No *aux = p;
    if (VaziaLista(aux))
    {
        printf("\n\n\t\t => LISTA VAZIA <==\n\n ");
    }
    else
    {
        for (; aux != NULL; aux = aux->prox)
        {

            imprimirTarefa(aux->info);
            printf("\n");
        }
    }
}

void imprimirListaConcluidas(No *p){
    printf("Listar tarefas concluidas\n");
    printf("\n\tSelecione uma das opcoes");
    printf("\n\t1 - Imprimir lista de concluidas completa");
    printf("\n\t2 - Imprimir lista de concluidas com atraso");
    printf("\n\t3 - Imprimir lista de concluidas sem atraso");
    printf("\n\t0 - Retornar\n");

    int opcao_LC;
    scanf("%d", &opcao_LC);
    No *aux = p;

    switch (opcao_LC){

        case 1:
            system("cls");
            imprimirLista(p);
            system("pause");
            break;

        case 2:
            system("cls");
            if (VaziaLista(aux)){
                printf("\n\n\t\t => LISTA VAZIA <==\n\n ");
            }else{
                while (aux != NULL){
                    Tarefa tarefa_comp = aux->info;
                    if(tarefa_comp.status == 1)
                    imprimirTarefa (aux->info);
                    printf("\n");
                    aux = aux->prox;
                }
            }
            system("pause");
            break;

        case 3:
            system("cls");
            if (VaziaLista(aux)){
                printf("\n\n\t\t => LISTA VAZIA <==\n\n ");
            }else{
                while (aux != NULL){
                    Tarefa tarefa_comp = aux->info;
                    if(tarefa_comp.status == 0) imprimirTarefa (aux->info);
                    printf("\n");
                    aux = aux->prox;
                }
             }
            system("pause");
            break;

            case 0:
                break;

            default:
                printf("Opcao invalida\n");
                break;
    }
}

No *liberaLista(No *receb){
    No *aux;
    while (receb != NULL)
    {
        aux = receb;
        receb = receb->prox;
        free(aux);
    }
    return NULL;
}

No* carregarLista(const char *n){
    No *aux = NULL;
    No* ultimo = NULL;
    FILE *arq = fopen(n, "r");
    // FILE *arq, ponteiro do tipo file que vai percorrer o arquivo
    // fopen(arquivo a ser aberto, r- read_only);
    Tarefa T;
    // Verificando se o arquivo foi aberto corretamente
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    // cria um novo no para cada informacao salva no arquivo
    while (fread(&T, sizeof(Tarefa), 1, arq) == 1)
    {
        // fread(local aonde vai ser guardado a informacao lida, tamanho da informacao a ser lida, quantas informacoes vao ser lidas, daonde vai ser lido)
        No *novoNo = (No *)malloc(sizeof(No));
        if (novoNo == NULL)
        {
            printf("Erro ao alocar memoria para o no.\n");
            exit(1);
        }

        novoNo->info = T;
        novoNo->prox = NULL;
        if(ultimo == NULL){
            aux = novoNo;
        }else{
            ultimo->prox = novoNo;
        }
        ultimo = novoNo;
    }
    // fecha o arquivo pois nao necessita mais ser usado
    fclose(arq);
    return aux;
}

void salvarLista(const char *n, No *l){
    FILE *arq;
    arq = fopen(n, "wt");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    No *q = l;
    while (q != NULL)
    {
        fwrite(&q->info, sizeof(Tarefa), 1, arq);
        // fwrite(o que sera armazenado, qual o tamanho da infoi a ser salva, quantas infos serao salvas, aonde sera salvo
        q = q->prox;
    }
    fclose(arq);
}

No* inserirListaOrdenada (No* l, Tarefa valor){
    No *novo = (No*) malloc(sizeof(No));
    No *aux  = l;
    No *prox = l->prox;
    novo->info = valor;
    if(aux == NULL){
        novo->prox = l;
    }else{
        if(comparaData(aux,novo) == 0){
            l = novo;
            novo->prox = aux;
        }else if(comparaData(aux,novo) == 1 && comparaData(prox,novo) == 0 && prox != NULL){
            aux->prox = novo;
            novo->prox = prox;
        }else if(comparaData(aux,novo) == 1 && prox == NULL){
            aux->prox = novo;
            novo->prox = NULL;
        }
    }
    return l;
}
int comparaData(No *A, No *B){ // retorna 1 se A for maior, 0 se B maior

    if(A->info.ter.ano > B->info.ter.ano){
        return 1;
    }else if(A->info.ter.ano < B->info.ter.ano){
        return 0;
    }else if(A->info.ter.mes > B->info.ter.mes){
        return 1;
    }else if(A->info.ter.mes < B->info.ter.mes){
        return 0;
    }else if(A->info.ter.dia > B->info.ter.dia){
        return 1;
    }else if(A->info.ter.dia < B->info.ter.dia){
        return 0;
    }else{
        return 1; //data de termino identicas
    }
}

// Funcoes Tarefa
int DataValida(int dia, int mes, int ano){
    if (mes < 1 || mes > 12) return 0; // Mês inválido
    switch (mes)
    {
    // Meses com 31 dias
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return (dia >= 1 && dia <= 31);
    // Fevereiro (ano bissexto)
    case 2:
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
        {
            return (dia >= 1 && dia <= 29); // Ano bissexto
        }
        else
        {
            return (dia >= 1 && dia <= 28); // Não bissexto
        }
    // Meses com 30 dias
    default:
        return (dia >= 1 && dia <= 30);
    }
}

Tarefa novaTarefa(Fila *f, No *lc, No *lp){
    Tarefa T;
    int check = 1;
    int check_data = 1;
    int check_cod = 1;
    do
    {
        if (check_cod == 0)
        {
            printf("\t Nao pode ou ja existe uma tarefa com esse codigo, digite novamente");
        }
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do codigo tente novamente.");
            }
            printf("\n\tDigite o codigo da tarefa: ");
            fflush(stdin);
            check = scanf("%d", &T.cod); //verificacao de leitura
            check_cod = verificarCod(f,lc,lp, T.cod); //verificacao de codigo
        }while(check == 0);
    }while(check_cod == 0);
    printf("\n\tDigite o nome da tarefa: ");
    fflush(stdin);
    gets(T.name);

    printf("\n\tDigite o nome do projeto que a tarefa pertence: ");
    fflush(stdin);
    gets(T.proj);
    do
    {
        if (check_data == 0)
        {
            printf("\tFormato de data invalido, tente novamente.");
        }
        printf("\n\tDigite a data de inicio da tarefa: ");
        check = 1;
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\n\tDigite o dia: ");
            fflush(stdin);
            check = scanf("%d", &T.ini.dia); //verificacao de leitura
        } while (check == 0);
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o mes: ");
            fflush(stdin);
            check = scanf("%d", &T.ini.mes); //verificacao de leitura
        } while (check == 0);
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o ano: ");
            fflush(stdin);
            check = scanf("%d", &T.ini.ano); //verificacao de leitura
        } while (check == 0);
        check_data = DataValida(T.ini.dia, T.ini.mes, T.ini.ano); //verificacao de data
    } while (check_data != 1);

    do
    {
        if (check_data == 0)
        {
            printf("\tFormato de data invalido, tente novamente.");
        }
        printf("\n\tDigite a data de termino da tarefa: ");
        check = 1;
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\n\tDigite o dia: ");
            fflush(stdin);
            check = scanf("%d", &T.ter.dia); //verificacao de leitura
        } while (check == 0);
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o mes: ");
            fflush(stdin);
            check = scanf("%d", &T.ter.mes); //verificacao de leitura
        } while (check == 0);
        do
        {
            if (check == 0)
            {
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o ano: ");
            fflush(stdin);
            check = scanf("%d", &T.ter.ano); //verificacao de leitura
        } while (check == 0);
        check_data = DataValida(T.ter.dia, T.ter.mes, T.ter.ano); //verificacao de data
    } while (check_data != 1);

    T.status = 0;
    return T;
}

void imprimirTarefa(Tarefa T){
    printf("\n\tCodigo da tarefa: %d", T.cod);
    printf("\n\tNome da tarefa: %s", T.name);
    printf("\n\tNome do projeto: %s", T.proj);
    printf("\n\tData de Inicio: %02d/%02d/%04d", T.ini.dia, T.ini.mes, T.ini.ano);
    printf("\n\tData de Termino: %02d/%02d/%04d", T.ter.dia, T.ter.mes, T.ter.ano);
    if (T.status == 0)
    {
        printf("\n\tTarefa em dia");
    }
    else if (T.status == 1)
    {
        printf("\n\tTarefa atrasada");
    }
    else
    {
        printf("\n\tTarefa pendente");
    }
}

Tarefa editarTarefa(Tarefa old){
    Tarefa new = old; // bova tarefa recebe todas as infos da tarefa antiga
    int check = 1;
    int check_data = 1;
    int opcao;
    int A = 0;

    while (A == 0)
    {
        system("cls");
        imprimirTarefa(new);
        printf("\n\n\tQual informacao deseja alterar?");
        printf("\n\t1 - Nome");
        printf("\n\t2 - Projeto");
        printf("\n\t3 - Data de inicio");
        printf("\n\t4 - Data de termino");
        printf("\n\t5 - Descartar alteracoes");
        printf("\n\t6 - Salvar alteracoes\n");
        scanf("%d", &opcao);
        system("cls");
        switch (opcao)
        {
        case 1:
            printf("\n\tNome anterior da tarefa: %s", old.name);
            printf("\n\tDigite o novo nome: ");
            fflush(stdin);
            gets(new.name);
            break;

        case 2:
            printf("\n\tNome anterior do projeto: %s", old.proj);
            printf("\n\tDigite o novo nome do projeto que a tarefa pertence: ");
            fflush(stdin);
            gets(new.proj);
            break;

        case 3:
            do
            {
                if (check_data == 0)
                {
                    printf("\tFormato de data invalido, tente novamente.");
                }
                printf("\n\tData de inicio anterior:%02d/%02d/%04d \n", old.ini.dia, old.ini.mes, old.ini.ano);
                printf("\n\tDigite a nova data de inicio da tarefa: ");
                check = 1;

                do
                {
                    if (check == 0)
                    {
                        printf("\tFalha na leitura do numero tente novamente.");
                    }
                    printf("\n\tDigite o novo dia: ");
                    fflush(stdin);
                    check = scanf("%d", &new.ini.dia);
                } while (check == 0);

                do
                {
                    if (check == 0)
                    {
                        printf("\tFalha na leitura do numero tente novamente.");
                    }
                    printf("\tDigite o novo mes: ");
                    fflush(stdin);
                    check = scanf("%d", &new.ini.mes);
                } while (check == 0);

                do
                {
                    if (check == 0)
                    {
                        printf("\tFalha na leitura do numero tente novamente.");
                    }
                    printf("\tDigite o novo ano: ");
                    fflush(stdin);
                    check = scanf("%d", &new.ini.ano);
                } while (check == 0);

                check_data = DataValida(new.ini.dia, new.ini.mes, new.ini.ano);
            } while (check_data != 1);
            break;

        case 4:
            do
            {
                if (check_data == 0)
                {
                    printf("\tFormato de data invalido, tente novamente.");
                }
                printf("\n\tData de termino anterior:%02d/%02d/%04d \n", old.ter.dia, old.ter.mes, old.ter.ano);
                printf("\n\tDigite a nova data de termino da tarefa: ");
                check = 1;

                do
                {
                    if (check == 0)
                    {
                        printf("\tFalha na leitura do numero tente novamente.");
                    }
                    printf("\n\tDigite o novo dia:");
                    fflush(stdin);
                    check = scanf("%d", &new.ter.dia);
                } while (check == 0);

                do
                {
                    if (check == 0)
                    {
                        printf("\tFalha na leitura do numero tente novamente.");
                    }
                    printf("\tDigite o novo mes: ");
                    fflush(stdin);
                    check = scanf("%d", &new.ter.mes);
                } while (check == 0);

                do
                {
                    if (check == 0)
                    {
                        printf("\tFalha na leitura do numero tente novamente.");
                    }
                    printf("\tDigite o novo ano: ");
                    fflush(stdin);
                    check = scanf("%d", &new.ter.ano);
                } while (check == 0);
                check_data = DataValida(new.ter.dia, new.ter.mes, new.ter.ano);
            } while (check_data != 1);
            break;

        case 5:
            return old;
            break;
        case 6:
            return new;
            break;
        default:
            printf("Opcao invalida\n");
        }
    }
    return old; // caso der erro ele cancela
}

Tarefa SelecionarTarefa(Fila* f){
    No* aux = f->ini;
    int code =0;
    int check = 1;
    Tarefa erro;
    memset(&erro, 0, sizeof(Tarefa));  //setando tarefa erro com 0 em todos os campos

    if(aux == NULL){
        system("pause");
        return erro; //caso nao ache o codigo retorna erro(tarefa nula)
    }

    do{
        if (check == 0){
            printf("\tFalha na leitura do codigo tente novamente.");
        }
        printf("\n\tCaso deseje sair, digite 0");
        printf("\n\tDigite o codigo da tarefa:");
        fflush(stdin);
        check = scanf("%d",&code);
    }while(check == 0);
    if(code == 0) return erro; //caso seja digitado 0 retorna erro(tarefa nula)
    aux = f->ini;
    while (aux->info.cod != code){
        aux=aux->prox;
        if(aux == NULL){
            printf("\n\tTarefa nao encontrada\n\n\t");
            system("pause");
            return erro; //caso nao ache o codigo retorna erro(tarefa nula)
        }
    }
    return aux->info;
}

No* ConcluirTarefa(Tarefa t, No *LC){
    int opcao;
    int A = 0;
    // variaveis de tempo
    time_t tempoAtual;
    struct tm *tempoInfo;
    time(&tempoAtual);          // Obtém o tempo atual em segundos desde a época
    tempoInfo = localtime(&tempoAtual); // Converte para uma estrutura tm

    while(A == 0){
        system("cls");
            imprimirTarefa(t);
            printf("\n\n\tSelecione a opcao a seguir: ");
            printf("\n\t1 - Concluir Tarefa");
            printf("\n\t2 - Sair\n");
            //adicionar um print para tarefa concluida
            scanf("%d", &opcao);
            system("cls");
        switch(opcao){
            case 1:
                LC = inserirLista(LC, t); //retorna a lista
                LC->info.ter.dia = tempoInfo->tm_mday;
                LC->info.ter.mes = tempoInfo->tm_mon + 1; // Os meses são de 0 a 11, então adicionamos 1
                LC->info.ter.ano = tempoInfo->tm_year + 1900; // Os anos são desde 1900
                return LC;
                break;
            case 2:
                A = 1;
                break;
            default:
                printf("Opcao invalida\n");
        }
    }
    return LC;
}

int verificarCod(Fila *f, No *lc, No *lp, int t){
    No* q;
    if(t <= 0) return 0;// nao pode tarefas com numeros negativos
    //percorre todas as tarefa comparando o codigo, se ja existir retorna 0
    // Fila principal
    for (q=f->ini; q!=NULL; q=q->prox){
        if(q->info.cod == t){
            return 0;
        }
    }
    // Lista concluidas
    for (q=lc; q!=NULL; q=q->prox){
        if(q->info.cod == t){
            return 0;
        }
    }
    // Lista pendentes
    for (q=lp; q!=NULL; q=q->prox){
        if(q->info.cod == t){
            return 0;
        }
    }
    return 1;
}

void verificarStatus(Fila *f) {
    // Obtendo a data e a hora atuais
    time_t tempoAtual;
    time(&tempoAtual);

    // atualizando as tarefas na fila
    No *faux = f->ini;
    while (faux != NULL) {
        time_t tempoTerminoTarefa;
        struct tm DataTerminoTarefa;
        memset(&DataTerminoTarefa, 0, sizeof(struct tm)); // setando todos os campos com 0
        DataTerminoTarefa.tm_year = faux->info.ter.ano - 1900; // Ano
        DataTerminoTarefa.tm_mon = faux->info.ter.mes - 1;     // Mês (0 a 11)
        DataTerminoTarefa.tm_mday = faux->info.ter.dia;
        tempoTerminoTarefa = mktime(&DataTerminoTarefa);
        //cai dentro if provavelmente por receber datas menores que 1900, que na conversao se torna um int negativo
        if(tempoTerminoTarefa == -1){
            // Erro na conversão da data
            faux->info.status = 1; // Status -1 para atrasada
        }else{
            // Compare as datas
            if(tempoAtual > tempoTerminoTarefa){
                faux->info.status = 1; // A tarefa está atrasada
            }else{
                faux->info.status = 0; // A tarefa está adiantada
            }
        }
        faux = faux->prox;
    }
}
    // função para alterar o status da tarefa para pendente
No* TarefaPendente(Tarefa t, No *LP){
    int opcao;
    int A = 0;

    while(A == 0){
        system("cls");
        imprimirTarefa(t);
        printf("\n\n\tSelecione a opcao a seguir: ");
        printf("\n\t1 - Mudar o status para PENDENTE.");
        printf("\n\t3 - Sair\n");
        //adicionar um print para tarefa concluida
        scanf("%d", &opcao);
        system("cls");
        switch(opcao){
            case 1:
                t.status = -1;
                LP = inserirListaOrdenada(LP, t); //retorna a lista
                return LP; // retorna a lista pendente com a tarefa
                break;
            case 2:
                A = 1;
                break;
            default:
                printf("Opcao invalida\n");
        }
    }
    return LP;
}

/*No* RemoverTarefaPendente(No *LP){
    Tarefa new;
    int opcao;
    int A = 0;

    //Seleção de tarefas
    new = SelecionarTarefaPendente(LP);
    if(new.cod == 0) return LP;

    while(A == 0){
        system("cls");
        imprimirLista(LP);
        printf("\n\n\tSelecione a opcao a seguir: ");
        printf("\n\t1 - Mudar o status para  NAO PENDENTE.");
        printf("\n\t2 - Sair\n");
        //adicionar um print para tarefa concluida
        scanf("%d", &opcao);
        system("cls");
        switch(opcao){
            case 1:
                LP = retiraTarefaPendente(LP,new);
                return LP;
                break;
            case 2:
                A = 1;
                break;
            default:
                printf("Opcao invalida\n");
        }
    }
    return LP;
}*/

/*Tarefa SelecionarTarefaPendente(No* f){
    No* aux = f;
    int code =0;
    int check = 1;
    Tarefa erro;
    memset(&erro, 0, sizeof(Tarefa));  //setando tarefa erro com 0 em todos os campos

    if(aux == NULL){
        system("pause");
        return erro; //caso nao ache o codigo retorna erro(tarefa nula)
    }

    do{
        if (check == 0){
            printf("\tFalha na leitura do codigo tente novamente.");
        }
        printf("\n\tCaso deseje sair, digite 0");
        printf("\n\tDigite o codigo da tarefa:");
        fflush(stdin);
        check = scanf("%d",&code);
    }while(check == 0);
    if(code == 0) return erro; //caso seja digitado 0 retorna erro(tarefa nula)
    aux = f;
    while (aux->info.cod != code){
        aux=aux->prox;
        if(aux == NULL){
            printf("\n\tTarefa nao encontrada\n\n\t");
            system("pause");
            return erro; //caso nao ache o codigo retorna erro(tarefa nula)
        }
    }
    return aux->info;
}*/

/*No *OrdenarListaData(No *lista){
    No *aux = inicializa();
    No *l = lista;
    Tarefa data_maior;
    while(l != NULL){
        if(l->info.ter.dia >= data_maior.ter.dia &&
           l->info.ter.mes >= data_maior.ter.mes &&
           l->info.ter.ano >= data_maior.ter.ano){
            data_maior = l->info;
           }
        l=l->prox;
    }
    while(l != NULL){
        if(l->info.ter.dia <= data_maior.ter.dia &&
           l->info.ter.mes <= data_maior.ter.mes &&
           l->info.ter.ano <= data_maior.ter.ano){
                aux=inserirLista(l,l->info);
           }
           l=l->prox;
           aux=aux->prox;
    }
    return aux;

}*/

#endif // FILA_H_INCLUDED
