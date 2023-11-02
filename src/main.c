#include "ray/raylib.h"
#include "ray/rlgl.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#include "defs.h"
#include "snskt/snake.h"
#define PD_HANDLER_IMPL
#include "snskt/pd_handler.h"

//#define GRABAR_
#ifdef GRABAR_

//#define MSF_GIF_IMPL
#include <time.h>
#define TIEMPO_LAPSO_GIF .1
#include "msf_gif.h"

#endif //GRABAR_ 


int main(void){

    // SETUP LIBPD
    Pa_Initialize();
    int inputdev = Pa_GetDefaultInputDevice();
    int outputdev = Pa_GetDefaultOutputDevice();
    int inputchan = pa_get_inputs(inputdev);
    int outputchan = pa_get_outputs(outputdev);
    int samplerate = 44100;
    int buffersize = 1024;
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

    // open patch       [; pd open file folder(
    libpd_openfile("sonidos.pd", "../pd");
    Pa_StartStream(stream);

    ///////////////

    // SETUP SNAKE
    nodoSnake_t* snake_p = MemAlloc(sizeof(nodoSnake_t));
    jueguito_t* jueguito_vars = MemAlloc(sizeof(jueguito_t));
    snake_p->sig = NULL;
    setup_snake(snake_p, jueguito_vars);
    /////////////
    
    // SETUP GIF RECORDER
    #ifdef GRABAR_ 
    f32 segundoFrame = 0;
    s32 centisecondsPerFrame = 5, bitDepth = 16;
    MsfGifState gifState;
    msf_gif_begin(&gifState, jueguito_vars->sW, jueguito_vars->sH);
    #endif //GRABAR_ 
    /////////////////////

    InitWindow(jueguito_vars->sW, jueguito_vars->sH, "snasket");
    SetTargetFPS(60);
    
    while (!WindowShouldClose()){
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

    // Libera el stream de portaudio y cierra
    Pa_StopStream(stream);
    Pa_Terminate();

    return 0;
}
