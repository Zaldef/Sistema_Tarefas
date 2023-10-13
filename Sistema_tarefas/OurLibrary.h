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
    Fila* inicializarFila();
    Fila* inserirFila(Fila *f, Tarefa t);
    Fila* inserirNoFila(Fila *f, No *n);
    int vaziaFila(Fila *f);
    void imprimirFila(Fila *f);
    int buscarNoFila(Fila *f1, Fila *f2, Fila *f3, int *flag);
    Fila* removerNoFila(Fila *f,int n, No **AuxN);
    void liberarFila(Fila *f);
    void carregarFila(const char *n, Fila *f);
    void salvarFila(const char *n, Fila *f);

    //LISTA
    Lista* inicializarLista();
    Lista* inserirListaInicio(Lista *l, No* n); //FUNCAO TESTE
    int vaziaLista(Lista* l);
    void imprimirLista(Lista *l);
    int buscarNoPendente(Lista *lp);
    Lista* inserirNoListaConcluida(Lista *l, No *n);// funcionando
    void atualizarData(No* aux);                    // funciona
    Lista* inserirNoListaPendente(Lista *l, No *n);   // nao funcionando
    void imprimirListaConcluidas(Lista *l);
    No* removerNoLista(Lista *l, int n);            // nao sei se funciona
    void liberarLista(Lista *l);
    Lista* carregarLista(const char *n, Lista *l);
    void salvarLista(const char *n, Lista *l);
    

    //OUTRAS
    Tarefa novaTarefa(Fila *f1, Fila *f2, Fila *f3, Lista *lc, Lista *lp);
    int verificarCod(Fila *f1, Fila *f2, Fila *f3, Lista *lc, Lista *lp, int t);
    int DataValida(int dia, int mes, int ano);
    void imprimirTarefa(Tarefa T);
    int editar(Fila* f1,Fila* f2,Fila* f3, Lista* lp);
    Tarefa editarTarefa(Tarefa old);
    void verificarStatus(Fila *f1, Fila *f2, Fila *f3);
    int comparaData(No *n1, No *n2);                // nao sei se funciona




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
            f->fim->prox = novo; // se a fila nao estiver vazia
        }else{
            f->ini = novo; // se a fila estiver vazia
        }
        f->fim = novo;
        return f;
    }

    Fila* inserirNoFila(Fila *f, No *n){
        n->prox = NULL;
        if (f->fim != NULL){ // se a fila nao estiver vazia
            f->fim->prox = n;
        }else{ // se a fila estiver vazia
            f->ini = n;
        }
        f->fim = n; // o fim da fila recebe o novo nó
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

    int buscarNoFila(Fila *f1, Fila *f2, Fila *f3, int *flag){
        int code;
        No *aux;
        int check = 1;

        do{
            if (check == 0){
                printf("\tFalha na leitura do codigo tente novamente.");
            }
            printf("\n\tCaso deseje sair, digite 0");
            printf("\n\tDigite o codigo da tarefa que deseja editar:");
            fflush(stdin);
            check = scanf("%d", &code); // verificação de leitura
        } while (check == 0);

        if(code == 0){
            return 0; // retorna 0 caso o usuario deseje sair
        }else if(code < 0){
            return -1; // retorna -1 caso o codigo seja invalido
        }
        // Fila 1
        for (aux=f1->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                *flag = 1; // flag 1 caso a tarefa seja encontrada na fila 1
                return code;
            }
        }
        // Fila 2
        for (aux=f2->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                *flag = 2; // flag 2 caso a tarefa seja encontrada na fila 2
                return code;
            }
        }
        // Fila 3
        for (aux=f3->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                *flag = 3; // flag 3 caso a tarefa seja encontrada na fila 3
                return code;
            }
        }
        *flag = -1; // flag -1 caso o codigo seja invalido
        return -1;
        // retorna 0 caso o usuario deseje sair, ou caso o codigo seja invalido
    }

    Fila* removerNoFila(Fila *f,int n, No **AuxN){
        Fila* auxf = inicializarFila();
        No* aux = f->ini;
        No* aux2;
        // vai rodar a lista ate achar o no que a gente quer remover, enquanto nao achar
        // ele vai inserindo os nos na fila auxiliar
        while(aux->info.cod != n){
            // guardando a info do prox, pois ao inserir na fila auxiliar, aux->prox vai ser perdido
            aux2 = aux->prox;
            auxf = inserirNoFila(auxf, aux);
            aux = aux2; // aux recebe o prox
        }
        // achou o no que a gente quer remover, ele envia pra main atraves de um ponteiro
        *AuxN = aux;
        aux = aux->prox;
        // vai inserindo os resto dos nos na fila auxiliar
        while(aux != NULL){
            // guardando a info do prox, pois ao inserir na fila auxiliar, aux->prox vai ser perdido
            aux2 = aux->prox;
            auxf = inserirNoFila(auxf, aux);
            aux = aux2; // aux recebe o prox
        }
        // seta a fila original como a auxiliar e libera a auxiliar antes de retornar a fila
        free(f);
        return auxf;
    }

    void liberarFila(Fila *f){
        No *aux = f->ini;
        No *aux2;
        while(aux != NULL){
            aux2 = aux->prox;
            free(aux);
            aux = aux2;
        }
        free(f);
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


// FUNCOES LISTA
    Lista* inicializarLista(){
        Lista* l = (Lista*) malloc(sizeof(Lista));
        l->ini = NULL;
        return l;
    }

    int vaziaLista(Lista* l){
        return (l->ini == NULL);
    }

    void imprimirLista(Lista *l){
        if (vaziaLista(l)){
            printf("\n\n\t\t ==> LISTA VAZIA <==\n\n ");
        }else{
            No *aux = l->ini;
            while(aux != NULL){
                imprimirTarefa(aux->info);
                printf("\n");
                aux = aux->prox;
            }
        }
    }

    int buscarNoPendente(Lista *lp){
        int code;
        No *aux;
        int check = 1;

        do{
            if (check == 0){
                printf("\tFalha na leitura do codigo tente novamente.");
            }
            printf("\n\tCaso deseje sair, digite 0");
            printf("\n\tDigite o codigo da tarefa que deseja editar:");
            fflush(stdin);
            check = scanf("%d", &code); // verificação de leitura
        } while (check == 0);

        if(code == 0){
            return 0; // retorna 0 caso o usuario deseje sair
        }else if(code < 0){
            return -1; // retorna -1 caso o codigo seja invalido
        }
        // Lista pendentes
        if(vaziaLista(lp) == 0){
            for (aux = lp->ini; aux!=NULL; aux=aux->prox){
                if(aux->info.cod == code){
                    return code;
                }
            }
        }
        return -1;
    }

    Lista* inserirNoListaConcluida(Lista *l, No *n) {
        No *aux_l = l->ini;
        atualizarData(n);

        if (aux_l == NULL) { // se a lista estiver vazia insira o nó escolhido no início
            n->prox = NULL;
            l->ini = n;
            return l; // Saia da função após inserção na lista vazia
        }

        No *anterior = NULL;
        // Loop para encontrar a posição de inserção com base na data de término
        while(comparaData(aux_l, n) != 1 && aux_l != NULL) {
            anterior = aux_l;
            aux_l = aux_l->prox;
        }

        n->prox = aux_l; // O próximo do nó escolhido aponta para o nó da lista com data maior
        if (anterior != NULL) {
            anterior->prox = n; // Se o nó anterior não for nulo, atualize o próximo do nó anterior
        } else {
            l->ini = n; // Se o nó anterior for nulo, atualize o início da lista
        }
        return l; // Retorna a lista atualizada
    }

    void atualizarData(No* aux){
        time_t tempoAtual;
        struct tm *tempoInfo;
        time(&tempoAtual);          // Obtém o tempo atual em segundos desde a época
        tempoInfo = localtime(&tempoAtual); // Converte para uma estrutura tm
        aux->info.ter.dia = tempoInfo->tm_mday;
        aux->info.ter.mes = tempoInfo->tm_mon + 1; // Os meses são de 0 a 11, então adicionamos 1
        aux->info.ter.ano = tempoInfo->tm_year + 1900; // Os anos são desde 1900
    }

    Lista* inserirNoListaPendente(Lista *l, No *n){
        // Loop para encontrar a posição de inserção com base na prioridade
        No* aux = l->ini;
        No* anterior = NULL;
        // Se a lista estiver vazia insira o nó escolhido no início
        if(aux == NULL){
            n->prox = NULL;
            l->ini = n;
            return l;
        }
        // Busca a posicao de insercao com base na prioridade
        // Se a prioridade for igual, busca a posicao de insercao com base na data de termino
        if(n->info.prioridade == 1){
            while(comparaData(aux, n) != 1 && n->info.prioridade == aux->info.prioridade && aux != NULL){
                anterior = aux;
                aux = aux->prox;
            }
            // Insere o no na lista
            n->prox = aux;
            if(anterior != NULL){
                anterior->prox = n;
            }else{
                l->ini = n;
            }
        }else if(n->info.prioridade == 2){
            while(n->info.prioridade != aux->info.prioridade && aux != NULL && aux->info.prioridade != 3){
                anterior = aux;
                aux = aux->prox;
            }
            while(comparaData(aux, n) != 1 && n->info.prioridade == aux->info.prioridade && aux != NULL){
                anterior = aux;
                aux = aux->prox;
            }
            anterior = aux;
            aux = aux->prox;
            // Insere o no na lista
            n->prox = aux;
            if(anterior != NULL){
                anterior->prox = n;
            }else{
                l->ini = n;
            }
        }else{
            while(n->info.prioridade != aux->info.prioridade && aux != NULL){
                anterior = aux;
                aux = aux->prox;
            }
            while(comparaData(aux, n) != 1 && n->info.prioridade == aux->info.prioridade && aux != NULL){
                anterior = aux;
                aux = aux->prox;
            }
            anterior = aux;
            aux = aux->prox;
            // Insere o no na lista
            n->prox = aux;
            if(anterior != NULL){
                anterior->prox = n;
            }else{
                l->ini = n;
            }
        }
        // Retorna a lista atualizada
        return l;
    }



        /*No *aux_l = (*l)->ini;
        int flag = 0;

        if (aux_l == NULL) { // se a lista estiver vazia insira o nó escolhido no início
            n->prox = NULL;
            (*l)->ini = n;
            return; // Saia da função após inserção na lista vazia
        }

        No *anterior = NULL;
        // Prioridade alta
        if(n->info.prioridade == 1){
            // Loop para encontrar a posição de inserção com base na prioridade
            while (aux_l != NULL && (aux_l->info.prioridade != 1)) {
                anterior = aux_l;
                aux_l = aux_l->prox;
            }

        }
        // Prioridade normal
        else if(n->info.prioridade == 2){
            // Loop para encontrar a posição de inserção com base na prioridade
            while (aux_l != NULL && (aux_l->info.prioridade != 2)) {
                anterior = aux_l;
                aux_l = aux_l->prox;
            }
        }
        // Prioridade baixa
        else if(n->info.prioridade == 3){
            // Loop para encontrar a posição de inserção com base na prioridade
            while (aux_l != NULL && (aux_l->info.prioridade != 3)) {
                anterior = aux_l;
                aux_l = aux_l->prox;
            }
        }

        // Verifique se a prioridade coincide e compare as datas de término
        while (aux_l != NULL && (aux_l->info.prioridade == n->info.prioridade) && flag != 1) {
            if (comparaData(aux_l, n) != 1) { // Comparar data de término
                anterior = aux_l;
                aux_l = aux_l->prox;
            } else {
                flag = 1; // Pare o loop interno quando a data de término do nó for maior
            }
        }

        n->prox = aux_l; // O próximo do nó escolhido aponta para o nó da lista com data maior
        if (anterior != NULL) {
            anterior->prox = n; // Se o nó anterior não for nulo, atualize o próximo do nó anterior
        } else {
            (*l)->ini = n; // Se o nó anterior for nulo, atualize o início da lista
        }
    }*/

    void imprimirListaConcluidas(Lista *l){
        printf("Listar tarefas concluidas\n");
        printf("\n\tSelecione uma das opcoes");
        printf("\n\t1 - Imprimir lista de concluidas completa");
        printf("\n\t2 - Imprimir lista de concluidas com atraso");
        printf("\n\t3 - Imprimir lista de concluidas sem atraso");
        printf("\n\t0 - Retornar\n");

        //variaveis auxiliares

        //variaveis de controle
        int opcao_LC;
        scanf("%d", &opcao_LC);
        No *aux = l->ini;

        switch (opcao_LC){

            case 1:
                system("cls");
                imprimirLista(l);
                system("pause");
            break;

            case 2:
                system("cls");
                if (vaziaLista(l)){
                 printf("\n\n\t\t => LISTA VAZIA <==\n\n ");
                }else{
                    while (aux != NULL){
                        if(aux->info.status == 1) imprimirTarefa(aux->info);
                        printf("\n");
                        aux = aux->prox;
                    }
                }
                system("pause");
            break;

            case 3:
                system("cls");
                if (vaziaLista(l)){
                    printf("\n\n\t\t => LISTA VAZIA <==\n\n ");
                }else{
                    while (aux != NULL){
                        if(aux->info.status == 0) imprimirTarefa (aux->info);
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

    No* removerNoLista(Lista *l, int n){
        No *aux = l->ini;
        No *ant = NULL;
        while(aux != NULL && aux->info.cod != n){
            ant = aux;
            aux = aux->prox;
        }
        if(ant == NULL){ //remover o primeiro
            l->ini = aux->prox;
        }else{ //remover do meio ou do fim
            ant->prox = aux->prox;
        }
        return aux;
    }

    void liberarLista(Lista *l){
        No *aux = l->ini;
        No *aux2;
        while(aux != NULL){
            aux2 = aux->prox;
            free(aux);
            aux = aux2;
        }
        free(l);
    }

    Lista* carregarLista(const char *n, Lista *l){
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

            if (l->ini == NULL)
            {
                l->ini = novoNo;
            }
            else
            {
                l->ini->prox = novoNo;
            }
        }
        // fecha o arquivo pois nao necessita mais ser usado
        fclose(arq);
        return l;
    }

    void salvarLista(const char *n, Lista *l){
        FILE *arq;
        arq = fopen(n, "wt");
        if (arq == NULL)
        {
            printf("Erro ao abrir o arquivo.");
            exit(1);
        }
        No *q = l->ini;
        while (q != NULL)
        {
            fwrite(&q->info, sizeof(Tarefa), 1, arq);
            // fwrite(o que sera armazenado, qual o tamanho da infoi a ser salva, quantas infos serao salvas, aonde sera salvo
            q = q->prox;
        }
        fclose(arq);
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
        if(t <= 0) return 0;// nao pode tarefas com numeros negativos ou igual a 0
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

    int editar(Fila* f1,Fila* f2,Fila* f3, Lista* lp){
        int code;
        No* aux;
        int check = 1;

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
        if(code == 0){
            return 0; //
        }else if(code < 0){
            return -1; // retorna -1 caso o codigo seja invalido
        }
        // busca na Fila 1
        for(aux=f1->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                aux->info = editarTarefa(aux->info); //modifica a tarefa selecionada
                return 1; // retorna 1 caso a tarefa seja encontrada
            }
        }
        // busca na Fila 2
        for(aux=f2->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                aux->info = editarTarefa(aux->info); //modifica a tarefa selecionada
                return 1;
            }
        }
        // busca na Fila 3
        for(aux=f3->ini; aux!=NULL; aux=aux->prox){
            if(aux->info.cod == code){
                aux->info = editarTarefa(aux->info); //modifica a tarefa selecionada
                return 1;
            }
        }
        // busca na Lista pendentes
        if(vaziaLista(lp) == 0){
            for (aux = lp->ini; aux!=NULL; aux=aux->prox){
                if(aux->info.cod == code){
                    aux->info = editarTarefa(aux->info); //modifica a tarefa selecionada
                    return 1;
                }
            }
        }
        // retorna 0 caso o codigo seja invalido
        return -1;
    }

    Tarefa editarTarefa(Tarefa old){
        Tarefa new = old; // nova tarefa recebe todas as infos da tarefa antiga
        int check = 1;
        int check_data = 1;
        int opcao;
        int A = 0;

        while (A == 0){
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
            switch (opcao){
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
                // Setando data de inicio
                do{

                    if (check_data == 0){
                        printf("\tFormato de data invalido, tente novamente.");
                    }
                    printf("\n\tData de inicio anterior:%02d/%02d/%04d \n", old.ini.dia, old.ini.mes, old.ini.ano);
                    printf("\n\tDigite a nova data de inicio da tarefa: ");
                    check = 1;

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\n\tDigite o novo dia: ");
                        fflush(stdin);
                        check = scanf("%d", &new.ini.dia);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo mes: ");
                        fflush(stdin);
                        check = scanf("%d", &new.ini.mes);
                    }while(check == 0);

                    do{
                        if (check == 0)
                        {
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo ano: ");
                        fflush(stdin);
                        check = scanf("%d", &new.ini.ano);
                    }while(check == 0);
                    check_data = DataValida(new.ini.dia, new.ini.mes, new.ini.ano);
                }while(check_data != 1);
            break;

            case 4:
                do{
                    if (check_data == 0){
                        printf("\tFormato de data invalido, tente novamente.");
                    }
                    printf("\n\tData de termino anterior:%02d/%02d/%04d \n", old.ter.dia, old.ter.mes, old.ter.ano);
                    printf("\n\tDigite a nova data de termino da tarefa: ");
                    check = 1;

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\n\tDigite o novo dia:");
                        fflush(stdin);
                        check = scanf("%d", &new.ter.dia);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo mes: ");
                        fflush(stdin);
                        check = scanf("%d", &new.ter.mes);
                    }while(check == 0);

                    do{
                        if (check == 0){
                            printf("\tFalha na leitura do numero tente novamente.");
                        }
                        printf("\tDigite o novo ano: ");
                        fflush(stdin);
                        check = scanf("%d", &new.ter.ano);
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
        return old; // caso der erro ele cancela
    }

    void verificarStatus(Fila *f1, Fila *f2, Fila *f3) {
        // Obtendo a data e a hora atuais
        time_t tempoAtual;
        time(&tempoAtual);
        time_t tempoTerminoTarefa;
        struct tm DataTerminoTarefa;
        memset(&DataTerminoTarefa, 0, sizeof(struct tm)); // setando todos os campos com 0

        // atualizando as tarefas na fila 1
        No *faux = f1->ini;
        while (faux != NULL) {
            // Convertendo a data de termino da tarefa para o formato time_t
            DataTerminoTarefa.tm_year = faux->info.ter.ano - 1900; // Ano
            DataTerminoTarefa.tm_mon = faux->info.ter.mes - 1;     // Mês (0 a 11)
            DataTerminoTarefa.tm_mday = faux->info.ter.dia;
            tempoTerminoTarefa = mktime(&DataTerminoTarefa);
            // Cai dentro if provavelmente por receber datas menores que 1900 ou maiores de 2030, que na conversao se torna um int negativo
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

        // atualizando as tarefas na fila 2
        faux = f2->ini;
        while (faux != NULL) {
            // Convertendo a data de termino da tarefa para o formato time_t
            DataTerminoTarefa.tm_year = faux->info.ter.ano - 1900; // Ano
            DataTerminoTarefa.tm_mon = faux->info.ter.mes - 1;     // Mês (0 a 11)
            DataTerminoTarefa.tm_mday = faux->info.ter.dia;
            tempoTerminoTarefa = mktime(&DataTerminoTarefa);
            // Cai dentro if provavelmente por receber datas menores que 1900 ou maiores de 2030, que na conversao se torna um int negativo
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

        // atualizando as tarefas na fila 3
        faux = f3->ini;
        while (faux != NULL) {
            // Convertendo a data de termino da tarefa para o formato time_t
            DataTerminoTarefa.tm_year = faux->info.ter.ano - 1900; // Ano
            DataTerminoTarefa.tm_mon = faux->info.ter.mes - 1;     // Mês (0 a 11)
            DataTerminoTarefa.tm_mday = faux->info.ter.dia;
            tempoTerminoTarefa = mktime(&DataTerminoTarefa);
            // Cai dentro if provavelmente por receber datas menores que 1900 ou maiores de 2030, que na conversao se torna um int negativo
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


#endif // OurLibrary_H_INCLUDED
