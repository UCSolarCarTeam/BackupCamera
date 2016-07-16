#include "backup_camera.h"

BackupCamera::BackupCamera(){
}

bool BackupCamera::init(SDL_Renderer **empty_renderer, SDL_Window **empty_window, int xpos, int ypos, int screen_width, int screen_height) {
    bool success = true;
    success = init_SDL(empty_renderer, empty_window, xpos, ypos, screen_width, screen_height) && success; 

    camera_one_ = new VideoStream();
    //song_player_one_ = new SongPlayer();

    //song_player_one_->initSongPlayer();
    //music_bar_one_ = new MusicBar(song_player_one_);

    return success;
}

//Creates the Window
bool BackupCamera::init_SDL(SDL_Renderer **empty_renderer, SDL_Window **empty_window, int xpos, int ypos, int screen_width, int screen_height) {
    bool success = true;
    if (SDL_Init(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        *empty_window = SDL_CreateWindow("Video Application", xpos, ypos, screen_width, screen_height, SDL_WINDOW_BORDERLESS);
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
bool BackupCamera::init_screen_settings(SDL_Window *window, int camera_device, int camera_height, int camera_width) {
    bool success = true;
    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    SDL_Rect camera_one_rect;
    camera_one_rect.x = 0;
    camera_one_rect.y = 0;
    camera_one_rect.w = w;
    camera_one_rect.h = h;
    success = camera_one_->init_setting(camera_one_rect, camera_device, camera_height, camera_width) && success;
    
    //SDL_Rect music_bar_one_rect;
    //music_bar_one_rect.x = 0;
    //music_bar_one_rect.y = h - 49;
    //music_bar_one_rect.w = w;
    //music_bar_one_rect.h = 49;
    //music_bar_one_->init_setting(music_bar_one_rect);

    return success;
}

//Gives the graphics_handler the SDL_Renderer
bool BackupCamera::init_graphics(SDL_Renderer *renderer) {
    bool success = true;
    if (renderer != NULL) {
        graphics_handler_ = new GraphicsHandler(renderer); 
    } else {
        success = false;
    }
    return success;
}

//only returns true if camera updates
//Used for any "Updates" you need. Currently there is only one "camera" within this class. 
bool BackupCamera::BackupCamera::update() {
    //music_bar_one_->update(graphics_handler_);
    return camera_one_->update(graphics_handler_);
}


bool BackupCamera::process_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                printf("SDL_QUIT was called\n");
                signalToQuit();
                return false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        printf("Esc was Pressed!\n");
                        signalToQuit();
                        return false;
                        break;
                }
        }
    }
    return true;
}

void BackupCamera::start_threads() {
    //song_player_one_->StartThread();
    camera_one_->StartThread();

}

void BackupCamera::processGPIO() {

}

void BackupCamera::signalToQuit() {
    camera_one_->signalToQuit();
    //song_player_one_->songQuit();
}

void BackupCamera::close() {
    //song_player_one_->closeSongPlayer();
    //song_player_one_->WaitForThreadToExit();
    camera_one_->WaitForThreadToExit();
}
    

