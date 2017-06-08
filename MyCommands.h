#pragma once

#include "Commands.h"

class CmdHelp : public Command
{
public:
	CmdHelp(const string commandName, const string commandDescription) : Command(commandName, commandDescription) { }
	bool exec(ConnectedClient *client, vector<string> args);
};

class CmdExit : public Command
{
public:
	CmdExit(const string commandName, const string commandDescription) : Command(commandName, commandDescription) { }
	bool exec(ConnectedClient *client, vector<string> args);
};
class CmdList : public Command
{
public:
	CmdList(const string commandName, const string commandDescription) : Command(commandName, commandDescription) { }
	bool exec(ConnectedClient *client, vector<string> args);
};



class CmdList : public Command
{
public:
	CmdList(const string commandName, const string commandDescription) : Command(commandName, commandDescription) { }
	bool exec(ConnectedClient *client, vector<string> args);
};

class CmdMsg : public Command
{
public:
	CmdMsg(const string commandName, const string commandDescription) : Command(commandName, commandDescription) { }
	bool exec(ConnectedClient *client, vector<string> args);
};

