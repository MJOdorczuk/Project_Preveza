#include "MyCommands.h"
#include <cassert>

CommandEngine::CommandEngine()
{
	this->registerCommand(new CmdHelp("help", "pomoc"));
	this->registerCommand(new CmdExit("exit", "koniec sesji klienta"));
	this->registerCommand(new CmdList("list", "wyswietl uzytkownikow"));
	this->registerCommand(new CmdMsg("msg","wyslij wiadomosc"));
	this->registerCommand(new CmdInvite("invite","zapros uzytkownika do gry"));
	this->registerCommand(new CmdEnd("end","zakoncz rozgrywke"));
	this->registerCommand(new CmdMove("move","wykonaj ruch w grze"));
	this->registerCommand(new CmdStart("start","rozpocznij nowa gre"));
}

bool CmdStart::exec(ConnectedClient *client, vector<string> args)
{
    client->setGame(client->server->startGame(client));
    return true;
}

bool CmdHelp::exec(ConnectedClient *client, vector<string> args)
{
	vector<Command*> list = client->server->listCommands();
	for(vector<string>::size_type i = 0; i<list.size(); ++i)
		client->putline(Common::EOLN + list.at(i)->getName() + " (" + list.at(i)->getDescription() + ")" + Common::EOLN);
	return true;
}

bool CmdExit::exec(ConnectedClient *client, vector<string> args)
{
	client->stop();
	return true;
}

bool CmdList::exec(ConnectedClient *client, vector<string> args)
{
	vector<ConnectedClient*> clients = client->getServer()->listClients();
	for(vector<ConnectedClient*>::size_type i = 0; i<clients.size(); ++i)
		client->putline(Common::EOLN + clients.at(i)->getUser());
	return true;
}

bool CmdMsg::exec(ConnectedClient *client, vector<string> args)
{
	if(args.size() < 3) return false;
	ConnectedClient* remote = client->getServer()->findClient(args.at(1));
	if(remote == NULL) return false;
	string message = "";
	for(vector<string>::size_type i = 2; i<args.size(); ++i)
	{
		message += "_" + args.at(i);
	}
	remote->putline(Common::EOLN + client->getUser() + ": " + message);
	return true;
}

bool CmdEnd::exec(ConnectedClient *client, vector<string> args)
{
    if(client->getGame() == NULL) return false;
    vector<ConnectedClient *> players = client->getGame()->getPlayers();
    GameSocket * game = client->getGame();
    for(vector<ConnectedClient *>::size_type i=0; i<players.size(); i++)
    {
        players.at(i)->setGame(NULL);
        players.at(i)->putline(Common::EOLN + "Gra zakonczona przez " + client->getUser());
    }
    client->server->order66(game);
    return true;
}

bool CmdInvite::exec(ConnectedClient *client, vector<string> args)
{
    ConnectedClient * player = client->getServer()->findClient(args.at(1));
    if(player == NULL) return false;
    player->setGame(client->getGame());
    client->getGame()->addPlayer(player);
    player->putline(Common::EOLN + "Dolaczasz do gry rozpoczetej przez " + client->getUser());
    client->putline(Common::EOLN + player->getUser() + " dolacza do twojej gry");
    return true;
}

bool CmdMove::exec(ConnectedClient *client, vector<string> args)
{
    if(client->getGame() == NULL) return false;
    vector<ConnectedClient *> players = client->getGame()->getPlayers();
    int i = 0;
    unsigned short response = client->getGame()->makeMove(args.at(1),client);
    switch(response)
        {
        case 0:
            {
                client->putline(Common::EOLN + "Nie trafiles");
                while(players.at(i++) != client);
                players.at(i)->putline(Common::EOLN + "Twoja tura");
                break;
            }
        case 1:
            {
                client->putline(Common::EOLN + "Trafiony!");
                break;
            }
        case 2:
            {
                client->putline(Common::EOLN + "Niepoprawny ruch");
                break;
            }
        case 3:
            {
                client->putline(Common::EOLN + "Trafiony zatopiony! Wygrales!");
                for(vector<ConnectedClient *>::size_type i=0; i<players.size(); i++)
                {
                    if(players.at(i)!=client) players.at(i)->putline(Common::EOLN + "Troche wlasnie przegrales. :( ");
                }
                client->server->order66(client->getGame());
                break;
            }
        case 4:
            {
                client->putline(Common::EOLN + "Statek ustawiony poprawnie");
                break;
            }
        case 5:
            {
                client->putline(Common::EOLN + "Wybierz kierunek ustawienia statku");
                break;
            }
        case 6:
            {
                for(vector<ConnectedClient *>::size_type i=0; i<players.size(); i++){players.at(i)->putline(Common::EOLN + "Gra się rozpoczyna");}
                break;
            }
        case 404:
            {
                client->putline(Common::EOLN + "Aj cwaniaczku, nie wolno ci tego robic ;)");
                break;
            }
        case 666:
            {
                client->putline(Common::EOLN + "Co ty u licha zrobiles, ze az wywalilo blad?");
                break;
            }
        }
        return true;
}
