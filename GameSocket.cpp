#include "gamesocket.h"

GameSocket::GameSocket(ConnectedClient *firstPlayer)
{
    this->players.push_back(firstPlayer);
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
