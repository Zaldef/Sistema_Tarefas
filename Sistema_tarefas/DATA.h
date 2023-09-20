#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

Data InsereData(){
    Data D;
    printf("\n\tDigite o dia: ");
    scanf("%d",&D.dia);
    printf("\tDigite o mes: ");
    scanf("%d",&D.mes);
    printf("\tDigite o ano: ");
    scanf("%d",&D.ano);
}


#endif // DATA_H_INCLUDED
