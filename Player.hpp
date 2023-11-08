#pragma once
#include "Object.hpp"

class Player:public Object{
    private:
        double gravity=350;
        double speed=0;
    public:
        void Update();
        void Gravity();
        void Render(SDL_Renderer* ren);
};