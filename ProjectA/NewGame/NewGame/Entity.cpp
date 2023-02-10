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