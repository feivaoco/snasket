#include "ray/raylib.h"
#include "snskt/snake.h"
#include "snskt/menu.h"
#include "defs.h"
#include "pd/z_libpd.h"


void update_menu_inicio(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    jueguito_vars->estados_menu_inicio = 0;
    Vector2 mv = GetMousePosition();
    Rectangle mr = (Rectangle){mv.x-5,mv.y-4,14,18};
    if(CheckCollisionRecs(mr,(Rectangle){jueguito_vars->sW/4, jueguito_vars->sH/2-120, jueguito_vars->sW/2,120})){
        if(!jueguito_vars->estado_sonido_opcion){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion = 1;
        }
        jueguito_vars->estados_menu_inicio = 1;

    }else{jueguito_vars->estado_sonido_opcion = 0;}

    switch(jueguito_vars->estados_menu_inicio){
        case 0:
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            break;
        case 1:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                
                jueguito_vars->estados = EnJueguito;
                setup_snake(snake_cabeza, jueguito_vars);
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                return;
            }
            break;
    }
    
}

void draw_menu_inicio(jueguito_t *jv){
    ClearBackground(BLUE);
    switch(jv->estados_menu_inicio){
        case 0:
            DrawRectangle(jv->sW/4, jv->sH/2-120, jv->sW/2,120,BLACK);
            break;
        case 1:
            DrawRectangle(jv->sW/4, jv->sH/2-120, jv->sW/2,120,WHITE);
            break;
    }
}

void update_menu_pausa(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    
    /*switch(GetKeyPressed()){
        case KEY_I:
            jueguito_vars->estados = EnJueguito;
            return;
        case KEY_O:
            jueguito_vars->estados = EnMenuInicio;
            return;
    }*/
    u32 xL = jueguito_vars->sW/6;
    u32 xR = xL*4;
    u32 yU = jueguito_vars->sH/6;
    u32 yD = yU*4;
    
    jueguito_vars->estados_menu_pausa = 0;

    Vector2 mv = GetMousePosition();
    Rectangle mr = (Rectangle){mv.x-5,mv.y-4,14,18};
    //DrawRectangle(mv.x-5,mv.y-4,14,18,RED);
    
    if(CheckCollisionRecs(mr,(Rectangle){xR/2, yU+40, xR/2,yD/4})){
        if(!(jueguito_vars->estado_sonido_opcion & 1)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 1;
        }
        jueguito_vars->estados_menu_pausa = 1;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 254;}


    if(CheckCollisionRecs(mr,(Rectangle){xL+80, yD-80, xR/4,yD/4})){
        if(!(jueguito_vars->estado_sonido_opcion & 2)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 2;
        }
        jueguito_vars->estados_menu_pausa = 2;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 253;}


    if(CheckCollisionRecs(mr,(Rectangle){xR-80, yD-80, xR/4,yD/4})){
        if(!(jueguito_vars->estado_sonido_opcion & 4)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 4;
        }
        jueguito_vars->estados_menu_pausa = 3;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 251;}

    switch(jueguito_vars->estados_menu_pausa){
        case 0:
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            break;
        case 1:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                jueguito_vars->estados = EnJueguito;
                return;
            }
            break;
        case 2:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                setup_snake(snake_cabeza,jueguito_vars);
                jueguito_vars->estados = EnJueguito;
                return;
            }
            break;
        case 3:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                jueguito_vars->estados = EnMenuTerminado;
                return;
            }
            break;
    }
}

void draw_menu_pausa(nodoSnake_t* s,jueguito_t *jueguito_vars){
    draw_snake(s, jueguito_vars);
    
    u32 xL = jueguito_vars->sW/6;
    u32 xR = xL*4;
    u32 yU = jueguito_vars->sH/6;
    u32 yD = yU*4;
    BeginScissorMode(xL, yU, xR, yD);
    
    

    switch(jueguito_vars->estados_menu_pausa){
        case 0:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,BLACK);
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,BLACK);
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,BLACK);
            break;

        case 1:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,WHITE);
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,BLACK);
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,BLACK);
            break;
        
        case 2:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,BLACK);
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,WHITE);
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,BLACK);
            break;
        
        case 3:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,BLACK);
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,BLACK);
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,WHITE);
            break;
    }
        

    EndScissorMode();
}


void update_menu_terminar(nodoSnake_t *s,jueguito_t *jv){
    jv->estados_menu_terminado = 0;

    Vector2 mv = GetMousePosition();
    Rectangle mr = (Rectangle){mv.x-5,mv.y-4,14,18};
    if(CheckCollisionRecs(mr,(Rectangle){jv->sW/4+120, jv->sH/4 + 90, jv->sW/2-240,60})){
        if(!(jv->estado_sonido_opcion & 1)){
            libpd_bang("bHover");
            jv->estado_sonido_opcion += 1;
        }
        jv->estados_menu_terminado = 1;
    }else{jv->estado_sonido_opcion = jv->estado_sonido_opcion & 254;}

    if(CheckCollisionRecs(mr,(Rectangle){jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80})){
        if(!(jv->estado_sonido_opcion & 2)){
            libpd_bang("bHover");
            jv->estado_sonido_opcion += 2;
        }
        jv->estados_menu_terminado = 2;
    }else{jv->estado_sonido_opcion = jv->estado_sonido_opcion & 253;}

    if(CheckCollisionRecs(mr,(Rectangle){jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80})){
        if(!(jv->estado_sonido_opcion & 4)){
            libpd_bang("bHover");
            jv->estado_sonido_opcion += 4;
        }
        jv->estados_menu_terminado = 3;
    }else{jv->estado_sonido_opcion = jv->estado_sonido_opcion & 251;}

    switch(jv->estados_menu_terminado){
        case 0:
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            break;
        case 1:
            
            break;
        case 2:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                setup_snake(s,jv);
                jv->estados = EnJueguito;
                return;
            }
            break;
        case 3:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                jv->estados = EnMenuInicio;
                return;
            }
            break;
    }

}




void draw_menu_terminar(nodoSnake_t *s,jueguito_t *jv){
    ClearBackground(LIGHTGRAY);
    const char *p=TextFormat("%d", jv->nodos_cantidad);
    const char* scoreText = TextFormat("SCORE: %s", p);
    DrawText(scoreText,jv->sW/2 - 260,jv->sH/4 ,86,BLUE);
    switch(jv->estados_menu_terminado){
        case 0:
            DrawRectangle(jv->sW/4+120, jv->sH/4 + 90, jv->sW/2-240,60,BLACK);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,BLACK);
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,BLACK);
            break;
        case 1:
            DrawRectangle(jv->sW/4+120, jv->sH/4 + 90, jv->sW/2-240,60,WHITE);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,BLACK);
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,BLACK);
            break;
        case 2:
            DrawRectangle(jv->sW/4+120, jv->sH/4 + 90, jv->sW/2-240,60,BLACK);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,WHITE);
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,BLACK);
            break;
        case 3:
            DrawRectangle(jv->sW/4+120, jv->sH/4 + 90, jv->sW/2-240,60,BLACK);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,BLACK);
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,WHITE);
            break;
    }

}