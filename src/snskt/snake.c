#include "defs.h"
#include <stdlib.h>
#include "snskt/snake.h"
#include "ray/raylib.h"
#include "stdio.h"

// nodos a aniadir cuando se come
#define na 5

// offset de coordenadas para el collider de la cabeza
#define offset_coll_cabeza 3
// size para el collider de la cabeza
#define size_coll_cabeza offset_coll_cabeza*2

// offset de coordenadas para el collider de la comida
#define offset_coll_comida 16
// size para el collider de la comida
#define size_coll_comida offset_coll_comida*2


void setup_snake(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    
    // tamanio de la ventana
    jueguito_vars->sH = 700;
    jueguito_vars->sW = 1000;
    
    // inicializacion de las variables del jueguito
    jueguito_vars->dir_anterior = 0;
    jueguito_vars->dir = 0;
    jueguito_vars->velocidad = 6;
    jueguito_vars->estados = 1;
    jueguito_vars->nodos_aniadir = 0;
    jueguito_vars->nodos_cantidad = 0;
    jueguito_vars->nodo_collider = NULL;

    // inicializacion de la posicion de la comida
    jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
    jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);

    // inicializacion de la posicion de la serpiente y poner null en su sig
    snake_cabeza->x = (f32)jueguito_vars->sW/4;
    snake_cabeza->y = (f32)jueguito_vars->sH/4;
    
    // inicializacion de los recs colliders
    jueguito_vars->coll_cabeza = (Rectangle){snake_cabeza->x-offset_coll_cabeza,
                                             snake_cabeza->y-offset_coll_cabeza,
                                             size_coll_cabeza,
                                             size_coll_cabeza};
    
    jueguito_vars->coll_comida = (Rectangle){jueguito_vars->comida_x-offset_coll_comida,
                                             jueguito_vars->comida_y-offset_coll_comida,
                                             size_coll_comida,
                                             size_coll_comida};

    // por si el juego ya habia empezado entonces se borran todos los nodos
    // que la serpiente tenia
    if(snake_cabeza->sig != NULL){
        nodoSnake_t *tmp = snake_cabeza->sig;
        nodoSnake_t *tmp_borrar;
        snake_cabeza->sig = NULL;
        while(1){
            tmp_borrar = tmp;
            if(tmp->sig == NULL){
                tmp = NULL;
                MemFree(tmp_borrar);
                break;
            }else{
                tmp = tmp->sig;
                MemFree(tmp_borrar);
            }
        }
    }
}

