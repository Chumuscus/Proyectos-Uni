#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

struct cartas{
    char color[10];
    int numero;
    int x,y;
};typedef struct cartas C;

struct jugadores{
    C cartas[108];
    int numeroCartas;
};typedef struct jugadores J;

bool posicion_mouse(ALLEGRO_EVENT,int,int,int,int);
void revolver_cartas(C[108]);
int repartir_cartas(C[108],J[5],int);
void conseguir_posicion_cartas(J*);
int conseguir_carta_a_imprimir(C,ALLEGRO_BITMAP* [5][13]);
void imprimir_cartas_jugadores(J,ALLEGRO_BITMAP* [5][13],int);
int seleccion_carta(ALLEGRO_EVENT,J,ALLEGRO_BITMAP* [5][13],int,ALLEGRO_BITMAP*);
void imprimir_barajas(J,ALLEGRO_BITMAP* [5][13],int);
bool validar_jugar_cartas(C,C[108],int,char[20]);
bool validar_jugar_una_carta(C,C,char[20]);
void comer_cartas(J*,int*,C[108]);
void poner_carta(J*,J*,int,int*);
int rellenar_pila_comer(C[108],J[5],int);
void imprimir_texto_color(ALLEGRO_BITMAP* [4],int);
int levantar_cartas_comodin(ALLEGRO_EVENT,ALLEGRO_BITMAP* [5][13],int,ALLEGRO_BITMAP*);
int carta_comer(int,int);
bool validar_jugar_carta_comer(C[108],int);
bool validar_jugar_una_carta_comer(C);

