#include "ConnectedClient.h"

ConnectedClient::ConnectedClient(TCPServer* server, int connected_socket, uint32_t ip, uint16_t port)
{
    this->server = server;
    this->connected_socket = connected_socket;
    this->ip = ip;
    this->port = port;
	this->start();
    pthread_create(&thread_id, NULL, run, (void*)this);
}

void ConnectedClient::putline(string str)
{
    send(connected_socket, str.c_str(), str.length(), 0);
}

void ConnectedClient::putchar(uint8_t c)
{
    send(connected_socket, (const char*)&c, 1, 0);
}

ConnectedClient::~ConnectedClient()
{
    disconnect();
}

void ConnectedClient::disconnect()
{
    shutdown(connected_socket, SHUT_RDWR);
}

string ConnectedClient::getline(bool asterisks)
{
    string line("");
    char c;
    size_t rxbytes;
    do {
        rxbytes = recv(connected_socket, &c, 1, 0);
        if(rxbytes == 1 && c>=32)
        {
            line += c;
            if(asterisks) c = '*';
            send(connected_socket, &c, 1, 0); //echo
        }
		if (rxbytes == -1) { this->stop(); throw exception("client disconnected"); }
    } while (rxbytes==1 && c!='\r');
    return line;
}

void* ConnectedClient::run(void* arg)
{
    ConnectedClient * client = (ConnectedClient*)arg;
	/*
	//supress TELNET local echo
	client->putchar(0xFF);
	client->putchar(0xFB); //FC
	client->putchar(0x01);

    client->putline("User: ");
    client->user = client->getline(false);
    cout << client->user << endl;

    client->putline(Common::EOLN + "Pass: ");
    client->pass = client->getline(true);
    cout << client->pass << endl;

	if(client->user != client->pass)
	{
		client->putline(Common::EOLN + "AUTH failed. ");
		client->disconnect();
		client->server->removeClient(client);
		return NULL;
	}
	*/
    string c("");
    do {c=client->getline();
	if(c.compare(0,5,"GET /")==0){client->putline(Common::EOLN + "dfhfh ");}
	/*
        client->putline(Common::EOLN + "Cmd: ");
		try {
			c = client->getline();
		} 
		catch(exception e)
		{
			client->putline(Common::EOLN + e.what());
			break;
		}

        cout << client->user << ": " << c << endl;

		try 
		{
			client->server->cmdEngine->exec(client, c);
			//if(c == "help")client->putline(Common::EOLN + "Pierwsza pomoc.");
			//else
			//	if(c == "exit")client->putline(Common::EOLN + "XXX.");

		} 
		catch(exception e)
		{
			client->putline(Common::EOLN + e.what());
		}*/
    } while(client->is_running());

    client->disconnect();
    client->server->removeClient(client);
    return NULL;
}

void ConnectedClient::getReady()
{
    return this->ready;
}

void ConnectedClient::setReady(bool state)
{
    this->ready = state;
}
