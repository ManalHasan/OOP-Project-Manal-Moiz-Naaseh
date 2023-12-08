#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Background.hpp"

class PauseScreen
{
    public:
        Background paused; 
    public:
        void Initialize(SDL_Renderer* ren);
        void Render(SDL_Renderer* ren);
};
