#include<SDL.h>
#include<SDL_image.h>
#include "Entity.hpp"
#include<iostream>


Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 1000;
	currentFrame.h = 1000;
};
float Entity::Get_x() {
	return x;
}
float Entity::Get_y() {
	return y;
}
SDL_Rect Entity::Get_CurrentFrame() {
	return currentFrame;
}
SDL_Texture* Entity::Get_tex() {
	return tex;
}
void Entity::Change_x(float p_x) {
	x = p_x;
}
void Entity::Change_y(float p_y) {
	y = p_y;
}
void Entity::Entity_run(float E_x0, float E_y0, float speed, float* delta_speed_x, float* delta_speed_y) 
{
	float delta_x = E_x0 - x;
	float delta_y = E_y0 - y;
	float delta_pos = sqrt(delta_x * delta_x + delta_y * delta_y);
	float delta_time = delta_pos / speed;
	*delta_speed_x = (delta_x) / delta_time;	
	*delta_speed_y = (delta_y) / delta_time;
}