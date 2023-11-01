
#ifndef SNAKE_H_
#define SNAKE_H_


#include "defs.h"

typedef struct nodoSnake_t{
    struct nodoSnake_t *sig;
    f32 x;
    f32 y;
    f32 last_x;
    f32 last_y;

}nodoSnake_t;

typedef struct jueguito_t{
    u16 controles;
    // bit 0 - sigue vivo ? 
    // bit 1 - comio la bola ?
    // bit 2  
    u8 estados;
    u8 velocidad;
    s32 sW;
    s32 sH;
}jueguito_t;

void setup_snake(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars);
void update_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars);
void draw_snake(nodoSnake_t *snake_cabeza,jueguito_t * jueguito_vars);



#endif // SNAKE_H_