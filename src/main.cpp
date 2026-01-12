#include "raylib.h"
#include "config.h"
#include "player.h"

int main() {
	InitWindow(windowConfig::width, windowConfig::height, "2D Platformer Movement [test]");
	SetTargetFPS(windowConfig::fps);
	// -- Initializes and configures the target FPS for the window

	Player p; // -- Instantiation of player object for easier access to attributes/methods

	while (!WindowShouldClose()) {
		p.update(); // -- Updates the player's input during every frame

		BeginDrawing();

		ClearBackground(DARKGRAY); // -- Background color

		DrawRectangleRec(p.player, RED); // -- Player

		// -- Debug message display
		if (IsKeyDown(KEY_W)) {
			DrawText(TextFormat("velocity_x: %d", (int)p.velocity().x), 0, 0, 20, RED);
			DrawText(TextFormat("pos_x: %d", (int)p.pos.x), 0, 20, 20, RED);
			DrawText(TextFormat("pos_y: %d", (int)p.pos.y), 0, 40, 20, RED);
		}
		
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
