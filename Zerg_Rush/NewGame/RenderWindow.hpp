#pragma once
#include<SDL.h>
#include<SDL_image.h>

#include "Entity.hpp"
#include "Bigguy.hpp"

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    SDL_Texture* loadSurface(const char* p_filepath);
    void renderCrosshair(SDL_Texture* p_Tex, int x, int y);
    void RenderSelect(SDL_Texture* SelectTex, int S_type);
    void Bar_load(const char* p_filepath);
    void Bar_render(int type);
    void cleanUp();
    void clear();
    void renderBG(SDL_Texture* background);
    void P_PLoad(const char* p_filepath);
    void P_Prender(int mode);
    void Retryload(const char* p_filepath);
    void renderRetry(int mode);
    void render(Entity& p_entity);
    void render1(Bigguy& p_guy);
    void display();
    SDL_Rect GetRetry();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* load_bar_tex;
    SDL_Surface* load_bar_surface;

    SDL_Texture* load_P_P_tex;
    SDL_Surface* load_P_P_surface;

    SDL_Texture* load_Retry_tex;
    SDL_Surface* load_Retry_surface;

    SDL_Rect Retry;
};