#include "backup_camera.h"


BackupCamera::BackupCamera()
{
    fullscreenFlag_ = false;
}

bool BackupCamera::init(SDL_Renderer** empty_renderer, SDL_Window** empty_window, int xpos, int ypos, int screen_width, int screen_height)
{
    bool success = true;
    success = init_SDL(empty_renderer, empty_window, xpos, ypos, screen_width, screen_height) && success;
    screenWidth_ = screen_width;
    screenHeight_ = screen_height;
    camera_one_ = new VideoStream();
    return success;
}

//Creates the Window
bool BackupCamera::init_SDL(SDL_Renderer** empty_renderer, SDL_Window** empty_window, int xpos, int ypos, int screen_width, int screen_height)
{
    bool success = true;

    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        int windowMode = (fullscreenFlag_ == true ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_BORDERLESS);
        *empty_window = SDL_CreateWindow("Video Application", xpos, ypos, screen_width, screen_height, windowMode);

        if (empty_window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            *empty_renderer = SDL_CreateRenderer(*empty_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (*empty_renderer == NULL)
            {
                printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
                printf("Creating a software empty_renderer instead\n");
                *empty_renderer = SDL_CreateRenderer(*empty_window, -1, SDL_RENDERER_SOFTWARE);

                if (*empty_renderer == NULL)
                {
                    printf("Renderer could not be created. SDL_Error: %s \n", SDL_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

//This is where you will define Rect's within the Window
bool BackupCamera::init_screen_settings(SDL_Window* window, int camera_device, int camera_height, int camera_width)
{
    bool success = true;
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect camera_one_rect;
    camera_one_rect.x = 0;
    camera_one_rect.y = 0;
    camera_one_rect.w = w;
    camera_one_rect.h = h;
    success = camera_one_->init_setting(camera_one_rect, camera_device, camera_height, camera_width) && success;
    return success;
}

//Gives the graphics_handler the SDL_Renderer
bool BackupCamera::init_graphics(SDL_Renderer* renderer)
{
    bool success = true;

    if (renderer != NULL)
    {
        graphics_handler_ = new GraphicsHandler(renderer);
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
    return camera_one_->update(graphics_handler_);
}


bool BackupCamera::process_events()
{
    using namespace cameraVariables;
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
        }
    }

    return true;
}

void BackupCamera::start_threads()
{
    camera_one_->StartThread();
}

void BackupCamera::processGPIO()
{
}

void BackupCamera::signalToQuit()
{
    camera_one_->signalToQuit();
}

void BackupCamera::close()
{
    camera_one_->WaitForThreadToExit();
}

void BackupCamera::toggleFullscreen()
{
    using namespace cameraVariables;
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
    camera_one_->resizeVideoRect(cameraOneNewRect);
}
