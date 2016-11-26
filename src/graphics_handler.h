#pragma once

#include <SDL.h>

class GraphicsHandler
{

public:
    GraphicsHandler(SDL_Renderer* renderer);
    void draw(SDL_Surface* surface, SDL_Rect locationRect, bool vertFlip, bool horizFlip );
    void draw(SDL_Surface* surface, int xPos, int yPos);
private:
    SDL_Renderer* renderer_;
};
