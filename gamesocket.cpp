#include "gamesocket.h"

GameSocket::GameSocket(ConnectedClient *firstPlayer)
{
    this->player1 = firstPlayer;
}

GameSocket::~GameSocket()
{
    //dtor
}

bool GameSocket::addPlayer(ConnectedClient *secondPlayer)
{
    if(this->player2) return true;
    this->player2 = secondPlayer;
    return false;
}
