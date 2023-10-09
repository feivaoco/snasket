#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Nodo_t{
    struct Nodo_t *sig;
    float x;
    float y;
    uint8_t dir;
    uint8_t last_dir;
}Nodo_t;

void setup_snake(Nodo_t *cabeza);
void update_snake(Nodo_t *cabeza);
void draw_snake(Nodo_t *cabeza);


float vel;


float comida_x;
float comida_y;
float comida_timer;
uint8_t se_comio;
uint32_t score;

int main(void){
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "snake");
    SetTargetFPS(60);
    
    Nodo_t* cabeza = malloc(sizeof(Nodo_t));
    cabeza->sig = NULL;
    
    setup_snake(cabeza);
    
    while (!WindowShouldClose()){
        
        update_snake(cabeza);
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawFPS(0, 0);
        
        draw_snake(cabeza);
        
        EndDrawing();
    }
    CloseWindow();       
    return 0;
}

void setup_snake(Nodo_t *cabeza){
    score = 0;
    cabeza->x = (float)GetScreenWidth()/4;
    cabeza->y = (float)GetScreenHeight()/4;
    cabeza->dir = 0;
    vel = 4.0;
    se_comio = 0;
    comida_x = GetRandomValue(0 + 10, GetScreenWidth() - 10);
    comida_y = GetRandomValue(0 + 10, GetScreenHeight() - 10);
    
}

void update_snake(Nodo_t *cabeza){
    cabeza->last_dir = cabeza->dir;
    if(IsKeyDown(KEY_D)) cabeza->dir = cabeza->dir == 1 ? 1:0;
    if(IsKeyDown(KEY_A)) cabeza->dir = cabeza->dir == 0 ? 0:1;
    if(IsKeyDown(KEY_W)) cabeza->dir = cabeza->dir == 3 ? 3:2;
    if(IsKeyDown(KEY_S)) cabeza->dir = cabeza->dir == 2 ? 2:3;
    switch(cabeza->dir){
        case 0:
            cabeza->dir = 0;
            break;
        case 1:
            cabeza->dir = 1;
            break;
        case 2:
            cabeza->dir = 2;
            break;
        case 3:
            cabeza->dir = 3;
            break;
    }
    uint8_t si_sig = 0;
    Nodo_t *nc = cabeza;
    while(1){
        
        if (nc->y > GetScreenHeight()+10) nc->y = 0;
        if (nc->y < -10) nc->y = GetScreenHeight();
        if (nc->x > GetScreenWidth()+10) nc->x = 0;
        if (nc->x < -10) nc->x = GetScreenWidth();
        switch (nc->dir) {
            case 0:
                nc->x += vel;
                break;
            case 1:
                nc->x -= vel;
                break;
            case 2:
                nc->y -= vel;
                break;
            case 3:
                nc->y += vel;
                break; 
        }
        if(nc->sig != NULL){ 
            nc->sig->last_dir = nc->sig->dir; 
            nc->sig->dir = nc->last_dir;    
            nc = nc->sig;
        }else {
            break;
        }
        
    }
    
    if(CheckCollisionRecs((Rectangle){cabeza->x-10,cabeza->y-10,20,20}, (Rectangle){comida_x-4,comida_y-4,8,8})){
        comida_x = GetRandomValue(0 + 10, GetScreenWidth() - 10);
        comida_y = GetRandomValue(0 + 10, GetScreenHeight() - 10);
        score += 1;
        vel *= 1.01;
        Nodo_t *nd = cabeza;
        uint8_t se_aniadio_nodo = 0; 
        while(!se_aniadio_nodo){
            if(nd->sig == NULL){
                nd->sig = malloc(sizeof(Nodo_t));
                switch (nc->dir) {
                    case 0:
                        nc->sig->dir = 0;nc->sig->x = nc->x - 10;nc->sig->y = nc->y;
                        break;
                    case 1:
                        nc->sig->dir = 1;nc->sig->x = nc->x + 10;nc->sig->y = nc->y;
                        break;
                    case 2:
                        nc->sig->dir = 2;nc->sig->x = nc->x;nc->sig->y = nc->y + 10;
                        break;
                    case 3:
                        nc->sig->dir = 3;nc->sig->x = nc->x;nc->sig->y = nc->y - 10;
                        break;
                }
                nd->sig->last_dir = nd->sig->dir;
                nd->sig->sig = NULL;
                se_aniadio_nodo = 1;     
            }else{
                nd = nd->sig;
            }
        }        
    }
    
    
}


void draw_snake(Nodo_t *cabeza){
    DrawText(TextFormat("%f",vel), GetScreenWidth() - 120, GetScreenHeight() - 50, 50, SKYBLUE);
    DrawText(TextFormat("%i",score), 20, GetScreenHeight() - 50, 50, SKYBLUE);
    //DrawRectangleRec((Rectangle){cabeza.x-10,cabeza.y-10,20,20}, GREEN);
    DrawCircle(cabeza->x,cabeza->y, 10, BLUE);
    Nodo_t *nc = cabeza;
    while(nc->sig != NULL){
        DrawCircle(nc->sig->x,nc->sig->y, 10, BLUE);;
        nc = nc->sig;
    }
    
    DrawCircle(comida_x,comida_y, 8, RED);
        
    
}

