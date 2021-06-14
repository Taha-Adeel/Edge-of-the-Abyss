#include "game.h"

Game::Game(): m_window(sf::VideoMode(720, 480), "Edge of the Abyss",
							sf::Style::Titlebar | sf::Style::Close){
	m_window.setFramerateLimit(60);
}

// Runs the main loop
void Game::run(){
	sf::Clock timer;
	auto lastTime = sf::Time::Zero;

	while(m_window.isOpen()){
		auto time = timer.getElapsedTime();
		timer.restart();

		//elapsedTime is used to update our physics properly, so that gameplay is independent of FPS
		auto elapsedTime = time - lastTime;
		lastTime = time;

		handleEvent();

		m_window.clear(sf::Color::Blue);
		//render stuff
        m_window.display();

	}
}

// Handles window events, called every frame
void Game::handleEvent()
{
    sf::Event e;

    while (m_window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
			case sf::Event::KeyPressed:
			if(e.key.code == sf::Keyboard::Escape)
				m_window.close();

            default:
                break;
        }
    }
	if(m_shouldExit)
		m_window.close();
}


void Game::exitGame(){
	m_shouldExit = true;
}