#include "backup_camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>


namespace cameraVariables
{
    SDL_Window* window_ = NULL;
}




int main(int argc, char* argv[])
{
    using namespace cameraVariables;

    if (argc != 7)
    {
        printf("Usage: %s   screen_x_cordinate  screen_y_coordinate  screen_width  screen_height  camera_res_x  camera_res_y\n", argv[0]);
        return 0;
    }

    BackupCamera* backupCamera = new BackupCamera();
    SDL_Renderer* renderer = NULL;

    if (!backupCamera->init(&renderer, &window_, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])))
    {
        fprintf(stderr, "Could not initialize!\n");
        return -1;
    }

    if (renderer == NULL)
    {
        printf("Renderer is null\n");
    }

    backupCamera->init_screen_settings(window_, 0, atoi(argv[5]), atoi(argv[6]));
    backupCamera->init_graphics(renderer);
    printf("Starting threads\n");
    backupCamera->start_threads();

    while (backupCamera->process_events())
    {
        if (backupCamera->update())
        {
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
        }
    }

    backupCamera->close();
    return 0;
}


