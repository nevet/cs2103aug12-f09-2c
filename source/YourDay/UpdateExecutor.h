#ifndef UPDATEEXECUTOR_H
#define UPDATEEXECUTOR_H

#include <vector>
#include "Executor.h"

using namespace std;
//@author A0091734A
class UpdateExecutor : public Executor
{
private:
	vector<string>* _focusingEntryList;
	vector<string>* _generalEntryList;
	vector<string>* _calendarEntryList;

	vector<string> _undoFocusingEntryList;

	Signal _focusingField;
	string _details;

public:
	UpdateExecutor(vector<string>* generalEntryList, vector<string>* calendarEntryList, string details, Signal focusingField);

	void execute();
	void undo();
};

#endif