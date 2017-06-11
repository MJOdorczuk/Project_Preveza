#include "gamesocket.h"

GameSocket::GameSocket(ConnectedClient *firstPlayer)
{
    this->players.push_back(firstPlayer);
    this->battletide.push_back(new unsigned short[10][10]);
}

GameSocket::~GameSocket()
{
    //dtor
}

bool GameSocket::addPlayer(ConnectedClient *secondPlayer)
{
    if(this->getPlayersNumbers()>1) return true;
    this->players.push_back(secondPlayer);
    this->battletide.push_back(new unsigned short[10][10]);
    return false;
}
