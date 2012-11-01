#include "UI.h"

void UI::setScreenSize()
{
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	//SMALL_RECT windowSize = {5, 5,windowsHeight, windowsWidth};

	COORD buffer={0,0};
	SetConsoleScreenBufferSize(hConsole,buffer);
//	SetConsoleWindowInfo(hconsole, TRUE, &windowSize);
}

void UI::drawBanner()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	cout<<"                ____  ____                _____                                 ";
	cout<<"                \\  \\\\/  //                |   \\\\                                ";
	cout<<"                 \\  \\\" //                 |    \\\\                               ";
	cout<<"                  \\   // ____  __ __  ____| |\\ || ____ __  ___                  ";
	cout<<"                   | || /   \\\\| || ||| _//| |/ ||/   ||\\ \\/ //                  ";
	cout<<"                   | || | O ||| |/ ||| || |    //| o || \\  //                   ";
	cout<<"                   |_|| \\___// \\__// |_|| |___// \\___|| /_//                    ";
	cout<<"                                                                                ";
}

void UI::drawCommandBox()
{
	gotoxy(0,commandInitY);
	SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY|FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
	cout<<"command:                                                                        ";
	cout<<endl;
	gotoxy(8,commandInitY);
}

void UI::setBackground()
{
	 SetConsoleTextAttribute(hConsole,  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void UI::clearBox(int startH, int height)
{
	setBackground();
	gotoxy(0,startH);
	for (int i=0; i<height; i++)
		for (int j=0; j<windowsWidth; j++)
			cout<<" ";
	gotoxy(0,startH);
}

void UI :: gotoxy(int x, int y) //goes to x,y console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UI::writeTitle(string words, int startX, int startY)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
		FOREGROUND_RED | FOREGROUND_GREEN);
	gotoxy(startX,startY);

	cout<<words<<endl;
}


void UI::changeFocusedField()
{
	switch (focusedField)
	{
	case GENERAL:
		focusedField = CALENDAR;
		break;
	case CALENDAR:
		focusedField = DIDUKNOW;
		break;
	case DIDUKNOW:
		focusedField = GENERAL;
		break;
	default:
		break;
	}
}

void UI::scrollUp(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	switch (focusedField)
	{
	case GENERAL:
		if (generalInitRowIndex > 0)
		{
			generalInitRowIndex --;
			clearBox(generalInitY, generalBoxHeight);
			generalEntryListDisplay(generalEntryList);
			drawCommandBox();
		}
		break;
	case CALENDAR:
		if (calendarInitRowIndex > 0)
		{
			calendarInitRowIndex --;
			clearBox(calendarInitY, calendarBoxHeight);
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex > 0)
		{
			diduknowInitRowIndex --;
			clearBox(diduknowInitY, bottomBoxHeight);
			diduknowBoxListDisplay(diduknowBoxList);
			drawCommandBox();
		}
		break;
	default:
		break;
	}
}

void UI::scrollDown(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	int generalSize = generalEntryList->size();
	int calendarSize = calendarEntryList->size();
	int diduknowSize = diduknowBoxList->size();

	switch (focusedField)
	{
	case GENERAL:
		if (generalInitRowIndex < generalSize -1)
		{
			generalInitRowIndex ++;
			clearBox(generalInitY, generalBoxHeight);
			generalEntryListDisplay(generalEntryList);
			drawCommandBox();
		}
		break;
	case CALENDAR:
		if (calendarInitRowIndex < calendarSize -1)
		{
			calendarInitRowIndex ++;
			clearBox(calendarInitY, calendarBoxHeight);
			calendarEntryListDisplay(calendarEntryList);
			drawCommandBox();
		}
		break;
	case DIDUKNOW:
		if (diduknowInitRowIndex < diduknowSize -1)
		{
			diduknowInitRowIndex ++;
			clearBox(diduknowInitY, bottomBoxHeight);
			diduknowBoxListDisplay(diduknowBoxList);
			drawCommandBox();
		}
		break;
	default:
		break;
	}
}

void UI::traceInput(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	char keyIn;
	input = "";

	while ((keyIn = getch()) != ENTER)
	{
		switch (keyIn)
		{
		case -32:
			keyIn = getch();
			switch (keyIn)
			{
			case 72:
				scrollUp(calendarEntryList, generalEntryList, diduknowBoxList);
				break;
			case 80:
				scrollDown(calendarEntryList, generalEntryList, diduknowBoxList);
				break;
			}
			break;
		case TAB:
			changeFocusedField();
			break;
		case BACKSPACE:
			if (input.size()>0)
			{
				input = input.substr(0, input.size()-1);
				cout << "\b \b";
			}
			break;
		default:
			if (keyIn != ENTER)
			{
				cout << keyIn;
				input += keyIn;
			}
			break;
		}
	}
}

