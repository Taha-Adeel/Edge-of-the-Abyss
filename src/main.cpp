#include "Game.h"
#include "Player.h"
int main(){
    Game& game = Game::getGameInstance();
    game.run();

    return 0;
}