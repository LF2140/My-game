#include<SDL.h>
#include<SDL_image.h>
#include "RenderWindow.hpp"
#include<iostream>
#include "Entity.hpp"
#include "Bigguy.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    return texture;
}

SDL_Texture* RenderWindow::loadSurface(const char* p_filepath) 
{
    SDL_Surface* loadedSurface = IMG_Load(p_filepath);
    if (!loadedSurface) {
        std::cout<<"Unable to load Surface. Error: "<< SDL_GetError() <<std::endl;
    }

    SDL_Texture* backgroundTexture = NULL;
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (backgroundTexture == NULL) {
        std::cout << "Unable to load background. Error: " << SDL_GetError() << std::endl;
    }
    return backgroundTexture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}
void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::renderBG(SDL_Texture* backgroundTex)
{
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 1280;
    destRect.h = 720;

    SDL_RenderCopy(renderer, backgroundTex, NULL, &destRect);
}

void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect src;
    src.x = p_entity.Get_CurrentFrame().x;
    src.y = p_entity.Get_CurrentFrame().y;
    src.w = p_entity.Get_CurrentFrame().w;
    src.h = p_entity.Get_CurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.Get_x();
    dst.y = p_entity.Get_y();
    dst.w = p_entity.Get_CurrentFrame().w / 16 ;
    dst.h = p_entity.Get_CurrentFrame().h / 16 ;

    SDL_RenderCopy(renderer, p_entity.Get_tex(), &src, &dst);
}
void RenderWindow::render1(Bigguy& p_guy){
    SDL_Rect src;
    src.x = p_guy.Get_CurrentFrame().x;
    src.y = p_guy.Get_CurrentFrame().y;
    src.w = p_guy.Get_CurrentFrame().w;
    src.h = p_guy.Get_CurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_guy.Get_x();
    dst.y = p_guy.Get_y();
    dst.w = p_guy.Get_CurrentFrame().w / 4;
    dst.h = p_guy.Get_CurrentFrame().h / 4;

    SDL_RenderCopy(renderer, p_guy.Get_tex(), &src, &dst);
    }
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
