#ifndef BASESTATE_H
#define BASESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "../Player.h"
class Game;

/**
 * @brief Defines an interface through which Game class interacts with current state.
 * 
 * Implementation of "state" design pattern. The functions handleEvent(), update(), render(), etc
 * can be called based on what state the game is in. In the future, states like Main Menu, Practice mode,
 * Level editor, etc. can be easily added by inheriting from this class.
 * 
 */
class StateBase{
  public:
    StateBase(Game& game): m_pGame(&game){}

    virtual ~StateBase() = default;

    virtual void handleEvent(sf::Event&) = 0;
    virtual void update(sf::Time) = 0;
    virtual void render(sf::RenderTarget& renderer) = 0;

  protected:
    Game* m_pGame;/**<Reference to the game object (context)*/
};

#endif	