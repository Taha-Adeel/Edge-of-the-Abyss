#include "Score.h"
#include "../States/PlayingState.h"
#include "Constants.h"
#include <iostream>
#include<cmath>

//Constructors
ScoreKeeper::ScoreKeeper(PlayingState* context):pointerPlayingState(context), font(ResourceFactory::getResourceFactory().fonts.get(CONSTANTS::SCORE_FONT))
{   
    fio.open(CONSTANTS::SCORE_FILE_PATH.c_str(), std::ios::in | std::ios::out);
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
    currentScore=0.f;
    auto camera_pos = pointerPlayingState->getCamera().getPosition();
    highScoreText.setFont(font);
    highScoreText.setString(std::string("High Score ")+ std::to_string(convertSecondsToScore(highScore)));
    highScoreText.setPosition(camera_pos.x + CONSTANTS::HIGHSCORE_X, camera_pos.y + CONSTANTS::HIGHSCORE_Y);
    highScoreText.setCharacterSize(30);
    highScoreText.setStyle(sf::Text::Bold);
    highScoreText.setFillColor(CONSTANTS::SCOREBOARD_COLOR);

    currentScoreText.setFont(font);
    currentScoreText.setString(std::string("Score ")+std::to_string(convertSecondsToScore(currentScore)));
    currentScoreText.setPosition(camera_pos.x + CONSTANTS::SCOREBOARD_X, camera_pos.y + CONSTANTS::SCOREBOARD_Y);
    currentScoreText.setCharacterSize(30);
    // currentScoreText.setStyle(sf::Text::Bold);
    currentScoreText.setFillColor(CONSTANTS::SCOREBOARD_COLOR);
}
//Destructor
ScoreKeeper::~ScoreKeeper(){if(fio.is_open())fio.close();}

//Accessors
const float ScoreKeeper::getCurrentScore() const{return currentScore;}
const float ScoreKeeper::getHighScore() const{return highScore;}

/**
* @brief Converts seconds of survival to points by floor(100*Seconds)
* 
* @param seconds 
* @return points
*/
int ScoreKeeper::convertSecondsToScore(float seconds)
{
    return static_cast<int>(100*floor(seconds));
}
/**
 * @brief Checks if current score is the best score after game is Over
 * 
 */
void ScoreKeeper::updateHighScore()
{
    if(currentScore >= highScore)
    {
        fio.close();
        remove(CONSTANTS::SCORE_FILE_PATH.c_str());
        fio.open(CONSTANTS::SCORE_FILE_PATH.c_str(), std::ios::out);
        fio<<currentScore;
        fio.close();
        highScore = currentScore;
    }
    std::cout<<"Game over. Score: "<<currentScore<<" , High Score: "<<highScore<<std::endl;
    currentScore = 0.f;
}
/**
 * @brief Updates the Text Fields for Scores
 * 
 * @param dt 
 */
void ScoreKeeper::updateTextBoxes(float dt)
{
    auto camera_pos = pointerPlayingState->getCamera().getPosition();
    currentScoreText.setString(std::string("Score ")+ std::to_string(convertSecondsToScore(currentScore)));
    highScoreText.setString(std::string("High Score ")+std::to_string(convertSecondsToScore(highScore)));

    currentScoreText.setPosition(camera_pos.x + CONSTANTS::SCOREBOARD_X
        , camera_pos.y + CONSTANTS::SCOREBOARD_Y);
    highScoreText.setPosition(camera_pos.x + CONSTANTS::HIGHSCORE_X
        , camera_pos.y + CONSTANTS::HIGHSCORE_Y);
}

void ScoreKeeper::update(sf::Time elapsedTime)
{
    float dt = elapsedTime.asSeconds();
    currentScore += dt * CONSTANTS::GAME_SPEED;
    if(currentScore > highScore)highScore = currentScore;
    this->updateTextBoxes(dt);
}
void ScoreKeeper::render(sf::RenderTarget& renderer)
{
    renderer.draw(currentScoreText);
    renderer.draw(highScoreText);
}
    