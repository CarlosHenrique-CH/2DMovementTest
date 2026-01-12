#pragma once
#include "raylib.h"
#include "config.h"

class Player{
private:
	// -- Player attributes
	const float width{ 80 }, height{ 120 };
	const int jump_force = 900;
	const int speed = 10;
	const int init_speed = 50;
	const int friction = 50;
	const float min_fric = 2;

public:
	// -- 2D Player model config
	// -- Initial position
	Vector2 pos = { (float)(windowConfig::width / 2 - width * 0.5f) , (float)(windowConfig::height / 2 - height * 0.5f) };
	Vector2 vel{0,0}; // -- Velocity parameters
	Rectangle player = { pos.x , pos.y, width, height }; // -- Player's shape model

	// -- Player Methods
	Vector2 & velocity();
	void move();
	void jump();
	void update();

};
