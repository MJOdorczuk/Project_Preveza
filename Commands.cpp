#include "Commands.h"
#include "MyCommands.h"

vector<string> Command::split(string str, const string& delimiter)
{
	vector<string> results;
	results.clear();
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) //znajdŸ pozycjê 'delimitera', jeœli siê da
    {
        results.push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length()); //odetnij znaleziony 'delimiter' z orygina³u
    }
    if(str.length() > 0)
        results.push_back(str); //ewentualna koñcówka napisu
	return results;
}




CommandEngine:: ~CommandEngine()
{
	vector<Command*>::iterator it;
	for(it = commands.begin(); it != commands.end(); ++it)
	{
		delete *it;
	}
	commands.clear();
}

vector<Command*> CommandEngine::listCommands()
{
	return commands;
}

bool CommandEngine::exec(ConnectedClient *client, string t)
{
	vector<string> args = Command::split(t, " ");
	if(args.size() == 0) throw ::exception("missing command name");

	vector<Command*>::iterator it;
	for(it = commands.begin(); it != commands.end(); ++it)
	{
		if( (*it)->getName() == args.at(0))
		{
			(*it)->exec(client, args);
			return true;
		}
	}
	throw ::exception("command not recognized.");
}

void CommandEngine::registerCommand(Command *command)
{
	commands.push_back(command);
	cout << "command '" << command->getName() << "' is now registered." << endl;
}
