#include "raylib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Nodo_t{
    struct Nodo_t *sig;
    float x;
    float y;
    float last_x;
    float last_y;
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
uint8_t dir;
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
    dir = 0;
    vel = 4.0;
    se_comio = 0;
    comida_x = GetRandomValue(0 + 10, GetScreenWidth() - 10);
    comida_y = GetRandomValue(0 + 10, GetScreenHeight() - 10);
    
}

void update_snake(Nodo_t *cabeza){
    
    if(IsKeyDown(KEY_D)) dir = dir == 1 ? 1:0;
    if(IsKeyDown(KEY_A)) dir = dir == 0 ? 0:1;
    if(IsKeyDown(KEY_W)) dir = dir == 3 ? 3:2;
    if(IsKeyDown(KEY_S)) dir = dir == 2 ? 2:3;
    cabeza->last_x = cabeza->x;
    cabeza->last_y = cabeza->y;
    if(cabeza->sig != NULL){
        cabeza->sig->x = cabeza->last_x;
        cabeza->sig->y = cabeza->last_y;
    }
    switch(dir){
        case 0:
            cabeza->x += vel;
            break;
        case 1:
            cabeza->x -= vel;
            break;
        case 2:
            cabeza->y -= vel;
            break;
        case 3:
            cabeza->y += vel;
            break;
    }
    if (cabeza->y > GetScreenHeight()+10) cabeza->y = 0;
    if (cabeza->y < -10) cabeza->y = GetScreenHeight();
    if (cabeza->x > GetScreenWidth()+10) cabeza->x = 0;
    if (cabeza->x < -10) cabeza->x = GetScreenWidth();
    uint8_t si_sig = 0;
    Nodo_t *nc = cabeza;
    while(nc->sig !=NULL){
        nc = nc->sig;
         
    
        
    }

    if(CheckCollisionRecs((Rectangle){cabeza->x-10,cabeza->y-10,20,20}, (Rectangle){comida_x-4,comida_y-4,8,8})){
        comida_x = GetRandomValue(0 + 10, GetScreenWidth() - 10);
        comida_y = GetRandomValue(0 + 10, GetScreenHeight() - 10);
        score += 1;
        vel *= 1.01;
        nc = cabeza;
        uint8_t se_aniadio_nodo = 0; 
        while(!se_aniadio_nodo){
            if(nc->sig == NULL){
                nc->sig = malloc(sizeof(Nodo_t));
                nc->sig->y = nc->last_y;
                nc->sig->x = nc->last_x;
                nc->sig->sig = NULL;
                se_aniadio_nodo = 1;     
            }else{
                nc = nc->sig;
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

