/**
* @author a00194847U
*/
#include <iostream>
#include <string>
#include "UIHandler.h"
#include "Signal.h"
#include "FunctionHandler.h"
using namespace std;

#define EXIT_SUCCESS 0

/**
* Main() is the over all work flow controller. It knows UIHandler and
* FunctionHandler. It repeatedly calls UIHandler to handler the user input and
* then pass the input to FunctionHandler to handle. If any error happens,
* main() will ask UIHandler to handle the feedback issue.
*/

int main()
{
	//recording general entries
	vector<string> generalEntryList;
	//recording calendar entries
	vector<string> calendarEntryList;
	//recording did-u-know box entries
	vector<string> diduknowBoxList;
	
	FunctionHandler function(&generalEntryList, &calendarEntryList, &diduknowBoxList);
	UIHandler ui;

	//terminating indicator, should be false at the beginning
	bool quit=false;

	ui.startingScreenDisplay();

	//saved entries should be displayed on the screen at the beginning
	ui.mainScreenDisplay(&generalEntryList);

	while (!quit)
	{
		ui.getInput();
		//for debugging using
		ui.setStatus();
		string userInput = ui.retrieveInput();

		function.execute(userInput, &quit, &generalEntryList, &calendarEntryList, &diduknowBoxList);

		Signal signal = function.getStatus();

		//display updated entries
		ui.mainScreenDisplay(&generalEntryList);
		//display updated did-u-know box list, e.g search resut
		ui.displayMessage(&diduknowBoxList);
		//display caught signals
		ui.displayMessage(signal);
	}

	function.saveData(&generalEntryList, &calendarEntryList, &diduknowBoxList);

	return EXIT_SUCCESS;
}