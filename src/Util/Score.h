#ifndef _SCORE_H
#define _SCORE_H
#include <string>
#include<fstream>
#include "../ResourceManager/ResourceFactory.h"
//#include "../Camera.h"
//#include "../States/PlayingState.h"

class PlayingState;
class ScoreKeeper
{
    //Camera* referenceCamera;
    PlayingState* pointerPlayingState;
    sf::Font& font;
    std::fstream fio;
    float currentScore;
    float highScore;
    sf::Text currentScoreText;
    sf::Text highScoreText;
    
public:
    ScoreKeeper(PlayingState* context);
    ~ScoreKeeper();

    //Accessors
    const float getCurrentScore() const;
    const float getHighScore() const;

    //Logic
    int convertSecondsToScore(float seconds);
    void updateHighScore();
    void updateTextBoxes(float dt);

    //Update and Render
    void update(sf::Time elapsedTime);
    void render(sf::RenderTarget& renderer);
};

#endif