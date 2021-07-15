#include "Game.h"
#include "Util/Constants.h"
#include <iostream>


/**
 * @brief Construct a new Game object once when called through getGameInstance()
 * 
 * Creates an sf::RenderWindow and sets max framerate to 60, and sets m_pCurrentState to
 * PlayingState.
 */
Game::Game(): m_window(sf::VideoMode(CONSTANTS::WINDOW_WIDTH, CONSTANTS::WINDOW_HEIGHT),
							CONSTANTS::WINDOW_TITLE,
							sf::Style::Titlebar | sf::Style::Close),
							m_pCurrentState(std::make_unique<PlayingState>(*this)){
	m_window.setFramerateLimit(60);
}


/**
 * @brief Returns a reference to the Game object.
 * 
 * Creates a new Game object first time it is called, and returns that 
 * instance whenever it is called again.
 * 
 * @return Game& 
 */
Game& Game::getGameInstance(){
	static Game instance;

	return instance;
}


/**
 * @brief Runs the main loop.
 * 
 * Runs a continuous while loop which runs while the game is open. Also keeps track of FPS.
 * 
 */
void Game::run(){
	sf::Clock timer;
	sf::Time elapsedTime;
	while(m_window.isOpen()){
		// sf::Clock::restart() returns the elapsed time since it was started, i.e elapsedTime holds
		// the frame time of the last frame.
		// elapsedTime is used to update our physics properly, so that gameplay is independent of FPS
		elapsedTime = timer.restart();

		m_pCurrentState->update(elapsedTime);
		
		m_window.clear(sf::Color(121, 25, 255));
		m_pCurrentState->render(m_window);
        m_window.display();

		handleEvent();
		// std::cout << "FPS: " << 1/elapsedTime.asSeconds() << '\n';
	}
}


/**
 * @brief Handles window events, called every frame
 * 
 * Checks for window close events, and then delegates work to m_currentState.
 * 
 */
void Game::handleEvent()
{
     while (m_window.pollEvent(m_ev)) {
        switch (m_ev.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
			case sf::Event::KeyPressed:
				if(m_ev.key.code == sf::Keyboard::Escape)
					m_window.close();

            default:
				m_pCurrentState->handleEvent(m_ev);
                break;
        }
    }
	if(m_shouldExit)
		m_window.close();
}


/**
 * @brief Returns a reference to the game window
 * 
 * @return sf::RenderWindow& 
 */
sf::RenderWindow& Game::getWindow(){
	return m_window;
}


/**
 * @brief Can be used from inside the code to exit the game * 
 */
void Game::exitGame(){
	m_shouldExit = true;
}