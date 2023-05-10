#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Bigguy.hpp"
#include <SDL_mixer.h>
#include <ctime>
#include <vector>

using namespace std;


bool gameRunning = true;
bool Bob_survive = false;
bool gameover = false;
bool Boss_turnred = false;
bool gamePause = false;
bool gamePlay = false;
bool retry = false;
bool Bob_deadth_sound = false;
bool can_inc_score = true;
bool can_dec_score = false;
int type = 5;
int score = 0;
int bonus_speed = 0;
int Boss_health = 50;
int timered = 300;
int high_score = 0;
int retry_delay = 0;
int angle = 0;
int Bob_change_delay = 8;
int Bob_change_delay_const = 8;
bool Reverse_bob = false;
int which_bob = 0;

const int WIDTH = 1920, HEIGHT = 1080;
int S_type = 3;

int playMusic(void* arg);
bool playmus = true;
bool playmus1 = false;

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO) > 0)
	{
		cout << "SDL_INIT has failed. Error: " << SDL_GetError() << endl;
	}
	if (!(IMG_Init(IMG_INIT_PNG)))
	{
		cout << "IMG_Init has failed. Error: " << SDL_GetError() << endl;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Failed to initialize SDL_mixer: " << Mix_GetError() << endl;
	}
	if (TTF_Init() < 0) {
		cout << "Failed to initialize SDL_ttf: " << Mix_GetError() << endl;
	}
	SDL_Thread* thread = SDL_CreateThread(playMusic, "PlayMusicThread", NULL);
	RenderWindow window("Project A", WIDTH, HEIGHT);

	SDL_Texture* beginTex = window.loadSurface("res/gfx/play.png");
	SDL_Texture* selectTex = window.loadTexture("res/gfx/select.png");
	SDL_Texture* pause = window.loadTexture("res/gfx/pause.png");
	SDL_Texture* background = window.loadSurface("res/gfx/BG.png");
	SDL_Texture* BobTex = window.loadTexture("res/gfx/Bob.png");
	SDL_Texture* BobTex1 = window.loadTexture("res/gfx/Bob1.png");
	SDL_Texture* BossTex = window.loadTexture("res/gfx/Boss.png");
	SDL_Texture* BossTex1 = window.loadTexture("res/gfx/Boss1.png");
	SDL_Texture* CrosshairTex = window.loadTexture("res/gfx/crosshair.png");
	SDL_Texture* gameoverTex = window.loadSurface("res/gfx/gameover.png");
	
	Mix_Chunk* damage_sound = Mix_LoadWAV("res/sound/damage.mp3");
	Mix_Chunk* bob_death_sound = Mix_LoadWAV("res/sound/bobdeath.mp3");

	//play-pause 
	vector<SDL_Texture*> P_P_tex;
	P_P_tex.push_back( window.loadTexture("res/gfx/P1.png") );
	P_P_tex.push_back( window.loadTexture("res/gfx/P2.png") );
	//Health bar
	vector <SDL_Texture*> Health_tex;
	Health_tex.push_back( window.loadTexture("res/gfx/Health_bar_1.png") );
	Health_tex.push_back( window.loadTexture("res/gfx/Health_bar_2.png") );
	Health_tex.push_back( window.loadTexture("res/gfx/Health_bar_3.png") );
	Health_tex.push_back( window.loadTexture("res/gfx/Health_bar_4.png") );
	Health_tex.push_back( window.loadTexture("res/gfx/Health_bar_5.png") );
	Health_tex.push_back( window.loadTexture("res/gfx/Health_bar_6.png") );
	//retry button
	vector <SDL_Texture*> Retry_tex;
	Retry_tex.push_back( window.loadTexture("res/gfx/retry1.png") );
	Retry_tex.push_back( window.loadTexture("res/gfx/retry2.png") );
	//mouse pos
	int mouse_x, mouse_y, retry_x, retry_y, retry_h;
	//spawn the 1st bob
	srand(time(NULL));
	float speed = 0;
	float e_x = 0;
	float e_y = 0;
	float delta_speed_x = 0;
	float delta_speed_y = 0;

	vector<Entity> Bob_Final;
	Entity Bob(e_x, e_y, BobTex);
	Bob_Final.push_back(Bob);
	Entity Bob1(e_x, e_y, BobTex1);
	Bob_Final.push_back(Bob1);
	Bob_Final[which_bob].Entity_run(WIDTH / 2, HEIGHT / 2, 5, &delta_speed_x, &delta_speed_y);

	window.ScoreLoad("res/font/lucon.ttf");

	int mode = 1;
	int retry_type = 0;
	int check = 1;
	Bigguy Boss(WIDTH/2 - 70, HEIGHT/2 - 70, BossTex);
	Bigguy Boss1(WIDTH/2 - 70, HEIGHT/2 - 70, BossTex1);
	

	Uint32 mouse_state;
	SDL_Event event;

	while (gameRunning)
	{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					gameRunning = false;
				if (gamePlay && event.button.button == SDL_BUTTON_LEFT && !gamePause && mouse_x >= Bob_Final[which_bob].Get_x()
					&& mouse_x <= Bob_Final[which_bob].Get_x() + 1000 / 16 &&
					mouse_y >= Bob_Final[which_bob].Get_y() && Bob_Final[which_bob].Get_y() + 1000 / 16)
				{
					//cout << "KILL BOB\n"
					if (!Boss_turnred)
						Mix_PlayChannel(1, bob_death_sound, 0);
					Bob_survive = false;
					if (Reverse_bob)
					{
						type--;
						if (can_dec_score && score>0)
						{
							score -= 50;
							can_dec_score = false;
						}
					}
					else if (can_inc_score && !Boss_turnred)
					{
						score += 50;
						can_inc_score = false;
					}
					switch (score)
					{
					case 100:
					{
						bonus_speed = 1;
						break;
					}
					case 300:
					{
						bonus_speed = 2;
						break;
					}
					case 750:
					{
						bonus_speed = 3;
						break;
					}
					case 1000:
					{
						bonus_speed = 4;
						break;
					}
					case 5000:
					{
						bonus_speed = 5;
						break;
					}
					}
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
							if (event.type == SDL_MOUSEBUTTONDOWN && retry_delay == 0 )
							{
								retry = false;
								gameover = false;
								type = 5;
								Boss_turnred = false;
								retry_type = 0;
								score = 0;
							}
						}
						else retry_type = 0;
					if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						gameover = false;
						gamePlay = false;
						playmus = true;
						playmus1 = false;
						score = 0;
					}
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
							playmus = false;
							continue;
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
					window.renderBG(beginTex);
					if (S_type != 3) {
						window.RenderSelect(selectTex, S_type);
					}
			}
			else if (!gameover && gamePlay && !retry) 
			{
				if (check)
				{
					window.renderBG(beginTex);
					SDL_Delay(2000);
					check--;

				}
				window.clear();
				window.renderBG(background);
				if (Bob_survive)
				{
					//cout << which_bob << endl;
					float Bob_x = Bob_Final[which_bob].Get_x();
					float Bob_y = Bob_Final[which_bob].Get_y();
					if (!gamePause)
					{
						if(Bob_change_delay==0)
						{
							Bob_Final[which_bob].Change_x(Bob_x + delta_speed_x);
							Bob_Final[which_bob].Change_y(Bob_y + delta_speed_y);
							angle += 5;
							if (angle == 360)
							{
								angle = 0;
							}
							Bob_change_delay = Bob_change_delay_const - bonus_speed;
						}
						Bob_change_delay--;
					}
					if (!Reverse_bob)
						window.render(Bob_Final[which_bob], angle);
					else window.render(Bob_Final[which_bob], angle);
				}
				else 
				{
					if (Boss_turnred) 
					{
						Mix_PlayChannel(2, damage_sound, 0);
						timered = 300;
						window.clear();
						while (timered--)
						{
							window.renderBG(background);
							window.render1(Boss1);
							window.Bar_render(Health_tex[type]);
							//crosshair
							{
								while (SDL_PollEvent(&event))
									mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
								//cout << mouse_x << " " << mouse_y << endl;
								if (!gamePause)
								window.renderCrosshair(CrosshairTex, mouse_x, mouse_y);

							}
							window.P_Prender(P_P_tex[mode]);
							window.ScoreRender(score,1);
							window.display();
						}
						Boss_turnred = false;
					}
					//spawn another Bob
					{
						speed = 5;
						float e_x1 = rand() % 4000-200;
						float e_y1 = rand() % 4000-200;
						int to_rev = rand() % 8+1;
						if (to_rev == 3)
						{
							Reverse_bob = true;
							which_bob = 1;
						}
						else
						{
							Reverse_bob = false;
							which_bob = 0;
						}
							
							//cout << endl <<endl <<e_x1 << " " << e_y1<<endl<<endl;
						if ((e_x1-WIDTH/2)*(e_x1-WIDTH/2) + (e_y1-HEIGHT/2)*(e_y1-HEIGHT/2)>=500*500)
						{
							Bob_Final[which_bob].Change_x(e_x1);
							Bob_Final[which_bob].Change_y(e_y1);
							Bob_Final[which_bob].Entity_run(WIDTH / 2, HEIGHT / 2, speed, &delta_speed_x, &delta_speed_y);
							Bob_survive = true;
							Bob_deadth_sound = false;
						}
						if (!Reverse_bob)
							can_inc_score = true;
						else
							can_dec_score = true;
							//cout << "spawn new bob\n";
					}
					
				}
				if (type >= 0)
				{
					window.render1(Boss);
				}

				//cout << (int)Bob.Get_x() << " " << WIDTH / 2 << " " << (int)Bob.Get_y() << " " << HEIGHT / 2 << endl;
				window.Bar_render(Health_tex[type]);
				
				if ( ( (int)Bob_Final[which_bob].Get_x() < 245/2 + (int)Boss.Get_x() ) && ( (int)Bob_Final[which_bob].Get_x() + 62/2 > (int)Boss.Get_x() )
					&& ( (int)Bob_Final[which_bob].Get_y() < 245/2 + (int)Boss.Get_y() ) && ( (int)Bob_Final[which_bob].Get_y() + 62/2 > (int)Boss.Get_y() ) )
				{
					if (!Reverse_bob)
					{
						type--;
						Boss_turnred = true;
					}
					//cout << type << endl;
					Bob_survive = false; 
					Bob.Change_x(-1000);
					Bob.Change_y(-1000);
				}
				


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
				window.P_Prender(P_P_tex[mode]);
				window.ScoreRender(score, 1);
				//SDL_Delay(8);
				window.display();
				if (type < 0)
				{
					gameover = true;
					retry = true;
					bonus_speed = 0;
					retry_delay = 2200;
					playmus1 = true;
					check = 1;
				}
			}
			else if ( gameover) {
				window.clear();
				window.renderBG(gameoverTex);
				if (score > high_score)
				{
					high_score = score;
				}
				window.ScoreRender(high_score, 2);
				if (retry_delay == 0)
				{
					window.renderRetry(Retry_tex[retry_type]);
				}
				else
					retry_delay--;
				//cout << window.GetRetry().x << " " << window.GetRetry().y << " " << window.GetRetry().w << " " << window.GetRetry().h << endl;
				//cout << mouse_x << " " << mouse_y << endl;
			}

			window.display();
	}	
		Mix_FreeChunk(bob_death_sound);
		Mix_FreeChunk(damage_sound);
		SDL_DestroyTexture(CrosshairTex);
		SDL_WaitThread(thread, NULL);
		Mix_CloseAudio();
		window.cleanUp();
	return 0;
}

