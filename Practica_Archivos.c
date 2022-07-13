#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nombre{
    char nombre[20];
    char apellido_paterno[20];
    char apellido_materno[20];
};typedef struct nombre N;

struct direccion{
    char calle[20];
    int numero_calle;
    char colonia[20];
    char codigo_postal[10];
};typedef struct direccion D;

struct telefono{
    char numero[13];
    char descripcion[30];
};typedef struct telefono T;

struct fecha_nacimiento{
    char dia[3];
    char mes[3];
    char year[5];
};typedef struct fecha_nacimiento F;

struct persona{
    N nombre;
    D direccion;
    char correo[1000];
    int cuantos,borrado;
    T telefono[4];
    F fecha;
    char rfc[11];
};typedef struct persona P;

void altaEnAgenda(P*);
void generarRfc(N,F,char[11]);
void imprimirAgenda(P,int);
void imprimirUno(P);
int buscarPorNombre(N,FILE*,T[4]);
P buscarPorRfc(char[11],FILE*);
N buscarPorTelefono(P,char[13],int);
int agregarTelefono(P,N,int);
int buscarPorFechaNacimiento(N*,char[3],FILE*);
void imprimirMes(N*,int);
P modificar(int,int,FILE*);
int buscarPorNombre2(N,FILE*,T[4]);
P borrar(int,FILE*);

