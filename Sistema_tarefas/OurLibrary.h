#ifndef OurLibrary_H_INCLUDED
#define OurLibrary_H_INCLUDED
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
        int prioridade;      // 1 alta, 2 normal, 3 baixa
    }Tarefa;

    typedef struct nos{
        Tarefa info;
        struct nos *prox;
    }No;

    typedef struct fila{
        No *ini;
        No *fim;
    }Fila;

    typedef struct lista{
        No *ini;
    }Lista;

//PROTOTIPOS
    //FILA
    Fila* inicializarrFila();
    Fila* inserirFila(Fila *f, Tarefa t);
    int vaziaFila(Fila *f);
    void imprimirFila(Fila *f);

    //LISTA
    Lista* inicializarLista();
    Lista* inserirListaInicio(Lista *l, Tarefa t);
    int vaziaLista(Lista* l);
    void imprimirLista(Lista *l);

    //OUTRAS
    Tarefa novaTarefa(Fila *f1, Fila *f2, Fila *f3, Lista *lc, Lista *lp);
    int verificarCod(Fila *f1, Fila *f2, Fila *f3, Lista *lc, Lista *lp, int t);
    int DataValida(int dia, int mes, int ano);
    void imprimirTarefa(Tarefa T);
    No* SelecionarNo(No *busca,int code);


// FUNCOES FILA
    Fila* inicializarFila(){
        Fila* f = (Fila*) malloc(sizeof(Fila));
        f->ini = f->fim = NULL;
        return f;
    }

    Fila* inserirFila(Fila *f, Tarefa t){
        No *novo = (No*) malloc(sizeof(No));
        novo->info = t;
        novo->prox = NULL;
        if (f->fim != NULL){
            f->fim->prox = novo;
        }else{
            f->ini = novo;
        }
        f->fim = novo;
        return f;
    }

    int vaziaFila(Fila *f){
        return (f->ini == NULL);
    }

    void imprimirFila(Fila *f){
        No *aux = f->ini;
        if (vaziaFila(f)){
            printf("\n\n\t\t ==> FILA VAZIA <==\n\n ");
        }else{
            for(; aux != NULL; aux = aux->prox){
                imprimirTarefa(aux->info);
                printf("\n");
            }
        }
    }

// FUNCOES LISTA
    Lista* inicializarLista(){
        return NULL;
    }

    Lista* inserirListaInicio(Lista *l, Tarefa t){
        system("pause");
        No *novo = (No*) malloc(sizeof(No));
        novo->info = t;
        novo->prox = l->ini;
        l->ini = novo;
        return l;
    }

    int vaziaLista(Lista* l){
        return (l == NULL);
    }

    void imprimirLista(Lista *l){
        if (vaziaLista(l)){
            printf("\n\n\t\t ==> LISTA VAZIA <==\n\n ");
        }else{
            No *aux = l->ini;
            for(; aux != NULL; aux = aux->prox){
                imprimirTarefa(aux->info);
                printf("\n");
            }
        }
    }

