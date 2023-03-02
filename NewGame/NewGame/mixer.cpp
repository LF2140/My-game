#include <iostream>
#include "mixer.hpp"

RenderMixer::RenderMixer(char * p_mixer)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music* music = Mix_LoadMUS(p_mixer);
    Mix_PlayMusic(music, -1);
}