int main()
{
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_init_image_addon();

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    ALLEGRO_DISPLAY* disp = al_create_display(1280, 720);

    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    ALLEGRO_BITMAP* imagenesCartas[5][13];
    ALLEGRO_BITMAP* textosColores[4];
    ALLEGRO_BITMAP* textosJugadores[4];
    ALLEGRO_BITMAP* menuPrincipal = al_load_bitmap("Assets/Menus/MenuPrincipal.png");
    ALLEGRO_BITMAP* menuJugadores = al_load_bitmap("Assets/Menus/MenuJugadores.png");
    ALLEGRO_BITMAP* menuColor = al_load_bitmap("Assets/Menus/MenuColor.png");
    ALLEGRO_BITMAP* menuGanador = al_load_bitmap("Assets/Menus/MenuGanador.png");
    ALLEGRO_BITMAP* menuEsperar = al_load_bitmap("Assets/Menus/MenuEsperar.png");
    ALLEGRO_BITMAP* fondo = al_load_bitmap("Assets/Menus/FondoIngame.png");
    ALLEGRO_BITMAP* botonComer = al_load_bitmap("Assets/Botones/BotonComer.png");
    ALLEGRO_BITMAP* botonSig = al_load_bitmap("Assets/Botones/BotonSig.png");
    textosColores[0] = al_load_bitmap("Assets/Textos/TextoAzul.png");
    textosColores[1] = al_load_bitmap("Assets/Textos/TextoRojo.png");
    textosColores[2] = al_load_bitmap("Assets/Textos/TextoVerde.png");
    textosColores[3] = al_load_bitmap("Assets/Textos/TextoAmarillo.png");
    textosJugadores[0] = al_load_bitmap("Assets/Textos/TextoJugador1.png");
    textosJugadores[1] = al_load_bitmap("Assets/Textos/TextoJugador2.png");
    textosJugadores[2] = al_load_bitmap("Assets/Textos/TextoJugador3.png");
    textosJugadores[3] = al_load_bitmap("Assets/Textos/TextoJugador4.png");


    ALLEGRO_EVENT event;

    srand(time(NULL));

    C cartas[108];
    J jugadores[5];
    bool click,puedeJugar,puedeJugar2,cartasComer=false,validar,finTurno;
    int estado=1,numeroJugadores,posicionBaraja,turno,turno2,posCarta=-1,reversa=1,i,j,negro=0,levantar=-1,acum=0,ganador;
    char img[30],color[20];

    FILE *F=fopen("cartas","rb");
    fread(cartas,sizeof(C),108,F);
    fclose(F);

    for(i=0;i<60;i++){
        if(i+1<10){
            sprintf(img,"Assets/Cartas/Cartas_%d%d.png",0,i+1);
        }else{
            sprintf(img,"Assets/Cartas/Cartas_%d.png",i+1);
        }
        imagenesCartas[i/13][i%13] = al_load_bitmap(img);
    }

    while(1){

        finTurno=false;

        if(estado==1){
            al_draw_bitmap(menuPrincipal,0,0,0);
            al_flip_display();
        }

        if(estado==2){
            al_draw_bitmap(menuJugadores,0,0,0);
            al_flip_display();
        }

        if(estado==3){

            al_draw_bitmap(fondo,0,0,0);
            turno2=turno%numeroJugadores;

            conseguir_posicion_cartas(&jugadores[turno2]);
            imprimir_cartas_jugadores(jugadores[turno2],imagenesCartas,-1);
            posCarta=seleccion_carta(event,jugadores[turno2],imagenesCartas,posCarta,fondo);
            al_draw_scaled_bitmap(textosJugadores[turno2],0,0,520,130,80,200,260,65,0);
            imprimir_barajas(jugadores[4],imagenesCartas,posicionBaraja);
            if(negro!=0){
                imprimir_texto_color(textosColores,negro);
            }
            if(cartasComer==true && acum==0){
                al_draw_bitmap(botonSig,1113,0,0);
                finTurno=true;
                if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                    if(posicion_mouse(event,1113,167,0,72)){
                        cartasComer=false;
                        if(reversa==1){
                            turno++;
                        }else{
                            turno--;
                        }
                    }
                }
            }
            if(cartasComer==false){
                puedeJugar=validar_jugar_cartas(jugadores[4].cartas[jugadores[4].numeroCartas-1],jugadores[turno2].cartas,jugadores[turno2].numeroCartas,color);
                if(puedeJugar==false){
                    al_draw_bitmap(botonComer,140,360,0);
                }
            }else{
                puedeJugar2=validar_jugar_carta_comer(jugadores[turno2].cartas,jugadores[turno2].numeroCartas);
                if(puedeJugar2==false){

                    for(i=0;i<acum;i++){
                        comer_cartas(&jugadores[turno2],&posicionBaraja,cartas);
                        printf("\n%d\n",posicionBaraja);
                        if(posicionBaraja>107){
                            for(i=0;i<jugadores[4].numeroCartas;i++){
                                printf("%d   %s   %d\n",i,jugadores[4].cartas[i].color,jugadores[4].cartas[i].numero);
                            }
                            posicionBaraja=rellenar_pila_comer(cartas,jugadores,numeroJugadores);
                            for(i=posicionBaraja;i<108;i++){
                                printf("%d   %s   %d\n",i,cartas[i].color,cartas[i].numero);
                            }
                        }
                    }
                    acum=0;
                }
            }
            al_flip_display();

        }

        if(estado==4){
            al_draw_bitmap(menuColor,0,0,0);
            levantar=levantar_cartas_comodin(event,imagenesCartas,levantar,menuColor);
            for(i=0;i<4;i++){
                if(levantar!=i){
                    al_draw_bitmap(imagenesCartas[4][i+3],125+(125+164)*i,330,0);
                }
            }
            al_flip_display();
        }

        if(estado==5){
            turno2=turno%numeroJugadores;
            al_draw_bitmap(menuEsperar,0,0,0);
            al_draw_bitmap(textosJugadores[turno2],375,200,0);
            al_flip_display();
        }

        if(estado==6){
            al_draw_bitmap(menuGanador,0,0,0);
            al_draw_bitmap(textosJugadores[ganador],375,200,0);
            al_flip_display();
        }

        if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            click=false;

            if(posicion_mouse(event,13,149,16,56)==true){
                estado=0;
                click=true;
            }

            if(estado==1 && posicion_mouse(event,437,400,309,150)==true && click==false){
                estado=2;
                click=true;
            }

            if(estado==2 && click==false){
                if(posicion_mouse(event,116,277,351,104)==true){
                    numeroJugadores=2;
                    click=true;
                }else if(posicion_mouse(event,498,277,352,104)==true){
                    numeroJugadores=3;
                    click=true;
                }else if(posicion_mouse(event,852,277,351,104)==true){
                    numeroJugadores=4;
                    click=true;
                }
                if(click==true){
                    estado=3;
                    turno=numeroJugadores*10000000;

                    do{
                        revolver_cartas(cartas);
                        posicionBaraja=repartir_cartas(cartas,jugadores,numeroJugadores);
                    }while(strcmp(cartas[posicionBaraja].color,"negro")==0 || cartas[posicionBaraja].numero>9);

                    jugadores[4].cartas[0]=cartas[posicionBaraja];
                    jugadores[4].numeroCartas=1;
                    posicionBaraja++;

                    printf("%d   %d\nBaraja Revuelta:\n\n",numeroJugadores,posicionBaraja);
                    for(i=0;i<108;i++){
                        printf("%d   %s   %d\n",i,cartas[i].color,cartas[i].numero);
                    }
                    printf("\nMano Jugadores:\n\n");
                    for(i=0;i<numeroJugadores;i++){
                        printf("Jugador %d    N Cartas %d\n",i,jugadores[i].numeroCartas);
                        for(j=0;j<7;j++){
                            printf("%d   %s   %d\n",i,jugadores[i].cartas[j].color,jugadores[i].cartas[j].numero);
                        }
                    }

                }
            }

            if(estado==3 && click==false && finTurno==false){
                if(posicion_mouse(event,jugadores[turno2].cartas[posCarta].x,164,jugadores[turno2].cartas[posCarta].y-50,234)==true && posCarta!=-1){
                    printf("La carta clickeada fue:   %s   %d\n",jugadores[turno2].cartas[posCarta].color,jugadores[turno2].cartas[posCarta].numero);
                    if(cartasComer==true){
                        validar=validar_jugar_una_carta_comer(jugadores[turno2].cartas[posCarta]);
                    }else{
                        validar=validar_jugar_una_carta(jugadores[4].cartas[jugadores[4].numeroCartas-1],jugadores[turno2].cartas[posCarta],color);
                    }
                    if(validar==true){
                        printf("La carta si se puede jugar\n");
                        printf("%d  %d\n",turno,turno2);
                        poner_carta(&jugadores[turno2],&jugadores[4],posCarta,&negro);
                        if(strcmp(jugadores[4].cartas[jugadores[4].numeroCartas-1].color,"negro")==0){
                            estado=4;
                            printf("\nSi fue negra\n");
                        }else{
                            estado=5;
                        }

                        if(jugadores[4].cartas[jugadores[4].numeroCartas-1].numero==10){
                            cartasComer=true;
                            acum=carta_comer(acum,2);
                        }else if(jugadores[4].cartas[jugadores[4].numeroCartas-1].numero==2 && estado==4){
                            cartasComer=true;
                            acum=carta_comer(acum,4);
                        }else if(jugadores[4].cartas[jugadores[4].numeroCartas-1].numero==11){
                            if(reversa==1){
                                turno++;
                            }else{
                                turno--;
                            }
                        }else if(jugadores[4].cartas[jugadores[4].numeroCartas-1].numero==12){
                            reversa=reversa*-1;
                        }
                        printf("La carta puesta fue: %s  %d",jugadores[4].cartas[jugadores[4].numeroCartas-1].color,jugadores[4].cartas[jugadores[4].numeroCartas-1].numero);
                        if(reversa==1){
                            turno++;
                        }else{
                            turno--;
                        }

                        if(jugadores[turno2].numeroCartas==0){
                            estado=6;
                            ganador=turno2;
                        }

                    }else{
                        printf("La carta no se puede jugar\n");
                    }
                    click=true;
                }else if(posicion_mouse(event,140,167,360,72)==true && cartasComer == true){
                    comer_cartas(&jugadores[turno2],&posicionBaraja,cartas);
                    printf("\n%d\n",posicionBaraja);
                    if(posicionBaraja>107){
                        for(i=0;i<jugadores[4].numeroCartas;i++){
                            printf("%d   %s   %d\n",i,jugadores[4].cartas[i].color,jugadores[4].cartas[i].numero);
                        }
                        posicionBaraja=rellenar_pila_comer(cartas,jugadores,numeroJugadores);
                        for(i=posicionBaraja;i<108;i++){
                            printf("%d   %s   %d\n",i,cartas[i].color,cartas[i].numero);
                        }
                    }

                    click=true;
                }
            }

            if(estado==4 && click==false){
                if(posicion_mouse(event,125,164,330,234)==true){
                    strcpy(color,"azul");
                    negro=1;
                    click=true;

                }else if(posicion_mouse(event,125+(164+125),164,330,234)==true){
                    strcpy(color,"rojo");
                    negro=2;
                    click=true;
                }else if(posicion_mouse(event,125+(164+125)*2,164,330,234)==true){
                    strcpy(color,"verde");
                    negro=3;
                    click=true;
                }else if(posicion_mouse(event,125+(164+125)*3,164,330,234)==true){
                    strcpy(color,"amarillo");
                    negro=4;
                    click=true;
                }
                if(click==true){
                    estado=5;
                    printf("\n%s\n",color);
                }
            }

            if(estado==5 && click==false){
                estado=3;
            }

        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || estado==0){
            break;
        }

        al_wait_for_event(queue, &event);
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
END_OF_MAIN();

