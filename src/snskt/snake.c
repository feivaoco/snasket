#include "defs.h"
#include <stdlib.h>
#include "snskt/snake.h"
#include "ray/raylib.h"
#include "stdio.h"
#include "pd/z_libpd.h"
#include "snskt/menu.h"
// si se quiere debugear los colliders
//#define DEBUG_SNAKE_
// nodos a aniadir cuando se come
#define na 3
// offset de coordenadas para el collider de la cabeza
#define offset_coll_cabeza 3
// size para el collider de la cabeza
#define size_coll_cabeza offset_coll_cabeza*2
// offset de coordenadas para el collider de la comida
#define offset_coll_comida 23
// size para el collider de la comida
#define size_coll_comida offset_coll_comida*2
// nodo en el que se inicia a aniadir 
#define ni_a 5


Color paletas[paletas_cantidad][6] = {
    {   
        BLACK,      SKYBLUE,
        BLUE,       LIME,
        LIGHTGRAY,  WHITE
    },
    {
        {0x00, 0x17, 0x7c, 0xFF},
        {0x84, 0x39, 0x6c, 0xFF},
        {0x59, 0x83, 0x44, 0xFF},
        {0xd0, 0x90, 0x71, 0xFF},
        {0xea, 0xce, 0x75, 0xFF},
        {0xf7, 0xff, 0xed, 0xFF},
    },
    {

        {0xf6, 0x24, 0x0f, 0xFF},
        {0x1d, 0xf6, 0x0f, 0xFF},
        {0x27, 0x70, 0xf6, 0xFF},
        {0xf2, 0xf6, 0x0f, 0xFF},
        {0xf6, 0x89, 0x0f, 0xFF},
        {0xff, 0xff, 0xff, 0xFF},
        
    },
    {
        {0x26, 0x1f, 0x1f, 0xff},
        {0xc0, 0xaa, 0x74, 0xff},
        {0xf1, 0xf1, 0xd1, 0xff},
        {0x31, 0x98, 0x35, 0xff},
        {0x0f, 0x4d, 0x32, 0xff},
        {0xff, 0x2d, 0x2d, 0xff},
        
    },
    {
        {0x32, 0x41, 0xe0, 0xFF},
        {0xa4, 0xef, 0x00, 0xFF},
        {0xff, 0xff, 0x00, 0xFF},
        {0xff, 0x52, 0xd2, 0xFF},
        {0x00, 0x00, 0x00, 0xFF},
        {0xff, 0xff, 0xff, 0xFF},

    },
    {
        {0xf4,0xc4,0xd4,0xFF},
        {0xea,0x92,0xab,0xFF},
        {0xaf,0x7f,0xc2,0xFF},
        {0x90,0x85,0xd0,0xFF},
        {0x8c,0x76,0xbe,0xFF},
        {0x61,0x56,0x7d,0xFF},
    },
    {
        {0x0a,0x0d,0x22,0xFF},
        {0x29,0x6b,0xaa,0xFF},
        {0x03,0xa6,0x6b,0xFF},
        {0xfc,0xff,0xff,0xFF},
        {0xf3,0xac,0x00,0xFF},
        {0xc8,0x19,0x22,0xFF},
    },
    {
        {0xe5,0xe2,0xd3,0xFF},
        {0xad,0xa3,0x94,0xFF},
        {0x2f,0x27,0x36,0xFF},
        {0x54,0x5a,0xfb,0xFF},
        {0x94,0xda,0xfc,0xFF},
        {0xc2,0x2d,0x41,0xFF},
    },
    {
        {0x25,0x1d,0x29,0xFF},
        {0x43,0x3d,0x4c,0xFF},
        {0x77,0x82,0x99,0xFF},
        {0x9c,0xae,0xbb,0xFF},
        {0xfb,0xcd,0xcd,0xFF},
        {0xff,0xff,0xff,0xFF},
    },
    {
        {0x46,0x42,0x5e,0xFF},
        {0x15,0x78,0x8c,0xFF},
        {0x00,0xb9,0xbe,0xFF},
        {0xff,0xee,0xcc,0xFF},
        {0xff,0xb0,0xa3,0xFF},
        {0xff,0x69,0x73,0xFF},
    },
};

