/**
    YourDay
    LangHandler.h
    Purpose: Calculates the total of 6 checks

    @author a0088455R
    @version 0.1 10/13/2012
*/
#ifndef LANGHANDLER_H
#define LANGHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <map>
#include <ctime>
#include <cassert>

#include "Signal.h"

#include "StatusHandler.h"
#include "StorageHandler.h"

#include "Executor.h"
#include "AddExecutor.h"
#include "DeleteExecutor.h"
#include "SearchExecutor.h"
#include "UpdateExecutor.h"
#include "ExitExecutor.h"

#include "Log.h"


using namespace std;

class LangHandler
{
private:

	StatusHandler sh;
	
	Log log;

	Signal command;
	Signal langStatus;

	string details;

	const static int MONTH[12];

	const static char SPACE_BAR;
	const static char DELIMINATOR;
	const static char PRIORITY_INDICATOR;
	
	const static string ADD_MARK_INDICATOR;
	const static string LOCATION_INDICATOR;
	const static string NULL_STRING;
	const static string UPDATE_MARK_INDICATOR;
	const static string UPDATE_UNMARK_INDICATOR;

	bool isLeap(int year);
	bool isDate(string date);
	bool isTime(string time);
	bool isInt(string inx);
	bool isLogicDate(string date);
	bool isLogicTime(string time);

	string getSuffix(string str, int pos);
	string getPrefix(string str, int pos);

	void splitPriority(string* str, string* priority) throw (string);
	void splitLocation(string* str, string* location) throw (string);
	void splitIndex(string* str, string* index) throw (string);
	void splitDate(string* str, string* date) throw (string);
	void splitTime(string* str, string* time, string* date) throw (string);
	void splitDescription(string* str, string* description) throw (string);

	void fillUpDate(string* date);

	void regulateDate(string* date);
	void regulateTime(string* time);
	void regulateLocation(string* location);
	void regulateDescription(string* description);

	/**
	* This operation is used to eliminate leading and trailing spaces of a
	* string.
	* 
	* @param str
	*			is the string needs to be spaces-freed
	*/
	void eliminateSpaces(string* str);

	/**
	* Encodes the raw string into the correct saving format
	*
	* @param input
	*			is a raw string that needs to be encoded
	* @param command
	*			is the command type
	* @return encoded string, format of the string is:
	* 
	* #index#description#location#time#date#priority#
	*
	* index:
	*		this field contains index information required by delete and update
	*		functions.
	* description:
	*		this field contains description of the task required by add, search
	*		and update functions.
	* location:
	*		this field contains location information required by add and search
	*		functions.
	* time:
	*		this field contains time information required by add and search
	*		functions.
	* date:
	*		this field contains date information required by add and search
	*		functions.
	* priority:
	*		this field contains priority information required by add and search
	*		functions.
	*		
	* Note that some fields are not necessarily required. However, if one field
	* if not required for a certain function, that field should not be OMITTED.
	*
	* e.g
	*
	* userInput = "add CS2103 TUT at COM on Friday"
	* encoded	= "##CS2103 TUT#COM##Friday##"
	*
	* explaination:
	*
	* since index field, time field and priority field are missing,
	* corresponding fields should be left as "blank".
	*
	* userInput = "delete 1"
	* encoded	= "#1######"
	*
	* explaination:
	*
	* only index field is specified, so other fields should be "blank".
	*/
	void encoder(string input, Signal command) throw (string);

	//@author A0088455R
	/**
	* This operation will set command type using userCommand. If userCommand
	* took from the user is invalid, COMMAND_E Signal will be set.
	*/
	void setCommand(string userCommand);

public :
	
	LangHandler();

	/**
	* Signals will be:
	* SUCCESS		User input has been successfully proceeded;
	* Exception signals threw by separate
	*/
	Signal getStatus();

	//@author A0088455R
	/**
	* Seperates user input's string into 2 parts, the command and the
	* encoded string.
	*
	* User command will be stored in private string userCommand;
	* Details info will be stored in private string details
	* 
	* e.g
	*
	* userInput = "add CS2103 tutorial at COM1";
	* return = {userCommand = "add", detials = "#CS2103 tutorial#COM1##"}
	* 
	* userInput = "delete 1";
	* return = {userCommand = "delete", details = "#1###"}
	*
	* details about format of encoded string can be found in encoded().
	*/
	void separate(string userInput) throw (string);

	/**
	* This operation will pack up an specific executor w.r.t user's command
	*/
	Executor* pack(bool* quit, Signal focusingField,
							   vector<string>* generalEntryList, 
							   vector<string>* calendarEntryList,
							   vector<string>* resultList,
							   StorageHandler* store);

	~LangHandler();
};


#endif