

#ifndef MAINNAMESPACE
#define MAINNAMESPACE

#include "backup_camera.h"

namespace mainVariables
{
    char const QUIT_EVENT_FLAG = 'A';
    char const ENTER_FULLSCREEN_EVENT_FLAG = 'B';
    char const EXIT_FULLSCREEN_EVENT_FLAG = 'C';
    SDL_Window* window_ = NULL;
    BackupCamera* backupCamera_ = NULL;
    bool quitSignal_ = false;

}



#endif