bool posicion_mouse(ALLEGRO_EVENT event,int x,int w,int y,int h){

    if(event.mouse.x>=x && event.mouse.x<=x+w && event.mouse.y>=y && event.mouse.y<=y+h){
        return true;
    }else{
        return false;
    }
}

void revolver_cartas(C cartas[108]){
    int i,x;
    C aux;
    for(i=0;i<108;i++){
        x=i+rand()%(108-i);
        aux=cartas[i];
        cartas[i]=cartas[x];
        cartas[x]=aux;
    }
}

int repartir_cartas(C cartas[108],J jugadores[4],int numeroJugadores){
    int i;
    for(i=0;i<numeroJugadores*7;i++){
        jugadores[i/7].cartas[i%7]=cartas[i];
    }
    for(i=0;i<numeroJugadores;i++){
        jugadores[i].numeroCartas=7;
    }
    return numeroJugadores*7;
}

void conseguir_posicion_cartas(J *jugador){
    int i,x;

    x=(1000-jugador->numeroCartas*164)/(jugador->numeroCartas+1);
    for(i=0;i<jugador->numeroCartas;i++){
        jugador->cartas[i].x=140+(x+i*(x+164));
        jugador->cartas[i].y=481;
    }
}

int conseguir_carta_a_imprimir(C carta,ALLEGRO_BITMAP *imagenesCartas[5][13]){
    if(strcmp(carta.color,"azul")==0){
        return carta.numero;
    }else if(strcmp(carta.color,"rojo")==0){
        return 100+carta.numero;
    }else if(strcmp(carta.color,"verde")==0){
        return 200+carta.numero;
    }else if(strcmp(carta.color,"amarillo")==0){
        return 300+carta.numero;
    }else{
        return 400+carta.numero-1;
    }
}

