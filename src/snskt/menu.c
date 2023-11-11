#include "ray/raylib.h"
#include "snskt/snake.h"
#include "snskt/menu.h"
#include "defs.h"
#include "pd/z_libpd.h"


void update_menu_inicio(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    // CAMBIAR LA PALETA DE COLORES
    switch(GetKeyPressed()){
        case KEY_F1:
            jueguito_vars->index_paleta += 1;
            if(jueguito_vars->index_paleta >= paletas_cantidad)
                jueguito_vars->index_paleta = 0;
            break;
        case KEY_F2:
            jueguito_vars->index_paleta -= 1;
            if(jueguito_vars->index_paleta < 0)
                jueguito_vars->index_paleta = paletas_cantidad - 1;
            break;
    }

    jueguito_vars->estados_menu_inicio = 0;
    Vector2 mv = GetMousePosition();
    Rectangle mr = (Rectangle){mv.x-5,mv.y-4,14,18};
    if(CheckCollisionRecs(mr,(Rectangle){jueguito_vars->sW/4-120, jueguito_vars->sH/2-160, jueguito_vars->sW/4+40,120})){
        if(!(jueguito_vars->estado_sonido_opcion & 1)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 1;
        }
        jueguito_vars->estados_menu_inicio = 1;

    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion  & 254;}


    if(CheckCollisionRecs(mr,(Rectangle){jueguito_vars->sW/4-80, jueguito_vars->sH/2+100, jueguito_vars->sW/2-240,80})){
        if(!(jueguito_vars->estado_sonido_opcion & 2)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 2;
        }
        jueguito_vars->estados_menu_inicio = 2;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 253;}

    
    if(CheckCollisionRecs(mr,(Rectangle){jueguito_vars->sW-160, jueguito_vars->sH/2+100, 100,100})){
        if(!(jueguito_vars->estado_sonido_opcion & 4)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 4;
        }
        jueguito_vars->estados_menu_inicio = 3;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 251;}

    if(CheckCollisionRecs(mr,(Rectangle){jueguito_vars->sW/2+20, jueguito_vars->sH/2+100, 100,100})){
        if(!(jueguito_vars->estado_sonido_opcion & 8)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 8;
        }
        jueguito_vars->estados_menu_inicio = 4;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 247;}

    
    if(CheckCollisionRecs(mr,(Rectangle){jueguito_vars->sW/2-45, jueguito_vars->sH/2-160, jueguito_vars->sW/2+10,120})){
        if(!(jueguito_vars->estado_sonido_opcion & 16)){
            libpd_bang("bHover");
            jueguito_vars->estado_sonido_opcion += 16;
        }
        jueguito_vars->estados_menu_inicio = 5;
    }else{jueguito_vars->estado_sonido_opcion = jueguito_vars->estado_sonido_opcion & 239;}


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
        case 2:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                libpd_bang("bSoundT");
            }
            break;
        case 3:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                jueguito_vars->volumen += 1;
                if(jueguito_vars->volumen > 50){
                    jueguito_vars->volumen = 50;
                }
                libpd_float("fVol",(f32)jueguito_vars->volumen/100);
            }
            break;
        case 4:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                jueguito_vars->volumen -= 1;
                if(jueguito_vars->volumen < 0){
                    jueguito_vars->volumen = 0;
                }
                libpd_float("fVol",(f32)jueguito_vars->volumen/100);
            }
            break;
        
        case 5:
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                jueguito_vars->estados = EnScoreboard;
                jueguito_vars->estados_menu_scoreboard = 0;
                return;
            }
            break;
        
    }
    
}

