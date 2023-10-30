#include "ray/raylib.h"
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
uint8_t dir;
int nodos_aniadir;
uint32_t nodos_cantidad;
Nodo_t *nodo15;
Nodo_t *nodos_colision;

int main(void){
    
    uint16_t sW = 800;
    uint16_t sH = 450;
    InitWindow(sW, sH, "snake");
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
    nodos_aniadir = 0;
    cabeza->x = (float)GetScreenWidth()/4;
    cabeza->y = (float)GetScreenHeight()/4;
    dir = 0;
    vel = 6.0;
    se_comio = 0;
    nodos_cantidad = 0;
    comida_x = GetRandomValue(0 + 10, GetScreenWidth() - 10);
    comida_y = GetRandomValue(0 + 10, GetScreenHeight() - 10);   
    if(cabeza->sig != NULL){
        Nodo_t *tmp = cabeza->sig;
        Nodo_t *tmp_borrar;
        cabeza->sig = NULL;
        while(1){
            tmp_borrar = tmp;
            if(tmp->sig == NULL){
                tmp = NULL;
                free(tmp_borrar);
                break;
            }else {
                tmp = tmp->sig;
                free(tmp_borrar);
            }
        }
    } 
}

void update_snake(Nodo_t *cabeza){
    if(IsKeyDown(KEY_I)) setup_snake(cabeza);
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dir = dir == 1 ? 1:0;
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) dir = dir == 0 ? 0:1;
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) dir = dir == 3 ? 3:2;
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) dir = dir == 2 ? 2:3;
    cabeza->last_x = cabeza->x;
    cabeza->last_y = cabeza->y;
    if(cabeza->sig != NULL){
        cabeza->sig->last_x = cabeza->sig->x;
        cabeza->sig->last_y = cabeza->sig->y;
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
    if (cabeza->y > GetScreenHeight()+5) cabeza->y = 0;
    if (cabeza->y < - 5) cabeza->y = GetScreenHeight();
    if (cabeza->x > GetScreenWidth()+5) cabeza->x = 0;
    if (cabeza->x < -5) cabeza->x = GetScreenWidth();
    uint8_t si_sig = 0;
    Nodo_t *nc = cabeza;
    nodos_cantidad = 0;
    while(nc->sig !=NULL){
        nodos_cantidad += 1;
        if(nodos_cantidad==15)
            nodo15 = nc;
        nc = nc->sig;
        if(nc->sig != NULL){
            nc->sig->last_x = nc->sig->x;
            nc->sig->last_y = nc->sig->y;
            nc->sig->x = nc->last_x;
            nc->sig->y = nc->last_y;     
        }
    }
    if(nodos_aniadir > 0){
        nc->sig = malloc(sizeof(Nodo_t));
        nc->sig->y = nc->last_y; 
        nc->sig->x = nc->last_x; 
        nc->sig->sig = NULL;
        nodos_aniadir -= 1;
        if(nodos_aniadir < 0) nodos_aniadir = 0;
    }    
    if(CheckCollisionRecs((Rectangle){cabeza->x-7,cabeza->y-7,14,14}, 
                          (Rectangle){comida_x-11,comida_y-11,22,22})){
        comida_x = GetRandomValue(0 + 10, GetScreenWidth() - 10);
        comida_y = GetRandomValue(0 + 10, GetScreenHeight() - 10);
        nodos_aniadir += 5;
    }

    
    
}
void draw_snake(Nodo_t *cabeza){
    DrawText(TextFormat("%i",nodos_cantidad), 20, GetScreenHeight() - 50, 50, SKYBLUE);
    DrawCircle(cabeza->x,cabeza->y, 10, BLUE);
    Nodo_t *nc = cabeza;
    while(nc->sig != NULL){
        DrawCircle(nc->sig->x,nc->sig->y, 10, BLUE);;
        nc = nc->sig;
    }
    DrawCircle(comida_x,comida_y, 8, BLACK);
    DrawRectangleLinesEx((Rectangle){comida_x-11,comida_y-11,22,22},1, RED);    
    DrawRectangleLinesEx((Rectangle){cabeza->x-7,cabeza->y-7,14,14},1, RED);
    if(nodo15!=NULL){
        nc = nodo15;
        while(nc->sig !=NULL){
            DrawRectangleLinesEx((Rectangle){nc->sig->x-4,nc->sig->y-4,8,8}, 1, RED);;
            nc = nc -> sig;
        }
    } 
}
