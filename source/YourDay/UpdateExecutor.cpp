#include <cassert>

#include "UpdateExecutor.h"

UpdateExecutor::UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details, Signal focusingField)
{
	assert(details!="");
	assert(generalEntryList!=NULL);
	assert(calendarEntryList!=NULL);
	assert(focusingField!=GENERAL || focusingField!=CALENDAR);

	switch (focusingField)
	{
		case GENERAL:
			_focusingEntryList = generalEntryList;
			_undoFocusingEntryList = *generalEntryList;

			break;

		case CALENDAR:
			_focusingEntryList = calendarEntryList;
			_undoFocusingEntryList = *calendarEntryList;

			break;

		default:
			break;
	}

	_details = details;
}

void UpdateExecutor::execute()
{
	int index;
	string oldEntry, newEntry;
	string newDate, newTime, newDescription, newPriority, newLocation;
	string oldDate, oldTime, oldDescription, oldPriority, oldLocation;

	vector<string>::iterator position;

	index=extractIndex(_details);
	
	if(index < 1)
	{
		throw string ("index is not existing\n");
	}
	else if(index > (_focusingEntryList->size()))
	{
		throw string ("index is larger than list size\n");
	}
	else 
	{
		oldEntry = _focusingEntryList->at(index-1);

		newDate = extractDate(_details);
		oldDate = extractDate(oldEntry);
		if(newDate == "")
		{
			newEntry = "#" + oldDate ;
		}
		else
		{
			newEntry = "#" +newDate;
		}

		newTime = extractTime(_details);
		oldTime = extractTime(oldEntry);
		if(newTime == "")
		{
			newEntry = newEntry + "#" + oldTime;
		}
		else
		{
			newEntry = newEntry + "#" + newTime;
		}

		newDescription = extractDescription(_details);
		oldDescription = extractDescription(oldEntry);
		if(newDescription == "")
		{
			newEntry = newEntry + "#" + oldDescription;
		}
		else
		{
			newEntry = newEntry + "#" + newDescription;
		}

		newLocation = extractLocation(_details);
		oldLocation = extractLocation(oldEntry);
		if(newLocation == "")
		{
			newEntry = newEntry + "#" + oldLocation;
		}
		else
		{
			newEntry = newEntry + "#" + newLocation;
		}

		newPriority = extractLocation(_details);
		oldPriority = extractLocation(oldEntry);
		if(newPriority == "")
		{
			newEntry = newEntry + "#" + oldPriority + "#";
		}
		else
		{
			newEntry = newEntry + "#" + newPriority + "#";
		}
		position = _focusingEntryList->begin() + index - 1;
		_focusingEntryList->erase(position);

		position = _focusingEntryList->begin() +index -1;
		_focusingEntryList->insert(position,newEntry);

		status = UPDATE_S;
	}
}

void UpdateExecutor::undo()
{
	*_focusingEntryList = _undoFocusingEntryList;
}