void draw_menu_inicio(jueguito_t *jv){
    ClearBackground(paletas[jv->index_paleta][1]);
    DrawText("SNASKET",130, 20, 130, paletas[jv->index_paleta][2]);
    DrawText(TextFormat("%d",jv->volumen),jv->sW/2+175, jv->sH/2+115, 80, paletas[jv->index_paleta][2]);
    DrawText("VOLUMEN",jv->sW/2+35, jv->sH/2+220, 70, paletas[jv->index_paleta][2]);
    switch(jv->estados_menu_inicio){
        case 0:
            DrawRectangle(jv->sW/4-120, jv->sH/2-160, jv->sW/4+40,120,paletas[jv->index_paleta][0]);
            DrawText("START",jv->sW/4-95, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][0]);
            DrawText("SOUND TEST",jv->sW/4-76, jv->sH/2+125, 30, paletas[jv->index_paleta][5]); 
            
            DrawTriangle((Vector2){jv->sW-160, jv->sH/2+100},(Vector2){jv->sW-160, jv->sH/2+200}, (Vector2){jv->sW-160+100,jv->sH/2+150},paletas[jv->index_paleta][0]);
            DrawTriangle((Vector2){jv->sW/2+20,jv->sH/2+150},(Vector2){jv->sW/2+120, jv->sH/2+200},(Vector2){jv->sW/2+120, jv->sH/2+100},paletas[jv->index_paleta][0]);

            
            DrawRectangle(jv->sW/2-45, jv->sH/2-160, jv->sW/2+10,120,paletas[jv->index_paleta][0]);
            DrawText("SCOREBOARD",jv->sW/2-20, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            break;
        case 1:
            DrawRectangle(jv->sW/4-120, jv->sH/2-160, jv->sW/4+40,120,paletas[jv->index_paleta][5]);
            DrawText("START",jv->sW/4-95, jv->sH/2-130, 60, paletas[jv->index_paleta][4]);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][0]);
            DrawText("SOUND TEST",jv->sW/4-76, jv->sH/2+125, 30, paletas[jv->index_paleta][5]); 
            
            DrawTriangle((Vector2){jv->sW-160, jv->sH/2+100},(Vector2){jv->sW-160, jv->sH/2+200}, (Vector2){jv->sW-160+100,jv->sH/2+150},paletas[jv->index_paleta][0]);
            DrawTriangle((Vector2){jv->sW/2+20,jv->sH/2+150},(Vector2){jv->sW/2+120, jv->sH/2+200},(Vector2){jv->sW/2+120, jv->sH/2+100},paletas[jv->index_paleta][0]);
            
            DrawRectangle(jv->sW/2-45, jv->sH/2-160, jv->sW/2+10,120,paletas[jv->index_paleta][0]);
            DrawText("SCOREBOARD",jv->sW/2-20, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            break;
        case 2:
            DrawRectangle(jv->sW/4-120, jv->sH/2-160, jv->sW/4+40,120,paletas[jv->index_paleta][0]);
            DrawText("START",jv->sW/4-95, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][5]);
            DrawText("SOUND TEST",jv->sW/4-76, jv->sH/2+125, 30, paletas[jv->index_paleta][4]); 

            DrawTriangle((Vector2){jv->sW-160, jv->sH/2+100},(Vector2){jv->sW-160, jv->sH/2+200}, (Vector2){jv->sW-160+100,jv->sH/2+150},paletas[jv->index_paleta][0]);
            DrawTriangle((Vector2){jv->sW/2+20,jv->sH/2+150},(Vector2){jv->sW/2+120, jv->sH/2+200},(Vector2){jv->sW/2+120, jv->sH/2+100},paletas[jv->index_paleta][0]);
            
            DrawRectangle(jv->sW/2-45, jv->sH/2-160, jv->sW/2+10,120,paletas[jv->index_paleta][0]);
            DrawText("SCOREBOARD",jv->sW/2-20, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            break;
        case 3:
            DrawRectangle(jv->sW/4-120, jv->sH/2-160, jv->sW/4+40,120,paletas[jv->index_paleta][0]);
            DrawText("START",jv->sW/4-95, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][0]);
            DrawText("SOUND TEST",jv->sW/4-76, jv->sH/2+125, 30, paletas[jv->index_paleta][5]);
            
            DrawTriangle((Vector2){jv->sW-160, jv->sH/2+100},(Vector2){jv->sW-160, jv->sH/2+200}, (Vector2){jv->sW-160+100,jv->sH/2+150},paletas[jv->index_paleta][5]);
            DrawTriangle((Vector2){jv->sW/2+20,jv->sH/2+150},(Vector2){jv->sW/2+120, jv->sH/2+200},(Vector2){jv->sW/2+120, jv->sH/2+100},paletas[jv->index_paleta][0]);
            
            DrawRectangle(jv->sW/2-45, jv->sH/2-160, jv->sW/2+10,120,paletas[jv->index_paleta][0]);
            DrawText("SCOREBOARD",jv->sW/2-20, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            break;
        case 4:
            DrawRectangle(jv->sW/4-120, jv->sH/2-160, jv->sW/4+40,120,paletas[jv->index_paleta][0]);
            DrawText("START",jv->sW/4-95, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][0]);
            DrawText("SOUND TEST",jv->sW/4-76, jv->sH/2+125, 30, paletas[jv->index_paleta][5]); 
            
            DrawTriangle((Vector2){jv->sW-160, jv->sH/2+100},(Vector2){jv->sW-160, jv->sH/2+200}, (Vector2){jv->sW-160+100,jv->sH/2+150},paletas[jv->index_paleta][0]);
            DrawTriangle((Vector2){jv->sW/2+20,jv->sH/2+150},(Vector2){jv->sW/2+120, jv->sH/2+200},(Vector2){jv->sW/2+120, jv->sH/2+100},paletas[jv->index_paleta][5]);
            
            DrawRectangle(jv->sW/2-45, jv->sH/2-160, jv->sW/2+10,120,paletas[jv->index_paleta][0]);
            DrawText("SCOREBOARD",jv->sW/2-20, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            break;
        case 5:
            DrawRectangle(jv->sW/4-120, jv->sH/2-160, jv->sW/4+40,120,paletas[jv->index_paleta][0]);
            DrawText("START",jv->sW/4-95, jv->sH/2-130, 60, paletas[jv->index_paleta][5]);
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][0]);
            DrawText("SOUND TEST",jv->sW/4-76, jv->sH/2+125, 30, paletas[jv->index_paleta][5]); 
            
            DrawTriangle((Vector2){jv->sW-160, jv->sH/2+100},(Vector2){jv->sW-160, jv->sH/2+200}, (Vector2){jv->sW-160+100,jv->sH/2+150},paletas[jv->index_paleta][0]);
            DrawTriangle((Vector2){jv->sW/2+20,jv->sH/2+150},(Vector2){jv->sW/2+120, jv->sH/2+200},(Vector2){jv->sW/2+120, jv->sH/2+100},paletas[jv->index_paleta][0]);

            
            DrawRectangle(jv->sW/2-45, jv->sH/2-160, jv->sW/2+10,120,paletas[jv->index_paleta][5]);
            DrawText("SCOREBOARD",jv->sW/2-20, jv->sH/2-130, 60, paletas[jv->index_paleta][4]);
            break;
    }
}

