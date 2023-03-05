#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include "Entity.hpp"
#include "Bigguy.hpp"

class RenderWindow {
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    SDL_Texture* loadSurface(const char* p_filepath);
    void renderCrosshair(SDL_Texture* p_Tex, int x, int y);
    void RenderSelect(SDL_Texture* SelectTex, int S_type);
    void P_Prender(SDL_Texture* p_tex);
    void renderRetry(SDL_Texture* p_tex);
    void Bar_render(SDL_Texture* p_tex);
    void cleanUp();
    void clear();
    void renderBG(SDL_Texture* background);
    void ScoreLoad(const char* p_tffpath);
    void ScoreRender(int score);
    void render(Entity& p_entity);
    void render1(Bigguy& p_guy);
    void display();
    SDL_Rect GetRetry();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Rect Retry;

    TTF_Font* font;
};