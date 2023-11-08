#ifdef aguanta
#include "ray/raylib.h"
#include "ray/rlgl.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#include "defs.h"
#include "snskt/snake.h"
#define PD_HANDLER_IMPL
#include "snskt/pd_handler.h"

#include "snskt/menu.h"

//#define GRABAR_
#ifdef GRABAR_
//#define MSF_GIF_IMPL
#include <time.h>
#define TIEMPO_LAPSO_GIF .15
#include "msf_gif.h"
#endif //GRABAR_ 


//#define RELEASE_
#define DEVELOPMENT_

#endif //aguanta


//#define aguanta

#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>


int main(void){

    MYSQL *con = mysql_init(NULL);








    #ifdef aguanta

    // SETUP LIBPD
    Pa_Initialize();
    int inputdev = Pa_GetDefaultInputDevice();
    int outputdev = Pa_GetDefaultOutputDevice();
    int inputchan = pa_get_inputs(inputdev);
    int outputchan = pa_get_outputs(outputdev);
    int samplerate = 44100;
    int buffersize = 2048;
    PaStream *stream = NULL;
    PaStreamParameters inputParams = {
        .device = (PaDeviceIndex)inputdev,
        .channelCount = inputchan,
        .sampleFormat = paFloat32,
        0,
        NULL
    };
    PaStreamParameters outputParams = {
        .device = (PaDeviceIndex)outputdev,
        .channelCount = outputchan,
        .sampleFormat = paFloat32,
        0,
        NULL
    };
    Pa_OpenStream(
        &stream,
        (inputchan > 0 ? &inputParams : NULL),
        (outputchan > 0 ? &outputParams : NULL),
        samplerate,
        buffersize,
        0,
        pa_callback,
        NULL
    );

    // init pd, match portaudio channels and samplerate
    libpd_set_printhook(pdprint);
    libpd_set_noteonhook(pdnoteon);
    libpd_init();
    libpd_init_audio(inputchan, outputchan, samplerate);
    
    // compute audio    [; pd dsp 1(
    libpd_start_message(1); // one entry in list
    libpd_add_float(1.0f);
    libpd_finish_message("pd", "dsp");

    #ifdef RELEASE_
    // open patch       [; pd open file folder(
    libpd_openfile("sonidos.pd", "assets");
    #endif //RELEASE_

    #ifdef DEVELOPMENT_
    // open patch       [; pd open file folder(
    libpd_openfile("sonidos.pd", "../pd");
    #endif //DEVELOPMENT_

    Pa_StartStream(stream);

    ///////////////
    

    // SETUP VARIABLES DEL JUEGUITO
    nodoSnake_t* snake_p = MemAlloc(sizeof(nodoSnake_t));
    snake_p->sig = NULL;

    jueguito_t* jueguito_vars = MemAlloc(sizeof(jueguito_t));
    jueguito_vars->sH = 700;
    jueguito_vars->sW = 900;
    jueguito_vars->index_paleta =0;
    jueguito_vars->estados = EnMenuInicio;

    jueguito_vars->volumen = 10;
    libpd_float("fVol",(f32)jueguito_vars->volumen/100);
   
    
    //////////////
    

    


    // SETUP GIF RECORDER
    #ifdef GRABAR_ 
    f32 segundoFrame = 0;
    s32 centisecondsPerFrame = 5, bitDepth = 16;
    MsfGifState gifState;
    msf_gif_begin(&gifState, jueguito_vars->sW, jueguito_vars->sH);
    #endif //GRABAR_ 
    /////////////////////


    // SETUP RAYLIB
    InitWindow(jueguito_vars->sW, jueguito_vars->sH, "snasket");
    #ifdef RELEASE_
    SetWindowIcon(LoadImage("assets/snasket.png"));
    #endif //RELEASE_
    
    #ifdef DEVELOPMENT_
    SetWindowIcon(LoadImage("../resources/snasket.png"));
    #endif //DEVELOPMENT_

    SetTargetFPS(FLAG_VSYNC_HINT);
    SetExitKey(KEY_NULL);
    /////////////////////////

    //Bucle principal
    while (!WindowShouldClose()){
        

        // SWITCH PARA UPDATE
        switch (jueguito_vars->estados){
            case EnMenuInicio:
                update_menu_inicio(snake_p, jueguito_vars);
                break;
            case EnJueguito:
                update_snake(snake_p,jueguito_vars);
                break;
            case EnMenuPausa:
                update_menu_pausa(snake_p, jueguito_vars);
                break;
            case EnMenuTerminado:
                update_menu_terminar(snake_p, jueguito_vars);
                break;
        }
        
        
        BeginDrawing();
        
        
        // SWITCH PARA DRAW
        switch (jueguito_vars->estados){
            case EnMenuInicio:
                draw_menu_inicio(jueguito_vars);
                break;
            case EnJueguito:
                draw_snake(snake_p,jueguito_vars);
                break;
            case EnMenuPausa:
                draw_menu_pausa(snake_p,jueguito_vars);
                break;
            case EnMenuTerminado:
                draw_menu_terminar(snake_p, jueguito_vars);
                break;
        }




        //DrawFPS(5, 5);   
        
        EndDrawing();
        /*
        // UPDATE SNAKE
        update_snake(snake_p, jueguito_vars);
        /////////////
        //¬ BLOQUE DE DIBUJO
        BeginDrawing();
        
        // DRAW SNAKE
        draw_snake(snake_p, jueguito_vars);
        /////////////
        DrawFPS(5, 5);        
        EndDrawing();
        //¬/////////////////
        */

        #ifdef GRABAR_ 
        segundoFrame += GetFrameTime();
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
        const char * gif_path =TextFormat("gif_snasket_%d.gif", (u32)now);
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

    // Libera el stream de portaudio y cierra
    Pa_StopStream(stream);
    Pa_Terminate();

    #endif //aguanta    

    return 0;
}
