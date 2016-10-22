#include "graphics_handler.h"

/*
 *The caller is responsible for SDL_FreeSurface on the *surface passed to this function
 */
void GraphicsHandler::draw(SDL_Surface* surface, SDL_Rect surface_rect, bool vert_flip, bool horiz_flip)
{
    SDL_RendererFlip flip;

    if (vert_flip == true && horiz_flip != true)
    {
        flip = SDL_FLIP_VERTICAL;
    }
    else if (vert_flip != true && horiz_flip == true)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (vert_flip == true && horiz_flip == true)
    {
        printf("ERROR cannot do both flips, google how plz byron\n");
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_RenderCopyEx(renderer_, texture, NULL, &surface_rect, 0, NULL, flip);
    SDL_DestroyTexture(texture);
}

/*
 *The caller is responsible for SDL_FreeSurface on the *surface passed to this function
 */
void GraphicsHandler::draw(SDL_Surface* surface, int x_pos, int y_pos)
{
    SDL_Rect texture_rect;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texture_rect.w, &texture_rect.h);
    texture_rect.x = x_pos;
    texture_rect.y = y_pos;
    SDL_RenderCopy(renderer_, texture, NULL, &texture_rect);
}

GraphicsHandler::GraphicsHandler(SDL_Renderer* renderer)
{
    if (renderer == NULL)
    {
        printf("renderer is NULL\n");
    }

    renderer_ = renderer;
}

