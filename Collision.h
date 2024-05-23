#pragma once
#include <SDL.h>

class Collision
{
public: 
	//acess and allign boundry box
	static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};