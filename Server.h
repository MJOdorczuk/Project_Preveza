#pragma once
#include "common.h"
#include "ConnectedClient.h"
#include "Commands.h"

class ConnectedClient;
class CommandEngine;
class Command;

class TCPServer
{
public:
    TCPServer();
    virtual ~TCPServer();
    virtual void start(uint16_t port);
    virtual void stop();
	virtual bool is_running();
	vector<ConnectedClient*> listClients();
	ConnectedClient* findClient(string client_name);
	vector<Command*> listCommands();

protected:	
	friend class ConnectedClient;
	friend class Command;

    virtual void addClient(ConnectedClient * client);
    virtual void removeClient(ConnectedClient * client);    
	static void* run(void *); 
	CommandEngine *cmdEngine;


private:
    int my_socket;
	volatile bool _is_running;
    uint16_t port;
    pthread_t thread_id;
    vector<ConnectedClient*> clients;
};

