#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Bigguy.hpp"

using namespace std;

const int WIDTH = 1280, HEIGHT = 720;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		cout << "SDL_INIT has failed. Error: " << SDL_GetError() << endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		cout << "IMG_Init has failed. Error: " << SDL_GetError() << endl;
	}

	RenderWindow window("Project A", WIDTH, HEIGHT);
	
	SDL_Texture* background = window.loadSurface("res/gfx/images.png");
	SDL_Texture* BobTex = window.loadTexture("res/gfx/Bob.png");
	SDL_Texture* BossTex = window.loadTexture("res/gfx/Boss.png");
	

	float e_x = 100;
	float e_y = 200;

	Entity Bob(e_x, e_y, BobTex);
	Bigguy Boss(WIDTH/2-110, HEIGHT/2-100, BossTex);

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		
		Bob.Change_x(e_x);
		Bob.Change_y(e_y);
		window.clear();
		window.renderBG(background);
		window.render(Bob);
		window.render1(Boss);
		//SDL_Delay(2);
		window.display();
	}
	window.cleanUp();
	return 0;
}