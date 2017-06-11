#ifndef GAMESOCKET_H
#define GAMESOCKET_H

class ConnectedClient;

class GameSocket
{
    public:
        ////
        //CONSTANTS
        ////

        const unsigned short MAX_PLAYER_NUMBER = 2;
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
        unsigned short ifHit(string coordinates, ConnectedClient *Player);
        unsigned short getPlayersNumbers(){return players.size()};
        vector<ConnectedClients*> getPlayers(){return players};
        unsigned short getTurn(){return this->turn};
    protected:
    private:
        //
        //  Private constructor of class
        //
        //  Constructor assigns pointer to first player who starts the game
        //
        GameSocket(ConnectedClient *firstPlayer);
        //
        //  DrawShips method initiates methods responsible for displaying whole game onto screen
        //
        void drawShips();
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
        //
        //  Pointers to ConnectedClient class type objects responsible for connecting players with game
        //
        vector<ConnectedClients*> players;
        //
        //  The turn variable is information who is supposed to make his movement right now
        //
        //  false - first player, true - second player
        //
        unsigned short turn;
};

#endif // GAMESOCKET_H
