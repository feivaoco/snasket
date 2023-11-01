#include "ray/raylib.h"
#include <stdint.h>
#include <stdlib.h>
#include "defs.h"
#include "snskt/snake.h"
#include "stdio.h"

int main(void){
    // SETUP SNAKE
    nodoSnake_t* snake_p = MemAlloc(sizeof(nodoSnake_t));
    jueguito_t* jueguito_vars = MemAlloc(sizeof(jueguito_t));
    snake_p->sig = NULL;
    setup_snake(snake_p, jueguito_vars);
    /////////////
    
    InitWindow(jueguito_vars->sW, jueguito_vars->sH, "snasket");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        // UPDATE SNAKE
        update_snake(snake_p, jueguito_vars);
        /////////////

        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        // DRAW SNAKE
        draw_snake(snake_p, jueguito_vars);

        /////////////

        DrawFPS(5, 5);        
        EndDrawing();
    }
    CloseWindow();   
    MemFree(snake_p);
    MemFree(jueguito_vars);    
    return 0;
}
