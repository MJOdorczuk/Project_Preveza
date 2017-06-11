#include "gamesocket.h"

GameSocket::GameSocket(ConnectedClient *firstPlayer)
{
    this->players.push_back(firstPlayer);
<<<<<<< HEAD:GameSocket.cpp
=======
    this->battletide.push_back(new unsigned short[10][10]);
>>>>>>> origin/GameSocket-temporary-branch-1:Gamesocket.cpp
}

GameSocket::~GameSocket()
{
    //dtor
}

bool GameSocket::addPlayer(ConnectedClient *secondPlayer)
{
<<<<<<< HEAD:GameSocket.cpp
    if(this->player2) return true;
    players.push_back(secondPlayer);
=======
    if(this->getPlayersNumbers()>1) return true;
    this->players.push_back(secondPlayer);
    this->battletide.push_back(new unsigned short[10][10]);
>>>>>>> origin/GameSocket-temporary-branch-1:Gamesocket.cpp
    return false;
}
