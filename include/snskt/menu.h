#ifndef SNAKE_MENU_H_
#define SNAKE_MENU_H_

#include "ray/raylib.h"
#include "snskt/snake.h"
#include "defs.h"


// Enum de los estados del jueguito
enum ESTADOS_JUEGUITO{
    // Estado en el que inicia la aplicacion
    // porque es el menu principal 
    EnMenuInicio    = 1,
    // Estado en el que se 
    // encuentra la aplicacion en el que se ejecuta el jueguito
    EnJueguito      = 2,
    // Estado en el que se pausa el jueguito
    // este estado solo se llama cuando se esta jugando
    EnMenuPausa     = 4,
    // Estado que se llama cuando se termina el jueguito o
    // cuando menu de pausa lo llama para terminar el jueguito
    EnMenuTerminado = 8
};


void update_menu_inicio(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars);
void draw_menu_inicio(jueguito_t *jueguito_vars);


void update_menu_pausa(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars);
void draw_menu_pausa(nodoSnake_t* s,jueguito_t *jueguito_vars);

void update_menu_terminar(nodoSnake_t* s,jueguito_t *jv);
void draw_menu_terminar(nodoSnake_t* s,jueguito_t *jv);


#endif //SNAKE_MENU_H_



