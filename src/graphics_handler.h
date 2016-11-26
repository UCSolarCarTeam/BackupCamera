#pragma once

#include <SDL.h>


class GraphicsHandler
{

public:
    GraphicsHandler(SDL_Renderer* renderer);
    void draw(SDL_Surface* surface, SDL_Rect location_rect, bool vert_flip, bool horiz_flip );
    void draw(SDL_Surface* surface, int x_pos, int y_pos);
private:
    SDL_Renderer* renderer_;
};
