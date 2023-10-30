#include "ray/raylib.h"
#include <stdint.h>

#include "defs.h"
#include "snskt/snake.h"


int main(void){
    
    u16 sW = 800;
    u16 sH = 450;
    InitWindow(sW, sH, "snake");
    SetTargetFPS(60);
    
    u32* pP = setup_snake();

    
    while (!WindowShouldClose()){
        
        
        BeginDrawing();
        ClearBackground(RAYWHITE);



        DrawFPS(0, 0);        
        EndDrawing();
    }
    CloseWindow();       
    return 0;
}
