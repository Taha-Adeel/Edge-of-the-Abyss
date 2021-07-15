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
	constexpr float SPAWNPOINT_X = 200.f;
	constexpr float SPAWNPOINT_Y = GROUNDHEIGHT - PLAYER_HEIGHT/2;
	constexpr float PLAYER_SPEED_X = 20.f;
	constexpr float PLAYER_SPEED_Y = 0.f;
	constexpr float PLAYER_JUMP_BOOST = -700.f; //use -1400.f to check for terminal velocity
	//constexpr float NORMAL_TIME_OF_FLIGHT = 0.603f;
	constexpr float PLAYER_ANGULAR_VELOCITY = 298.6f;//298.61f/8;
	constexpr float TERMINAL_SPEED = 720.f;// reaches ground at ~715.f for normal jumps. 

	constexpr int TILE_WIDTH = 42;
	constexpr int TILE_HEIGHT = 42;
	constexpr int TILE_SPACING = 2;
}

#endif