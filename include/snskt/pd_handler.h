#ifndef PD_HANDLER_H_
#define PD_HANDLER_H_
#include <stdio.h>
#include "pd/z_libpd.h"
#include "pa/portaudio.h"

// PORTAUDIO

// returns number of input channels for device index or 0 if none
static int pa_get_inputs(PaDeviceIndex dev);

// returns number of output channels for device index or 0 if none
static int pa_get_outputs(PaDeviceIndex dev);

// portaudio sample render callback
static int pa_callback(const void *inputBuffer, void *outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo* timeInfo,
                       PaStreamCallbackFlags statusFlags, void *userData);

// UTIL
#include <unistd.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN

// EVITAR CONCLIFCTO CON RAYLIB
#define NOGDI               // All GDI defines and routines
#define NOUSER              // All USER defines and routines
/////////////////////////////////

#include <windows.h>
#endif

// cross-platform sleep
// from https://gist.github.com/rafaelglikis/ee7275bf80956a5308af5accb4871135
void sleep_ms(int ms);

// MAIN

void pdprint(const char *s);
void pdnoteon(int ch, int pitch, int vel);

void bang_collider_comida();
#endif // PD_HANDLER_H_



#ifdef PD_HANDLER_IMPL
// PORTAUDIO

// returns number of input channels for device index or 0 if none
static int pa_get_inputs(PaDeviceIndex dev) {
    const PaDeviceInfo *info = Pa_GetDeviceInfo(dev);
    return (info ? info->maxInputChannels : 0);
}

// returns number of output channels for device index or 0 if none
static int pa_get_outputs(PaDeviceIndex dev) {
    const PaDeviceInfo *info = Pa_GetDeviceInfo(dev);
    return (info ? info->maxOutputChannels : 0);
}

// portaudio sample render callback
static int pa_callback(const void *inputBuffer, void *outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo* timeInfo,
                       PaStreamCallbackFlags statusFlags, void *userData) {
  // assumes blocksize is *always* a multiple of libpd_blocksize(),
  // if not, then additional buffer is required
  int ticks = framesPerBuffer / libpd_blocksize(); 
  libpd_process_float(ticks, inputBuffer, outputBuffer);
  return 0;
}

// cross-platform sleep
// from https://gist.github.com/rafaelglikis/ee7275bf80956a5308af5accb4871135
void sleep_ms(int ms) {
  #ifdef _WIN32
    Sleep(ms);
  #elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
  #else
    usleep(ms * 1000);
  #endif
}


// MAIN

void pdprint(const char *s) {
  printf("%s", s);
}

void pdnoteon(int ch, int pitch, int vel) {
  printf("noteon: %d %d %d\n", ch, pitch, vel);
}



#endif //PD_HANDLER_IMPL
