#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct carros{
    char modelo[20];
    int cantidad;
    float precio;
};typedef struct carros C;

struct marcas{
    char nombre[20];
    C modelos[50];
    int cuantos;
    int total;
};typedef struct marcas M;

struct ventas{
    float ganancias;
    M vendidos[20];
    int cantidadMarcas;
    int ventast;
};typedef struct ventas V;

void imprimirReporte(V*,int,int);
void imprimir(M*,int);
void modeloSin(M*,int);
int anadirModelo(M*,int,char[20]);
int anadirMarca(M*,int*);
int vender(M*,V*,C*,int,char[20],int);
C* buscarModelo(M*,int,char[20]);

int main()
{
    M marcas[50],*apM;
    V ventas[12],*apV;
    C *apC;
    int op,op2,val,indice=2,aux,mes;
    char modelo[20];
    apM=&marcas[0];
    apV=&ventas[0];

    do{
        printf("\nSeleccione una opcion\n1.Agregar a inventario\n2.Mostrar inventario\n3.Realizar ventas\n4.Reporte de ventas mensuales\n5.Mostar modelos fuera de inventario\n0.Salir\n");
        scanf("%d",&op);
        switch(op){
            case 1:
                do{
                    printf("\nSeleccione una opcion\n1.Registrar Marca\n2.Registrar Modelo\n3.Modificar inventario de modelo\n4.Modificar precio de modelo\n0.Regresar\n");
                    scanf("%d",&op2);
                    switch(op2){
                        case 1:
                            val=anadirMarca(apM,&indice);
                            if(val==-1){
                                printf("\nNo es posible anadir mas marcas\n");
                            }else{
                                if(val==-2){
                                    printf("\nEsa marca ya esta registrada\n");
                                }
                            }
                            break;
                        case 2:
                            val=anadirModelo(apM,indice,"vacio123a");
                            if(val==-1){
                                printf("\nEsa marca no se encuentra registrada\n");
                            }else{
                                if(val==-2){
                                    printf("\nNo hay espacio para añadir la cantidad deseada de modelos\n");
                                }
                            }
                            break;
                        case 3:
                            printf("\nModelo a modificar\n");
                            fflush(stdin);
                            gets(modelo);
                            strupr(modelo);
                            apC=buscarModelo(apM,indice,modelo);
                            if(apC!=NULL){
                                printf("\nCuantos vehiculos de este modelo fueron recibidos? (O cuantos se retiran con -)\n");
                                scanf("%d",&aux);
                                if(apC->cantidad+aux>=0){
                                    apC->cantidad=apC->cantidad+aux;
                                }else{
                                    printf("\nEl inventario no puede ser menor a 0\n");
                                }
                            }else{
                                printf("\nEse modelo no se encuentra registrado\n");
                            }
                            break;
                        case 4:
                            printf("\nModelo a modificar\n");
                            fflush(stdin);
                            gets(modelo);
                            strupr(modelo);
                            apC=buscarModelo(apM,indice,modelo);
                            if(apC!=NULL){
                                printf("\nValor nuevo del precio\n");
                                scanf("%f",&apC->precio);
                            }else{
                                printf("\nEse modelo no se encuentra registrado\n");
                            }
                            break;
                        case 0:
                            break;
                        default:
                            printf("\nOpcion invalida\n");
                            break;
                    }
                }while(op2!=0);
                break;
            case 2:
                imprimir(apM,indice);
                break;
            case 3:
                printf("\nModelo a vender\n");
                fflush(stdin);
                gets(modelo);
                strupr(modelo);
                apC=buscarModelo(apM,indice,modelo);
                if(apC!=NULL){
                    if(apC->cantidad>0){
                        val=1;
                    }else{
                        printf("\nEse modelo no cuenta con inventario\n");
                        val=0;
                    }
                }else{
                    printf("\nEse modelo no se encuentra registrado\n");
                    val=0;
                }
                if(val==1){
                    do{
                        printf("\nMes de la venta (Entre 1 y 12)\n");
                        scanf("%d",&mes);
                        if(mes>12 || mes<1){
                            printf("\nMes invalido\n");
                        }
                    }while(mes>12 || mes<1);
                    val=vender(apM,apV,apC,indice,modelo,mes-1);
                }
                break;
            case 4:
                do{
                    printf("\n1.Imprimir reporte de un solo mes\n2.Imprimir todos los reportes\n0.Regresar\n");
                    scanf("%d",&op2);
                    switch(op2){
                        case 1:
                            do{
                                printf("\nMes del reporte (Entre 1 y 12)\n");
                                scanf("%d",&mes);
                                if(mes>12 || mes<1){
                                    printf("\nMes invalido\n");
                                }
                            }while(mes>12 || mes<1);
                            imprimirReporte(apV,mes-1,1);
                            break;
                        case 2:
                            imprimirReporte(apV,0,12);
                            break;
                        case 0:
                            break;
                        default:
                            printf("\nOpcion invalida\n");
                            break;
                    }
                }while(op2!=0);
                break;
            case 5:
                modeloSin(apM,indice);
                break;
            case 0:
                break;
            default:
                printf("\nOpcion invalida\n");
                break;
        }
    }while(op!=0);
    return 0;
}

