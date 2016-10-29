#pragma once

#include <cv.h>
#include "opencv2/opencv.hpp"
//for the rasperry pi
#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif
extern "C" {
#include <SDL.h>
#include <SDL_ttf.h>
}
#include <stdio.h>
#include <unistd.h>

#ifdef __amd64__
#ifndef RUNNINGONINTEL
#define RUNNINGONINTEL
#endif
#else
#ifndef RUNNINGONPI
#define RUNNINGONPI
#endif
#include "WiringPiButtons.hpp"
#endif


#include "graphics_handler.h"
#include "videoStream.hpp"

//event flags to pass back to main super loop
#define QUIT_EVENT_FLAG 'A'
#define ENTER_FULLSCREEN_EVENT_FLAG 'B'
#define EXIT_FULLSCREEN_EVENT_FLAG 'C'



class BackupCamera
{


public:
    BackupCamera();
    bool init(SDL_Renderer** empty_renderer, SDL_Window** empty_window, int xpos, int ypos, int screen_width, int screen_height);
    bool init_graphics(SDL_Renderer* renderer);
    bool init_screen_settings(SDL_Window* window, int camera_device, int camera_height, int camera_width);
    vector<char> process_events();
    bool update();
    void start_threads();

    void close();
    void resizeCameraRect(SDL_Window* window);

private:
    bool init_SDL(SDL_Renderer** empty_renderer, SDL_Window** empty_window, int xpos, int ypos, int screen_width, int screen_height);
    void init_graphics_handler(SDL_Renderer* renderer);
    void processGPIO();
    void signalToQuit();




    GraphicsHandler* graphics_handler_;


    /** Displayable **/
    VideoStream* camera_one_;

    bool fullscreenFlag_;


    int screenWidth_;
    int screenHeight_;

};
