#ifndef SNAKE_H_
#define SNAKE_H_

#include "ray/raylib.h"
#include "defs.h"

#include "mysql/mysql.h"

#define paletas_cantidad 10

// paletas de colores del jueguito
extern Color paletas[paletas_cantidad][6];

// Estructura para los nodos usados en el snake
typedef struct nodoSnake_t{
    struct nodoSnake_t *sig;
    f32 x;
    f32 y;
    f32 last_x;
    f32 last_y;

}nodoSnake_t;


// estructura de usuarios para el scoreboard
typedef struct player_db_t{
    struct player_db_t* sig;
    char name[14];
    s32 score;

}player_db_t;

// Estructura para usar las variables del juego en un puntero
typedef struct jueguito_t{
    // direccion para comparar
    u8 dir;
    u8 dir_anterior;
    // 1  bit 0 - en menu inicio
    // 2  bit 1 - en jueguito snake
    // 4  bit 2 - en menu pausa
    // 8  bit 3 - en menu terminado
    u8 estados;
    // velocidad del snake
    f32 velocidad;   
    // tamaño de ventana en anchura
    s32 sW;
    // tamaño de ventana en altura
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

    // score del jueguito
    //u32 puntuacion;
    
    // estados del menu inicio para el highlight de opciones
    u8 estados_menu_inicio;
    // estados del menu pausa para el highlight de opciones
    u8 estados_menu_pausa;
    // estados del menu pausa para el highlight de opciones
    u8 estados_menu_terminado;
    // estados del menu submit record
    u8 estados_menu_submit_record;
    // estados del menu scoreboard
    u8 estados_menu_scoreboard;

    // estado sonido de los menu
    u8 estado_sonido_opcion;


    // indice de la paleta de colores
    s8 index_paleta;

    // volumen del jueguito
    s8 volumen;

    // conecxion mysql
    MYSQL* con;

    // scoreboard users
    player_db_t* player;
    
    // numero que controla cuando se incia a dibujar los scores
    s64 init_dibujar_score;

    // cantidad scores
    u16 cantidad_scores;

    // contador dibujar board;
    f32 contador_veces_dibujar_board;

    // jugador database insert
    
}jueguito_t;

void jugando_snake(nodoSnake_t *snake_cabeza, jueguito_t *jueguito_vars);
void setup_snake(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars);
void update_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars);
void draw_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars);



#endif // SNAKE_H_