void imprimir_cartas_jugadores(J jugador,ALLEGRO_BITMAP *imagenesCartas[5][13],int rest){
    int i,carta;

    for(i=0;i<jugador.numeroCartas;i++){
        if(i!=rest){
            carta=conseguir_carta_a_imprimir(jugador.cartas[i],imagenesCartas);
            al_draw_bitmap(imagenesCartas[carta/100][carta%100],jugador.cartas[i].x,jugador.cartas[i].y,0);
        }
    }
}

int seleccion_carta(ALLEGRO_EVENT event,J jugador,ALLEGRO_BITMAP *imagenesCartas[5][13],int posCarta,ALLEGRO_BITMAP *fondo){
    int i,y=234,carta;
    for(i=jugador.numeroCartas-1;i>=0;i--){
        if(posCarta==i){
            jugador.cartas[i].y=jugador.cartas[i].y-50;
            y=y+50;
        }
        if(posicion_mouse(event,jugador.cartas[i].x,164,jugador.cartas[i].y,y)==true){
            al_draw_bitmap(fondo,0,0,0);
            imprimir_cartas_jugadores(jugador,imagenesCartas,i);
            carta=conseguir_carta_a_imprimir(jugador.cartas[i],imagenesCartas);
            al_draw_bitmap(imagenesCartas[carta/100][carta%100],jugador.cartas[i].x,jugador.cartas[i].y,0);
            return i;
        }
    }
    return -1;
}

