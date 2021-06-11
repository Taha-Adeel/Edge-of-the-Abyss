#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Game{
public:
	Game();

	void run();
	void exitGame();

private:
	void handleEvent();

	sf::RenderWindow m_window;

	bool m_shouldExit = false;

};

#endif