void conectar_a_db_scoreboard(jueguito_t* jv){
    jv->con = mysql_init(NULL);

    mysql_real_connect(jv->con, 
                            //credenciales de base de datos 
                            0, NULL, 0);
    mysql_query(jv->con, "select scores.name_player, scores.score from scores order by scores.score desc");

    MYSQL_RES *result = mysql_store_result(jv->con);

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;


    jv->scoreboard = MemAlloc(sizeof(player_db_t));
    jv->scoreboard->sig  = NULL;
    player_db_t *tmp = jv->scoreboard;

    while ((row = mysql_fetch_row(result))){
        tmp->name = row[0];
        sscanf(row[1], "%d", &tmp->score);

        tmp->sig = MemAlloc(sizeof(player_db_t));
        tmp->sig->sig = NULL;
        tmp = tmp->sig;
    }

    mysql_free_result(result);
    mysql_close(jv->con);


}

void update_menu_scoreboard(jueguito_t *jv){
    // CAMBIAR LA PALETA DE COLORES
    switch(GetKeyPressed()){
        case KEY_F1:
            jv->index_paleta += 1;
            if(jv->index_paleta >= paletas_cantidad)
                jv->index_paleta = 0;
            break;
        case KEY_F2:
            jv->index_paleta -= 1;
            if(jv->index_paleta < 0)
                jv->index_paleta = paletas_cantidad - 1;
            break;
    }

    switch(jv->estados_menu_scoreboard){
        case 0:
            jv->init_dibujar_score=0;
            conectar_a_db_scoreboard(jv);
            //printf("\nSI SE PUDO\n");
            jv->estados_menu_scoreboard = 1;
            jv->dibujar_board = 1;
            break;
        
    }
}
void draw_menu_scoreboard(jueguito_t *jv){
    player_db_t *tmp = jv->scoreboard;
    u32 xL = (jv->sW/6)-120;
    u32 xR = xL*28;
    u32 yU = (jv->sH/6)-100;
    u32 yD = yU*42;
    u32 yMore = yU;
    BeginScissorMode(xL, yU, xR, yD);
    
    ClearBackground(paletas[jv->index_paleta][1]);

    switch(jv->estados_menu_scoreboard){
        case 0:
            DrawText("Uniendose a\nbase de datos...",xR/2-130, yD/2-60, 50, paletas[jv->index_paleta][2]);
            break;
        case 1:
            //printf("\nEntrando a dibujar\n");
            
            while(1){
                yMore += 100;  
                printf("%s %d \n", tmp->name, tmp->score);  
                DrawText(TextFormat("%s",tmp->name),xR/4,yMore,40,paletas[jv->index_paleta][0]);
                DrawText(TextFormat("%d",tmp->score),xR/4+420,yMore,40,paletas[jv->index_paleta][0]);
                if( tmp->sig->sig == NULL){
                    break;
                }
                tmp = tmp->sig;
            }
            break;  
    }


    EndScissorMode();    

}





