#ifndef GAMESOCKET_H
#define GAMESOCKET_H

class ConnectedClient;

class GameSocket
{
    public:
        ////
        //CONSTANTS
        ////
    
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's neither ship nor the field was hit by other player.
        //
    const uint8_t NOT_HIT_NO_SHIP;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's no ship but the field was hit by other player.
        //
    const uint8_t HIT_NO_SHIP;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's ship but the field was not hit by other player.
        //
    const uint8_t NOT_HIT_SHIP;
        //
        //  It's returned by checking current state of chosen field in method ifHit(coordinates);
        //
        //  Is returned when there's ship and the field was hit by other player.
        //
    const uint8_t HIT_SHIP;
        //
        //  It's returned by method
        //
    const uint8_t PLAYER1_TURN;
    const uint8_t PLAYER@_TURN;
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
        uint8_t ifHit(string coordinates, ConnectedClient *Player);
        uint8_t getPlayersNumbers(){return players.size()};
        vector<ConnectedClients*> getPlayers(){return players};
        uint8_t getTurn(){;
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
        uint8_t battletide[10][10][2];
        //
        //  Pointers to ConnectedClient class type objects responsible for connecting players with game
        //
        vector<ConnectedClients*> players;
        //
        //  The turn variable is information who is supposed to make his movement right now
        //
        //  false - first player, true - second player
        //
        uint8_t turn;
};

#endif // GAMESOCKET_H
