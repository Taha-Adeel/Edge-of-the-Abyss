#ifndef _SCORE_H
#define _SCORE_H
#include <string>
#include<fstream>
#include<iostream>
#include "../Levels/Level.h"
#include "../Camera.h"
#include "Constants.h"
class ScoreKeeper
{
    Level* referenceLevel;
    Camera* referenceCamera;
    std::fstream fio;
    float currentScore;
    float highScore;
    sf::Font font;
    sf::Text currentScoreText;
    sf::Text highScoreText;
    
public:
    ScoreKeeper(Level& level, Camera& camera):referenceLevel(&level), referenceCamera(&camera)
    {   
        fio.open(CONSTANTS::SCORE_FILE_PATH.c_str(), std::ios::in | std::ios::out);
        //if(!fio)throw std::runtime_error("Could not open scores file");
        //if(!(fio>>highScore))highScore = 0.f;
        if (fio.fail()) //check for file open failure
        {
            std::runtime_error("Could not open score file");
        }
        if (fio.peek() == std::ifstream::traits_type::eof() )
        {
            // Empty File
            std::cout<<"Creating score file"<<std::endl;
            highScore = 0.f;
        } 
        else fio>>highScore;
        
         if (!font.loadFromFile(CONSTANTS::FONT_FILE_PATH))
        {
            std::cout<<"Font Loading Failed \n";
        }
        currentScore=0.f;


        currentScoreText.setFont(font);
        currentScoreText.setString(std::to_string(currentScore));
        currentScoreText.setPosition(referenceCamera->getPosition().x + CONSTANTS::SCOREBOARD_X, referenceCamera->getPosition().y + CONSTANTS::SCOREBOARD_Y);
        currentScoreText.setCharacterSize(15);
        currentScoreText.setStyle(sf::Text::Bold);
        currentScoreText.setFillColor(sf::Color::Yellow);

        highScoreText.setFont(font);
        highScoreText.setString(std::to_string(highScore));
        highScoreText.setPosition(referenceCamera->getPosition().x + CONSTANTS::HIGHSCORE_X, referenceCamera->getPosition().y + CONSTANTS::HIGHSCORE_Y);
        highScoreText.setCharacterSize(15);
        highScoreText.setStyle(sf::Text::Bold);
        highScoreText.setFillColor(sf::Color::Yellow);

    }
    ~ScoreKeeper(){if(fio.is_open())fio.close();}
    const float getCurrentScore() const{return currentScore;}
    const float getHighScore() const{return highScore;}
    //const std::string getLevelName() const{return referenceLevel->getMapName();}

    void updateHighScore()
    {
        if(currentScore >= highScore)
        {
            fio.close();
            //remove(CONSTANTS::SCORE_FILE_PATH.c_str());
            remove(CONSTANTS::SCORE_FILE_PATH.c_str());
            fio.open(CONSTANTS::SCORE_FILE_PATH.c_str(), std::ios::out);
            fio<<currentScore;
            fio.close();
            highScore = currentScore;
        }
        std::cout<<"Game over. Score: "<<currentScore<<" , High Score: "<<highScore<<std::endl;
    }
    void updateTextBoxes(float dt)
    {
        currentScoreText.move(referenceCamera->getVelocity().x * dt, referenceCamera->getVelocity().y * dt);
        currentScoreText.setString(std::to_string(currentScore));
        highScoreText.setString(std::to_string(highScore));
        std::cout<<currentScore<<"::"<<highScore<<std::endl;
    }
    void update(sf::Time elapsedTime)
    {
        float dt = elapsedTime.asSeconds();
        currentScore += dt;
        if(currentScore > highScore)highScore = currentScore;
        this->updateTextBoxes(dt);
    }
    void render(sf::RenderTarget& renderer)
    {
        renderer.draw(currentScoreText);
        renderer.draw(highScoreText);
    }
    
};

#endif