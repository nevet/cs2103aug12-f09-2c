#ifndef SIGNAL_H
#define SIGNAL_H

enum Signal
{
	MASK	= 0xFFFF0000,
	SUCCESS = 0x10000000,
	ERR		= 0x01000000,
	FAIL    = 0x00100000,
	ASK		= 0x00010000,
	CLEAR	= 0x00000000,

//@author a0088455r
//for interpreting commands that is sent drom language handler
	ADD_COMMAND		= 0x00000001,
	DELETE_COMMAND	= 0x00000002,
	EDIT_COMMAND	= 0x00000003,
	SEARCH_COMMAND	= 0x00000004,
	UNDO_COMMAND	= 0x00000005,
	EXIT_COMMAND    = 0x00000006,
	
	DISPLAY_E		= ERR | 0x00000001,
	COMMAND_E		= ERR | 0x00000002,
	OPTION_E		= ERR | 0x00000003,
	LENGTH_X_E		= ERR | 0x00000004,
	LENGTH_Z_E		= ERR | 0x00000005,	
	EMPTY_ENTRY_E	= ERR | 0x00000006,	//for adding empty string
	INDEX_E			= ERR | 0x00000007,
	DATE_E			= ERR | 0x00000008,
	TIME_E			= ERR | 0x00000009,

	ADD_S		= SUCCESS | ADD_COMMAND,
	DELETE_S	= SUCCESS | DELETE_COMMAND,

	ADD_F		= FAIL | ADD_COMMAND,
	DELETE_F	= FAIL | DELETE_COMMAND,
	SEARCH_F	= FAIL | SEARCH_COMMAND,
	UPDATE_F	= FAIL | EDIT_COMMAND,

	DELETE_A	= ASK | DELETE_COMMAND,


	
};

#endif