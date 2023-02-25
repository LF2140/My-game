#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Bigguy.hpp"
#include <vector>
#include <ctime>

using namespace std;

const int WIDTH = 1920, HEIGHT = 1080;

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
	
	SDL_Texture* beginTex = window.loadSurface("res/gfx/play.png");
	SDL_Texture* selectTex = window.loadTexture("res/gfx/select.png");
	SDL_Texture* pause = window.loadTexture("res/gfx/pause.png");
	SDL_Texture* background = window.loadSurface("res/gfx/BG.png");
	SDL_Texture* BobTex = window.loadTexture("res/gfx/Bob.png");
	SDL_Texture* BossTex = window.loadTexture("res/gfx/Boss.png");
	SDL_Texture* BossTex1 = window.loadTexture("res/gfx/Boss1.png");
	SDL_Texture* CrosshairTex = window.loadTexture("res/gfx/crosshair.png");
	SDL_Texture* gameoverTex = window.loadSurface("res/gfx/gameover.png");
	
	int mouse_x, mouse_y, retry_x, retry_y, retry_h;
	int S_type = 3;

	srand(time(0));
	float speed = rand() % 10 + 5;
	float e_x = 0;
	float e_y = 0;
	float delta_speed_x = 0;
	float delta_speed_y = 0;
	Entity Bob(e_x, e_y, BobTex);
	Bob.Entity_run(WIDTH / 2, HEIGHT / 2, 5, &delta_speed_x, &delta_speed_y);
	
	window.Bar_load("res/gfx/health_bar.png");
	window.P_PLoad("res/gfx/P_P.png");
	window.Retryload("res/gfx/retry.png");

	int type = 5;
	int mode = 1;
	int retry_type = 0;
	Bigguy Boss(WIDTH/2 - 70, HEIGHT/2 - 70, BossTex);
	Bigguy Boss1(WIDTH/2 - 70, HEIGHT/2 - 70, BossTex1);
	
	bool gameRunning = true;
	bool Bob_survive = true;
	bool gameover = false;
	bool Boss_turnred = false;
	bool gamePause = false;
	bool gamePlay = false;
	bool retry = false;
	Uint32 mouse_state;
	SDL_Event event;

	while (gameRunning)
	{
			
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
				if (gamePlay && event.button.button == SDL_BUTTON_LEFT && !gamePause && mouse_x >= Bob.Get_x()
					&& mouse_x <= Bob.Get_x() + 1000 / 16 &&
					mouse_y >= Bob.Get_y() && Bob.Get_y() + 1000 / 16)
				{
					cout << "KILL BOB\n";
					Bob_survive = false;
				}

				if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && !gamePause)
				{
					cout << "ESC " << endl;
					mode = 0;
					gamePause = true;
				}

				else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && gamePause)
				{
					cout << "ESC " << endl;
					mode = 1;
					gamePause = false;
				}
				
				if (gameover)
				{
					mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
					retry_x = mouse_x - window.GetRetry().x - window.GetRetry().w/2;
					retry_y = mouse_y - window.GetRetry().y - window.GetRetry().h/2;
					retry_h = window.GetRetry().h/2;
					if (retry_x * retry_x + retry_y * retry_y < retry_h * retry_h)
					{
						retry_type = 1;
						if (event.type == SDL_MOUSEBUTTONDOWN)
						{
							retry = false;
							gameover = false;
							type = 5;
							Boss_turnred = false;
							retry_type = 0;
						}
					}
					else retry_type = 0;
				}

				if (!gamePlay)
				{
					mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
					if (mouse_x >= 600 && mouse_x <= (600 + 730) && mouse_y >= 350 && mouse_y <= (350 + 330))
					{
						S_type = 1;
						if (event.button.button == SDL_BUTTON_LEFT)
						{
							gamePlay = true;
						}
					}
					else if (mouse_x >= 600 && mouse_x <= (600 + 730) && mouse_y >= 610 && mouse_y <= (610 + 330))
					{
						S_type = 2;
						if (event.button.button == SDL_BUTTON_LEFT)
						{
							gameRunning = false;
						}
					}
					else S_type = 3;
					//gamePlay = true;
				}

			}

			if (!gamePlay && !gameover)
			{
					window.clear();
					window.renderBG(beginTex);
					if (S_type != 3)
						window.RenderSelect(selectTex, S_type);
			}
			else if (!gameover && gamePlay && !retry) 
			{

				window.clear();
				window.renderBG(background);
				if (Bob_survive)
				{
					float Bob_x = Bob.Get_x();
					float Bob_y = Bob.Get_y();
					if (!gamePause)
					{
						Bob.Change_x(Bob_x + delta_speed_x);
						Bob.Change_y(Bob_y + delta_speed_y);
					}
					window.render(Bob);
				}
				else 
				{
					if (Boss_turnred) 
					{
						int timered = 300;
						while (timered--)
						{
							window.clear();
							window.renderBG(background);
							window.render1(Boss1);
							window.Bar_render(type);
							//crosshair
							{
								while (SDL_PollEvent(&event))
									mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
								//cout << mouse_x << " " << mouse_y << endl;
								if (!gamePause)
								window.renderCrosshair(CrosshairTex, mouse_x, mouse_y);

							}
							window.P_Prender(mode);
						}
						Boss_turnred = false;
					}
					//spawn another Bob
					{
						srand(time(0));
						speed = rand() %10 + 5;
						float e_x1 = rand() % 4000 ;
						float e_y1 = rand() % 4000;
							//cout << endl <<endl <<e_x1 << " " << e_y1<<endl<<endl;
							Bob.Change_x(e_x1);
							Bob.Change_y(e_y1);
							Bob.Entity_run(WIDTH / 2, HEIGHT / 2, speed, &delta_speed_x, &delta_speed_y);
							Bob_survive = true;
							//cout << "spawn new bob\n";
					}
					
				}
				if (type >= 0)
				{
					window.render1(Boss);
				}

				//cout << (int)Bob.Get_x() << " " << WIDTH / 2 << " " << (int)Bob.Get_y() << " " << HEIGHT / 2 << endl;
				
				if ( ( (int)Bob.Get_x() < 245/2 + (int)Boss.Get_x() ) && ( (int)Bob.Get_x() + 62/2 > (int)Boss.Get_x() )
					&& ( (int)Bob.Get_y() < 245/2 + (int)Boss.Get_y() ) && ( (int)Bob.Get_y() + 62/2 > (int)Boss.Get_y() ) ) 
				{
					type--;
					//cout << type << endl;
					Bob_survive = false; 
					Boss_turnred = true;
				}
				


				window.Bar_render(type);
				//crosshair
				{
					mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
					//cout << mouse_x << " " << mouse_y << endl;
					if (!gamePause)
						window.renderCrosshair(CrosshairTex, mouse_x, mouse_y);

				}
				if (gamePause)
				{
					window.renderBG(pause);
				}
				window.P_Prender(mode);

				SDL_Delay(5);

				if (type < 0)
				{
					gameover = true;
					retry = true;
				}


			}
			else if ( gameover) {
				window.clear();
				window.renderBG(gameoverTex);
				window.renderRetry(retry_type);
				cout << window.GetRetry().x << " " << window.GetRetry().y << " " << window.GetRetry().w << " " << window.GetRetry().h << endl;
				cout << mouse_x << " " << mouse_y << endl;
			}
			window.display();
	}	
		SDL_DestroyTexture(CrosshairTex);
		window.cleanUp();
	return 0;
}