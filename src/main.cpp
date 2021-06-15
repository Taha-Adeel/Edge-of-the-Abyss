#include "Game.h"

int main(){
    Game& game = Game::getGameInstance();
    game.run();

    return 0;
}