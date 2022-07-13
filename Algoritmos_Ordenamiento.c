#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX 10000

void llena(int*);
void imprime(int*,int);
bool comparar(int*,int,int);
void swap(int*,int,int);
int bubble(int*);
int bubble_revisar(int*);
int bubble_mejorado(int*);
int bubble_mejorado_revisar(int*);
int simple(int*);
int simple_revisar(int*);
int selection_sort(int*);


double what_time_is_it()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}

int main()
{
    int i,j,numCiclos=0,arr[MAX][50],*ap=&arr[0][0];
    clock_t t;
    double tiempoCPU,tiempoReal;
    srand(time(NULL));

    llena(ap);

    printf("\nVector Desordenado:\nNumero de Ciclos : %d   %d\n",numCiclos,sizeof(arr));
    //imprime(ap,0);

    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=bubble(ap+MAX*1);
    t=clock()-t;
    printf("\nBubble:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,1,0) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,1);


    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=bubble_revisar(ap+MAX*2);
    t=clock()-t;
    printf("\nBubble Revisar:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,2,1) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,2);


    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=bubble_mejorado(ap+MAX*3);
    t=clock()-t;
    printf("\nBubble Mejorado:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,3,2) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,3);


    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=bubble_mejorado_revisar(ap+MAX*4);
    t=clock()-t;
    printf("\nBubble Mejorado Revisar:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,4,3) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,4);


    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=simple(ap+MAX*5);
    t=clock()-t;
    printf("\nSimple:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,5,4) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,5);


    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=simple_revisar(ap+MAX*6);
    t=clock()-t;
    printf("\nSimple Revisar:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,6,5) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,6);


    t=clock();
    tiempoReal=what_time_is_it();
    numCiclos=selection_sort(ap+MAX*7);
    t=clock()-t;
    printf("\nSelection Sort:\nNumero de Ciclos : %d\nIgual: %s",numCiclos,comparar(ap,7,6) ? "true" : "false");
    printf("\nClocks: %ld    Tiempo CPU: %lf     Tiempo Real: %lf\n",t,((double)t)/CLOCKS_PER_SEC,what_time_is_it()-tiempoReal);
    //imprime(ap,7);


    /*for(i=0;i<10;i++){
        imprime(ap,i);
    }*/



    return 0;
}

void llena(int *ap){

    int i,j;

    for(i = 0; i<MAX; i++){
        *(ap+i)=rand()%10000;
    }
    for(i = 1; i<10; i++){
        for(j = 0; j<MAX; j++){
            *(ap+i*MAX+j)=*(ap+j);
        }
    }

}

void imprime(int *ap,int pos){

    printf("\n\n");
    for(int i = 0; i<MAX; i++){
        printf("%5d ",*(ap+pos*MAX+i));
    }

}

bool comparar(int *ap,int pos1,int pos2){

    int i;

    for(int i = 0; i<MAX; i++){
        if(*(ap+pos1*MAX+i) != *(ap+pos2*MAX+i)){
            return false;
        }
    }

    return true;

}

void swap(int *ap,int x, int y){

    int aux;

    aux=*(ap+x);
    *(ap+x)=*(ap+y);
    *(ap+y)=aux;

}

int bubble(int *ap){

    int nCiclos=0,aux,i,j;

    for(i = 0; i<MAX; i++){
        for(j = 0; j<MAX-1; j++){
            nCiclos++;
            if(*(ap+j)>*(ap+j+1)){
                swap(ap,j,j+1);
            }
        }
    }

    return nCiclos;
}

int bubble_revisar(int *ap){

    int nCiclos=0,aux,i,j,b;

    for(i = 0; i<MAX; i++){
        b=1;
        for(j = 0; j<MAX-1; j++){
            nCiclos++;
            if(*(ap+j)>*(ap+j+1)){
                swap(ap,j,j+1);
                b=0;
            }
        }
        if(b)
            return nCiclos;

    }

    return nCiclos;
}

int bubble_mejorado(int *ap){

    int nCiclos=0,aux,i,j;

    for(i = 0; i<MAX; i++){
        for(j = 0; j<MAX-i-1; j++){
            nCiclos++;
            if(*(ap+j)>*(ap+j+1)){
                swap(ap,j,j+1);
            }
        }
    }

    return nCiclos;
}

int bubble_mejorado_revisar(int *ap){

    int nCiclos=0,aux,i,j,b;

    for(i = 0; i<MAX; i++){
        b=1;
        for(j = 0; j<MAX-i-1; j++){
            nCiclos++;
            if(*(ap+j)>*(ap+j+1)){
                swap(ap,j,j+1);
                b=0;
            }
        }
        if(b)
            return nCiclos;
    }

    return nCiclos;
}

int simple(int *ap){

    int nCiclos=0,aux,i,j;

    for(i = 0; i<MAX; i++){
        for(j = i+1; j<MAX; j++){
            nCiclos++;
            if(*(ap+j)<*(ap+i)){
                swap(ap,j,i);
            }
        }
    }

    return nCiclos;
}

int simple_revisar(int *ap){

    int nCiclos=0,aux,i,j,b;

    for(i = 0; i<MAX; i++){
        b=1;
        for(j = i+1; j<MAX; j++){
            nCiclos++;
            if(*(ap+j)<*(ap+i)){
                swap(ap,i,j);
                b=0;
            }
        }

        if(b)
            return nCiclos;
    }

    return nCiclos;
}

int selection_sort(int *ap){

    int i,j,valorMenor,nCiclos=0;

    for(i = 0; i<MAX-1; i++){
        valorMenor=i;
        for(j = i; j<MAX; j++){
            nCiclos++;
            if(*(ap+j)<*(ap+valorMenor)){
                valorMenor=j;
            }
        }
        swap(ap,i,valorMenor);
    }

    return nCiclos;
}
