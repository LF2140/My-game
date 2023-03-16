#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include <cmath>
#include <algorithm>
class Entity {
public:
	Entity();
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
	float Get_x();
	float Get_y();
	SDL_Rect Get_CurrentFrame();
	SDL_Texture* Get_tex();
	void Change_x(float p_x);
	void Change_y(float p_y);
	void Entity_run(float E_x0, float E_y0,float speed, float* delta_speed_x, float* delta_speed_y);
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};