void update_menu_pausa(nodoSnake_t *snake_cabeza,jueguito_t *jueguito_vars){
    // CAMBIAR LA PALETA DE COLORES
    switch(GetKeyPressed()){
        case KEY_F1:
            jueguito_vars->index_paleta += 1;
            if(jueguito_vars->index_paleta >= paletas_cantidad)
                jueguito_vars->index_paleta = 0;
            break;
        case KEY_F2:
            jueguito_vars->index_paleta -= 1;
            if(jueguito_vars->index_paleta < 0)
                jueguito_vars->index_paleta = paletas_cantidad - 1;
            break;
    }
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
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("RESUME",xR/2+25, yU+70, 60, paletas[jueguito_vars->index_paleta][5]);            
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("RESTART",xL+93, yD-35, 26, paletas[jueguito_vars->index_paleta][5]); 
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("FINISH",xR-50, yD-35, 26, paletas[jueguito_vars->index_paleta][5]); 
            break;

        case 1:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,paletas[jueguito_vars->index_paleta][5]);
            DrawText("RESUME",xR/2+25, yU+70, 60, paletas[jueguito_vars->index_paleta][4]);   
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("RESTART",xL+93, yD-35, 26, paletas[jueguito_vars->index_paleta][5]); 
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("FINISH",xR-50, yD-35, 26, paletas[jueguito_vars->index_paleta][5]); 
            break;
        
        case 2:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("RESUME",xR/2+25, yU+70, 60, paletas[jueguito_vars->index_paleta][5]);   
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][5]);
            DrawText("RESTART",xL+93, yD-35, 26, paletas[jueguito_vars->index_paleta][4]); 
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("FINISH",xR-50, yD-35, 26, paletas[jueguito_vars->index_paleta][5]); 
            break;
        
        case 3:
            DrawRectangle(xR/2, yU+40, xR/2,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("RESUME",xR/2+25, yU+70, 60, paletas[jueguito_vars->index_paleta][5]);   
            DrawRectangle(xL+80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][0]);
            DrawText("RESTART",xL+93, yD-35, 26, paletas[jueguito_vars->index_paleta][5]); 
            DrawRectangle(xR-80, yD-80, xR/4,yD/4,paletas[jueguito_vars->index_paleta][5]);
            DrawText("FINISH",xR-50, yD-35, 26, paletas[jueguito_vars->index_paleta][4]); 
            break;
    }
        

    EndScissorMode();
}


