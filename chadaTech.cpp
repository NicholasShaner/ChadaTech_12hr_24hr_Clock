// chadaTech.cpp

/***************
 *  CS-210 3-3 Project One
 *  chadaTech.cpp
 *
 *  Nicholas Shaner
 *  SNHU
 *  CS-210-R4727
 *  Prof. Cory Thoma
 *  March 24, 2024
 * 
 ***************/

/*
* declaration of inheritance from header file
* allowing use of program functions
*/
#include "chadaTechHeader.h"

// main method to drive program
int main() {

    setTime();  //setTime function call for initial time set by user
    
    /*
    * do/while loop created to allow continual program operation until
    * sentinel value is returned after user command to exit progam
    */
    do {
        dispMenu();
        menuChoice();
        cout << '\n';
        dispClocks();
    } while (appRunning);

return 0;
}

/*
* setTime method definition. takes user input of hours, minutes, seconds 
* and AM/PM and sets global variable value 
*/
void setTime() {
    
    //local variables for handling user input
    char setSeconds;
    bool confirmSet = true;

    cout << "What is the current hour in 12-hour format?\n";
    cin >> twelveHour;  // user input for hours in, in 12-hour format
    cout << "Is this " << twelveHour << " AM or PM?\n";
    /*
    * do/while loop to uppercase and validate user input
    * iterating until user input matches either "AM" or "PM"
    */
    do {
        cin >> AmPm;
        for (int i = 0; i < AmPm.length(); i++) {
            AmPm[i] = toupper(AmPm[i]);
        }
        if (!(AmPm == "AM" || AmPm == "PM")) {
            cout << "Invalid response, please enter AM or PM.\n";
        }
    } while (!(AmPm == "AM" || AmPm == "PM")); 

    /*
    * evalutates hours input and status of AM/PM values to 
    * set matching 24-hour clock time
    */
    if (AmPm == "PM") {
        twentyFourHour = twelveHour + 12;
    }
    else {
        twentyFourHour = twelveHour;
    }
    
    cout << "What is the current minutes?\n";
    cin >> Minutes;
    
    cout << "Would you like to set seconds? (y/n)\n";
    cin >> setSeconds;
    
    /*
    * do/while loop for input validation and processing of 
    * user desire to set seconds or not. If not, sets seconds value to 0.
    * uses local bool variable to break loop
    */
    do {
        if (setSeconds == 'y' || setSeconds == 'Y') {
            cout << "What is the current seconds?\n";
            cin >> seconds;
            break;
        }
        else if (setSeconds =='n' || setSeconds == 'N') {
            seconds = 0;
            confirmSet = false;
        }
        else {
            cout << "I am sorry, please answer 'y' or 'n'\n";
            cout << "Would you like to set seconds? (y/n)? \n";
            cin >> setSeconds;
        }
    } while (confirmSet == true);
}

/*
* menuChoice function to process and validate user menu requests
*/
int menuChoice() {

    int menuChoice;   
    
    cout << "Please enter your selection: \n";
    cin >> menuChoice;

    /*
    * switch used to process evaluate menu choice and call necessary function
    */
    switch (menuChoice) {
        case 1:
            addHour();
            break;
        case 2:
            addMinute();
            break;
        case 3:
            addSecond();
            break;
        case 4:
            cout << "Thank you for using our clock!\n";
            appRunning = false;
            exit(0);
        default:
            cout << "I'm sorry please select from one of the menu items (1 - 4)\n";
            cin >> menuChoice;
    }
}

/*
* addHour funtion to process and evaluate user request to add a hour to the clock.
*/
int addHour(){

    twelveHour += 1;  // incremental statement to add 1-hour per user request
    if (twelveHour == 13) {  // if statement to process 12-hour roll over after 12 o-oclock reached
        twelveHour = 1;
    }

    correctAmPm();  // function call to correct AM/PM as 12-oclock reached

    twentyFourHour += 1;  // increments 24-hour variable value
    if (twentyFourHour == 24) {  // if statement to process rollover as value reaches 24-hour aka midnight
        twentyFourHour = 0;
    }
    return twelveHour;
    return twentyFourHour;
}

/*
* function definition to correct AM / PM during morning and evening shifts. if 12-oclock reached and 
* AmPm value is "AM", then AmPm value is changed to "PM" and visa versa
*/
string correctAmPm() {
    if (twelveHour == 12 && AmPm == "AM") {
        AmPm = "PM";
    }
    else if (twelveHour == 12 && AmPm == "PM") {
        AmPm = "AM";
    }
    else {
        return AmPm;
    }

    return AmPm;
}

/*
* addMinute functions to process user request to add minutes to clock
*/
int addMinute(){
    Minutes += 1;  // increments minutes by 1
    if (Minutes == 60) {  // if statement to process rollover of 60 minutes to the next hour
        Minutes = 0;
        addHour();  // makes function call to addHour if rollover required to add additional hour in response to minutes
    }
    return Minutes;

}

/*
* addSeconds method definition to process user request to add seconds to the clock*/
int addSecond(){
    seconds += 1;  // increments seconds by 1
    if (seconds == 60) {  // if statement to handle rollover of 60 seconds to 1 minute
        seconds = 0;
        addMinute();  // function call to addMinute in respnse to rollover of 1 minute
    }
    return seconds;
}

/*
* function definition to call and display the menu for the user
*/
void dispMenu(){

    cout << "             *************************\n";
    cout << "             * 1 - Add One Hour      *\n";
    cout << "             * 2 - Add One Minute    *\n";
    cout << "             * 3 - Add One Second    *\n";
    cout << "             * 4 - Exit Program      *\n";
    cout << "             *************************\n";
    cout <<"\n\n";
}

/*
* function definition to call and display the current clock time after each user adjustment
*/
void dispClocks() {
    
    cout << "*************************    *************************\n";
    cout << "*     12-Hour Clock     *    *     24-Hour Clock     *\n";
    cout << "*      " << setfill('0') << setw(2) << twelveHour << ":" << setfill('0') << setw(2) << Minutes << ":" << setfill('0') << setw(2) << seconds << "  " << AmPm << "     *    ";
    cout << "*       " << setfill('0') << setw(2) << twentyFourHour << ":" << setfill('0') << setw(2) << Minutes << ":" << setfill('0') << setw(2) << seconds << "        *\n";
    cout << "*************************    *************************\n";
    cout << "\n\n";
}