int anadirModelo(M *apM,int indice,char aux[20]){
    int i,j=0,pos=0,band=0,cant,inv;
    float precio;
    char nom[20];
    C *apC;
    if(strcmp(aux,"vacio123a")==0){
        printf("\nMarca del modelo a anadir\n");
        fflush(stdin);
        gets(nom);
        strupr(nom);
    }else{
        strcpy(nom,aux);
    }
    while(pos<indice && band==0){
        if(strcmp((nom),((apM+pos)->nombre))==0){
            band=1;
            apC=&((apM+pos)->modelos[0]);
        }else{
            pos++;
        }
    }
    if(band==0){
        return -1;
    }

    printf("\nCuantos modelos desea anadir?\n");
    scanf("%d",&cant);
    if((apM+i)->cuantos+cant>50){
        return -2;
    }
    for(i=0;i<cant;i++){
        printf("\nNombre del modelo a anadir\n");
        fflush(stdin);
        gets(nom);
        strupr(nom);
        j=0;
        while(j<(apM+pos)->cuantos && band!=2){
            if(strcmp(nom,(apC+j)->modelo)==0){
                band=2;
                printf("\nEse modelo ya se encuentra registrado\n");
            }else{
                j++;
            }
        }
        if(band!=2){
            printf("\nCual es el precio del modelo?\n");
            scanf("%f",&precio);
            printf("\nCuantos autos de este modelo se tienen en inventario?\n");
            scanf("%d",&inv);
            strcpy((apC+(apM+pos)->cuantos)->modelo,nom);
            (apC+(apM+pos)->cuantos)->precio=precio;
            (apC+(apM+pos)->cuantos)->cantidad=inv;
            (apM+pos)->cuantos=(apM+pos)->cuantos+1;
        }
    }
    return 1;
}

int anadirMarca(M *apM,int *indice){
    char nom[20];
    M aux;
    int i,j,mar,val;
    if(*indice==50){
        return -1;
    }
    printf("\nNombre de la marca a anadir\n");
    fflush(stdin);
    gets(nom);
    for(i=0;i<*indice;i++){
        if(strcmp(nom,(apM+i)->nombre)==0){
            return -2;
        }
    }
    strcpy((apM+*indice)->nombre,strupr(nom));
    *indice=*indice+1;
    for(i=0;i<*indice;i++){
        for(j=0;j<*indice-1;j++){
            if(strcmp((apM+j)->nombre,(apM+j+1)->nombre)>0){
                aux=*(apM+j);
                *(apM+j)=*(apM+j+1);
                *(apM+j+1)=aux;
            }
        }
    }
    do{
        printf("Desea anadir modelos para esta marca?\n1.Si\n2.No\n");
        scanf("%d",&mar);
        switch(mar){
            case 1:
                val=anadirModelo(apM,*indice,nom);
                if(val==-2){
                    printf("\nNo hay espacio para añadir la cantidad deseada de modelos\n");
                }
                break;
            case 2:
                break;
            default:
                printf("\nOpcion invalida\n");
                break;
        }
    }while(mar!=2 && mar!=1);
    return 1;
}

int vender(M *apM,V *apV,C *apC,int indice,char modelo[20],int mes){
    int i,j,rev=0,posMar=0,posMod=0;
    C *apC2;
    M *apM2;
    char marca[20];
    apM2=&((apV+mes)->vendidos);

    (apV+mes)->ganancias=(apV+mes)->ganancias+apC->precio;
    apC->cantidad=apC->cantidad-1;
    (apV+mes)->ventast=(apV+mes)->ventast+1;

    for(i=0;i<indice;i++){
        apC2=&((apM+i)->modelos[0]);
        for(j=0;j<(apM+i)->cuantos;j++){
            if(strcmp((apC2+j)->modelo,modelo)==0){
                strcpy(marca,(apM+i)->nombre);
            }
        }
    }

    while(posMar<(apV+mes)->cantidadMarcas && rev==0){
        if(strcmp((apM2+posMar)->nombre,marca)==0){
            rev=1;
        }else{
            posMar++;
        }
    }
    if(rev==1){
        (apM2+posMar)->total=(apM2+posMar)->total+1;
        rev=0;
        apC2=&((apM2+posMar)->modelos);
        while(posMod<(apM2+posMar)->cuantos && rev==0){
            if(strcmp((apC2+posMod)->modelo,modelo)==0){
                rev=1;
            }else{
                posMod++;
            }
        }
        if(rev==1){
            (apC2+posMod)->cantidad=(apC2+posMod)->cantidad+1;
        }else{
            strcpy((apC2+(apM2+posMar)->cuantos)->modelo,modelo);
            (apC2+(apM2+posMar)->cuantos)->cantidad=1;
            (apM2+posMar)->cuantos=(apM2+posMar)->cuantos+1;
        }
    }else{
        apC2=&((apM2+(apV+mes)->cantidadMarcas)->modelos[0]);
        strcpy((apM2+(apV+mes)->cantidadMarcas)->nombre,marca);
        (apM2+(apV+mes)->cantidadMarcas)->cuantos=1;
        strcpy(apC2->modelo,modelo);
        apC2->cantidad=1;
        (apV+mes)->cantidadMarcas=(apV+mes)->cantidadMarcas+1;
    }
}