void setup_snake(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    
    
    
    // inicializacion de las variables del jueguito
    jueguito_vars->dir_anterior = 0;
    
    jueguito_vars->velocidad = 380;
   
    jueguito_vars->nodos_aniadir = na;
    jueguito_vars->nodos_cantidad = 0;
    jueguito_vars->nodo_collider = NULL;
    jueguito_vars->tiempo_aniadir_nodo = 0;

    // inicializacion de la posicion de la comida
    jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
    jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);

    // inicializacion de la posicion de la serpiente
    jueguito_vars->dir =GetRandomValue(0,3);
    switch (jueguito_vars->dir){
        case 0:
            snake_cabeza->x = (f32)jueguito_vars->sW-size_coll_cabeza-150;
            snake_cabeza->y = (f32)jueguito_vars->sH/2;
            break;
        case 1:
            snake_cabeza->x = size_coll_cabeza+150;
            snake_cabeza->y = (f32)jueguito_vars->sH/2;
            break;
        case 2:
            snake_cabeza->x = (f32)jueguito_vars->sW/2;
            snake_cabeza->y = size_coll_cabeza+150;
            break;
        case 3:
            snake_cabeza->x = (f32)jueguito_vars->sW/2;
            snake_cabeza->y = (f32)jueguito_vars->sH-size_coll_cabeza-150;
            break;
    }
    
    
    // inicializacion de los recs colliders
    jueguito_vars->coll_cabeza = (Rectangle){snake_cabeza->x-offset_coll_cabeza,
                                             snake_cabeza->y-offset_coll_cabeza,
                                             size_coll_cabeza ,
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

    if(IsKeyPressed(KEY_P)){
        jueguito_vars->estados = EnMenuPausa;
        return;
    }

    // Delta time para multiplicar y tener velocidad constante
    f32 delta_time = GetFrameTime();

    // Checar si ya perdio
    /*if(!(jueguito_vars->estados & 2)){
        setup_snake(snake_cabeza,jueguito_vars);
    }*/

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
    /*if(IsKeyPressed(KEY_I)){ 
        libpd_bang("bMorido");
        jueguito_vars->puntuacion = jueguito_vars->nodos_cantidad;
        setup_snake(snake_cabeza,jueguito_vars);
    }*/
    
    // Input switch
    switch (GetKeyPressed()){
        case KEY_D:
        case KEY_RIGHT:
            jueguito_vars->dir = jueguito_vars->dir == 1 ? 1:0;
            //libpd_bang("bBD");
            break;
        case KEY_A:
        case KEY_LEFT:
            jueguito_vars->dir = jueguito_vars->dir == 0 ? 0:1;
            //libpd_bang("bSn");
            break;
        case KEY_W:
        case KEY_UP:
            jueguito_vars->dir = jueguito_vars->dir == 3 ? 3:2;
            //libpd_bang("bHH");
            break;
        case KEY_S:
        case KEY_DOWN:
            jueguito_vars->dir = jueguito_vars->dir == 2 ? 2:3;
            //libpd_bang("bCB");
            break;
        
        // CAMBIAR LA PALETA DE COLORES
        case KEY_F1:
            jueguito_vars->index_paleta += 1;
            if(jueguito_vars->index_paleta >= paletas_cantidad)
                jueguito_vars->index_paleta = 0;
            break;
        case KEY_F2:
            jueguito_vars->index_paleta -= 1;
            if(jueguito_vars->index_paleta < 0)
                jueguito_vars->index_paleta = paletas_cantidad - 1;
            break;default:
            break;
    }
   
    /*
    if(IsKeyPressed(KEY_D)||IsKeyPressed(KEY_RIGHT)) jueguito_vars->dir = jueguito_vars->dir == 1 ? 1:0;
    if(IsKeyPressed(KEY_A)||IsKeyPressed(KEY_LEFT)) jueguito_vars->dir = jueguito_vars->dir == 0 ? 0:1;
    if(IsKeyPressed(KEY_W)||IsKeyPressed(KEY_UP)) jueguito_vars->dir = jueguito_vars->dir == 3 ? 3:2;
    if(IsKeyPressed(KEY_S)||IsKeyPressed(KEY_DOWN)) jueguito_vars->dir = jueguito_vars->dir == 2 ? 2:3;
    */
    
    // Cambiar direccion
    switch (jueguito_vars->dir){
        case 0:
            snake_cabeza->x += jueguito_vars->velocidad * delta_time;
            break;
        case 1:
            snake_cabeza->x -= jueguito_vars->velocidad * delta_time;
            break;
        case 2:
            snake_cabeza->y -= jueguito_vars->velocidad * delta_time;
            break;
        case 3:
            snake_cabeza->y += jueguito_vars->velocidad * delta_time;
            break;
    }

    if(snake_cabeza->y > jueguito_vars->sH + 5) snake_cabeza->y = 0;
    if(snake_cabeza->y < - 5) snake_cabeza->y = jueguito_vars->sH;
    
    if(snake_cabeza->x > jueguito_vars->sW + 5) snake_cabeza->x = 0;
    if(snake_cabeza->x < - 5) snake_cabeza->x = jueguito_vars->sW;
   
    nodoSnake_t *nodo_temp = snake_cabeza;
    jueguito_vars->nodos_cantidad = 0;

    while (nodo_temp->sig != NULL){
        jueguito_vars->nodos_cantidad += 1;
        if(jueguito_vars->nodos_cantidad == ni_a)
            jueguito_vars->nodo_collider = nodo_temp;
        nodo_temp = nodo_temp->sig;
        if(nodo_temp->sig != NULL){
            nodo_temp->sig->last_x = nodo_temp->sig->x;
            nodo_temp->sig->last_y = nodo_temp->sig->y;
            nodo_temp->sig->x = nodo_temp->last_x;
            nodo_temp->sig->y = nodo_temp->last_y;
        }
    }

    // Bloque de codigo para aniadir un nodo a la cola
    if(jueguito_vars->nodos_aniadir > 0){
        jueguito_vars->tiempo_aniadir_nodo += 1 * GetFrameTime();
        if(jueguito_vars->tiempo_aniadir_nodo > .25){
            // Le manda al archivo del puredata abierto un bang como [s bNodo] entonces
            // un [r bNodo] recibira el bang mandando en esta funcion
            libpd_bang("bNodo");
            nodo_temp->sig = MemAlloc(sizeof(nodoSnake_t));
            nodo_temp->sig->y = nodo_temp->last_y;
            nodo_temp->sig->x = nodo_temp->last_x;
            nodo_temp->sig->sig = NULL;
            jueguito_vars->nodos_aniadir -= 1;
            if(jueguito_vars->nodos_aniadir < 0) jueguito_vars->nodos_aniadir = 0;
            jueguito_vars->tiempo_aniadir_nodo = 0;
        }     
    }

    jueguito_vars->coll_cabeza.x = snake_cabeza->x-offset_coll_cabeza;
    jueguito_vars->coll_cabeza.y = snake_cabeza->y-offset_coll_cabeza;

    //Checar si colisionan los rectangulos de la cabeza y la comida
    if(CheckCollisionRecs(jueguito_vars->coll_cabeza,
                          jueguito_vars->coll_comida  )){

        // Le manda al archivo del puredata abierto un bang como [s bColComida] entonces
        // un [r bColComida] recibira el bang mandando en esta funcion
        libpd_bang("bColComida");

        jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
        jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);
        jueguito_vars->coll_comida.x = jueguito_vars->comida_x - offset_coll_comida;
        jueguito_vars->coll_comida.y = jueguito_vars->comida_y - offset_coll_comida;
        jueguito_vars->nodos_aniadir += na;
        
        nodo_temp = snake_cabeza;
        while(nodo_temp != NULL){
            if(CheckCollisionRecs((Rectangle){nodo_temp->x-2 ,
                                nodo_temp->y-2,
                                4, 4},
                                jueguito_vars->coll_comida) ){
                jueguito_vars->comida_x = GetRandomValue(0+10, jueguito_vars->sW - 10);
                jueguito_vars->comida_y = GetRandomValue(0+10, jueguito_vars->sH - 10);
                jueguito_vars->coll_comida.x = jueguito_vars->comida_x - offset_coll_comida;
                jueguito_vars->coll_comida.y = jueguito_vars->comida_y - offset_coll_comida;        
                nodo_temp = snake_cabeza;
                continue;
            }
            nodo_temp = nodo_temp->sig;
        }
    }
    
    // Checar si colisiona con su cola
    if(jueguito_vars->nodo_collider != NULL){
        nodo_temp = jueguito_vars->nodo_collider;
        while (nodo_temp!=NULL){
            if(CheckCollisionRecs((Rectangle){nodo_temp->x-2 ,
                                nodo_temp->y-2,
                                4, 4},
                                jueguito_vars->coll_cabeza)){
                
                

                // Le manda al archivo del puredata abierto un bang como [s bMorido] entonces
                // un [r bMorido] recibira el bang mandando en esta funcion
                libpd_bang("bMorido");
                
                
                
                jueguito_vars->estados = EnMenuTerminado; 
                return;
            }
            nodo_temp = nodo_temp->sig;
        }
    }
}


