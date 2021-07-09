#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "States/PlayingState.h"
#include "Util/NonCopyable.h"
#include "Util/NonMoveable.h"

/**
 * @brief Main game class.
 * 
 *  Main controlling class of the game. Handles the game loop and the elapsed time between each frame.
 *  It is non-copyable and non-movable (and a singleton). 
 */
class Game: public NonCopyable, public NonMovable{
public:
	//public accessors
	static Game& getGameInstance();
	sf::RenderWindow& getWindow();
	
	//public functions
	void run();
	void exitGame();
 // void changeState(std::unique_ptr<StateBase>){};

private:
	//private constructor
	Game();

	//private member variables
	sf::RenderWindow m_window;/**<The window on which everything is rendered*/
	bool m_shouldExit = false;
	std::unique_ptr<StateBase> m_pCurrentState;/**<Base class pointer to the current state*/
	sf::Event m_ev;/**<Stores the events(KeyPress, WindowClose, etc) in it*/

	//private member function
	void handleEvent();
};

#endif