#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640, 480), "Edge of the Abyss",sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    while(window.isOpen()){
        while(window.pollEvent(ev)){
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(ev.key.code == sf::Keyboard::Escape)
                    window.close();
                break;

            
            }
        }
        window.clear(sf::Color::Blue);
        window.display();
    }

    return 0;
}