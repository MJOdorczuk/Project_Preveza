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


/*
class CmdList : public Command
{
public:
	CmdList(ConnectedClient *client, string t) : Command(client, t) { }
	CmdList() : Command() { }
	const string getName() { return "list"; }
	bool exec();
};

class CmdMsg : public Command
{
public:
	CmdMsg(ConnectedClient *client, string t) : Command(client, t) { }
	CmdMsg() : Command() { }
	const string getName() { return "msg"; }
	const string getDescription() { return string("usage: <msg> <username> <text to send>"); }
	bool exec();
};

*/