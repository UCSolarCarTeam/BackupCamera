#include "BackupCamera.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

int main(int argc, char* argv[])
{
    if (argc != 7)
    {
        printf("Usage: %s   screen_x_cordinate  screen_y_coordinate  screen_width  screen_height  camera_res_x  camera_res_y\n", argv[0]);
        return 0;
    }

    BackupCamera* backupCamera = new BackupCamera();
    SDL_Renderer* renderer = NULL;

    // passing in an empty SDL_Renderer*. init will handle initializing SDL and if successfull,
    // will pass back a non NULL SDL_Renderer*
    if (!backupCamera->init(&renderer, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])))
    {
        fprintf(stderr, "Could not initialize!\n");
        return -1;
    }

    if (renderer == NULL)
    {
        printf("Renderer is null\n");
    }

    backupCamera->initScreenSettings(0, atoi(argv[5]), atoi(argv[6]));
    backupCamera->initGraphics(renderer);
    printf("Starting threads\n");
    backupCamera->startThreads();

    while (backupCamera->processEvents())
    {
        // update() will only return when a new image has been grabbed
        // and processed from the backup camera
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
