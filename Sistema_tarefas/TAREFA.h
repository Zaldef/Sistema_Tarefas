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
    char proj[NUM_CHAR]; // � qual projeto a tarefa pertence
    Data ini; //data de inicio
    Data ter; //data de termino
    int status; //1 atrasada e 0 em dia e -1 pendente
}Tarefa;

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

Tarefa novaTarefa(){
    Tarefa T;
    int check = 1;
    int check_data = 1;
    do{
        if (check == 0){
            printf("\tFalha na leitura do codigo tente novamente.");
        }
        printf("\n\tDigite o codigo da tarefa: ");
        fflush(stdin);
        check = scanf("%d", &T.cod);
    }while(check == 0);

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

Tarefa editarTarefa(Tarefa old){
    Tarefa new;
    int check = 1;
    int check_data = 1;
    new.cod = old.cod;

    system("cls");
    printf("\n\tEditando a tarefa %d\n", new.cod);

    printf("\n\tNome anterior da tarefa: %s",old.name);
    printf("\n\tDigite o novo nome: ");
    fflush(stdin);
    gets(new.name);

    printf("\n\tNome anterior do projeto: %s",old.proj);
    printf("\n\tDigite o novo nome do projeto que a tarefa pertence: ");
    fflush(stdin);
    gets(new.proj);

    do{
        if (check_data == 0){
            printf("\tFormato de data invalido, tente novamente.");
        }
        printf("\n\tData anterior:%02d/%02d/%04d \n",old.ini.dia,old.ini.mes,old.ini.ano);
        printf("\n\tDigite a nova data de inicio da tarefa: ");
        check = 1;
        do{
            if (check == 0){
                printf("\tFalha na leitura do numero tente novamente.");
            }
            printf("\n\tDigite o novo dia:");

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

    do{
        if (check_data == 0){
            printf("\tFormato de data invalido, tente novamente.");
        }
        printf("\n\tData anterior:%02d/%02d/%04d \n",old.ter.dia,old.ter.mes,old.ter.ano);
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

    return new;
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

#endif // TAREFA_H_INCLUDED
