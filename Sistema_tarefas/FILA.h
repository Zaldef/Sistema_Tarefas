#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#define NUM_CHAR 30

//ESTRUTURAS
typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct info{
    int cod; //codigo da tarefa
    char name[NUM_CHAR]; // nome da tarefa
    char proj[NUM_CHAR]; // qual projeto a tarefa pertence
    Data ini; //data de inicio
    Data ter; //data de termino
    int status; //1 atrasada e 0 em dia e -1 pendente
}Tarefa;

typedef struct nos{
    Tarefa info;
    struct nos *prox;
}No;

typedef struct fila{
    No * ini;
    No * fim;
} Fila;

// prototipos fila
Fila* CriaFila();                            //CRIA A FILA
int VaziaFila (Fila* f);                     //VERIFICA SE A FILA EST� VAIZA
No* ins_fim (No* fim, Fila *f);
void InsereFila (Fila* f, int v);            //INSER��O
int RetiraFila (Fila* f);                   //REMO��O
Fila* liberaFila (Fila* f);                  //LIBERA A FILA
void imprimeFila (Fila* f);                  //IMPRIME A FILA
void carregarFila(const char *n,Fila* f);    //CARREGA UMA FILA SALVADA EXTERNAMENTE
void salvarFila(const char *n,Fila* f);      //SALVA UMA FILA EM ARQUIVO EXTERNO
// Prototipo Tarefa
Tarefa novaTarefa(Fila* f);                 //Criando nova tarefa
void imprimirTarefa(Tarefa T);              //Imprimir Tarefa
void editarFila(Fila* f);                   //
Tarefa editarTarefa(Tarefa old);             //
int verificarCod(Fila *f, int t);
// Funcoes de fila
int VaziaFila(Fila* f){
    if (f->ini==NULL) return 1;
    return 0;
}

Fila* CriaFila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

No* ins_fim (No* fim, Fila *f){
    No* p = (No*) malloc(sizeof(No));
    p->info = novaTarefa(f); //chama esta funcao para guardar infos da tarefa
    p->prox = NULL;
    if (fim != NULL)
    fim->prox = p;
    return p;
}

void inserirFila(Fila* f){
    f->fim = ins_fim(f->fim, f);
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
            printf("Tarefa nao existe");
            return;
        };
        aux=aux->prox;
    }
    aux->info = editarTarefa(aux->info);
}
// Funcoes Lista

No* inicializa(){
    return NULL;
}

No* inserirLista (No* recebida, Tarefa valor){
    No *novo ;
    novo= (No*) malloc(sizeof(No));
    novo->info = valor;
    novo->prox = recebida;
    return novo;
}

int vazia(No *recebida){
    if (recebida == NULL){
        return 1;
    }
    return 0;
}

void imprimirLista(No* p){
    No* aux = p;
    if(vazia(aux)){
        printf("\n\n\t\t => LISTA VAZIA <==\n\n ");
    }else{
    for(;aux != NULL; aux = aux->prox){
        imprimirTarefa(aux->info);
        printf("\n");
    }

    }
}

No* liberaLista(No *receb){
    No *aux;
    while(receb!= NULL){
        aux=receb;
        receb=receb->prox;
        free(aux);
    }
    return NULL;
}

No* carregarLista(const char *n,No* L){
    No *aux = NULL;
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
            printf("Erro ao alocar memoria para o no.\n");
            exit(1);
        }

        novoNo->info = T;
        novoNo->prox = aux;
        aux = novoNo;
        }
    // fecha o arquivo pois nao necessita mais ser usado
    fclose(arq);
    return aux;
}


void salvarLista(const char *n,No* l){
    FILE *arq;
    arq = fopen(n, "wt");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
    }
    No* q = l;
    while(q!=NULL){
        fwrite(&q->info,sizeof(Tarefa),1,arq);
        //fwrite(o que sera armazenado, qual o tamanho da infoi a ser salva, quantas infos serao salvas, aonde sera salvo
        q = q->prox;
    }
    fclose(arq);
}

