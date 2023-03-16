#include<SDL.h>
#include<SDL_image.h>
#include "Bigguy.hpp"
#include<iostream>


Bigguy::Bigguy(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 980;
	currentFrame.h = 980;
};
float Bigguy::Get_x() {
	return x;
}
float Bigguy::Get_y() {
	return y;
}
SDL_Rect Bigguy::Get_CurrentFrame() {
	return currentFrame;
}
SDL_Texture* Bigguy::Get_tex() {
	return tex;
}
void Bigguy::Change_x(float p_x) {
	x = p_x;
}
void Bigguy::Change_y(float p_y) {
	y = p_y;
}