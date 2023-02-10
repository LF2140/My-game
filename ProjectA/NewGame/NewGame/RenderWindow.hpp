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
    void cleanUp();
    void clear();
    void renderBG(SDL_Texture* background);
    void render(Entity& p_entity);
    void render1(Bigguy& p_guy);
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};