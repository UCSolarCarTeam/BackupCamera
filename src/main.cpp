#include "backup_camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

//how to use:
//./<binary> xpos ypos


SDL_Window* window_;
BackupCamera* backupCamera_;
bool quitSignal_;


void handleEvent(char eventCode)
{
    switch (eventCode)
    {
        case  QUIT_EVENT_FLAG:
            quitSignal_ = true;
            break;

        case  ENTER_FULLSCREEN_EVENT_FLAG:
            SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
            backupCamera_->resizeCameraRect(window_);
            break;

        case  EXIT_FULLSCREEN_EVENT_FLAG:
            SDL_SetWindowFullscreen(window_, 0);
            backupCamera_->resizeCameraRect(window_);
            break;
    }
}


int main(int argc, char* argv[])
{
    if (argc != 7)
    {
        printf("Usage: %s   screen_x_cordinate  screen_y_coordinate  screen_width  screen_height  camera_res_x  camera_res_y\n", argv[0]);
        return 0;
    }

    backupCamera_ = new BackupCamera();
    SDL_Renderer* renderer = NULL;
    window_ = NULL;

    if (!backupCamera_->init(&renderer, &window_, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])))
    {
        fprintf(stderr, "Could not initialize!\n");
        return -1;
    }

    if (renderer == NULL)
    {
        printf("Renderer is null\n");
    }

    backupCamera_->init_screen_settings(window_, 0, atoi(argv[5]), atoi(argv[6]));
    backupCamera_->init_graphics(renderer);
    printf("Starting threads\n");
    backupCamera_->start_threads();
    vector<char> eventsToHandle;
    quitSignal_  = false;

    while (!quitSignal_)
    {
        eventsToHandle = backupCamera_->process_events();

        if (backupCamera_->update())
        {
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
        }

        while (!eventsToHandle.empty())
        {
            handleEvent(eventsToHandle.back());
            eventsToHandle.pop_back();
        }
    }

    backupCamera_->close();
    return 0;
}


