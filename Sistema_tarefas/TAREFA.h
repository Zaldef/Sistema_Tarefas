#ifndef TAREFA_H_INCLUDED
#define TAREFA_H_INCLUDED

#define NUM_CHAR 30

typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct info{
    int cod; //codigo da tarefa
    char name[NUM_CHAR]; // nome da tarefa
    char proj[NUM_CHAR]; // á qual projeto a tarefa pertence
    Data ini; //data de inicio
    Data ter; //data de termino
    int status; //1 atrasada e 0 em dia e -1 pendente
}Tarefa;



Tarefa novaTarefa(){
    Tarefa T;
    printf("\n\tDigite o codigo da tarefa: ");
    scanf("%d", &T.cod);
    printf("\n\tDigite o nome da tarefa: ");
    fflush(stdin);
    gets(T.name);
    printf("\n\tDigite o nome do projeto que a tarefa pertence: ");
    fflush(stdin);
    gets(T.proj);
    printf("\n\tDigite a data de inicio da tarefa: ");
    printf("\n\tDigite o dia: ");
    scanf("%d",&T.ini.dia);
    printf("\tDigite o mes: ");
    scanf("%d",&T.ini.mes);
    printf("\tDigite o ano: ");
    scanf("%d",&T.ini.ano);
    printf("\n\tDigite a data de termino: ");
    scanf("%d",&T.ter.dia);
    printf("\tDigite o mes: ");
    scanf("%d",&T.ter.mes);
    printf("\tDigite o ano: ");
    scanf("%d",&T.ter.ano);
    return T;
}

Tarefa novaTarefaTeste(){
    Tarefa T;
    char a = 'a';
    T.cod = 1;
    T.name[0] = a;
    T.proj[0] = a;
    T.ini.ano = 2000;
    T.ini.mes = 01;
    T.ini.dia = 01;
    T.ter.ano = 2000;
    T.ter.mes = 02;
    T.ter.dia = 02;
    return T;
}

void imprimirTarefa(Tarefa T){
    printf("\n\tCodigo da tarefa: %d",T.cod);
    printf("\n\tNome da tarefa: %s",T.name);
    printf("\n\tNome do projeto: %s",T.proj);
    printf("\n\tData de Inicio: %d/%d/%d",T.ini.dia,T.ini.mes,T.ini.ano);
    printf("\n\tData de Termino: %d/%d/%d",T.ter.dia,T.ter.mes,T.ter.ano);
}

void salvarTarefa(FILE *arquivo, Tarefa tarefa) {

    fprintf(arquivo, "Código: %d\n", tarefa.cod);
    fprintf(arquivo, "Nome: %s\n", tarefa.name);
    fprintf(arquivo, "Projeto: %s\n", tarefa.proj);
    fprintf(arquivo, "Data de Início: %d/%d/%d\n", tarefa.ini.dia, tarefa.ini.mes, tarefa.ini.ano);
    fprintf(arquivo, "Data de Término: %d/%d/%d\n", tarefa.ter.dia, tarefa.ter.mes, tarefa.ter.ano);
    fprintf(arquivo, "Status: %d\n", tarefa.status);
    fprintf(arquivo, "--------------------------------\n");

}

Tarefa carregarTarefa(const char *nomeArquivo){
    FILE *arquivo;
    int linha =20;
    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(1);
        //return 1;
    }
    Tarefa T;
    sscanf(linha, "Código: %d", &T.cod);
    sscanf(linha, "Nome: %s", &T.name);
    sscanf(linha, "Projeto: %s", T.proj);
    sscanf(linha, "Data de Início: %d/%d/%d", &T.ini.dia, &T.ini.mes, &T.ini.ano);
    sscanf(linha, "Data de Término: %d/%d/%d", &T.ter.dia, &T.ter.mes, &T.ter.ano);
    sscanf(linha, "Status: %d", &T);

}

#endif // TAREFA_H_INCLUDED
