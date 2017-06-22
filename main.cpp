#include "common.h"
#include "Server.h"


int main()
{
    TCPServer server;
    server.start(1666);
    while(server.is_running())
	{
		common.sleep(1);
		cout << "*";
	}
    return NULL;
    }
