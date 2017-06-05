#pragma once
#include "common.h"
#include "Server.h"
#include "Commands.h"

class TCPServer;

class ConnectedClient
{
public:
    ConnectedClient(TCPServer* server, int connected_socket, uint32_t ip, uint16_t port);
    virtual ~ConnectedClient();
    virtual void disconnect();   
	virtual void putline(string str);
	void putchar(uint8_t c);
    virtual string getline(bool asterisks = false);

	virtual bool is_running() { return _is_running; };
	virtual void stop() { _is_running = false; }
	virtual void start() { _is_running = true; }
	TCPServer* getServer() { return server; }
	string getUser() { return user; }
	TCPServer* server;
	bool getReady();
	void setReady(bool state);

protected:
    static void* run(void *);
	
private:
    bool ready;
    uint32_t ip;
    uint16_t port;
    int connected_socket;
    string user, pass;
    pthread_t thread_id;
	volatile bool _is_running;
    
};
