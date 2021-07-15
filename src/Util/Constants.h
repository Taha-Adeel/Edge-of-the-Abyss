#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace CONSTANTS{
	constexpr unsigned int WINDOW_WIDTH = 1280; 
	constexpr unsigned int WINDOW_HEIGHT = 720;
	const std::string WINDOW_TITLE = "Edge of the Abyss";

	constexpr float GROUNDHEIGHT = 571.f;

	constexpr float GRAVITY = 2500.f;

	constexpr float PLAYER_WIDTH = 42.f;
	constexpr float PLAYER_HEIGHT = 42.f;
	constexpr float SPAWNPOINT_X = 0.f;
	constexpr float SPAWNPOINT_Y = GROUNDHEIGHT - PLAYER_HEIGHT/2;

	constexpr float PLAYER_SPEED_X = 100.f;
	constexpr float PLAYER_SPEED_Y = 0.f;
	constexpr float PLAYER_JUMP_BOOST = -700.f;
	constexpr float TERMINAL_SPEED = 750.f; 
	constexpr float PLAYER_ANGULAR_VELOCITY = 290.f;
	
	constexpr int TILE_WIDTH = 42;
	constexpr int TILE_HEIGHT = 42;
	constexpr int TILE_SPACING = 2;

    constexpr int CAMERA_OFFSET_X_LEFT = 300;
    constexpr int CAMERA_OFFSET_Y_TOP = 300;
    constexpr int CAMERA_OFFSET_Y_BOTTOM = 400;
    constexpr int CAMERA_OFFSET_GROUND_Y = 0;
}

#endif