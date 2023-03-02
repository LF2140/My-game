#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class RenderMixer {
public:
	RenderMixer(char *p_mixer);


private:
	Mix_Music* music;
};