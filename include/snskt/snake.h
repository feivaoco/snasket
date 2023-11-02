
#ifndef SNAKE_H_
#define SNAKE_H_

#include "ray/raylib.h"
#include "defs.h"

// Estructura para los nodos usados en el snake
typedef struct nodoSnake_t{
    struct nodoSnake_t *sig;
    f32 x;
    f32 y;
    f32 last_x;
    f32 last_y;

}nodoSnake_t;


// Estructura para usar las variables del juego en un puntero
typedef struct jueguito_t{
    // direccion para comparar
    u8 dir;
    u8 dir_anterior;
    // 1 bit 0 - sigue vivo ? 
    // lo siguiente abajo sigue en proceso de definicion
    // 2 bit 1 - comio la bola ?
    // 4 bit 2 - si siguiente
    // 8 bit 3 - 
    u8 estados;
    // velocidad del snake
    f32 velocidad;   
    // tamaño de ventana
    s32 sW;
    s32 sH;

    // comida coordenadas
    f32 comida_x;
    f32 comida_y;

    // nodos siguientes de cabeza
    s16 nodos_aniadir;
    u32 nodos_cantidad;

    // rectangulo para el collider de la cabeza
    Rectangle coll_cabeza;
    Rectangle coll_comida;

    // lista de nodos para los colliders
    nodoSnake_t *nodo_collider;    

    // tiempo de espera para aniadir un nodo
    f32 tiempo_aniadir_nodo;

}jueguito_t;

void setup_snake(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars);
void update_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars);
void draw_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars);



#endif // SNAKE_H_