//Gary Jenks
//9-15-21 (start)
//Chada tech clock round 2 
//must build a clock that displays both 12hour clock and 24 hour clock
// display a selection menu to take a user choice input
// selection 1-3 choose to add time to either the hour,minute,sec
// selection 4 ends the program
//users will be able to add time to either the hours minutes and seconds 
//---------------------------------------------------------------------
// current bugs or missing features
// 1. does not clear screen
// 
//---------------------------------------------------------------------
// 9/17/21 (turning in) clearing the screen still alludes me,
// the system(CLS) did not seem to work and adding 50 blank lines works but doenst feel right so I left that out 


//===========================================================================
// Includes
#include <iostream>
#include <cstring>
#include <iomanip> //for the set percision
#pragma warning(disable : 4996) //getting this warning trying to use localtime 

using namespace std;




//========================================================================
//Global variables
int hour; // keeps hours
int minutes;// keeps minutes
int seconds;// keeps seconds
int menuSelect;// keep track of the users selection 
int hourAdd;// to keep track of hours added
int minAdd;// to keep track of mins added
int secondAdd;// to keep track of seconds added




//========================================================================
//functions 

// void Menu() is here just to read ut the menu options
void Menu() {
	cout << "Please choose a menu option" << endl << endl;
	cout << "1: Add Hours." << endl;
	cout << "2: Add Minutes." << endl;
	cout << "3: Add Seconds." << endl;
	cout << "4: Quit program." << endl;
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//these functions control the time added
//they flow up by being stacked like this as they call each other when one has extra time

void AdditionalHours(int hoursAdded) { hourAdd += hoursAdded; };

void AdditionalMinutes(int minsAdded) { 
	//local variables to handle excess mins
	int remainderMins = 0;
	int extraHours = 0;
	
	//handles excess mins if the amount added is more than 60 then calls to add to the additional hours function
	if (minsAdded >= 60){
		extraHours = (minsAdded / 60);
		minsAdded = (minsAdded % 60);
		AdditionalHours(extraHours);
		minAdd += minsAdded;
	}
	else { minAdd += minsAdded; };
	
};

//same setup as the one above
void AdditionalSeconds(int secondsAdded) {
	int remainderSecs = 0;
	int extraMins = 0;

	if (secondsAdded >= 60) {
		extraMins = (secondsAdded / 60);
		secondsAdded = (secondsAdded % 60);
		AdditionalMinutes(extraMins);
		secondAdd += secondsAdded;
	}
	else { secondAdd += secondsAdded; };
	
};

//end of time added functions
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$



//used the example set in the video https://www.youtube.com/watch?v=12gm2ceXrt0&list=PLZ9WBSr7mPgl3VYO00MTcE2n_B3Ys6zKU&index=1&t=14s
//found extra documentation at https://www.softwaretestinghelp.com/date-and-time-in-cpp/
void GetTime() {
	time_t ttime = time(0);
	tm* local_time = localtime(&ttime);

	//local variables to help handle excess time
	int tempHour = 0;
	int tempMins = 0;

	hour = local_time->tm_hour + hourAdd;
	//followed a similar method as the time added functions to handle excess time 
	minutes = local_time->tm_min + minAdd;
	if (minutes >= 60) {
		tempHour = (minutes / 60);
		hour = local_time->tm_hour + hourAdd + tempHour;
		minutes = (minutes % 60);

	};

	seconds = local_time->tm_sec + secondAdd;
	if (seconds >= 60) {
		tempMins = (minutes / 60);
		minutes = local_time->tm_min + minAdd + tempMins;
		seconds = (seconds % 60);

	};
}


//This function takes in the 24 time and handles the conversion from 24 to 12 hours
void TwelveHrClock(int &hour, int &minutes, int &seconds) {

	//local variables 
	bool isPM = false;
	string amOrPm = "AM";
	int hour12 = hour;// using this to separate the hour12 out from the hour
	
	//determine AM/PM using a boolean to set the string info
	//**********************************************
		if (hour >= 12) {
			isPM = true;
		}

		if (isPM == true) {
			amOrPm = "PM";
		}
	//************************************************

	//conversions 
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		//catches over 12
		if (hour >= 24) {
			hour12 % 24;
		}
		// catches midnight
		if (hour == 0) {
			hour12 = 12;
		}
		// catches noon
		if (hour12 >= 13) {
			hour12 = hour12 % 12;
		}
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	//final output
	cout << hour12 << ":" << minutes << ":" << seconds << " " << amOrPm << endl << endl;
	
}


// the twenty four hour clock is straight forward so i have it print first
//and then attached the call for the twelve hour clock as well it looks neater i feel with the PM/AM on the end
void TwentyFourHrClock(int &hour, int &minutes, int &seconds) {
	cout << fixed << setprecision(2); //<< setfill('0');
	cout << hour << ":" << minutes << ":" << seconds << " || ";
	TwelveHrClock(hour, minutes, seconds);
}

void Menuselction(int menuSelect) {
	//local variables
	int hourInput = 0, minInput, secInput;

	//cout << menuSelect << endl;
	//begins the if else chain to handle menu selction
	if (menuSelect == 1) {
		cout << "Please input the amount of hours you wish to add: " << endl;
		cin >> hourInput;
		AdditionalHours(hourInput);
		cout << endl;
		//test readout
		/*cout << hourAdd << endl << endl;
		GetTime();
		TwentyFourHrClock(hour,minutes,seconds);*/
	}
	else if (menuSelect == 2) {
		cout << "Please input the amount of minutes you wish to add: " << endl;
		cin >> minInput;
		AdditionalMinutes(minInput);
		cout << endl;
		//test readout
		/*cout << minAdd << endl << endl;
		GetTime();
		TwentyFourHrClock(hour, minutes, seconds);*/
	}
	else if (menuSelect == 3) {
		cout << "Please input the amount of seconds you wish to add: " << endl;
		cin >> secInput;
		AdditionalSeconds(secInput);
		cout << endl;
		//test readout
		/*cout << secondAdd << endl << endl;
		GetTime();
		TwentyFourHrClock(hour, minutes, seconds);*/
	}else if (menuSelect == 4) {
		cout << "Thanks for choosing Chada Tech's Clock" << endl; 
	}
	else {
		cout << "Please only choose between the numbers 1-4" << endl << endl;
		cin.clear();
		cin.ignore(100, '\n');
	};
	

};

//=========================================================================

//**************************************************************************
//Main

int main() {
	hourAdd = 0;
	minAdd = 0;
	secondAdd = 0;
	cout << fixed << setprecision(2);
	cout << "Hello welcome to the clock app" << endl << endl;
	
	do {
		cout << "The current time is set to" << endl;
		GetTime();

		TwentyFourHrClock(hour, minutes, seconds);

		Menu();

		//get users menuselecetion option
		cin >> menuSelect;

		Menuselction(menuSelect);
		
	} while (menuSelect != 4);

}

//**************************************************************************


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! check list
//! // the following is what needs to happen
	// clear screen 
	// //found some documentation https://www.cplusplus.com/articles/4z18T05o/ but hesitant to use system("CLS")
	//  
	// display time in two formats (good 9/16/21)
	// display the menu below it (good 9/15/21)
	// options should be add hour, add minute, add sec(good 9/15/21)
	// get user input for the menu selection (good 9/15/21)
	// do what the user requested
	//		add to hours (good 9/16/21)
	//		add to mins (9/16/21 works but bugged needs to prevent going over 60 and add to hour when it does )
	//		(***********bug fixed handled the excess mins doing the same for seconds*********** 9/16/21)
	//		add to seconds(good 9/16/21)
	// loop back to display menu (9/16/21 works however enters infinite loop if user enters a character instead of int)
	//		(**************bug fixed using cin.clear and cin.ingore(100, '\n')****************** 9/16/21)
	// look for input exit (good 9/16/21)
//! !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!