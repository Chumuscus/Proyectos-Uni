#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tablero[6][6],i,j,p1,p2,ganar=0,turno=0,pJ[2],repTurno=0,direccion,posI,posJ,lineaDibujada,direccionCuadrado,cuadradosLlenos=0;
    char cuadrados[5][5],lineas[12][6],nJ[2];

    pJ[0]=0;
    pJ[1]=0;

    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            tablero[i][j]=i*6+j+1;
        }
    }

    for(i=0;i<12;i++){
        for(j=0;j<6;j++){
            lineas[i][j]=' ';
        }
    }


    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            cuadrados[i][j]=' ';
        }
    }

    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            printf("  %2d  ",tablero[i][j]);
            if(j!=5){
                printf("%c",lineas[i*2][j]);
            }
        }
            printf("\n");
        if(i!=5){
            for(j=0;j<6;j++){
                printf("   %c  ",lineas[i*2+1][j]);
                if(j!=5){
                    printf("%c",cuadrados[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\nLetra del jugador 1: ");
    fflush(stdin);
    scanf("%c",&nJ[0]);
    printf("\nLetra del jugador 2: ");
    fflush(stdin);
    scanf("%c",&nJ[1]);

    while(ganar==0){

        repTurno=0;

        printf("\nPuntos del jugador 1 %c : %d\nPuntos del jugador 2 %c : %d",nJ[0],pJ[0],nJ[1],pJ[1]);

        printf("\n\nTurno del jugador %d : %c\n\n",turno+1,nJ[turno]);

        for(i=0;i<6;i++){
            for(j=0;j<6;j++){
                printf("  %2d  ",tablero[i][j]);
                if(j!=5){
                    printf("%c",lineas[i*2][j]);
                }
            }
                printf("\n");
            if(i!=5){
                for(j=0;j<6;j++){
                    printf("   %c  ",lineas[i*2+1][j]);
                    if(j!=5){
                        printf("%c",cuadrados[i][j]);
                    }
                }
            }
            printf("\n");
        }

        do{
            printf("\nPrimer punto para conectar ");
            fflush(stdin);
            scanf("%d",&p1);
        }while(p1>36 || p1<1);

        do{
            printf("\nSegundo punto para conectar ");
            fflush(stdin);
            scanf("%d",&p2);
        }while(p2>36 || p2<1);

        direccion=0;

        if((p1-1)/6!=0){
            if(p1-6==p2){
                direccion=1;
            }
        }

        if(p1%6!=0 && direccion==0){
            if(p1+1==p2){
                direccion=2;
            }
        }

        if((p1-1)/6!=5 && direccion==0){
            if(p1+6==p2){
                direccion=3;
            }
        }

        if(p1%6!=1 && direccion==0){
            if(p1-1==p2){
                direccion=4;
            }
        }

        if(direccion==0){

            printf("\nERROR\nLos puntos no pertenecen al mismo cuadrado\nSe te restara un punto\n");
            pJ[turno]=pJ[turno]-1;

        }else{

            posI=-1;
            posJ=-1;
            i=0;
            j=0;

            while(posI==-1 && posJ==-1){
                while(posI==-1 && posJ==-1 && j<6){
                    if(p1==tablero[i][j]){
                        posI=i;
                        posJ=j;
                    }
                    j++;
                }
                j=0;
                i++;
            }

            lineaDibujada=0;

            switch(direccion){
                case 1:

                    if(lineas[(posI*2)-1][posJ]==' '){
                        posI=(posI*2)-1;
                        lineas[posI][posJ]='|';
                    }else{
                        lineaDibujada=1;
                    }
                    break;

                case 2:

                    if(lineas[posI*2][posJ]==' '){
                        posI=posI*2;
                        lineas[posI][posJ]='-';
                    }else{
                        lineaDibujada=1;
                    }
                    break;

                case 3:

                    if(lineas[(posI*2)+1][posJ]==' '){
                        posI=(posI*2)+1;
                        lineas[posI][posJ]='|';
                    }else{
                        lineaDibujada=1;
                    }
                    break;

                case 4:

                    if(lineas[posI*2][posJ-1]==' '){
                        posI=posI*2;
                        posJ=posJ-1;
                        lineas[posI][posJ]='-';
                    }else{
                        lineaDibujada=1;
                    }
                    break;

            }

            if(lineaDibujada==1){

            printf("\nERROR\nLa linea ya habia sido dibujada antes\nSe te restara un punto\n");
            pJ[turno]=pJ[turno]-1;

            }else{
                direccionCuadrado=0;
                switch(direccion){

                    case 1: case 3:

                        if(posJ!=5){
                            if(lineas[posI-1][posJ] != ' ' && lineas[posI][posJ+1] != ' ' && lineas[posI+1][posJ] != ' '){
                                cuadrados[(posI-1)/2][posJ]=nJ[turno];
                                pJ[turno]=pJ[turno]+1;
                                repTurno=1;
                                cuadradosLlenos=cuadradosLlenos+1;
                            }
                        }
                        if(posJ!=0){
                            if(lineas[posI-1][posJ-1] != ' ' && lineas[posI][posJ-1] != ' ' && lineas[posI+1][posJ-1] != ' '){
                                cuadrados[(posI-1)/2][posJ-1]=nJ[turno];
                                pJ[turno]=pJ[turno]+1;
                                repTurno=1;
                                cuadradosLlenos=cuadradosLlenos+1;
                            }
                        }
                        break;

                    case 2: case 4:

                        if(posI!=0){
                            if(lineas[posI-1][posJ] != ' ' && lineas[posI-2][posJ] != ' ' && lineas[posI-1][posJ+1] != ' '){
                                cuadrados[(posI/2)-1][posJ]=nJ[turno];
                                pJ[turno]=pJ[turno]+1;
                                repTurno=1;
                                cuadradosLlenos=cuadradosLlenos+1;
                            }
                        }
                        if(posI!=5){
                            if(lineas[posI+1][posJ] != ' ' && lineas[posI+2][posJ] != ' ' && lineas[posI+1][posJ+1] != ' '){
                                cuadrados[(posI/2)][posJ]=nJ[turno];
                                pJ[turno]=pJ[turno]+1;
                                repTurno=1;
                                cuadradosLlenos=cuadradosLlenos+1;
                            }

                        }


                        break;

                }
            }

        }

        if(cuadradosLlenos==25){
            if(pJ[0]==pJ[1]){
                ganar=3;
            }else{
                if(pJ[0]>pJ[1]){
                    ganar=1;
                }else{
                    ganar=2;
                }
            }
        }

        if(repTurno==0){
            if(turno==0){
                turno=1;
            }else{
                turno=0;
            }
        }

    }

    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            printf("  %2d  ",tablero[i][j]);
            if(j!=5){
                printf("%c",lineas[i*2][j]);
            }
        }
            printf("\n");
        if(i!=5){
            for(j=0;j<6;j++){
                printf("   %c  ",lineas[i*2+1][j]);
                if(j!=5){
                    printf("%c",cuadrados[i][j]);
                }
            }
        }
        printf("\n");
    }

    printf("\nPuntos del jugador 1 %c : %d\nPuntos del jugador 2 %c : %d\n\n",nJ[0],pJ[0],nJ[1],pJ[1]);

    if(ganar==3){
        printf("\n\nEmpate, ambos jugadores consiguieron %d puntos\n\n",pJ[0]);
    }else{
        printf("\n\nFelicidades, gano el jugador %d %c\n\n",ganar,nJ[ganar-1]);
    }

    return 0;
}