void imprimir_barajas(J barajaJugadas,ALLEGRO_BITMAP *imagenesCartas[5][13],int posicionBaraja){
    int i,carta;
    for(i=0;i<107-posicionBaraja;i++){
        al_draw_bitmap(imagenesCartas[4][7],394-i*.15,143-i*1.1,0); // 1.3 || 1.1
    }
    al_draw_bitmap(imagenesCartas[4][2],394-i*.15,143-i*1.1,0);

    for(i=0;i<barajaJugadas.numeroCartas-1;i++){
        al_draw_bitmap(imagenesCartas[4][7],722-i*.15,143-i*1.1,0);
    }

    carta=conseguir_carta_a_imprimir(barajaJugadas.cartas[barajaJugadas.numeroCartas-1],imagenesCartas);
    al_draw_bitmap(imagenesCartas[carta/100][carta%100],722-i*.15,143-i*1.1,0);
}

bool validar_jugar_cartas(C cartaJugada,C cartasJugador[108],int numeroCartas,char color[20]){
    int i;
    for(i=0;i<numeroCartas;i++){
        if(strcmp(cartaJugada.color,"negro")==0){
            if(strcmp(cartasJugador[i].color,"negro")==0 || strcmp(cartasJugador[i].color,color)==0){
                return true;
            }
        }else{
            if(strcmp(cartasJugador[i].color,"negro")==0 || strcmp(cartasJugador[i].color,cartaJugada.color)==0 || cartasJugador[i].numero==cartaJugada.numero){
                return true;
            }
        }
    }
    return false;
}

bool validar_jugar_una_carta(C cartaBaraja,C cartaJugador,char color[20]){

    if(strcmp(cartaBaraja.color,"negro")==0){
        if(strcmp(cartaJugador.color,"negro")==0 || strcmp(cartaJugador.color,color)==0){
            return true;
        }
    }else{
        if(strcmp(cartaJugador.color,"negro")==0 || strcmp(cartaJugador.color,cartaBaraja.color)==0 || cartaJugador.numero==cartaBaraja.numero){
            return true;
        }
    }
    return false;
}

void comer_cartas(J *jugador,int *posicionBaraja,C cartas[108]){

    jugador->cartas[jugador->numeroCartas]=cartas[*posicionBaraja];
    *posicionBaraja=*posicionBaraja+1;
    jugador->numeroCartas++;
}

void poner_carta(J *jugador,J *pila,int posCarta,int *negro){
    int i;

    jugador->numeroCartas=jugador->numeroCartas-1;
    pila->cartas[pila->numeroCartas]=jugador->cartas[posCarta];
    pila->numeroCartas=pila->numeroCartas+1;
    for(i=posCarta;i<jugador->numeroCartas;i++){
        jugador->cartas[i]=jugador->cartas[i+1];
    }
    if(*negro!=0){
        *negro=0;
    }

}

