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
	
	window.Bar_load("res/gfx/health_bar.png");
	int type = 5;

	float e_x = 0;
	float e_y = 0;
	float delta_speed_x = 0;
	float delta_speed_y = 0;
	Entity Bob(e_x, e_y, BobTex);
	Bob.Entity_run(WIDTH / 2, HEIGHT / 2, 5, &delta_speed_x, &delta_speed_y);
	Bigguy Boss(WIDTH/2-110, HEIGHT/2-100, BossTex);

	bool gameRunning = true;
	bool Bob_survive = true;
	SDL_Event event;

	while (gameRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				e_x = 0;
				e_y = 0;
				Bob_survive = true;
			}
		}
		window.clear();
		window.renderBG(background);
		
		if (Bob_survive)
		{
			if (e_x < WIDTH / 2)
				e_x += delta_speed_x;
			else
				e_x -= delta_speed_x;
			if (e_y < HEIGHT / 2)
				e_y += delta_speed_y;
			else
				e_y -= delta_speed_y;
				Bob.Change_x(e_x);
				Bob.Change_y(e_y);
				window.render(Bob);
			}
		cout <<(int)Bob.Get_x() << " " << WIDTH / 2 << " " << (int)Bob.Get_y() << " " << HEIGHT / 2 << endl;
		if ( ((int)Bob.Get_x() == WIDTH / 2 || abs((int)Bob.Get_x() - WIDTH/2) == 1)  && ((int)Bob.Get_y() == HEIGHT/2)|| abs((int)Bob.Get_y() - HEIGHT/2) == 1) {
			type--;
			//cout << type << endl;
			Bob_survive = false;
			Bob.Change_x(e_x + 5);
			Bob.Change_y(e_y + 5);
		}
		if (type >= 0) {
			window.render1(Boss);
		}
		window.Bar_render(type);
		SDL_Delay(10);
		if (type == 0) {
			break;
		}
		window.display();
		window.gameover("res/gfx/gameover.png");
	}
	window.cleanUp();
	return 0;
}