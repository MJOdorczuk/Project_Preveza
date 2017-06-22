#ifndef GAMESOCKET_H
#define GAMESOCKET_H
#include <vector>
#include <string>

using namespace std;

class ConnectedClient;

class GameSocket
{
    private:

        ////
        //  VARIABLES
        ////

        //
        //  Pointers to ConnectedClient class type objects responsible for connecting players with game
        //
        vector <ConnectedClient*> players;
        //
        //  The turn variable is information who is supposed to make his movement right now
        //
        //  Value of this variable is the number of currently having turn player's pointer in players vector
        //
        unsigned short turn;
        //
        //  The battletide is an array containing all information about current position of ships, hit points and state of ships
        //
        //  First argument corresponds to X-axis position
        //  Second argument corresponds to Y-axis position
        //  Third argument corresponds to number of plane (0 - plane of first player, 1 - plane of second player)
        //
        //  The array can have four value
        //      0 - no ship, no hit
        //      1 - ship, no hit
        //      2 - hit ship
        //      3 - hit blank pole
        //
        unsigned short battletide[10][10][2];
        unsigned short ships[2]; //Both are supposed to be changed to vectors
        unsigned short currentX, currentY;
        unsigned short phase;
        unsigned short points[2];

    public:

        ////
        //CONSTANTS
        ////

        const unsigned short MAX_PLAYER_NUMBER = 2, MIN_PLAYER_NUMBER = 2;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's neither ship nor the field was hit by other player.
        //
        const unsigned short NOT_HIT_NO_SHIP = 0;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's no ship but the field was hit by other player.
        //
        const unsigned short HIT_NO_SHIP = 1;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's ship but the field was not hit by other player.
        //
        const unsigned short NOT_HIT_SHIP = 2;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's ship and the field was hit by other player.
        //
        const unsigned short HIT_SHIP = 3;
        //
        //  It's returned by method getTurn(turn).
        //
        //  Is returned when first player is supposed to make a move.
        //
        const unsigned short PLAYER1_TURN = 0;
        //
        //  It's returned by method getTurn(turn).
        //
        //  Is returned when second player is supposed to make a move.
        //
        const unsigned short PLAYER2_TURN = 1;

        const unsigned short MISS = 0, HIT = 1, NOT_AVAILABLE = 2, WIN = 3, ERR = 666, AVAILABLE = 1, ACCES_DENIED = 404, SHIP_SET = 4, BLANK = 5;
        const unsigned short SETUP_PHASE = 0, BATTLE_PHASE = 1;

        ////
        //  METHODS
        ////

        //
        //  Constructor assigns pointer to first player who starts the game
        //
        GameSocket(ConnectedClient *firstPlayer);
        //
        //  Virtual destructor of GameSocket
        //
        virtual ~GameSocket();
        //
        //  AddPlayer method sets pointer for second player.
        //
        //  It returns information if second player is already in game (false - is not, true - is)
        //
        bool addPlayer(ConnectedClient *secondPlayer);
        unsigned short makeMove(string command, ConnectedClient *Player);
        unsigned short getPlayersNumber(){return players.size();}
        vector <ConnectedClient*> getPlayers(){return players;}
        ConnectedClient* getTurn(){return players.at(turn);}
    protected:
    private:
        //
        //  DrawShips method initiates methods responsible for displaying whole game onto screen
        //
        void drawShips();
        unsigned short ifHit(unsigned short x, unsigned short y);
        unsigned short ifDirectionCorrect(char direction, unsigned short x, unsigned short y, unsigned short turn);
        unsigned short ifSurroundingClear(unsigned short x, unsigned short y, unsigned short turn);
        void putShip(unsigned short x, unsigned short y, char direction, unsigned short turn);
        unsigned short checkPlayer(ConnectedClient* player);
};

#endif // GAMESOCKET_H
