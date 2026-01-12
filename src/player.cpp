#include "player.h"
#include <algorithm>
#include <cmath>

// -- Gets the sign of a variable's value
int static sign(float x) {
	if (x < 0) { return -1; }
	else { return 1; }
	return 0;
}

// -- Velocity definition: returns a reference (an alias) of the velocity struct created in player.h, in other words:
//	  the original value in memory of the struct's attributes
Vector2 & Player::velocity(){
	return vel;
}

// -- Move function that gets user input to make the player move
void Player::move() {
	int x{ (IsKeyDown(KEY_D)) - (IsKeyDown(KEY_A))};							// -- Gets the input axis sign
	velocity().x += x * init_speed * GetFrameTime();							// -- multiplies it by the initial speed and the interval between frames (1/60)
	velocity().x = std::clamp(velocity().x, (float)-speed, (float)speed);		// -- clamps the value of velocity().x to a limit
	if (x != 0) {															// -- Detects if user input is received
		pos.x += velocity().x;												// -- updates the player's horizontal position to add its velocity
		if (x != sign(velocity().x)) {										// -- "if the player wants to go to the opposite way, then"
			velocity().x -= sign(velocity().x) * friction * GetFrameTime();	// -- subtracts the velocity by its sign times the friction and GetFrameTime()
		}																	
	}
	else {																	// -- "if user input is not received"
		pos.x += velocity().x;												// -- keeps the player in movement
		if (std::fabs(velocity().x) < min_fric) {							// if the absolute value of velocity is lower than the minimum value of friction, then
			velocity().x = 0;
		}
		else {																// -- "and player is in movement, then"
			velocity().x -= sign(velocity().x) * friction * GetFrameTime();	// -- applies friction
		}
	}
	
}

// -- Jump function
void Player::jump() {
	const float grav = 2000;													// -- Local gravity variable
	bool onGround = pos.y + 1 > windowConfig::height - player.height;		// -- Verifies if there's ground to collide with the player by 1 pixel
	velocity().y += grav * GetFrameTime();									// -- Multiplies the y velocity by the gravity times the frame interval 
																			//	  (smoother and less FPS dependent fall)
	if (onGround) {
		pos.y = windowConfig::height - player.height;						// -- Keeps player on ground

		if (IsKeyDown(KEY_SPACE)) {
			velocity().y = 0;												// -- Zero the y velocity so it doesn't get altered by the previous velocity value
			velocity().y -= jump_force;										// -- Jump
			pos.y += velocity().y * GetFrameTime();							// -- Apply the changes to the y coordinate
		}

	}
	else {
		pos.y += velocity().y * GetFrameTime();								// -- Same thing as line 53
	}
}
// -- Update player input
void Player::update() {
	move();
	jump();
	player.x = pos.x;
	player.y = pos.y;
}