int main()
{
    int indice=0,op,op2,cuantos,i,pos,numPersonas;
    P agenda={NULL};
    T telefonos[4];
    N nombreBuscar,nombreImprimir,personasMes[30]={NULL},*apN=&personasMes[0];
    char rfcBuscar[11],telefono[13],mesBuscar[3];
    FILE *F;

    do{
      printf("\nElige una opcion \n 1. Dar de alta \n 2. Imprimir la agenda \n 3. Buscar por nombre \n 4. Buscar por RFC \n 5. Modificar Dato \n 6. Buscar por fecha de nacimiento \n 7. Borrar \n 8. Salir \n");
      scanf("%d",&op);
      switch(op){
        case 1:
            altaEnAgenda(&agenda);
            agenda.borrado=1;
            F=fopen("agenda.bin","ab");
            fwrite(&agenda,sizeof(P),1,F);
            fclose(F);
            break;

        case 2:
            F=fopen("agenda.bin","rb");
            i=0;

            fread(&agenda,sizeof(P),1,F);
            while(!feof(F)){
                imprimirAgenda(agenda,i);
                if(agenda.borrado==1){
                    i++;
                }
                fread(&agenda,sizeof(P),1,F);
            }
            fclose(F);
            break;

        case 3:
            printf("\nDame nombre a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.nombre);
            printf("Dame apellido paterno a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.apellido_paterno);
            printf("Dame apellido materno a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.apellido_materno);
            cuantos=buscarPorNombre(nombreBuscar,F,telefonos);
            if(cuantos!=-1){
                for(i=0;i<cuantos;i++){
                    printf("\n\tTelefono %d: %s\n\t\t    %s",i+1,telefonos[i].numero,telefonos[i].descripcion);
                }
            }else{
                printf("\n\nNo existe esa persona en la agenda\n\n");
            }
            break;


        case 4:
            printf("\nDame RFC a buscar\n");
            fflush(stdin);
            gets(rfcBuscar);
            agenda=buscarPorRfc(rfcBuscar,F);
            if(strcmp(agenda.rfc,"")!=0){
                imprimirUno(agenda);
            }else{
                printf("\n\nNo existe ese RFC en la agenda\n\n");
            }
            break;

        case 5:
            printf("\nDame nombre a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.nombre);
            printf("Dame apellido paterno a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.apellido_paterno);
            printf("Dame apellido materno a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.apellido_materno);
            cuantos=buscarPorNombre2(nombreBuscar,F,telefonos);
            if(cuantos!=-1){
                do{
                    printf("\nCampo a modificar:\n1.Nombre\n2.Direccion\n3.Correo\n4.Telefonos\n5.Fecha Nacimiento\n");
                    fflush(stdin);
                    scanf("%d",&op2);
                }while(op2>5 || op2<1);
                agenda=modificar(op2,cuantos,F);
                F=fopen("agenda.bin","r+b");
                fseek(F,sizeof(P)*cuantos,SEEK_SET);
                fwrite(&agenda,sizeof(P),1,F);
                fclose(F);
            }else{
                printf("\n\nNo existe esa persona en la agenda\n\n");
            }
            break;

        case 6:
            printf("\n\nDame el mes a buscar con dos digitos\n\n");
            fflush(stdin);
            gets(mesBuscar);
            numPersonas=buscarPorFechaNacimiento(apN,mesBuscar,F);
            imprimirMes(apN,numPersonas);
            break;

        case 7:
            printf("\nDame nombre a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.nombre);
            printf("Dame apellido paterno a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.apellido_paterno);
            printf("Dame apellido materno a buscar\n");
            fflush(stdin);
            gets(nombreBuscar.apellido_materno);
            cuantos=buscarPorNombre2(nombreBuscar,F,telefonos);
            if(cuantos!=-1){
                agenda=borrar(cuantos,F);
                F=fopen("agenda.bin","r+b");
                fseek(F,sizeof(P)*cuantos,SEEK_SET);
                fwrite(&agenda,sizeof(P),1,F);
                fclose(F);
            }else{
                printf("\n\nNo existe esa persona en la agenda\n\n");
            }
            break;

        case 8:
            break;
        default:
            printf("Esa no es una opcion valida, selecciona otra opcion \n");
            break;
      }
  }while(op!=8);
}


void altaEnAgenda(P *agenda){
    int i;

    printf("Dame tu nombre\n");
    fflush(stdin);
    gets(agenda->nombre.nombre);
    printf("Dame tu apellido paterno\n");
    fflush(stdin);
    gets(agenda->nombre.apellido_paterno);
    printf("Dame tu apellido materno\n");
    fflush(stdin);
    gets(agenda->nombre.apellido_materno);
    printf("Dame tu calle\n");
    fflush(stdin);
    gets(agenda->direccion.calle);
    printf("Dame tu numero de calle\n");
    fflush(stdin);
    scanf("%d",&(agenda->direccion.numero_calle));
    printf("Dame tu colonia\n");
    fflush(stdin);
    gets(agenda->direccion.colonia);
    printf("Dame tu codigo postal\n");
    fflush(stdin);
    gets(agenda->direccion.codigo_postal);
    do{
        printf("Cuantos telefonos quieres registrar \n");
        fflush(stdin);
        scanf("%d",&(agenda->cuantos));
        if(agenda->cuantos<4 && agenda->cuantos>0){
            for(i=0;i<agenda->cuantos;i++){
                printf("Dame el numero de telefono\n");
                fflush(stdin);
                gets(agenda->telefono[i].numero);
                printf("Dame la descripcion del numero de telefono\n");
                fflush(stdin);
                gets(agenda->telefono[i].descripcion);
            }
        }
    }while(agenda->cuantos>4 || agenda->cuantos<0);
    printf("Dame tu correo electronico\n");
    fflush(stdin);
    gets(agenda->correo);
    printf("Dame tu dia de nacimiento (dos digitos)\n");
    fflush(stdin);
    gets(agenda->fecha.dia);
    printf("Dame tu mes de nacimiento (dos digitos)\n");
    fflush(stdin);
    gets(agenda->fecha.mes);
    printf("Dame tu anio de nacimiento\n");
    fflush(stdin);
    gets(agenda->fecha.year);
    generarRfc(agenda->nombre,agenda->fecha,agenda->rfc);

}

void generarRfc(N nombre,F fecha,char rfc[11]){
  rfc[0]='\0';
  strncat(rfc,nombre.apellido_paterno,2);
  strncat(rfc,nombre.apellido_materno,1);
  strncat(rfc,nombre.nombre,1);
  rfc[4]=fecha.year[2];
  rfc[5]=fecha.year[3];
  rfc[6]='\0';
  strncat(rfc,fecha.mes,2);
  strncat(rfc,fecha.dia,2);
  strupr(rfc);

}

void imprimirAgenda(P agenda,int x){
    int i;
    if(agenda.borrado==1){
        printf("\nPersona %d:\n",x+1);
        printf("\n\tNombre:     %s %s %s",agenda.nombre.nombre,agenda.nombre.apellido_paterno,agenda.nombre.apellido_materno);
        printf("\n\tDireccion:  %s %d \n\t\t    Colonia %s \n\t\t    Codigo postal %s",agenda.direccion.calle,agenda.direccion.numero_calle,agenda.direccion.colonia,agenda.direccion.codigo_postal);
        printf("\n\tCorreo:     %s ",agenda.correo);
        printf("\n\tNumero de\n\ttelefonos:  %d",agenda.cuantos);
        for(i=0;i<agenda.cuantos;i++){
            printf("\n\tTelefono %d: %s\n\t\t    %s",i+1,agenda.telefono[i].numero,agenda.telefono[i].descripcion);
        }
        printf("\n\tFecha\n\tNacimiento: %s/%s/%c%c",agenda.fecha.dia,agenda.fecha.mes,agenda.fecha.year[2],agenda.fecha.year[3]);
        printf("\n\tRFC:        %s\n",agenda.rfc);
    }

}

void imprimirUno(P persona){
    int i;
    printf("\n\tNombre:     %s %s %s",persona.nombre.nombre,persona.nombre.apellido_paterno,persona.nombre.apellido_materno);
    printf("\n\tDireccion:  %s %d \n\t\t    Colonia %s \n\t\t    Codigo postal %s",persona.direccion.calle,persona.direccion.numero_calle,persona.direccion.colonia,persona.direccion.codigo_postal);
    printf("\n\tCorreo:     %s ",persona.correo);
    printf("\n\tNumero de\n\ttelefonos:  %d",persona.cuantos);
    for(i=0;i<persona.cuantos;i++){
        printf("\n\tTelefono %d: %s\n\t\t    %s",i+1,persona.telefono[i].numero,persona.telefono[i].descripcion);
    }
    printf("\n\tFecha\n\tNacimiento: %s/%s/%c%c",persona.fecha.dia,persona.fecha.mes,persona.fecha.year[2],persona.fecha.year[3]);
    printf("\n\tRFC:        %s\n",persona.rfc);
}

int buscarPorNombre(N nombreB,FILE *F,T telefonos[4]){
    int i,j;
    P agenda;

    F=fopen("agenda.bin","rb");
    fread(&agenda,sizeof(P),1,F);

    while(!feof(F)){
        if(agenda.borrado==1){
            if(strcmp(agenda.nombre.nombre,nombreB.nombre)==0 && strcmp(agenda.nombre.apellido_materno,nombreB.apellido_materno)==0 && strcmp(agenda.nombre.apellido_paterno,nombreB.apellido_paterno)==0){
                for(j=0;j<agenda.cuantos;j++){
                    telefonos[j]=agenda.telefono[j];
                }
                fclose(F);
                return agenda.cuantos;
            }
        }
        fread(&agenda,sizeof(P),1,F);
    }
    fclose(F);
    return -1;
}

P buscarPorRfc(char rfc[11],FILE *F){
    int i;
    P agenda,vacia={NULL};

    F=fopen("agenda.bin","rb");
    fread(&agenda,sizeof(P),1,F);

    while(!feof(F)){
        if(agenda.borrado==1){
            if(strcmp(rfc,agenda.rfc)==0){
                fclose(F);
                return agenda;
            }
        }
        fread(&agenda,sizeof(P),1,F);
    }
    fclose(F);
    return vacia;
}

int buscarPorNombre2(N nombreB,FILE *F,T telefonos[4]){
    int i,j,cont=0;
    P agenda;

    F=fopen("agenda.bin","rb");
    fread(&agenda,sizeof(P),1,F);

    while(!feof(F)){
        if(agenda.borrado==1){
            if(strcmp(agenda.nombre.nombre,nombreB.nombre)==0 && strcmp(agenda.nombre.apellido_materno,nombreB.apellido_materno)==0 && strcmp(agenda.nombre.apellido_paterno,nombreB.apellido_paterno)==0){
                fclose(F);
                return cont;
            }
        }
        cont++;
        fread(&agenda,sizeof(P),1,F);
    }
    fclose(F);
    return -1;
}

P modificar(int op,int pos,FILE *F){
    P agenda;
    int i;

    F=fopen("agenda.bin","rb");
    fseek(F,sizeof(P)*pos,SEEK_SET);
    fread(&agenda,sizeof(P),1,F);

    switch(op){

        case 1:
            printf("Dame tu nombre\n");
            fflush(stdin);
            gets(agenda.nombre.nombre);
            printf("Dame tu apellido paterno\n");
            fflush(stdin);
            gets(agenda.nombre.apellido_paterno);
            printf("Dame tu apellido materno\n");
            fflush(stdin);
            gets(agenda.nombre.apellido_materno);
            generarRfc(agenda.nombre,agenda.fecha,agenda.rfc);
            break;

        case 2:
            printf("Dame tu calle\n");
            fflush(stdin);
            gets(agenda.direccion.calle);
            printf("Dame tu numero de calle\n");
            fflush(stdin);
            scanf("%d",&(agenda.direccion.numero_calle));
            printf("Dame tu colonia\n");
            fflush(stdin);
            gets(agenda.direccion.colonia);
            printf("Dame tu codigo postal\n");
            fflush(stdin);
            gets(agenda.direccion.codigo_postal);
            break;

        case 3:
            printf("Dame tu correo electronico\n");
            fflush(stdin);
            gets(agenda.correo);
            break;

        case 4:
            do{
                printf("Cuantos telefonos quieres registrar \n");
                fflush(stdin);
                scanf("%d",&(agenda.cuantos));
                if(agenda.cuantos<4 && agenda.cuantos>0){
                    for(i=0;i<agenda.cuantos;i++){
                        printf("Dame el numero de telefono\n");
                        fflush(stdin);
                        gets(agenda.telefono[i].numero);
                        printf("Dame la descripcion del numero de telefono\n");
                        fflush(stdin);
                        gets(agenda.telefono[i].descripcion);
                    }
                }
            }while(agenda.cuantos>4 || agenda.cuantos<0);
            break;

        case 5:
            printf("Dame tu dia de nacimiento (dos digitos)\n");
            fflush(stdin);
            gets(agenda.fecha.dia);
            printf("Dame tu mes de nacimiento (dos digitos)\n");
            fflush(stdin);
            gets(agenda.fecha.mes);
            printf("Dame tu anio de nacimiento\n");
            fflush(stdin);
            gets(agenda.fecha.year);
            generarRfc(agenda.nombre,agenda.fecha,agenda.rfc);
            break;
    }
    fclose(F);
    return agenda;
}

int buscarPorFechaNacimiento(N *apN,char mes[3],FILE *F){
    int c=0;
    P agenda;

    F=fopen("agenda.bin","rb");

    fread(&agenda,sizeof(P),1,F);
    while(!feof(F)){
        if(strcmp(agenda.fecha.mes,mes)==0){
            *(apN+c)=agenda.nombre;
            c++;
        }
        fread(&agenda,sizeof(P),1,F);
    }
    fclose(F);
    return c;
}

void imprimirMes(N *apN,int numPersonas){
    int i;
    printf("\n\n %d Personas cumplen ese mes:\n\n",numPersonas);
    for(i=0;i<numPersonas;i++){
        printf("%s %s %s\n",(apN+i)->nombre,(apN+i)->apellido_paterno,(apN+i)->apellido_materno);
    }
}

P borrar(int pos,FILE *F){
    P agenda;

    F=fopen("agenda.bin","rb");
    fseek(F,sizeof(P)*pos,SEEK_SET);
    fread(&agenda,sizeof(P),1,F);
    agenda.borrado=0;
    fclose(F);

    return agenda;
}

/*
int i;
    P agenda,vacia={NULL};

    F=fopen("agenda.bin","rb");
    fread(&agenda,sizeof(P),1,F);

    while(!feof(F)){
        if(agenda.borrado==1){
            if(strcmp(rfc,agenda.rfc)==0){
                fclose(F);
                return agenda;
            }
        }
        fread(&agenda,sizeof(P),1,F);
    }
    fclose(F);
    return vacia;
*/
