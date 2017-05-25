#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "ConnectedClient.h"
using namespace std;

class ConnectedClient;

class Command
{
public:
	Command(const string commandName, const string commandDescription) : commandName(commandName), commandDescription(commandDescription) {}
	virtual bool exec(ConnectedClient *client, vector<string> args) = 0;
	virtual const string getName() { return commandName; }
	virtual const string getDescription() { return commandDescription; }
	static vector<string> split(string str, const string& delimiter);

protected:
	string commandName, commandDescription;
};

class CommandEngine
{
public:
	CommandEngine();
	virtual ~CommandEngine();
	virtual void registerCommand(Command *command);
	virtual bool exec(ConnectedClient *client, string t);
	virtual vector<Command*> listCommands();

protected:
	vector <Command*> commands;
};

