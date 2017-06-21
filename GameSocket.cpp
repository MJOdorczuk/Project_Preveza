#include "gamesocket.h"


GameSocket::GameSocket(ConnectedClient *firstPlayer)
{
    this->players.push_back(firstPlayer);
    this->turn = PLAYER1_TURN;
    this->phase = SETUP_PHASE;
    this->currentX = 666;
    this->currentY = 666;
    this->points[0] = 20;
    this->points[1] = 20;
}

GameSocket::~GameSocket()
{
    //dtor
}

bool GameSocket::addPlayer(ConnectedClient *secondPlayer)
{
    if(this->players.size()>=MAX_PLAYER_NUMBER) return true;
    this->players.push_back(secondPlayer);
    return false;
}

unsigned short GameSocket::checkPlayer(ConnectedClient* player)
{
    for(int i=0; i<players.size(); i++){if(players.at(i) == player) return i;}
    return ACCES_DENIED;
}

void GameSocket::putShip(unsigned short x, unsigned short y, char direction, unsigned short turn)
{
    unsigned short dx = 0, dy = 0, length;
    unsigned short quantity = ships[(turn)%players.size()];
    if(quantity<4)length = 1;
    else if(quantity<7)length = 2;
    else if(quantity<9)length = 3;
    else length = 4;
    switch(direction)
    {
        case('N'):
            {
            dy = -1;
            break;
            }
        case('S'):
            {
                dy = 1;
                break;
            }
        case('W'):
            {
                dx = -1;
                break;
            }
        case('E'):
            {
                dx = 1;
                break;
            }
        default:{break;}
    }
    for(int i=0; i<length; i++) battletide[x+dx*i][y+dy*i][turn%players.size()] = NOT_HIT_SHIP;
}

unsigned short GameSocket::ifHit(unsigned short x, unsigned short y)
{
    if(x>9 || y>9) return NOT_AVAILABLE;
    unsigned short condition = battletide[x][y][(turn+1)%players.size()];
    if(condition == NOT_HIT_NO_SHIP) return MISS;
    if(condition == HIT_NO_SHIP || condition == HIT_SHIP) return NOT_AVAILABLE;
    if(condition == NOT_HIT_SHIP) return HIT;
    else return ERR;
}

unsigned short GameSocket::ifSurroundingClear(unsigned short x, unsigned short y, unsigned short turn)
{
    unsigned short i, j, condition;
    if(x>9 || y>9 || turn>=MAX_PLAYER_NUMBER) return NOT_AVAILABLE;
    if(x==0) i=0;
    else i=x-1;
    if(y==0) j=0;
    else j=y-1;
    for(;i<x+1-x%9;i++)
        for(;j<y+1-y%9;y++)
        {
            condition = battletide[i][j][(turn)%players.size()];
            if(condition == HIT_NO_SHIP || condition == HIT_SHIP || condition == NOT_HIT_SHIP) return NOT_AVAILABLE;
        }
    return AVAILABLE;
}

unsigned short GameSocket::ifDirectionCorrect(char direction, unsigned short x, unsigned short y, unsigned short turn)
{
    if(x>9 || y>9 || (direction != 'N' && direction != 'S' && direction != 'W' && direction != 'E' && direction != 'U')) return NOT_AVAILABLE;
    unsigned short condition = battletide[x][y][(turn)%players.size()];
    unsigned short quantity = ships[(turn)%players.size()];
    unsigned short dx = 0, dy = 0, length;
    if(quantity<4)length = 1;
    else if(quantity<7)length = 2;
    else if(quantity<9)length = 3;
    else length = 4;
    switch(direction)
    {
        case('N'):
            {
            dy = -1;
            break;
            }
        case('S'):
            {
                dy = 1;
                break;
            }
        case('W'):
            {
                dx = -1;
                break;
            }
        case('E'):
            {
                dx = 1;
                break;
            }
        default:{break;}
    }
    if(direction == 'U')
    {
        if(condition == NOT_HIT_NO_SHIP) return AVAILABLE;
        if(condition == HIT_NO_SHIP || condition == HIT_SHIP || condition == NOT_HIT_SHIP) return NOT_AVAILABLE;
    }
    if(condition == NOT_HIT_NO_SHIP || condition == NOT_HIT_SHIP)
    {
        for(int i=0; i<length; i++){if(ifSurroundingClear(x+i*dx,y+i*dy,this->turn) == NOT_AVAILABLE) return NOT_AVAILABLE;}
        return AVAILABLE;
    }
    if(condition == HIT_NO_SHIP || condition == HIT_SHIP) return NOT_AVAILABLE;
    else return ERR;
}

unsigned short GameSocket::makeMove(string command, ConnectedClient* Player)
{
    if(players.size() < MIN_PLAYER_NUMBER) return NOT_AVAILABLE;
    if(this->phase != SETUP_PHASE && Player != players.at(this->turn)) return NOT_AVAILABLE;
    unsigned short turn = checkPlayer(Player);
    if(turn == ACCES_DENIED) return ACCES_DENIED;
    unsigned short x = this->currentX, y = this->currentY;
    if(command == "N" || command == "S" || command == "W" || command == "E")
    {
        if(x > 9 || y > 9) return NOT_AVAILABLE;
        else if(ifDirectionCorrect(command.at(0),x,y,turn) != AVAILABLE || this->ships[turn]<9) return NOT_AVAILABLE;
        else
        {
            putShip(x,y,command.at(0),turn);
            this->ships[turn]++;
            for(int i = 0; i < players.size(); i++) if(this->ships[i]<10) return HIT;
            this->phase = BATTLE_PHASE;
            return HIT;
        }
    }
    if(command.at(0)<'A' || command.at(0)>'J' || command.at(1)<'0' || command.at(1)>'9') return NOT_AVAILABLE;
    x = (unsigned short)(command.at(0) - 'A');
    y = (unsigned short)(command.at(1) - '0');
    if(this->phase == SETUP_PHASE)
    {
        if(x > 9 || y > 9) return NOT_AVAILABLE;
        else if(ifDirectionCorrect('U',x,y,turn) != AVAILABLE) return NOT_AVAILABLE;
        this->currentX = x;
        this->currentY = y;
        return HIT;
    }
    else if(this->phase == BATTLE_PHASE)
    {
        if(x > 9 || y > 9) return NOT_AVAILABLE;
        unsigned short shipstatus = ifHit(x,y);
        if(shipstatus == ERR) return ERR;
        else if(shipstatus == NOT_AVAILABLE) return NOT_AVAILABLE;
        else if(shipstatus == MISS)
        {
            this->battletide[x][y][(turn+1)%players.size()] = HIT_NO_SHIP;
            this->turn = (this->turn+1)%players.size();
            return MISS;
        }
        else if(shipstatus == HIT)
        {
            this->battletide[x][y][(turn+1)%players.size()] = HIT_SHIP;
            this->points[(turn+1)%players.size()]--;
            if(this->points[(turn+1)%players.size()] == 0) return WIN;
            this->turn = (this->turn+1)%players.size();
            return HIT;
        }
        else return ERR;
    }
    else return ERR;
}
