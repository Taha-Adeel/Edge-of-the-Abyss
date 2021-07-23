#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace CONSTANTS{
	constexpr unsigned int WINDOW_WIDTH = 1280; 
	constexpr unsigned int WINDOW_HEIGHT = 720;
	const std::string WINDOW_TITLE = "Edge of the Abyss";

	constexpr float GAME_SPEED = 1.f;

	const std::vector<std::string> LEVELS{"Level-1", "Level-2", "portaltest", "gamemap", "checkmap"};
	const sf::Color BG_COLOR = sf::Color(121, 25, 255);
	const sf::Vector2f BG_VELOCITY = sf::Vector2f(-30.f * GAME_SPEED, -30.f * GAME_SPEED);
	const sf::Color GROUND_BG_COLOR = sf::Color(65, 0, 156);
	constexpr float GROUNDHEIGHT = 552.f;

	constexpr float GRAVITY = 1244.f * (GAME_SPEED * GAME_SPEED);

	constexpr int DEFAULT_PLAYER_SPRITE_INDEX = 39;
	constexpr float PLAYER_WIDTH = 42.f;
	constexpr float PLAYER_HEIGHT = 42.f;
	constexpr float SPAWNPOINT_X = 0.f;
	constexpr float SPAWNPOINT_Y = GROUNDHEIGHT - PLAYER_HEIGHT/2;

	constexpr float PLAYER_SPEED_X = 260.f * GAME_SPEED;
	constexpr float PLAYER_SPEED_Y = 0.f;
	constexpr float PLAYER_JUMP_BOOST = -470.f * GAME_SPEED;
	constexpr float TERMINAL_SPEED = -PLAYER_JUMP_BOOST * 1.2f; 
	constexpr float PLAYER_ANGULAR_VELOCITY = 230.f * GAME_SPEED;
	

	constexpr float PLANE_WIDTH = 42.f;
	constexpr float PLANE_HEIGHT = 26.f;
	constexpr float PLANE_ACCELARATION = GRAVITY * 0.35;
	constexpr float PLANE_TERMINAL_VELOCITY_Y = 1.2 * PLANE_ACCELARATION;
	
	constexpr int TILE_WIDTH = 42;
	constexpr int TILE_HEIGHT = 42;
	constexpr int TILE_SPACING = 2;

	constexpr int CAMERA_OFFSET_X_LEFT = 300;
	constexpr int CAMERA_OFFSET_Y_TOP = 150;
	constexpr int CAMERA_OFFSET_Y_BOTTOM = 400;
	constexpr int CAMERA_OFFSET_GROUND_Y = 0;

	const std::string SCORE_FILE_PATH = "scores.txt";
	const std::string SCORE_FONT = "Miver";
	const sf::Color SCOREBOARD_COLOR = sf::Color::White;
	constexpr float HIGHSCORE_X = 900.f;
	constexpr float HIGHSCORE_Y = 20.f;
	constexpr float SCOREBOARD_X = HIGHSCORE_X;
	constexpr float SCOREBOARD_Y = HIGHSCORE_Y + 50.f;
}

#endif