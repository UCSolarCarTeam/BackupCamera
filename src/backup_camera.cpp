#include "backup_camera.h"

BackupCamera::BackupCamera()
    : fullscreenFlag_(false)
    , lastTouchEventTime_(0)
    , window_(NULL)
{}

bool BackupCamera::init(SDL_Renderer** emptyRenderer, int xPos, int yPos, int screenWidth, int screenHeight)
{
    bool success = true;
    success = initSDL(emptyRenderer, &window_, xPos, yPos, screenWidth, screenHeight) && success;
    screenWidth_ = screenWidth;
    screenHeight_ = screenHeight;
    cameraOne_ = new VideoStream();
    return success;
}

//Creates the Window
bool BackupCamera::initSDL(SDL_Renderer** emptyRenderer, SDL_Window** emptyWindow, int xPos, int yPos, int screenWidth, int screenHeight)
{
    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    int windowMode = (fullscreenFlag_ == true ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_BORDERLESS);
    *emptyWindow = SDL_CreateWindow("Video Application", xPos, yPos, screenWidth, screenHeight, windowMode);

    if (emptyWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    *emptyRenderer = SDL_CreateRenderer(*emptyWindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (*emptyRenderer == NULL)
    {
        printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
        printf("Creating a software empty_renderer instead\n");

        *emptyRenderer = SDL_CreateRenderer(*emptyWindow, -1, SDL_RENDERER_SOFTWARE);

        if (*emptyRenderer == NULL)
        {
            printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
            return false;
        }
    }

    return true;
}

//This is where you will define Rect's within the Window
bool BackupCamera::initScreenSettings(int cameraDevice, int cameraHeight, int cameraWidth)
{
    bool success = true;
    int w, h;
    SDL_GetWindowSize(window_, &w, &h);
    printf("W: %d H: %d\n", w, h);
    SDL_Rect cameraOneRect;
    cameraOneRect.x = 0;
    cameraOneRect.y = 0;
    cameraOneRect.w = w;
    cameraOneRect.h = h;
    success = cameraOne_->initSetting(cameraOneRect, cameraDevice, cameraHeight, cameraWidth) && success;
    return success;
}

//Gives the graphics_handler the SDL_Renderer
bool BackupCamera::initGraphics(SDL_Renderer* renderer)
{
    bool success = true;

    if (renderer != NULL)
    {
        graphicsHandler_ = new GraphicsHandler(renderer);
    }
    else
    {
        success = false;
    }

    return success;
}

//only returns true if camera updates
//Used for any "Updates" you need. Currently there is only one "camera" within this class.
bool BackupCamera::BackupCamera::update()
{
    return cameraOne_->update(graphicsHandler_);
}

bool BackupCamera::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                printf("SDL_QUIT was called\n");
                signalToQuit();
                return false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        printf("Esc was Pressed!\n");
                        signalToQuit();
                        return false;
                        break;

                    case SDLK_f:
                        this->toggleFullscreen();
                        break;
                }

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.clicks == 2)
                {
                    this->toggleFullscreen();
                }

                break;

            case SDL_FINGERDOWN:
                if ((event.tfinger.timestamp - lastTouchEventTime_) <= 500)
                {
                    this->toggleFullscreen();
                    lastTouchEventTime_ = 0;
                }
                else
                {
                    lastTouchEventTime_ = event.tfinger.timestamp;
                }

                break;
        }
    }

    return true;
}

void BackupCamera::startThreads()
{
    cameraOne_->StartThread();
}

void BackupCamera::processGPIO()
{
}

void BackupCamera::signalToQuit()
{
    cameraOne_->signalToQuit();
}

void BackupCamera::close()
{
    cameraOne_->WaitForThreadToExit();
}

void BackupCamera::toggleFullscreen()
{
    int w, h;
    SDL_Rect cameraOneNewRect;
    cameraOneNewRect.x = 0;
    cameraOneNewRect.y = 0;

    if (!fullscreenFlag_)
    {
        SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_GetWindowSize(window_, &w, &h);
        cameraOneNewRect.w = w;
        cameraOneNewRect.h = h;
    }
    else
    {
        SDL_SetWindowFullscreen(window_, 0);
        cameraOneNewRect.w = screenWidth_;
        cameraOneNewRect.h = screenHeight_;
    }

    fullscreenFlag_ = !fullscreenFlag_;
    cameraOne_->resizeVideoRect(cameraOneNewRect);
}
