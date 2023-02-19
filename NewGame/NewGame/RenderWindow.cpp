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
    SDL_FreeSurface(loadedSurface);
    return backgroundTexture;
}

void RenderWindow::renderCrosshair(SDL_Texture* p_tex, int x, int y) 
{
    SDL_Rect dst;
    dst.x = x - 50;
    dst.y = y - 50;
    dst.w = 100;
    dst.h = 100;
    SDL_RenderCopy(renderer, p_tex , NULL, &dst);
}

void RenderWindow::Bar_load(const char* p_filepath) {
    load_bar_surface = IMG_Load(p_filepath);
    if (!load_bar_surface) {
        std::cout << "Unable to load Surface. Error: " << SDL_GetError() << std::endl;
    }

    load_bar_tex = NULL;
    load_bar_tex = SDL_CreateTextureFromSurface(renderer, load_bar_surface);
    if (load_bar_tex == NULL) {
        std::cout << "Unable to load background. Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(load_bar_surface);
}
void RenderWindow::Bar_render(int type) {
    int width = load_bar_surface->w;
    int height = load_bar_surface->h;
    int pieceWidth = width;
    int pieceHeight = height / 6;

    SDL_Rect src = { 0, 0, pieceWidth, pieceHeight };
    SDL_Rect dst = { 0, 0, pieceWidth, pieceHeight };

    src.x = 0 * pieceWidth;
    src.y = type * pieceHeight;
    dst.x = 812;
    dst.y = 350;
    dst.w = width / 2;
    dst.h = height / 16;
    SDL_RenderCopy(renderer, load_bar_tex, &src, &dst);

    //SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyTexture(load_bar_tex);
    SDL_DestroyTexture(load_P_P_tex);
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
    destRect.w = 1920;
    destRect.h = 1080;

    SDL_RenderCopy(renderer, backgroundTex, NULL, &destRect);
}

void RenderWindow::P_PLoad(const char* p_filepath)
{
    load_P_P_surface = IMG_Load(p_filepath);
    if (!load_P_P_surface) {
        std::cout << "Unable to load Surface. Error: " << SDL_GetError() << std::endl;
    }

    load_P_P_tex = NULL;
    load_P_P_tex = SDL_CreateTextureFromSurface(renderer, load_P_P_surface);
    if (load_P_P_tex == NULL) {
        std::cout << "Unable to load background. Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(load_P_P_surface);
}
void RenderWindow::P_Prender(int mode)
{
    int width = load_P_P_surface->w;
    int height = load_P_P_surface->h;
    int pieceWidth = width/2;
    int pieceHeight = height;

    SDL_Rect src = { 0, 0, pieceWidth, pieceHeight };
    SDL_Rect dst = { 0, 0, pieceWidth, pieceHeight };

    src.x = mode * pieceWidth;
    src.y = 0 * pieceHeight;
    dst.x = 1650;
    dst.y = 130;
    dst.w = width/15;
    dst.h = height/8;
    SDL_RenderCopy(renderer, load_P_P_tex, &src, &dst);

    SDL_RenderPresent(renderer);
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
    dst.w = p_guy.Get_CurrentFrame().w / 6;
    dst.h = p_guy.Get_CurrentFrame().h / 6;
    SDL_RenderCopy(renderer, p_guy.Get_tex(), &src, &dst);
    }
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}


