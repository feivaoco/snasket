#include "ray/raylib.h"
#include <stdint.h>
#include <stdlib.h>
#include "defs.h"
#include "snskt/snake.h"

int main(void){
    

    // SETUP SNAKE
    nodoSnake_t* snake_p = malloc(sizeof(nodoSnake_t));
    jueguito_t* jueguito_vars = malloc(sizeof(jueguito_t));
    setup_snake(snake_p, jueguito_vars);
    /////////////
    
    InitWindow(jueguito_vars->sW, jueguito_vars->sH, "snasket");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        // UPDATE SNAKE
        update_snake(snake_p, jueguito_vars);
        
        /////////////
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DRAW SNAKE
        draw_snake(snake_p, jueguito_vars);

        /////////////

        DrawFPS(0, 0);        
        EndDrawing();
    }
    CloseWindow();       
    return 0;
}
