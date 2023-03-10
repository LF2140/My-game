#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "RenderWindow.hpp"
#include<iostream>
#include<string>
#include "Entity.hpp"
#include "Bigguy.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL), font(NULL)
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
    //SDL_RenderPresent(renderer);
}
void RenderWindow::RenderSelect(SDL_Texture* SelectTex, int S_type)
{
    SDL_Rect dst;
    dst.x = 600;
    if (S_type == 1)
    {
        dst.y = 350;
    }
    else if (S_type == 2)
    {
        dst.y = 610;
    }
    dst.w = 730;
    dst.h = 330;
    SDL_RenderCopy(renderer, SelectTex, NULL, &dst);
}

void RenderWindow::P_Prender(SDL_Texture* p_tex)
{;
    SDL_Rect dst;
    dst.x = 1650;
    dst.y = 130;
    dst.w = 428/7;
    dst.h = 438/7;
    SDL_RenderCopy(renderer, p_tex, NULL, &dst);

    //SDL_RenderPresent(renderer);
}

void RenderWindow::renderRetry(SDL_Texture* p_tex)
{
    SDL_Rect dst;
    dst.x = 1920/2-97;
    dst.y = 1080/2-79;
    dst.w = 195;
    dst.h = 187;
    Retry.x = dst.x;
    Retry.y = dst.y;
    Retry.w = dst.w;
    Retry.h = dst.h;
    SDL_RenderCopy(renderer, p_tex, NULL, &dst);

    SDL_RenderPresent(renderer);
}

void RenderWindow::Bar_render(SDL_Texture* p_tex)
{
    SDL_Rect dst;
    dst.x = 650;
    dst.y = 120;
    dst.w = 629 - 12 ;
    dst.h = 148/2 - 12 ;
    SDL_RenderCopy(renderer, p_tex, NULL, &dst);

    //SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
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


void RenderWindow::ScoreLoad(const char* p_tffpath)
{
    font = TTF_OpenFont(p_tffpath, 25);
    if (font == NULL)
    {
        std::cout << "can load font error: " << SDL_GetError() << std::endl;
    }
}
void RenderWindow::ScoreRender(int score, int mode)
{
    SDL_Surface* scoreSurface = NULL;
    SDL_Texture* scoreTexture = NULL;
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Rect scoreRect;
    if (mode == 1)
    {
        std::string scoreStr = "Score: " + std::to_string(score);
        scoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
        scoreRect = { 200, 130, scoreSurface->w, scoreSurface->h };
    }
    else
    {
        std::string scoreStr = "High Score: " + std::to_string(score);
        scoreSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
        scoreRect = { 200, 130, scoreSurface->w, scoreSurface->h };
    }
    scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_DestroyTexture(scoreTexture);
    SDL_FreeSurface(scoreSurface);
    //SDL_RenderPresent(renderer);
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
    dst.w = p_guy.Get_CurrentFrame().w / 8;
    dst.h = p_guy.Get_CurrentFrame().h / 8;
    SDL_RenderCopy(renderer, p_guy.Get_tex(), &src, &dst);
    }
void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
SDL_Rect RenderWindow::GetRetry()
{
    return Retry;
}