void update_menu_terminar(nodoSnake_t *s,jueguito_t *jv){
    // CAMBIAR LA PALETA DE COLORES
    switch(GetKeyPressed()){
        case KEY_F1:
            jv->index_paleta += 1;
            if(jv->index_paleta >= paletas_cantidad)
                jv->index_paleta = 0;
            break;
        case KEY_F2:
            jv->index_paleta -= 1;
            if(jv->index_paleta < 0)
                jv->index_paleta = paletas_cantidad - 1;
            break;
    }



    jv->estados_menu_terminado = 0;

    Vector2 mv = GetMousePosition();
    Rectangle mr = (Rectangle){mv.x-5,mv.y-4,14,18};
    
    if(CheckCollisionRecs(mr,(Rectangle){jv->sW/4+50, jv->sH/4 + 90, jv->sW/2-90,60})){
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
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                jv->estados = EnSubmitRecord;
                jv->estados_menu_submit_record = 0;
                return;
            }
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
    ClearBackground(paletas[jv->index_paleta][4]);
    const char *p=TextFormat("%d", jv->nodos_cantidad);
    const char* scoreText = TextFormat("SCORE: %s", p);
    DrawText(scoreText,jv->sW/2 - 220,jv->sH/4 ,86,paletas[jv->index_paleta][2]);
    switch(jv->estados_menu_terminado){
        case 0:
            DrawRectangle(jv->sW/4+50, jv->sH/4 + 90, jv->sW/2-90,60,paletas[jv->index_paleta][0]);
            DrawText("SUBMIT SCORE",jv->sW/4+70, jv->sH/4 + 100, 40, paletas[jv->index_paleta][5]);   
                        
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][0]);
            DrawText("RESTART",jv->sW/4-74, jv->sH/2+120, 40, paletas[jv->index_paleta][5]);   
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][0]);
            DrawText("MENU",jv->sW/2+130, jv->sH/2+120, 40, paletas[jv->index_paleta][5]); 
            break;
        case 1:
            DrawRectangle(jv->sW/4+50, jv->sH/4 + 90, jv->sW/2-90,60,paletas[jv->index_paleta][5]);
            DrawText("SUBMIT SCORE",jv->sW/4+70, jv->sH/4 + 100, 40, paletas[jv->index_paleta][4]);   
            
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][0]);
            DrawText("RESTART",jv->sW/4-74, jv->sH/2+120, 40, paletas[jv->index_paleta][5]);   
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][0]);
            DrawText("MENU",jv->sW/2+130, jv->sH/2+120, 40, paletas[jv->index_paleta][5]); 
            break;
        case 2:
            DrawRectangle(jv->sW/4+50, jv->sH/4 + 90, jv->sW/2-90,60,paletas[jv->index_paleta][0]);
            DrawText("SUBMIT SCORE",jv->sW/4+70, jv->sH/4 + 100, 40, paletas[jv->index_paleta][5]);   
            
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][5]);
            DrawText("RESTART",jv->sW/4-74, jv->sH/2+120, 40, paletas[jv->index_paleta][4]);  
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][0]);
            DrawText("MENU",jv->sW/2+130, jv->sH/2+120, 40, paletas[jv->index_paleta][5]); 

            break;
        case 3:
            DrawRectangle(jv->sW/4+50, jv->sH/4 + 90, jv->sW/2-90,60,paletas[jv->index_paleta][0]);
            DrawText("SUBMIT SCORE",jv->sW/4+70, jv->sH/4 + 100, 40, paletas[jv->index_paleta][5]);   
            
            DrawRectangle(jv->sW/4-80, jv->sH/2+100, jv->sW/2-240,80, paletas[jv->index_paleta][0]);
            DrawText("RESTART",jv->sW/4-74, jv->sH/2+120, 40, paletas[jv->index_paleta][5]); 
            DrawRectangle(jv->sW/2+80, jv->sH/2+100, jv->sW/2-240,80,paletas[jv->index_paleta][5]);
            DrawText("MENU",jv->sW/2+130, jv->sH/2+120, 40, paletas[jv->index_paleta][4]); 

            break;
    }

}







void update_menu_submit_score(jueguito_t *jv){
    // CAMBIAR LA PALETA DE COLORES
    switch(GetKeyPressed()){
        case KEY_F1:
            jv->index_paleta += 1;
            if(jv->index_paleta >= paletas_cantidad)
                jv->index_paleta = 0;
            break;
        case KEY_F2:
            jv->index_paleta -= 1;
            if(jv->index_paleta < 0)
                jv->index_paleta = paletas_cantidad - 1;
            break;
    }

    switch(jv->estados_menu_submit_record){
        case 0:

            break;
    }


}

void draw_menu_submit_score(jueguito_t *jv){
    u32 xL = (jv->sW/6)-120;
    u32 xR = xL*28;
    u32 yU = (jv->sH/6)-100;
    u32 yD = yU*42;

    BeginScissorMode(xL, yU, xR, yD);
    
    ClearBackground(paletas[jv->index_paleta][1]);

    switch(jv->estados_menu_submit_record){
        case 0:
            DrawText("Uniendose a\nbase de datos...",xR/2-130, yD/2-60, 50, paletas[jv->index_paleta][2]);
            break;        
    }


    EndScissorMode();    
    
}