void imprimir(M *apM,int indice){
    int i,j,tot=0;
    C *apC;
    for(i=0;i<indice;i++){
        if((apM+i)->cuantos>0){
            apC=&((apM+i)->modelos[0]);
            (apM+i)->total=0;
            printf("\n%s:\n",(apM+i)->nombre);
            for(j=0;j<(apM+i)->cuantos;j++){
                printf("   %s - %d\n",(apC+j)->modelo,(apC+j)->cantidad);
                printf("\t Precio del modelo: %.2f\n",(apC+j)->precio);
                tot=tot+(apC+j)->cantidad;
                (apM+i)->total=(apM+i)->total+(apC+j)->cantidad;
            }
            printf("\nInventario total de %s : %d\n",(apM+i)->nombre,(apM+i)->total);
        }
    }
    printf("\nSe cuentan con %d vehiculos en inventario\n",tot);
}

C* buscarModelo(M *apM,int indice,char modelo[20]){
    int i,j;
    C *apC;
    for(i=0;i<indice;i++){
        apC=&((apM+i)->modelos[0]);
        for(j=0;j<(apM+i)->cuantos;j++){
            if(strcmp((apC+j)->modelo,modelo)==0){
                return (apC+j);
            }
        }
    }
    return NULL;
}

void modeloSin(M *apM,int indice){
    int i,j,band=0;
    C *apC;
    for(i=0;i<indice;i++){
        if((apM+i)->cuantos>0){
            band=0;
            apC=&((apM+i)->modelos[0]);
            j=0;
            while(band==0 && j<(apM+i)->cuantos){
                if((apC+j)->cantidad==0){
                    band=1;
                }else{
                    j++;
                }
            }
            if(band==1){
                printf("\n%s:\n",(apM+i)->nombre);
                for(j=0;j<(apM+i)->cuantos;j++){
                    if((apC+j)->cantidad==0){
                        printf("   %s - %d\n",(apC+j)->modelo,(apC+j)->cantidad);
                        printf("\t Precio del modelo: %.2f\n",(apC+j)->precio);
                    }
                }
            }
        }
    }
}

void imprimirReporte(V *apV,int mes,int cant){
    int i,j,k,tot=0,maxMod=0,maxMar=0,minMar=9999999,sinVend[50];
    M *apM;
    C *apC;
    char maxMarNom[20],maxModNom[20],minMarNom[20];
    apM=&((apV+mes)->vendidos[0]);
    for(k=mes;k<mes+cant;k++){
        maxMod=0;
        maxMar=0;
        minMar=9999999;
        tot=0;
        maxMarNom[0]='\0';
        maxModNom[0]='\0';
        minMarNom[0]='\0';
        printf("\nReporte del mes %d\n\n",k+1);
        for(i=0;i<(apV+k)->cantidadMarcas;i++){
            if((apM+i)->cuantos>0){
                apC=&((apM+i)->modelos[0]);
                (apM+i)->total=0;
                printf("\n%s:\n",(apM+i)->nombre);
                for(j=0;j<(apM+i)->cuantos;j++){
                    printf("   %s - %d\n",(apC+j)->modelo,(apC+j)->cantidad);
                    tot=tot+(apC+j)->cantidad;
                    (apM+i)->total=(apM+i)->total+(apC+j)->cantidad;
                    if((apC+j)->cantidad>maxMod){
                        maxMod=(apC+j)->cantidad;
                        strcpy(maxModNom,(apC+j)->modelo);
                    }
                }
                printf("\Las ventas totales de %s son %d\n",(apM+i)->nombre,(apM+i)->total);
                if((apM+i)->total>maxMar){
                    maxMar=(apM+i)->total;
                    strcpy(maxMarNom,(apM+i)->nombre);
                }
                if((apM+i)->total<minMar){
                    minMar=(apM+i)->total;
                    strcpy(minMarNom,(apM+i)->nombre);
                }
            }
        }
        if(minMar==9999999){
            minMar=0;
        }
        printf("\nLas ventas totales de la agencia en el mes son %d y los ingresos totales %.2f\n",tot,(apV+k)->ganancias);
        printf("La marca mas vendida fue %s con %d ventas\nEl modelo mas vendido fue %s con %d ventas\n",maxMarNom,maxMar,maxModNom,maxMod);
        printf("La marca menos vendida fue %s con %d ventas\n",minMarNom,minMar);
    }
}