int playMusic(void* arg)
{
	Mix_Chunk* music = Mix_LoadWAV("res/sound/gamePlay.mp3");
	Mix_Chunk* select = Mix_LoadWAV("res/sound/select.mp3");
	Mix_Chunk* over = Mix_LoadWAV("res/sound/gameover.mp3");
	Mix_Chunk* background_music = Mix_LoadWAV("res/sound/background_music.mp3");
	while(gameRunning)
	{
		if (!gamePlay)
		{
			Mix_PlayChannel(0, music, 0);

			while (Mix_Playing(0))
			{
				if (!playmus || !gameRunning)
				{
					Mix_HaltChannel(0);
					break;
				}
			}
			if (S_type == 1)
				Mix_PlayChannel(1, select, 0);
		}
		else if (gameover)
		{
			Mix_PlayChannel(0, over, 0);

			while (Mix_Playing(0))
			{
				if (!retry || !playmus1)
				{
					Mix_HaltChannel(0);
					break;
				}
			}
			if (!retry)
				Mix_PlayChannel(1, select, 0);
		}
		else if (!gameover && gamePlay && !retry)
		{	
			Mix_PlayChannel(0, background_music, 0);
			while (Mix_Playing(0))
			{
				if (type<0)
				{
					Mix_HaltChannel(0);
					break;
				}
				if (gamePause)
				{
					Mix_Pause(0);
				}
				else
				{
					Mix_Resume(0);
				}
			}
		}
	}
	
	Mix_FreeChunk(background_music);
	return 0;
}