#include "Server.h"

TCPServer::TCPServer()
{
    my_socket = -1;
	_is_running = false;
	cmdEngine = new CommandEngine();
}

TCPServer::~TCPServer()
{
	if(_is_running) stop();
	delete cmdEngine;
	for(vector<GameSocket *>::size_type i=0; i<games.size(); i++) delete games.at(i);
}


ConnectedClient* TCPServer::findClient(string user)
{
	//vector<ConnectedClient*>::iterator it;
	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		if((*it)->getUser() == user)
		{
			return *it;
		}
	}
	return NULL;
}

vector<Command*> TCPServer::listCommands()
{
	return cmdEngine->listCommands();
}
vector<ConnectedClient*> TCPServer::listClients()
{
	return clients;
}

void TCPServer::addClient(ConnectedClient * client)
{
    clients.push_back(client);
}

void TCPServer::removeClient(ConnectedClient * client)
{
    //vector<ConnectedClient*>::iterator it;
	for(auto it = clients.begin(); it != clients.end(); ++it)
	{
		if(*it == client)
		{
			clients.erase(it);
			delete client;
			return;
		}
	}
}

void TCPServer::start(uint16_t port)
{
    this->port = port;
	_is_running = true;
    pthread_create(&thread_id, NULL, run, (void*)this);
}

void TCPServer::stop()
{
    shutdown(my_socket, SHUT_RDWR);
	_is_running = false;
}

bool TCPServer::is_running()
{
	return _is_running;
}

void* TCPServer::run(void *arg)
{
    cerr << "TCPServer::run" << endl;
    TCPServer *server = (TCPServer *)arg;

    server->my_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( server->my_socket == -1)
    {
		server->stop();
        return NULL;
    }

	sockaddr_in local;
    memset((char*)&local, 0, sizeof(local));
	local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(server->port);
    if(bind(server->my_socket, (const sockaddr*)&local, sizeof(local)) == -1)
    {
        cerr << "problem: bind (" << WSAGetLastError() << ")" << endl;
		server->stop();
        return NULL;
    }

    if(listen(server->my_socket, 10) == -1)
    {
        cerr << "problem: listen" << endl;
		server->stop();
        return NULL;
    }

	while(server->is_running())
	{
		sockaddr_in remote;
		socklen_t sockaddrlen = sizeof(remote);
        int client_socket = accept(server->my_socket, (sockaddr*)&remote, &sockaddrlen);
        if(client_socket != -1)
        {
            cout << "client connected: "
                << remote.sin_addr.s_addr
                << " : " << remote.sin_port
                << endl;
            server->addClient(new ConnectedClient(server, client_socket, remote.sin_addr.s_addr, remote.sin_port));
        }
        else
        {
            cout << "accept error." << endl;
			server->stop();
        }
    }
    return NULL;
}

GameSocket * TCPServer::startGame(ConnectedClient * player)
{
    bool helpingtemp = false;
    for(vector<ConnectedClient *>::size_type i=0; i<clients.size(); i++){if(clients.at(i) == player) helpingtemp = true;}
    if(!helpingtemp) return NULL;
    games.push_back(new GameSocket(player));
    return games.at(games.size());
}

void TCPServer::order66(GameSocket * gametokill)
{
    for(vector<GameSocket *>::size_type i=0; i<games.size(); i++)
    {
        if(games.at(i) == gametokill)
        {
            delete gametokill;
            games.at(i) = NULL; //Really bad solution. Just no time to make it better.
        }
    }
}
