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
                    //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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


vector<char> BackupCamera::process_events()
{
    SDL_Event event;
    vector<char> returningEvents = vector<char>();

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                printf("SDL_QUIT was called\n");
                signalToQuit();
                returningEvents.push_back(QUIT_EVENT_FLAG);
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        printf("Esc was Pressed!\n");
                        signalToQuit();
                        returningEvents.push_back(QUIT_EVENT_FLAG);
                        break;

                    case SDLK_f:
                        if (fullscreenFlag_ == false)
                        {
                            returningEvents.push_back(ENTER_FULLSCREEN_EVENT_FLAG);
                        }
                        else
                        {
                            returningEvents.push_back(EXIT_FULLSCREEN_EVENT_FLAG);
                        }

                        break;
                }
        }
    }

    return returningEvents;
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

void BackupCamera::resizeCameraRect(SDL_Window* window)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Rect camera_one_new_rect;
    camera_one_new_rect.x = 0;
    camera_one_new_rect.y = 0;

    if (!fullscreenFlag_) //should work witthout the if statement, but moving back to window doesnt shrink back for some reason when reading window size
    {
        camera_one_new_rect.w = w;
        camera_one_new_rect.h = h;
    }
    else
    {
        camera_one_new_rect.w = screenWidth_;
        camera_one_new_rect.h = screenHeight_;
    }

    fullscreenFlag_ = !fullscreenFlag_;
    camera_one_->resizeVideoRect(camera_one_new_rect);
}
