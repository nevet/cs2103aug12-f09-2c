#ifndef SIGNAL_H
#define SIGNAL_H

enum Signal
{
	MASK	= 0xFFFF0000,
	SUCCESS = 0x10000000,
	ERR		= 0x01000000,
	FAIL    = 0x00100000,
	DISPLAY	= 0x00010000,
	CLEAR	= 0x00000000,

	GENERAL			= DISPLAY | 0x00000001,
	CALENDAR		= DISPLAY | 0x00000002,
	DIDUKNOW		= DISPLAY | 0x00000003,
	DISPLAY_ALL		= DISPLAY | 0x00000004,
	DISPLAY_PART	= DISPLAY | 0x00000005,
	DIDUKNOW_INIT	= DISPLAY | 0x00000006,
	DIDUKNOW_CLEAR	= DISPLAY | 0x00000007,

//for interpreting commands that is sent drom language handler
	ADD_COMMAND		= 0x00000001,
	DELETE_COMMAND	= 0x00000002,
	EDIT_COMMAND	= 0x00000003,
	SEARCH_COMMAND	= 0x00000004,
	UNDO_COMMAND	= 0x00000005,
	EXIT_COMMAND    = 0x00000006,
	NULL_COMMAND    = 0x00000007,

	ADD_S_G		= SUCCESS | 0x00000001,
	ADD_S_C		= SUCCESS | 0x00000002,
	DELETE_S_G	= SUCCESS | 0x00000003,
	DELETE_S_C	= SUCCESS | 0x00000004,
	UPDATE_S_G	= SUCCESS |	0x00000005,
	UPDATE_S_C  = SUCCESS | 0x00000006,
};

#endif