int rellenar_pila_comer(C cartas[108],J jugadores[5],int numeroJugadores){
    int i,j,nCartas,x;
    C aux;
    nCartas=jugadores[4].numeroCartas-1;
    jugadores[4].numeroCartas=1;

    printf("%d",nCartas);

    for(i=0;i<nCartas;i++){
        x=i+rand()%(nCartas-i);
        printf("%d   %s   %d    %d   %s   %d\n",i,jugadores[4].cartas[i].color,jugadores[4].cartas[i].numero,x,jugadores[4].cartas[x].color,jugadores[4].cartas[x].numero);
        aux=jugadores[4].cartas[i];
        jugadores[4].cartas[i]=jugadores[4].cartas[x];
        jugadores[4].cartas[x]=aux;
    }
    aux=jugadores[4].cartas[0];
    jugadores[4].cartas[0]=jugadores[4].cartas[i];
    jugadores[4].cartas[i]=aux;

    for(i=0;i<nCartas+1;i++){
        printf("%d   %s   %d\n",i,jugadores[4].cartas[i].color,jugadores[4].cartas[i].numero);
    }

    j=1;
    printf("\nnCartas  %d      108-nCartas  %d\n",nCartas,108-nCartas);
    for(i=108-nCartas;i<108;i++){
        printf("\n j %d     i %d ",j,i);
        cartas[i]=jugadores[4].cartas[j];
        j++;
    }
    return 108-nCartas;
}

void imprimir_texto_color(ALLEGRO_BITMAP *textos[4],int color){
    if(color==1){
        al_draw_bitmap(textos[0],925,200,0);
    }else if(color==2){
        al_draw_bitmap(textos[1],925,200,0);
    }else if(color==3){
        al_draw_bitmap(textos[2],925,200,0);
    }else{
        al_draw_bitmap(textos[3],925,200,0);
    }
}

int levantar_cartas_comodin(ALLEGRO_EVENT event,ALLEGRO_BITMAP *imagenesCartas[5][13],int mantener,ALLEGRO_BITMAP *menuColor){
    int y[4],i;

    for(i=0;i<4;i++){
        y[i]=0;
    }

    if(mantener!=-1){
        y[mantener]=50;
    }

    if(posicion_mouse(event,125,164,330-y[0],234+y[0])==true){
        al_draw_bitmap(imagenesCartas[4][3],125,280,0);
        return 0;
    }else if(posicion_mouse(event,125+(164+125),164,330-y[1],234+y[1])==true){
        al_draw_bitmap(imagenesCartas[4][4],125+(125+164)*1,280,0);
        return 1;
    }else if(posicion_mouse(event,125+(164+125)*2,164,330-y[2],234+y[2])==true){
        al_draw_bitmap(imagenesCartas[4][5],125+(125+164)*2,280,0);
        return 2;
    }else if(posicion_mouse(event,125+(164+125)*3,164,330-y[3],234+y[3])==true){
        al_draw_bitmap(imagenesCartas[4][6],125+(125+164)*3,280,0);
        return 3;
    }
    return -1;
}

int carta_comer(int acum,int cartasAComer){
    return acum+cartasAComer;
}

bool validar_jugar_carta_comer(C cartasJugador[108],int numeroCartas){
    int i;
    for(i=0;i<numeroCartas;i++){
        if(strcmp(cartasJugador[i].color,"negro")==0 && cartasJugador[i].numero==2){
            return true;
        }
        if(cartasJugador[i].numero==10){
            return true;
        }
    }
    return false;
}

bool validar_jugar_una_carta_comer(C carta){
    if(strcmp(carta.color,"negro")==0 && carta.numero==2){
        return true;
    }
    if(carta.numero==10){
        return true;
    }
    return false;
}