void draw_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars){
    // LIMPIAR PANTALLA
    ClearBackground(paletas[jueguito_vars->index_paleta][4]);


    // Dibujar serpiente
    nodoSnake_t *nodo_temp = snake_cabeza->sig;
    while(nodo_temp != NULL){
        DrawCircle(nodo_temp->x,nodo_temp->y,10,paletas[jueguito_vars->index_paleta][1]);
        nodo_temp = nodo_temp->sig;
    }
    DrawCircle(snake_cabeza->x,snake_cabeza->y,10,paletas[jueguito_vars->index_paleta][2]);

    // Dibujar comida
    DrawCircle(jueguito_vars->comida_x,jueguito_vars->comida_y,15,paletas[jueguito_vars->index_paleta][3]);

    #ifdef DEBUG_SNAKE_
    // Para dibujar los colliders
    DrawRectangleLinesEx(jueguito_vars->coll_cabeza,1,RED);
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
        
        
    }
    #endif //DEBUG_SNAKE_

    // Dibujar score
    DrawText("SCORE", 20, jueguito_vars->sH-100,50,paletas[jueguito_vars->index_paleta][2]);
    DrawText(TextFormat("%i",jueguito_vars->nodos_cantidad), 20, jueguito_vars->sH-50,50,paletas[jueguito_vars->index_paleta][2]);
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
