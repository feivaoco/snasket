#include "ray/raylib.h"
#include "ray/rlgl.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#include "defs.h"
#include "snskt/snake.h"


//#define GRABAR_
#ifdef GRABAR_ 
#include <time.h>
#define TIEMPO_LAPSO_GIF .1
#include "msf_gif.h"
#endif //GRABAR_ 


int main(void){
    // SETUP SNAKE
    nodoSnake_t* snake_p = MemAlloc(sizeof(nodoSnake_t));
    jueguito_t* jueguito_vars = MemAlloc(sizeof(jueguito_t));
    snake_p->sig = NULL;
    setup_snake(snake_p, jueguito_vars);
    f32 segundoFrame = 0;
    /////////////
    
    #ifdef GRABAR_ 
    // SETUP GIF RECORDER
    s32 centisecondsPerFrame = 5, bitDepth = 16;
    MsfGifState gifState;
    msf_gif_begin(&gifState, jueguito_vars->sW, jueguito_vars->sH);
    /////////////////////
    #endif //GRABAR_ 

    InitWindow(jueguito_vars->sW, jueguito_vars->sH, "snasket");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
        #ifdef GRABAR_ 
        segundoFrame += GetFrameTime();
        #endif //GRABAR_ 
        // UPDATE SNAKE
        update_snake(snake_p, jueguito_vars);
        /////////////


        //¬ BLOQUE DE DIBUJO
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        // DRAW SNAKE
        draw_snake(snake_p, jueguito_vars);
        /////////////

        DrawFPS(5, 5);        
        EndDrawing();
        //¬/////////////////

        #ifdef GRABAR_ 
        if(segundoFrame > TIEMPO_LAPSO_GIF){
            // Grabar la pantalla para el gif
            msf_gif_frame(&gifState, rlReadScreenPixels(jueguito_vars->sW,jueguito_vars->sH), centisecondsPerFrame, bitDepth, jueguito_vars->sW * 4);
            segundoFrame = 0;
        }
        #endif //GRABAR_ 
    }

    CloseWindow();   

    #ifdef GRABAR_ 
    // Genera gif
    MsfGifResult result = msf_gif_end(&gifState);
    if (result.data) {
        time_t now = time(NULL);
        const char * gif_path =TextFormat("../demos_gif/gif_snasket_%d.gif", (u32)now);
        FILE * fp = fopen(gif_path, "wb");
        fwrite(result.data, result.dataSize, 1, fp);
        fclose(fp);
    }
    // Libera el espacio de memoria del resultado del gif
    msf_gif_free(result);
    #endif //GRABAR_ 

    // Libera el espacio de memoria
    MemFree(snake_p);
    MemFree(jueguito_vars);    

    return 0;
}