// Funcoes Tarefa
int DataValida(int dia, int mes, int ano){
    if(mes < 1 || mes > 12){
        return 0; // Mês inválido
    }
    switch(mes){
        // Meses com 31 dias
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return(dia >= 1 && dia <= 31);
        // Fevereiro (tratamento de ano bissexto)
        case 2:
            if((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
                return (dia >= 1 && dia <= 29); // Ano bissexto
            }else{
                return (dia >= 1 && dia <= 28); // Não bissexto
            }
        // Meses com 30 dias
        default:
            return (dia >= 1 && dia <= 30);
    }
}

Tarefa novaTarefa(Fila *f){
    Tarefa T;
    int check = 1;
    int check_data = 1;
    int check_cod = 1;
    do{
        if (check_cod == 0){
            printf("\t Já existe um tarefa com esse codigo, digite novamente");
        }
        do{
            if (check == 0){
                printf("\tFalha na leitura do codigo tente novamente.");
            }
            printf("\n\tDigite o codigo da tarefa: ");
            fflush(stdin);
            check = scanf("%d", &T.cod);
            check_cod = verificarCod(f, T.cod);
        }while(check == 0);
    }while(check_cod == 0);
    printf("\n\tDigite o nome da tarefa: ");
    fflush(stdin);
    gets(T.name);

    printf("\n\tDigite o nome do projeto que a tarefa pertence: ");
    fflush(stdin);
    gets(T.proj);
    do{
        if (check_data == 0){
            printf("\tFormato de data invalido, tente novamente.");
        }
        printf("\n\tDigite a data de inicio da tarefa: ");
        check = 1;
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\n\tDigite o dia: ");
            fflush(stdin);
            check = scanf("%d",&T.ini.dia);
        }while(check == 0);
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o mes: ");
            fflush(stdin);
            check = scanf("%d",&T.ini.mes);
        }while(check == 0);
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o ano: ");
            fflush(stdin);
            check = scanf("%d",&T.ini.ano);
        }while(check == 0);
        check_data = DataValida(T.ini.dia, T.ini.mes, T.ini.ano);
    }while(check_data != 1);

    do{
        if (check_data == 0){
            printf("\tFormato de data invalido, tente novamente.");
        }
        printf("\n\tDigite a data de termino da tarefa: ");
        check = 1;
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\n\tDigite o dia: ");
            fflush(stdin);
            check = scanf("%d",&T.ter.dia);
        }while(check == 0);
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o mes: ");
            fflush(stdin);
            check = scanf("%d",&T.ter.mes);
        }while(check == 0);
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\tDigite o ano: ");
            fflush(stdin);
            check = scanf("%d",&T.ter.ano);
        }while(check == 0);
        check_data = DataValida(T.ter.dia, T.ter.mes, T.ter.ano);
    }while(check_data != 1);

    T.status = 0;
    return T;
}

void imprimirTarefa(Tarefa T){
    printf("\n\tCodigo da tarefa: %d",T.cod);
    printf("\n\tNome da tarefa: %s",T.name);
    printf("\n\tNome do projeto: %s",T.proj);
    printf("\n\tData de Inicio: %02d/%02d/%04d",T.ini.dia,T.ini.mes,T.ini.ano);
    printf("\n\tData de Termino: %02d/%02d/%04d",T.ter.dia,T.ter.mes,T.ter.ano);
    if(T.status == 0){
        printf("\n\tTarefa em dia");
    }else if(T.status == 1){
        printf("\n\tTarefa atrasada");
    }else{
        printf("\n\tTarefa pendente");
    }
}

Tarefa editarTarefa(Tarefa old){
    Tarefa new = old; // bova tarefa recebe todas as infos da tarefa antiga
    int check = 1;
    int check_data = 1;
    int opcao;
    int A = 0;

    while(A == 0){
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
        switch(opcao){
            case 1:
                printf("\n\tNome anterior da tarefa: %s",old.name);
                printf("\n\tDigite o novo nome: ");
                fflush(stdin);
                gets(new.name);
                break;

            case 2:
                printf("\n\tNome anterior do projeto: %s",old.proj);
                printf("\n\tDigite o novo nome do projeto que a tarefa pertence: ");
                fflush(stdin);
                gets(new.proj);
                break;

            case 3:
                do{
                    if (check_data == 0){
                        printf("\tFormato de data invalido, tente novamente.");
                    }
                    printf("\n\tData de inicio anterior:%02d/%02d/%04d \n",old.ini.dia,old.ini.mes,old.ini.ano);
                    printf("\n\tDigite a nova data de inicio da tarefa: ");
                    check = 1;

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\n\tDigite o novo dia: ");
                        fflush(stdin);
                        check = scanf("%d",&new.ini.dia);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                    printf("\tDigite o novo mes: ");
                    fflush(stdin);
                    check = scanf("%d",&new.ini.mes);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo ano: ");
                        fflush(stdin);
                        check = scanf("%d",&new.ini.ano);
                    }while(check == 0);

                    check_data = DataValida(new.ini.dia, new.ini.mes, new.ini.ano);
                }while(check_data != 1);
                break;

            case 4:
                do{
                    if (check_data == 0){
                        printf("\tFormato de data invalido, tente novamente.");
                    }
                    printf("\n\tData de termino anterior:%02d/%02d/%04d \n",old.ter.dia,old.ter.mes,old.ter.ano);
                    printf("\n\tDigite a nova data de termino da tarefa: ");
                    check = 1;

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\n\tDigite o novo dia:");
                        fflush(stdin);
                        check = scanf("%d",&new.ter.dia);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo mes: ");
                        fflush(stdin);
                        check = scanf("%d",&new.ter.mes);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo ano: ");
                        fflush(stdin);
                        check = scanf("%d",&new.ter.ano);
                    }while(check == 0);
                    check_data = DataValida(new.ter.dia, new.ter.mes, new.ter.ano);
                }while(check_data != 1);
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
    return old; //caso der erro ele cancela
}

int verificarCod(Fila *f, int t){
    No* q;
    for (q=f->ini; q!=NULL; q=q->prox){
        if(q->info.cod != t){
            return 0;
        }
    }
    return 1;
}


#endif // FILA_H_INCLUDED
