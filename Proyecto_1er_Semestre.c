#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int rcl[10],rr[10],i,j,k,r,c,ncl,nren,nr,nobj,nt,av,b,b1,b2,b3,b4,t=0;
    char m[50][50],ro[10][3]={' '},aux[2]={' '};

    // Pedir datos
    do{
        printf("Cuantas columnas quiere en el tablero?\nEntre 10 y 50\nNumero: ");
        scanf("%d",&ncl);
        // Fuera de rango
        if (ncl < 10 || ncl > 50){
            printf("\n\tFuera del rango! Vuelve a intentarlo!\n\n");
        }
    }while(ncl>50 || ncl<10);
    do{
        printf("Cuantos renglones quiere en el tablero?\nEntre 10 y 50\nNumero: ");
        scanf("%d",&nren);
        // Fuera de rango
        if (nren > 50 || nren < 10){
            printf("\n\tFuera del rango! Vuelve a intentarlo!\n\n");
        }
    }while(nren>50 || nren<10);
    do{
        printf("Cuantos robots quiere?\nEntre 1 y 10\nNumero: ");
        scanf("%d",&nr);
        // Fuera de rango
        if (nr > 10 || nr < 1){
            printf("\n\tFuera del rango! Vuelve a intentarlo!\n\n");
        }
    }while(nr>10 || nr<1);
    do{
        printf("Cuantos objetos quiere?\nDebe ser mayor al doble del numero de robots y menor a 30\nNumero: ");
        scanf("%d",&nobj);
        // Fuera de rango
        if (nobj > 30 || nobj<=nr*2){
            printf("\n\tFuera del rango! Vuelve a intentarlo!\n\n");
        }
    }while(nobj>30 || nobj<=nr*2);
    do{
        printf("Cuantos turnos quiere?\nDe 2 en adelante\n");
        scanf("%d",&nt);
        if (nt<2){
            printf("\n\tFuera de rango! Vuelve a intentarlo!\n\n");
        }
    }while(nt<2);

    // Por el base 0, resta 1
    nren--;
    ncl--;

    // Llena el tablero con "*" hasta donde lo menciona el usuario
    for(i=0;i<=nren;i++){
        for(j=0;j<=ncl;j++){
            m[i][j]='*';
        }
    }

    // Llena el tablero con Robots
    i=0;
    while(i!=nr){
        // x, y Aleatorios
        r=rand()%(nren+1);
        c=rand()%(ncl+1);
        // Si no hay otro robot, entonces ponlo como robot
        if(m[r][c]=='*'){
            // Guarda las cordenadas del bot, siendo que "i" es el # del bot
            rcl[i]=c;
            rr[i]=r;
            // Estados del objeto 'R' sin objeto
            ro[i][0]='R';
            // Lo coloca en el principal
            m[r][c]='R';
            i++;
        }
    }
    // Llena el tablero con Objetos
    i=0;
    while(i!=nobj){
        // x, y Aleatorios
        r=rand()%(nren+1);
        c=rand()%(ncl+1);

        // Si no hay otro objeto, entonces ponlo como objeto
        if(m[r][c]=='*'){
            // Opcion random del 1 a 4
            av=rand()%4+1;
            switch(av){
            case 1:
                m[r][c]='o';
                break;
            case 2:
                m[r][c]='e';
                break;
            case 3:
                m[r][c]='i';
                break;
            case 4:
                m[r][c]='u';
                break;
            }
            i++;
        }
    }
    system("cls");
    // Impresion del tablero general de INICIO
    printf("\nEstado inicial!\n");
    for(i=0;i<=nren;i++){
        for(j=0;j<=ncl;j++){
            printf("%c  ",m[i][j]);
        }
        printf("\n");
    }

    //
    do{
        sleep(1);
        system("cls");
        t++;
        for(i=0;i<nr;i++){ // Movimiento del robot
            b1=0; b2=0; b3=0; b4=0; // Si todos son 0 entonces se puede mover a cualquier direccion.

            if(rr[i]!=0){ // Si no esta en la primera fila del tablero
                if(m[rr[i]-1][rcl[i]]!='*'){ // Si NO hay un lugar disposible en la posicion del bot, notifica que no se puede mover hacia arriba.
                    b1=1;
                }
            }else{ // No se puede mover hacia arriba
                b1=1;
            }

            if(rcl[i]!=ncl){ // Si no esta en la ultima columna del tablero
                if(m[rr[i]][rcl[i]+1]!='*'){ // Si NO hay un lugar disposible en la posicion del bot, notifica que no se puede mover hacia la derecha.
                    b2=2;
                }
            }else{ // No se puede mover hacia la derecha
                b2=2;
            }

            if(rr[i]!=nren){ // Si no esta en la ultima fila del tablero
                if(m[rr[i]+1][rcl[i]]!='*'){ // Si NO hay un lugar disposible en la posicion del bot, notifica que no se puede mover hacia la abajo.
                    b3=3;
                }
            }else{ // No se puede mover hacia abajo
                b3=3;
            }

            if(rcl[i]!=0){ // Si no esta en la primera columna
                if(m[rr[i]][rcl[i]-1]!='*'){ // Si NO hay un lugar disposible en la posicion del bot, notifica que no se puede mover hacia la izq.
                    b4=4;
                }
            }else{ // No se puede mover hacia la izq
                b4=4;
            }

            if(b1+b2+b3+b4!=10){ // Si tiene bloqueado los 4 lados entonces no hagas.
                do{ // Saca un # rand mientras no se igual a un bx; Si bx son 0 entonces se mueve a cualquier posicion.
                    av=rand()%4+1;
                }while(av==b1 || av==b2 || av==b3 || av==b4);

                m[rr[i]][rcl[i]]='*'; // Limpia la posicion actual del robot

                switch(av){
                case 1:
                    rr[i]=rr[i]-1;
                    break;
                case 2:
                    rcl[i]=rcl[i]+1;
                    break;
                case 3:
                    rr[i]=rr[i]+1;
                    break;
                case 4:
                    rcl[i]=rcl[i]-1;
                    break;
                }
                m[rr[i]][rcl[i]]='R'; // Recoloca el robot
            }
        }

        for(i=0;i<nr;i++){ // Recoleccion de objetos
            b=0;
            if(rr[i]!=0){ // Si no esta en la primera fila
                if(m[rr[i]-1][rcl[i]]!='*' && m[rr[i]-1][rcl[i]]!='R'){ // Si NO hay un lugar disponible y no hay un robot = Es un objeto
                    if(strlen(ro[i])== 1){ // Si no tiene un objeto
                        aux[0]=m[rr[i]-1][rcl[i]]; // Copia el valor del objeto
                        strncat(ro[i],aux,1); // Pasa el objeto a "ro" en el 2do elemento
                        m[rr[i]-1][rcl[i]]='*'; // Limpia la casilla
                    }else{ // Si tiene un objeto
                        aux[0]=m[rr[i]-1][rcl[i]]; // Copia el valor del objeto de la casilla
                        m[rr[i]-1][rcl[i]]=ro[i][1]; // Remplaza el objeto de la casilla por el objeto del robot
                        ro[i][1]=aux[0]; //Pasa el objeto al robot
                    }
                    b=1;
                }
            }

            if(rcl[i]!=ncl && b==0){ // Si no esta en la ultima columna && No tomo un objeto con anterioridad
                if(m[rr[i]][rcl[i]+1]!='*' && m[rr[i]][rcl[i]+1]!='R'){
                    if(strlen(ro[i])== 1){
                        aux[0]=m[rr[i]][rcl[i]+1];
                        strncat(ro[i],aux,1);
                        m[rr[i]][rcl[i]+1]='*';
                    }else{
                        aux[0]=m[rr[i]][rcl[i]+1];
                        m[rr[i]][rcl[i]+1]=ro[i][1];
                        ro[i][1]=aux[0];
                    }
                    b=1;
                }
            }

            if(rr[i]!=nren && b==0){ // Si no esta en la ultima fila && No tomo un objeto con anterioridad
                if(m[rr[i]+1][rcl[i]]!='*' && m[rr[i]+1][rcl[i]]!='R'){
                    if(strlen(ro[i])== 1){
                        aux[0]=m[rr[i]+1][rcl[i]];
                        strncat(ro[i],aux,1);
                        m[rr[i]+1][rcl[i]]='*';
                    }else{
                        aux[0]=m[rr[i]+1][rcl[i]];
                        m[rr[i]+1][rcl[i]]=ro[i][1];
                        ro[i][1]=aux[0];
                    }
                    b=1;
                }
            }

            if(rcl[i]!=0 && b==0){ // Si no esta en la primera columna && No tomo un objeto con anterioridad
                if(m[rr[i]][rcl[i]-1]!='*' && m[rr[i]][rcl[i]-1]!='R'){
                    if(strlen(ro[i])== 1){
                        aux[0]=m[rr[i]][rcl[i]-1];
                        strncat(ro[i],aux,1);
                        m[rr[i]][rcl[i]-1]='*';
                    }else{
                        aux[0]=m[rr[i]][rcl[i]-1];
                        m[rr[i]][rcl[i]-1]=ro[i][1];
                        ro[i][1]=aux[0];
                    }
                }
            }
        }
        // Impresion del tablero
        printf("\nTurno %d\n",t);
        for(i=0;i<=nren;i++){ //     Fila
            for(j=0;j<=ncl;j++){ //  Columna
                if(m[i][j]=='R'){ // Si hay un robot
                    for(k=0;k<nr;k++){ // Repite por el numero de robots
                        if(i==rr[k] && j==rcl[k]){ // Si la fila == numero de robot en fila && Columna == numero de robot en columna
                            if(strlen(ro[k])== 1){ // Si no tiene Objeto
                                printf("%s  ",ro[k]); // Imprime que un espacio
                            }else{  // Si tiene un objeto
                                printf("%s ",ro[k]); // Imprime el objeto que tiene
                            }
                        }
                    }
                }else{ // Si no hay robot, imprime el tablero normal
                    printf("%c  ",m[i][j]);
                }
            }
            printf("\n");
        }
    }while(t!=nt); // Repite hasta los turnos del usuario
    printf("\n"); system("pause"); // Debug Alec
    return 0;
}
