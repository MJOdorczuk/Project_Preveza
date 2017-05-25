#include "MyCommands.h"
#include <cassert>

CommandEngine::CommandEngine()
{
	this->registerCommand(new CmdHelp("help", "pomoc"));
	this->registerCommand(new CmdExit("exit", "koniec sesji klienta"));
	this->registerCommand(new CmdList("list", "wyswietl uzytkownikow"));
	//this->registerCommand(new CmdMsg());
}



bool CmdList::exec(ConnectedClient *client, vector<string> args) 
{  
	/*for(int i=0; i<client->server->listClients().size() ;i++)
	{

	client->putline("\r\n"+client->server->listClients().at(i)->getUser());
	client->putline
	}*/
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


/*bool CmdList::exec()
{
	vector<ConnectedClient*> clients = client->getServer()->listClients();
	for(vector<ConnectedClient*>::size_type i = 0; i<clients.size(); ++i)
		client->putline(Common::EOLN + clients.at(i)->getUser());
	return true;
}

bool CmdMsg::exec()
{
	if(args.size() < 3) return false;
	ConnectedClient* remote = client->getServer()->findClient(args.at(1));
	if(remote == NULL) return false;
	remote->putline(Common::EOLN + client->getUser() + ": " + args.at(2));
	return true;
}
*/