void UI::coloredDisplayFormattedString(int index, string row)
{
	string part = "";
	int colorArray[6] = {INDEX_COLOR, DESCRIPTION_COLOR, LOCATION_COLOR, TIME_COLOR, DATE_COLOR, PRIORITY_COLOR};
	int countColor = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countColor]);

	if (row[0] == '#' && row[1] == '#')		//for search result, the index of result in the entry list is added to result string,
	{										//so don't need to display index in the diduknowBoxList
		cout<<" "<<index<<". ";
	}

	for (int i = 1; i<row.size(); i++)
	{
		if (row[i] != '#' )
		{
			part += row[i];
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colorArray[countColor]);
			countColor++;
			if (countColor != 2 || part.size() <= maxCharDetail)
				{
					cout <<  part;
				}
			else
			{
				cout <<part.substr(0, maxCharDetail) << "...";
			}
			part = "";
			if ((i !=row.size()-1)&&(i != 1))
			{
				cout << "\t";
			}
		}
		
	}
	cout<<endl;
	
}

void UI::generalEntryListDisplay(vector<string>* generalEntryList)
{
	int sizeOfGeneral;
	int terminateIndex;
	string row;

	gotoxy(generalInitX, generalInitY);
	sizeOfGeneral=generalEntryList->size();
	
	terminateIndex = min (sizeOfGeneral, generalInitRowIndex + generalBoxHeight);
	
	for (int i = generalInitRowIndex; i< terminateIndex; i++)
	{
		row = generalEntryList ->at(i);
		coloredDisplayFormattedString(i+1, row);
	}
}

void UI::calendarEntryListDisplay(vector<string>* calendarEntryList)
{
	int sizeOfCalendar;
	int terminateIndex;
	string row;

	gotoxy(calendarInitX, calendarInitY);
	sizeOfCalendar=calendarEntryList->size();
	terminateIndex = min (sizeOfCalendar, calendarInitRowIndex + calendarBoxHeight);

	for (int i = calendarInitRowIndex; i< terminateIndex; i++)
	{
		row = calendarEntryList ->at(i);
		coloredDisplayFormattedString(i+1, row);
	}
}

void UI::diduknowBoxListDisplay(vector<string>* diduknowBoxList)
{
	int sizeOfDiduknow;
	int terminateIndex;
	string row;

	gotoxy(diduknowInitX, diduknowInitY);
	sizeOfDiduknow=diduknowBoxList->size();
	terminateIndex = min(sizeOfDiduknow, diduknowInitRowIndex + bottomBoxHeight);
	
	for (int i = diduknowInitRowIndex; i< terminateIndex; i++)
	{
		row = diduknowBoxList ->at(i);
		coloredDisplayFormattedString(i+1, row);
	}
}

void UI::startingScreenDisplay()
{
	system("CLS");
	
	drawBanner();
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED |15 );
	cout<<"--------------------------------------------------------------------------------";
	cout<<"|                    YourDay - always making your day :)                       |";
	cout<<"--------------------------------------------------------------------------------";
	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(30,18);
	cout<<"Press Enter to continue";
	getchar();
}

void UI::mainScreenDisplay(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	setBackground();
	system("CLS");

	writeTitle("General: ", 0,0);
	writeTitle("Calendar: ", 0, calendarInitY -2);

	generalEntryListDisplay(generalEntryList);
	calendarEntryListDisplay(calendarEntryList);
	diduknowBoxListDisplay(diduknowBoxList);
	
	drawCommandBox();
}

UI::UI()
{
	input = "";
	focusedField = GENERAL;

	startingScreenDisplay();
}

void UI::userInteract(vector<string>* calendarEntryList, vector<string>* generalEntryList, vector<string>* diduknowBoxList)
{
	int generalTemp = generalEntryList->size() - generalBoxHeight;
	int calendarTemp = calendarEntryList->size() - calendarBoxHeight;
	int diduknowTemp = diduknowBoxList->size() - bottomBoxHeight;
	generalInitRowIndex = max(0, generalTemp);
	calendarInitRowIndex = max(0, calendarTemp);
	diduknowInitRowIndex = max(0, diduknowTemp);

	mainScreenDisplay(calendarEntryList, generalEntryList, diduknowBoxList);
	traceInput(calendarEntryList, generalEntryList, diduknowBoxList);
}

string UI::retrieveInput()
{
	return input;
}

UI::~UI()
{
}