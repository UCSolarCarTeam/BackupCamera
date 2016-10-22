#include "backup_camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

//how to use:
//./<binary> xpos ypos
int main(int argc, char* argv[])
{
    if (argc != 7)
    {
        printf("Invalid number of arguments. Needs six arguments separated by spaces"
               "./<binary> screen_x screen_y "
               "screen_width screen_height "
               "camera_res_x camera_res_y\n");
        return 0;
    }

    BackupCamera* backup_camera = new BackupCamera();
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;

    if (!backup_camera->init(&renderer, &window, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])))
    {
        fprintf(stderr, "Could not initialize!\n");
        return -1;
    }

    if (renderer == NULL)
    {
        printf("Renderer is null\n");
    }

    backup_camera->init_screen_settings(window, 0, atoi(argv[5]), atoi(argv[6]));
    backup_camera->init_graphics(renderer);
    printf("Starting threads\n");
    backup_camera->start_threads();

    while (backup_camera->process_events())
    {
        if (backup_camera->update())
        {
            SDL_RenderPresent(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
        }
    }

    backup_camera->close();
    return 0;
}
