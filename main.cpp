#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(640, 480), "Edge of the Abyss",sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;
    sf::CircleShape shape1(100.f);
    int colchanged=0;
    shape1.setFillColor(sf::Color::Green);
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
                else if(ev.key.code == sf::Keyboard::Enter)
                    {colchanged++;}
                break;

            
            }
        }
        // update
        if(colchanged%2)
            shape1.setFillColor(sf::Color::Blue);
        else  shape1.setFillColor(sf::Color::Green);
        // render
        window.clear(sf::Color::Blue);
        window.draw(shape1);
        window.display();
    }

    return 0;
}