// OUTRAS FUNCOES
    Tarefa novaTarefa(Fila *f1, Fila *f2, Fila *f3, Lista *lc, Lista *lp){
        Tarefa T;
        int check = 1;
        int check_data = 1;
        int check_cod = 1;
        // Setando codigo da tarefa
        do{
            if (check_cod == 0){
                printf("\t Nao pode ou ja existe uma tarefa com esse codigo, digite novamente");
            }
            do{
                if (check == 0){
                    printf("\tFalha na leitura do codigo tente novamente.");
                }
                printf("\n\tDigite o codigo da tarefa: ");
                fflush(stdin);
                check = scanf("%d", &T.cod); //verificacao de leitura
                check_cod = verificarCod(f1,f2,f3,lc,lp, T.cod); //verificacao de codigo
            }while(check == 0);
        }while(check_cod == 0);
        // Setando nome da tarefa
        printf("\n\tDigite o nome da tarefa: ");
        fflush(stdin);
        gets(T.name);
        // Setando Nome do projeto
        printf("\n\tDigite o nome do projeto que a tarefa pertence: ");
        fflush(stdin);
        gets(T.proj);
        // Setando data de inicio
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
                check = scanf("%d", &T.ini.dia); //verificacao de leitura
            } while (check == 0);
            do{
                if (check == 0){
                    printf("\tFalha na leitura do numero tente novamente.");
                }
                printf("\tDigite o mes: ");
                fflush(stdin);
                check = scanf("%d", &T.ini.mes); //verificacao de leitura
            } while (check == 0);
            do{
                if (check == 0){
                    printf("\tFalha na leitura do numero tente novamente.");
                }
                printf("\tDigite o ano: ");
                fflush(stdin);
                check = scanf("%d", &T.ini.ano); //verificacao de leitura
            } while (check == 0);
            check_data = DataValida(T.ini.dia, T.ini.mes, T.ini.ano); //verificacao de data
        } while (check_data != 1);
        // Setando data de termino
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
                check = scanf("%d", &T.ter.dia); //verificacao de leitura
            } while (check == 0);
            do{
                if (check == 0){
                    printf("\tFalha na leitura do numero tente novamente.");
                }
                printf("\tDigite o mes: ");
                fflush(stdin);
                check = scanf("%d", &T.ter.mes); //verificacao de leitura
            } while (check == 0);
            do{
                if (check == 0){
                    printf("\tFalha na leitura do numero tente novamente.");
                }
                printf("\tDigite o ano: ");
                fflush(stdin);
                check = scanf("%d", &T.ter.ano); //verificacao de leitura
            } while (check == 0);
            check_data = DataValida(T.ter.dia, T.ter.mes, T.ter.ano); //verificacao de data
        } while (check_data != 1);
        // Setando prioridade
        do{
            do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\n\tDigite a prioridade da tarefa: ");
            printf("\n\t1 - Alta");
            printf("\n\t2 - Normal");
            printf("\n\t3 - Baixa\n\t");
            fflush(stdin);
            check = scanf("%d", &T.prioridade); //verificacao de leitura
            } while (check == 0);
        }while(T.prioridade < 1 || T.prioridade > 3);
        
        // Setando status
        T.status = 0;
        return T;
    }

    int verificarCod(Fila *f1, Fila *f2, Fila *f3, Lista *lc, Lista *lp, int t){
        No* aux;
        if(t <= 0) return 0;// nao pode tarefas com numeros negativos
        //percorre todas as tarefa comparando o codigo, se ja existir retorna 0
        // Fila 1
        for (aux=f1->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == t){
                return 0;
            }
        }
        // Fila 2
        for (aux=f2->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == t){
                return 0;
            }
        }
        // Fila 3
        for (aux=f3->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == t){
                return 0;
            }
        }

        // Lista concluidas
        if(vaziaLista(lc) == 0){
            for (aux = lc->ini; aux!=NULL; aux=aux->prox){
                if(aux->info.cod == t){
                    return 0;
                }
            }
        }

        // Lista pendentes
        if(vaziaLista(lp) == 0){
            for (aux = lp->ini; aux!=NULL; aux=aux->prox){
                if(aux->info.cod == t){
                    return 0;
                }
            }
        }


        return 1;
    }

    int DataValida(int dia, int mes, int ano){
        if (mes < 1 || mes > 12) return 0; // Mês inválido
        switch (mes){
        // Meses com 31 dias
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return (dia >= 1 && dia <= 31);
        // Fevereiro (ano bissexto)
        case 2:
            if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)){
                return (dia >= 1 && dia <= 29); // Ano bissexto
            } else{
                return (dia >= 1 && dia <= 28); // Não bissexto
            }
        // Meses com 30 dias
        default:
            return (dia >= 1 && dia <= 30);
        }
    }

    void imprimirTarefa(Tarefa T){
        printf("\n\tCodigo da tarefa: %d", T.cod);
        printf("\n\tNome da tarefa: %s", T.name);
        printf("\n\tNome do projeto: %s", T.proj);
        printf("\n\tData de Inicio: %02d/%02d/%04d", T.ini.dia, T.ini.mes, T.ini.ano);
        printf("\n\tData de Termino: %02d/%02d/%04d", T.ter.dia, T.ter.mes, T.ter.ano);

        if(T.status == 0){
            printf("\n\tTarefa em dia");
        }else if(T.status == 1){
            printf("\n\tTarefa atrasada");
        }else{
            printf("\n\tTarefa pendente");
        }

        if(T.prioridade == 1){
            printf("\n\tPrioridade alta");
        }else if(T.prioridade == 2){
            printf("\n\tPrioridade normal");
        }else{
            printf("\n\tPrioridade baixa");
        }
    }

    void editarFilaLista(Fila* f1,Fila* f2,Fila* f3, No* lp){
        int flag = 0;
        No* aux;
        int code = buscarNo(f1, f2, f3, lp, &flag);
        if(code > 0){
            aux =
            editarTarefa(aux->info); //modifica alguma tarefa
        }else if(code < 0){
            printf("\n\tCodigo invalido\n\t");
            system("pause");
        }
    }

    int editar(Fila* f1,Fila* f2,Fila* f3, No* lp){
        int code;
        No* aux;

        do{
            if (check == 0){
                printf("\tFalha na leitura do codigo tente novamente.");
            }
            printf("\n\tCaso deseje sair, digite 0");
            printf("\n\tDigite o codigo da tarefa que deseja editar:");
            fflush(stdin);
            check = scanf("%d", &code); // verificação de leitura
        } while (check == 0);
        // retorna 0 caso o usuario deseje sair, ou caso o codigo seja invalido
        if(code <= 0){
            return 0;
        }
        // busca na Fila 1
        for(aux=f1->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                editarTarefa(aux->info); //modifica a tarefa selecionada
                return 1; // retorna 1 caso a tarefa seja encontrada
            }
        }
        // busca na Fila 2
        for(aux=f2->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                editarTarefa(aux->info); //modifica a tarefa selecionada
                return 1;
            }
        }
        // busca na Fila 3
        for(aux=f3->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                editarTarefa(aux->info); //modifica a tarefa selecionada
                return 1;
            }
        }
        // busca na Lista pendentes
        if(vaziaLista(lc) == 0){
            for (aux = lp->ini; aux!=NULL; aux=aux->prox){
                if(aux->info.cod == code){
                    editarTarefa(aux->info); //modifica a tarefa selecionada
                    return 1;
                }
            }
        }
        // retorna 0 caso o codigo seja invalido
        return 0;        
    }

    Tarefa editarTarefa(Tarefa old){
    Tarefa new = old; // nova tarefa recebe todas as infos da tarefa antiga
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


    //PEDRO
    No* SelecionarNo(No *busca,int code){
        No *aux = busca;
        while(aux != NULL){
            if(aux->info.cod == code){
                return aux;
            }
            aux=aux->prox;
        }
    }

    //TAY


#endif // OurLibrary_H_INCLUDED
