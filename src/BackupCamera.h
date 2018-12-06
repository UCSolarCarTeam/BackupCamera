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
#endif

#include "GraphicsHandler.h"
#include "VideoStream.hpp"

class BackupCamera
{

public:
    BackupCamera();
    /**
     * Used to initialize the Backup Camera
     * This function will initialize SDL, so pass it an empty SDL_Renderer, and after this init function
     * returns, the <code>SDL_Renderer**</code> will be initialized.
     */
    bool init(SDL_Renderer** emptyRenderer, int xPos, int yPos, int screenWidth, int screenHeight);
    bool initGraphics(SDL_Renderer* renderer);
    bool initScreenSettings(int cameraDevice, int cameraHeight, int cameraWidth);
    bool processEvents();
    bool update();
    void startThreads();
    void close();
    void toggleFullscreen();

private:
    bool initSDL(SDL_Renderer** emptyRenderer, SDL_Window** emptyWindow, int xPos, int yPos, int screenWidth, int screenHeight);
    void initGraphicsHandler(SDL_Renderer* renderer);
    void processGPIO();
    void signalToQuit();

    GraphicsHandler* graphicsHandler_;
    /** Displayable **/
    VideoStream* cameraOne_;
    bool fullscreenFlag_;
    Uint32 lastTouchEventTime_;
    int screenWidth_;
    int screenHeight_;
    SDL_Window* window_;
};
