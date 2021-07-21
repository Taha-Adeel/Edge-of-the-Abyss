#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace CONSTANTS{
	constexpr unsigned int WINDOW_WIDTH = 1280; 
	constexpr unsigned int WINDOW_HEIGHT = 720;
	const std::string WINDOW_TITLE = "Edge of the Abyss";

	const sf::Color BG_COLOR = sf::Color(121, 25, 255);
	const sf::Vector2f BG_VELOCITY = sf::Vector2f(-30.f, -30.f);
	const sf::Color GROUND_BG_COLOR = sf::Color(65, 0, 156);
	constexpr float GROUNDHEIGHT = 571.f;

	constexpr float GRAVITY = 2500.f;

	constexpr int DEFAULT_PLAYER_SPRITE_INDEX = 29;
	constexpr float PLAYER_WIDTH = 42.f;
	constexpr float PLAYER_HEIGHT = 42.f;
	constexpr float SPAWNPOINT_X = 0.f;
	constexpr float SPAWNPOINT_Y = GROUNDHEIGHT - PLAYER_HEIGHT/2;

	constexpr float PLAYER_SPEED_X = 250.f;
	constexpr float PLAYER_SPEED_Y = 0.f;
	constexpr float PLAYER_JUMP_BOOST = -750.f;
	constexpr float TERMINAL_SPEED = 750.f; 
	constexpr float PLAYER_ANGULAR_VELOCITY = 290.f;
	

	constexpr float PLANE_WIDTH = 42.f;
	constexpr float PLANE_HEIGHT = 26.f;
	constexpr float PLANE_SPAWN_POINT_X  = 0.f ;
	constexpr float PLANE_SPAWN_POINT_Y  = SPAWNPOINT_Y - 200.f;
	constexpr float PLANE_SPEED_X = PLAYER_SPEED_X ;//500.f;
	constexpr float PLANE_SPEED_Y = 50.f;
	constexpr float PLANE_MAX_HEIGHT = 0.f ;
	constexpr float PLANE_MIN_HEIGHT = SPAWNPOINT_Y - 20.f ;
    constexpr float PLANE_ACCELARATION = 600.f;
	constexpr float PLANE_TERMINAL_VELOCITY_Y = 300.f;
	
	constexpr int TILE_WIDTH = 42;
	constexpr int TILE_HEIGHT = 42;
	constexpr int TILE_SPACING = 2;

    constexpr int CAMERA_OFFSET_X_LEFT = 300;
    constexpr int CAMERA_OFFSET_Y_TOP = 150;
    constexpr int CAMERA_OFFSET_Y_BOTTOM = 400;
    constexpr int CAMERA_OFFSET_GROUND_Y = 0;
}

#endif