#ifndef GAMESOCKET_H
#define GAMESOCKET_H

class ConnectedClient;

class GameSocket
{
    public:
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
        char battletide[10][10][2];
        //
        //  Pointers to ConnectedClient class type objects responsible for connecting players with game
        //
        ConnectedClient *player1, *player2;
        //
        //  The turn variable is information who is supposed to make his movement right now
        //
        //  false - first player, true - second player
        //
        bool turn;
};

#endif // GAMESOCKET_H
