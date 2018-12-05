#include "GraphicsHandler.h"

/*
 *The caller is responsible for SDL_FreeSurface on the *surface passed to this function
 */
void GraphicsHandler::draw(SDL_Surface* surface, SDL_Rect surfaceRect, bool vertFlip, bool horizFlip)
{
    SDL_RendererFlip flip;
    double rotateAngle = 0;

    if (vertFlip == true && horizFlip != true)
    {
        flip = SDL_FLIP_VERTICAL;
    }
    else if (vertFlip != true && horizFlip == true)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (vertFlip == true && horizFlip == true)
    {
        //Rotating 180 degrees is the same as flipping along the horizontal and verical axis.
        flip = SDL_FLIP_NONE;
        rotateAngle = 180;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_RenderCopyEx(renderer_, texture, NULL, &surfaceRect, rotateAngle, NULL, flip);
    SDL_DestroyTexture(texture);
}

/*
 *The caller is responsible for SDL_FreeSurface on the *surface passed to this function
 */
void GraphicsHandler::draw(SDL_Surface* surface, int xPos, int yPos)
{
    SDL_Rect textureRect;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_QueryTexture(texture, NULL, NULL, &textureRect.w, &textureRect.h);
    textureRect.x = xPos;
    textureRect.y = yPos;
    SDL_RenderCopy(renderer_, texture, NULL, &textureRect);
}

GraphicsHandler::GraphicsHandler(SDL_Renderer* renderer)
{
    if (renderer == NULL)
    {
        printf("renderer is NULL\n");
    }

    renderer_ = renderer;
}
