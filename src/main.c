#include "raylib.h"
#include <stdint.h>

void draw_snake(int rows, int cols);

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "snake");
    SetTargetFPS(60);
    
    int rows = 25;
    int cols = 30;
        
    
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        
        draw_snake(rows, cols);
        
        EndDrawing();
    }
    CloseWindow();       
    return 0;
}

void draw_snake(int rows, int cols){
    //dibujando celdas
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            DrawRectangleLinesEx((Rectangle){(int)(GetScreenWidth()/4) + j * 15, 40 + i * 15, 15,15}, 1, BLACK);
        }   
    }
}

