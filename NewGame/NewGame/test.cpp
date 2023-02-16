#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Crosshair Example",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

    SDL_Surface* crosshair_surface = IMG_Load("res/gfx/crosshair.png");
    SDL_Texture* crosshair_texture = SDL_CreateTextureFromSurface(renderer,
        crosshair_surface);
    SDL_FreeSurface(crosshair_surface);

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        int mouse_x, mouse_y;
        Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

        SDL_Rect dst;
        dst.x = mouse_x - 16;
        dst.y = mouse_y - 16;
        dst.w = 32;
        dst.h = 32;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, crosshair_texture, nullptr,&dst);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(crosshair_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}