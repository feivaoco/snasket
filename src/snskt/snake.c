#include "defs.h"
#include <stdlib.h>
#include "snskt/snake.h"
#include "ray/raylib.h"
#include "stdio.h"

// nodos a aniadir cuando se come
#define na 5

void setup_snake(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    
   
    jueguito_vars->sH = 450;
    jueguito_vars->sW = 800;
    
    jueguito_vars->dir_anterior = 0;
    jueguito_vars->dir = 0;
    jueguito_vars->velocidad = 6;
    jueguito_vars->estados = 1;
    jueguito_vars->nodos_aniadir = 0;
    jueguito_vars->nodos_cantidad = 0;

    jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
    jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);

    snake_cabeza->x = (f32)jueguito_vars->sW/4;
    snake_cabeza->y = (f32)jueguito_vars->sH/4;
    snake_cabeza->sig = NULL;

    

    jueguito_vars->coll_cabeza = (Rectangle){snake_cabeza->x-7,
                                             snake_cabeza->y-7,
                                             14,
                                             14};
    
    jueguito_vars->coll_comida = (Rectangle){jueguito_vars->comida_x-11,
                                             jueguito_vars->comida_y-11,
                                             22,
                                             22};

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
    jueguito_vars->dir_anterior = jueguito_vars->dir;

    // Reiniciar el jueguito
    if(IsKeyPressed(KEY_I)) setup_snake(snake_cabeza,jueguito_vars);
    
    // Input
    if(IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT)) jueguito_vars->dir = jueguito_vars->dir == 1 ? 1:0;
    if(IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT)) jueguito_vars->dir = jueguito_vars->dir == 0 ? 0:1;
    if(IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP)) jueguito_vars->dir = jueguito_vars->dir == 3 ? 3:2;
    if(IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN)) jueguito_vars->dir = jueguito_vars->dir == 2 ? 2:3;

    snake_cabeza->last_x = snake_cabeza->x;
    snake_cabeza->last_y = snake_cabeza->y;

    if(snake_cabeza->sig != NULL){
        snake_cabeza->sig->last_x = snake_cabeza->sig->x;
        snake_cabeza->sig->last_y = snake_cabeza->sig->y;
        snake_cabeza->sig->x = snake_cabeza->last_x;
        snake_cabeza->sig->y = snake_cabeza->last_y;
    }

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

    jueguito_vars->coll_cabeza.x = snake_cabeza->x-7;
    jueguito_vars->coll_cabeza.y = snake_cabeza->y-7;

    //Checar si colisionan los rectangulos de la cabeza y la comida
    if(CheckCollisionRecs(jueguito_vars->coll_cabeza,
                          jueguito_vars->coll_comida  )){
        jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
        jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);
        jueguito_vars->coll_comida.x = jueguito_vars->comida_x - 11;
        jueguito_vars->coll_comida.y = jueguito_vars->comida_y - 11;
        jueguito_vars->nodos_aniadir += na;
    
    }
    
   
    
}
void draw_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars){
    
    DrawCircle(snake_cabeza->x,snake_cabeza->y,10,BLUE);
    nodoSnake_t *nodo_temp = snake_cabeza;
    while(nodo_temp->sig != NULL){
        DrawCircle(nodo_temp->sig->x,nodo_temp->sig->y,10,BLUE);
        nodo_temp = nodo_temp->sig;
    }
    DrawCircle(jueguito_vars->comida_x,jueguito_vars->comida_y,8,BLACK);

    DrawRectangleLinesEx(jueguito_vars->coll_cabeza,1,RED);
    DrawRectangleLinesEx(jueguito_vars->coll_comida,1,RED);

    DrawText(TextFormat("%i",jueguito_vars->nodos_cantidad), 20, jueguito_vars->sH-50,50,SKYBLUE);
}
