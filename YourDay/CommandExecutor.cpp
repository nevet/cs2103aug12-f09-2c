#include <assert.h>
#include "CommandExecutor.h"

//set the status signal of command execution process
void CommandExecutor::setStatus(Signal statusSignal)
{
	status = statusSignal;
}

//add an entry as a pure string to the entry list vector
void CommandExecutor::addEntry(vector<string> * entryList, string detail)
{
	if (detail == "")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		entryList -> push_back(detail);
	}
}

void CommandExecutor::deleteEntry(vector<string>* entryList, string entry)
{
	vector<string>* tempEntryList;
	string temp;
	if ( entry =="")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		for(int i=0;i<entryList->size();i++)
		{
			temp=entryList->back();
			entryList->pop_back();
			if(temp!=entry)
				tempEntryList->push_back(temp);
			else
				break;
		}
		for(int i=0;i<tempEntryList->size();i++)
		{
			temp=tempEntryList->back();
			tempEntryList->pop_back();
			entryList->push_back(entry);
		}
	}
}

void CommandExecutor::searchEntry(vector<string>* entryList, string keyWord, vector<string>* matchedEntryList)
{
	vector<string>* tempEntryList;
	string temp;

	matchedEntryList->clear();
	if ( keyWord =="")
	{
		setStatus(EMPTY_ENTRY_E);
	}
	else
	{
		for(int i=0;i<entryList->size();i++)
		{
			temp=entryList->at(i);
			if(temp.find(keyWord))
				matchedEntryList->push_back(temp);
		}
	}
}

void CommandExecutor::updateEntry(vector<string>* entryList, string entry)
{
}

CommandExecutor::CommandExecutor()
{
	//clearStatus();
}

//get the command execution process status
Signal CommandExecutor::getStatus()
{
	return status;
}

//clear the command execusion status to default CLEAR signal
void CommandExecutor::clearStatus()
{
	status = CLEAR;
}

void CommandExecutor::executeCommand(vector <string> * entryList, Signal type, string detail)
{
	vector <string> * matchedEntryList;
	string temp;

	switch (type)
	{
	case ADD_COMMAND:
		{
			addEntry(entryList, detail);
			break;
		}
	case DELETE_COMMAND:
		{
			deleteEntry(entryList, detail);
			break;
		}
	case SEARCH_COMMAND:
		{
			searchEntry(entryList, detail, matchedEntryList);
			for(int i=0;i<matchedEntryList->size();i++)
			{
				temp=matchedEntryList->at(i);
				cout<<i<<" :"<<temp<<endl;
			}
			matchedEntryList->clear();
			break;
		}
	case EDIT_COMMAND:
		{
			updateEntry(entryList, detail);
			break;
		}
	default:
		{
			setStatus(COMMAND_E);
			break;
		}
	}
}

CommandExecutor::~CommandExecutor()
{
}