void update_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars){
    // Checar si ya perdio
    if(!(jueguito_vars->estados & 1)){
        setup_snake(snake_cabeza,jueguito_vars);
    }

    // esto para comparar si se cambio de direccion para saber si poner un nodo mas en los nodos colliders
    jueguito_vars->dir_anterior = jueguito_vars->dir;

    // Antes de que cambie de coordenadas la serpiente hay que darle la posicion anterior
    // a su nodos
    snake_cabeza->last_x = snake_cabeza->x;
    snake_cabeza->last_y = snake_cabeza->y;
    if(snake_cabeza->sig != NULL){
        snake_cabeza->sig->last_x = snake_cabeza->sig->x;
        snake_cabeza->sig->last_y = snake_cabeza->sig->y;
        snake_cabeza->sig->x = snake_cabeza->last_x;
        snake_cabeza->sig->y = snake_cabeza->last_y;
    }

    
    // Reiniciar el jueguito
    if(IsKeyPressed(KEY_I)) setup_snake(snake_cabeza,jueguito_vars);
    
    // Input
    if(IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT)) jueguito_vars->dir = jueguito_vars->dir == 1 ? 1:0;
    if(IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT)) jueguito_vars->dir = jueguito_vars->dir == 0 ? 0:1;
    if(IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP)) jueguito_vars->dir = jueguito_vars->dir == 3 ? 3:2;
    if(IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN)) jueguito_vars->dir = jueguito_vars->dir == 2 ? 2:3;

    // Cambiar direccion
    switch (jueguito_vars->dir){
        case 0:
            snake_cabeza->x += jueguito_vars->velocidad;
            break;
        case 1:
            snake_cabeza->x -= jueguito_vars->velocidad;
            break;
        case 2:
            snake_cabeza->y -= jueguito_vars->velocidad;
            break;
        case 3:
            snake_cabeza->y += jueguito_vars->velocidad;
            break;
    }

    if(snake_cabeza->y > jueguito_vars->sH + 5) snake_cabeza->y = 0;
    if(snake_cabeza->y < - 5) snake_cabeza->y = jueguito_vars->sH;
    
    if(snake_cabeza->x > jueguito_vars->sW + 5) snake_cabeza->x = 0;
    if(snake_cabeza->x < - 5) snake_cabeza->x = jueguito_vars->sW;
    
    //jueguito_vars->estados = jueguito_vars->estados & 251;
    nodoSnake_t *nodo_temp = snake_cabeza;
    jueguito_vars->nodos_cantidad = 0;

    while (nodo_temp->sig != NULL){
        jueguito_vars->nodos_cantidad += 1;
        if(jueguito_vars->nodos_cantidad == 15)
            jueguito_vars->nodo_collider = nodo_temp;
        nodo_temp = nodo_temp->sig;
        if(nodo_temp->sig != NULL){
            nodo_temp->sig->last_x = nodo_temp->sig->x;
            nodo_temp->sig->last_y = nodo_temp->sig->y;
            nodo_temp->sig->x = nodo_temp->last_x;
            nodo_temp->sig->y = nodo_temp->last_y;
        }
    }

    if(jueguito_vars->nodos_aniadir > 0){
        nodo_temp->sig = MemAlloc(sizeof(nodoSnake_t));
        nodo_temp->sig->y = nodo_temp->last_y;
        nodo_temp->sig->x = nodo_temp->last_x;
        nodo_temp->sig->sig = NULL;
        jueguito_vars->nodos_aniadir -= 1;
        if(jueguito_vars->nodos_aniadir < 0) jueguito_vars->nodos_aniadir = 0;
    }

    jueguito_vars->coll_cabeza.x = snake_cabeza->x-offset_coll_cabeza;
    jueguito_vars->coll_cabeza.y = snake_cabeza->y-offset_coll_cabeza;

    

    //Checar si colisionan los rectangulos de la cabeza y la comida
    if(CheckCollisionRecs(jueguito_vars->coll_cabeza,
                          jueguito_vars->coll_comida  )){
        jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
        jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);
        jueguito_vars->coll_comida.x = jueguito_vars->comida_x - offset_coll_comida;
        jueguito_vars->coll_comida.y = jueguito_vars->comida_y - offset_coll_comida;
        jueguito_vars->nodos_aniadir += na;
    
    }
    
    // Checar si colisiona con su cola
    if(jueguito_vars->nodo_collider != NULL){
        nodo_temp = jueguito_vars->nodo_collider;
        while (nodo_temp!=NULL){
            if(CheckCollisionRecs((Rectangle){nodo_temp->x-2,nodo_temp->y-2,4,4},
                                jueguito_vars->coll_cabeza)){
                // operacion estados AND 1111 1110 es igual a estados ???? ???0
                jueguito_vars->estados = jueguito_vars->estados & 254; 
                break;
            }
            nodo_temp = nodo_temp->sig;
        }
    }
   
    
}


void draw_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars){
    // Dibujar serpiente
    nodoSnake_t *nodo_temp = snake_cabeza;
    while(nodo_temp != NULL){
        DrawCircle(nodo_temp->x,nodo_temp->y,10,BLUE);
        nodo_temp = nodo_temp->sig;
    }
    
    // Dibujar comida
    DrawCircle(jueguito_vars->comida_x,jueguito_vars->comida_y,8,BLACK);

    // Para dibujar los colliders
    /*DrawRectangleLinesEx(jueguito_vars->coll_cabeza,1,RED);
    DrawRectangleLinesEx(jueguito_vars->coll_comida,1,RED);
    if(jueguito_vars->nodo_collider != NULL){
        nodo_temp = jueguito_vars->nodo_collider;
        while (nodo_temp!=NULL){
            DrawRectangleLinesEx((Rectangle){nodo_temp->x-2,
                                        nodo_temp->y-2,
                                        4,4}
            ,1,RED);
            nodo_temp = nodo_temp->sig;
        }
        
        
    }*/

    // Dibujar score
    DrawText(TextFormat("%i",jueguito_vars->nodos_cantidad), 20, jueguito_vars->sH-50,50,SKYBLUE);
    //DrawText(TextFormat("%i",jueguito_vars->estados), jueguito_vars->sW-20, jueguito_vars->sH-50,50,RED);

    
}



/*
    1.- problema con generar recs collider para q se muera el gusano
        Nodos cada vez que cambia de direccion:
        El primer nodo va ser ek 15 y de ahi ek ultimo o el que cambia de direccion

        si el siguiente nodo tiene un x o y diferente entonces es porq la serpiente
        ocupa un cuadro nuevo
        0 es cabeza, o es un nodo
                o-------o-------0 
                |
                |
                |
                |         o
                o---------o
        cada vez que se cambie de una direccion se va a generar un nodo
        para generar un collider rectangulo  

        1.1- Hacer un array de nodos
            los nodos van a ser del 15 al ultimo, y entre medio de estos van
            ser los que esten cambiando de direccion al gusano
*/
