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
	SDL_Texture* gameoverTex = window.loadSurface("res/gfx/gameover.png");
	window.Bar_load("res/gfx/health_bar.png");
	int type = 5;

	float e_x = 0;
	float e_y = 0;
	float save_e_x = e_x;
	float save_e_y = e_y;
	float delta_speed_x = 0;
	float delta_speed_y = 0;
	Entity Bob(e_x, e_y, BobTex);
	Bob.Entity_run(WIDTH / 2, HEIGHT / 2, 5, &delta_speed_x, &delta_speed_y);
	Bigguy Boss(WIDTH/2-110, HEIGHT/2-100, BossTex);

	bool gameRunning = true;
	bool Bob_survive = true;
	bool gameover = false;
	SDL_Event event;

	while (gameRunning)
	{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					e_x = save_e_x;
					e_y = save_e_y;
					Bob_survive = true;
				}
				if (gameover && event.type == SDL_MOUSEBUTTONDOWN) {
					gameRunning = false;
				}
			}
			if (!gameover) 
			{

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
				cout << (int)Bob.Get_x() << " " << WIDTH / 2 << " " << (int)Bob.Get_y() << " " << HEIGHT / 2 << endl;
				if ( ( (int)Bob.Get_x() < 245/2 + (int)Boss.Get_x() ) && ( (int)Bob.Get_x() + 62/2 > (int)Boss.Get_x() )
					&& ( (int)Bob.Get_y() < 245/2 + (int)Boss.Get_y() ) && ( (int)Bob.Get_y() + 62/2 > (int)Boss.Get_y() ) ) 
				{
					type--;
					//cout << type << endl;
					Bob_survive = false; 
					Bob.Change_x(e_x + 500);
					Bob.Change_y(e_y + 500);
				}
				if (type >= 0)
				{
					window.render1(Boss);
				}
				window.Bar_render(type);
				SDL_Delay(5);
				if (type < 0)
				{
					gameover = true;
				}
			}
			else {
				window.renderBG(gameoverTex);
			}
			window.display();
	}	
		window.cleanUp();
	return 0;
}