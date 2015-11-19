//**************************************************************************************************************************************
//	CODE FILENAME:	LaraAssign6.cpp
//
//	DESCRIPTION:	This program will store the home listing for a local realtor association to keep tracks of homes
//					for sale in the area. the data is base on the MLS Number, asking price, the status: whether available,
//					sold, or contract. the zipcode, and the realtor company.
//					This program will prompt user to make selection whether to read data from file, or to work with
//					new data. A menu will be display to guide the user for selection.
//
//	CLASS/TERM:	CS362 - Data Structure / 14F8W1
//
//	DESIGNER:	Jose Lara
//
//		Functions:	Main Function.
//					Header				- Give program discription to the user.
//					Menu				- Main Menu of choices.
//					ReadData 			- read the data from file LISTING.txt.
//					ValidateHomeStatus	- use to validate the integer value of the home status to string.
//					DisplayListing		- displays the current data that the user is working whether from the file or user input.
//					DeleteListing		- will delete from the record, the MLS# enter by the user.
//					SaveDataToFile		- stores the new data onto file (file name must be enter by user).
//					ZipCodeInput 		- checks for the user input of data to ensure is entered in correct format.
//					AddListing			- will add new listing records enter by the user.
//					ExitProgram			- Exits the progam from the menu of choices.
//					isEmpty				- checks if the list is empty or not.
//					DisplayMLSList		- Displays the list of MLS to make selections to.
//					PriceChanges		- Opens file to compare prices changes from the file and the data on the listing.
//					MakeChanges			- Function to make changes to Existing Listings.
//                  CheckIfFileExist	- checks if a current file exits.
//					PromptForFile		- Prompts for the name of file to read data or to save data.
//**************************************************************************************************************************************
#include <iostream>     // Header is to access the cin and cout objects.
#include <iomanip>      // use for setw() func
#include <string>		// Header for String usage
#include <fstream>		// ifstream and oftream in readData function and SaveDataToFile function
#include <cctype>		// use for isdigit(), toupper()

using namespace std;	// this is to avoid the std prefix when writting the code.

// home status
enum HOME_STATUS{AVAILABLE, CONTRACT, SOLD};

//Global variables
const int 	EXIT_FUNC = 1,			// exits the program from function
			MAX_ARRAY = 2000,		// Maximun of data hold for arrays in PriceChanges function
			EXIT_SUCCESSFUL = 5,	// use to exit from loop in read data function
			EXIT_PROGRAM = -5;		// use to exit from read data function if the file doesn't exist

const string TEMP_FILE = "CHARGES.TXT";	// name of File to be use in PriceChanges function;

// home listing Data
struct ListingRec{
	int 	MLSNumber,
			status;

	double	price;

	string 	zipCode,
			realtyCompany;

	ListingRec *next;		// creates a pointer of ListingRec
};

// functions prototype
void Header();
char Menu(ListingRec *first);
string PromptForFile();
int ReadData(ListingRec *&first, ListingRec *&last, string nameOfFile);
void DeleteListing(ListingRec *&first, int MLSToDel, bool &success);
void AddListing(ListingRec *&first);
void DisplayListing(ListingRec *&first);
void SaveDataToFile(ListingRec *&first);
bool isEmpty(ListingRec *first);
void ValidateHomeStatus(int num, string& valueStatus);
int ZipCodeInput(string target, int& intVar);
int ExitProgram();
bool CheckIfFileExist(string& name);
void DisplayMLSList(ListingRec *&first);
int PriceChanges(ListingRec *&first);
int MakeChanges(ListingRec *&first);

//**************************************************************************************************************************************
//	Function Name:	Main Function
//
//	Description:	prompt user to make selection whether to read data from file, or to work with new data.
//					a menu will be display to guide the user for selection. Utilizing loops and Switch statements to make selection.
//
//		Functions:	ReadData - read the data from file LISTING.txt.
//					ValidateHomeStatus - use to validate the integer value of the home status to string.
//					Display - displays the current data that the user is working whether from the file or user input.
//					DeleteRecord - will delete from the record, the MLS# enter by the user.
//					SaveDataToFile - stores the new data onto the LISTING.txt file
//					ZipCodeInput - checks for the user input of data to ensure is entered in correct format.
//					AddData - will add new listing records enter by the user.
//
//			output: After the user make selection it will display the results to the screen. if the input is
//					enter incorrectly, it will reprompt the user to enter again.
//
//				return value:	A return statement of 0 for program to finish corrently.
//
//***********************************************************************************************************************
int main()		// Main Function
{
	string nameOfFile;			// holds name of file to read data from
	bool success;				// use to check if MLSNumber in the list was deleted correctly.

	char	choice, 			// holds menu choices selection from the user
			ch, 				// holds choice to save data before exiting program
			tempChar,			// holds user selection to re-enter new file name to be read or not
			Sel;				// holds user selection to load data from file

	int MLSToDel,				// MLS number to be deleted from the list
		valueInt, 				// use to exit loop before exiting program
		tempReadData;			// holds return value from readData function if file is not found

	ListingRec *first = NULL;	// hold temp first node list value
	ListingRec *last = NULL;	// hold temp last node list value

	// Display program header description
	Header();

	do
	{
		// prompt to load data from file.
		cout << "Do you want to load existing data from File (Y/N): ";
		cin >> Sel;
		cout << endl;

	} while(toupper(Sel) != 'Y' && toupper(Sel) != 'N');

	if(toupper(Sel) == 'Y')	{

		nameOfFile = PromptForFile();		// prompt for the file name to read data from

		if(!nameOfFile.empty())				// check that file is not empty
		{
            tempReadData = ReadData(first, last, nameOfFile);
		}	// end of if

	}	// end of outter if

	// re-prompt the user to enter a correct file name or menu
	while((tempReadData == 1) || toupper(tempChar) == 'T'){

			tempReadData = 0;	// changed temp to exit loop if M is press

			cout << "\nPress T - To Try Another File Name. " << endl;
			cout << "Press M - For Main Menu. " << endl;
			cout << "Pick: ";
			cin >> tempChar;

			// re-prompt for new file name
			if(toupper(tempChar) == 'T') {
					nameOfFile = PromptForFile();
					tempReadData = ReadData(first, last, nameOfFile);

			} // end of if

	} //  end of while

	do
	{
		choice = Menu(first);			// Display Menu to user

		switch(toupper(choice))			// verify choice from menu
		{
			case 'A':					// Add new Listing Function

				do{
					AddListing(first);
					cout << "Do you want to Add another listing (Y/N): ";
					cin >> ch;

				}while(toupper(ch) == 'Y');	// continue adding other listing until user says no

				break;						// break for case A

			case 'D':

				DisplayListing(first);		// display listing function
				break;						// break for case D

			case 'R':

				DisplayMLSList(first);		// display list of MLS numbers

				cout << "Please Enter MLS # to be Deleted: ";
				cin >> MLSToDel;

				DeleteListing(first, MLSToDel, success);	// remove listing function

				if(success){
					cout << endl << "MLS # " << MLSToDel << " was deleted Successfully." << endl;
				}

				break;						// break for case R

			case 'C':

				MakeChanges(first);			// function to make changes to listing
				break;						// break for case C

			case 'E':

				if(!isEmpty(first))			// check if list is empty
				{
					cout << "You are about to exit the Program. Do you want to Save the Data (Y/N): ";
					cin >> ch;

						if(toupper(ch) == 'Y'){
							SaveDataToFile(first);	// save data to file
						}
						else
							cout << "Data Was not Save! " << endl;
				}

				valueInt = ExitProgram();	// exit program function
				break;						// break for case E

			default:
				break;
		}	// end of switch

	} while(choice != 'E' && valueInt != EXIT_PROGRAM);

	cout << endl << endl;
	return 0;	// finishes the program.

}	// end of main

//************************************************************************************************************************************
//	Function Name:	Header.
//	Description:	Discription of the program.
//
//		Parameters: None.
//
//				output:	Displays description of program to user.
//
//************************************************************************************************************************************
void Header(){
	// description to user.
	cout << setw(55) << "Program to Store Home Listings. " << endl << endl;

} // end of Header

//************************************************************************************************************************************
//	Function Name:	Menu.
//	Description:	Display Menu to user to make selection.
//
//		Parameters:
//				input:	first	-	A link list of record.
//
//				output:	Displays Main Menu of choice to user.
//
//************************************************************************************************************************************
char Menu(ListingRec *first)
{
	char choice;		// hold menu choice

	cout << endl;
	cout << "Please Select from the Following Choices: " << endl;
	cout << "Press: A - To Add new Listing." << endl;
	cout << "Press: D - To display Listing." << endl;

	if(!isEmpty(first))		// display only if list is not empty
	{
		cout << "Press: R - To remove a Listing." << endl;

	}
	cout << "Press: C - To make Changes to Listing." << endl;
	cout << "Press: E - To Exit Program." << endl;

	cin >> choice;
	cout << endl;

	return choice;

} // end of menu

//************************************************************************************************************************************
//	Function Name:	PromptForFile.
//	Description:	Ask the user if the want to load the data from file
//
//		Parameters: None.
//
//				output:	Ask the user if the want to load the data from file, if the choice is yes. It ask for the name of file.
//						the file name is pass as return statement to the calling Function.
//
//************************************************************************************************************************************
string PromptForFile() {

	string  nameOfFile;		// name of file to be search

	cin.ignore();			// clear cin buffer

	cout << "Please Enter Name of File (eg. LISTING.TXT): ";
	getline(cin, nameOfFile);
	cout << endl;

	return nameOfFile;

}	// end of PromptForFile

//************************************************************************************************************************************
//	Function Name:	ReadData.
//	Description:	Ask the user if the want to load the data from file
//
//	parameters:
//		input:	first 		- first Element of the linked list created to be pass to other functions.
//				last 		- will store the last element of the list created from the file.
//				nameOfFile	- it acepts the name of file to read the data from.
//
//			ouput:
//				first 		- first Element of the linked list created to be pass to other functions.
//				last 		- will store the last element of the list created from the file.
//
//		output:	passes the file data to other function for its usage
//************************************************************************************************************************
int ReadData(ListingRec *&first, ListingRec *&last, string nameOfFile){

	// temporary variables
	int 	tempMLSNumber,
            tempstatus;

	double	tempprice;

	string 	tempzipCode,
            temprealtyCompany;

	ListingRec  *newNode;	// nodes to be created

	first = NULL;			// make first node point to nothing

	ifstream inFile;		// stream use to read the data from the file.

	inFile.open(nameOfFile.c_str());	// open file

	// prompt to create new record
	if(!inFile)
	{
		inFile.clear();	// clears buffer if name of File does not exist
		cout << "File does not Exist. " << endl << endl;
		return EXIT_FUNC;
	}

	else
	{
		// check if the file exist but there is no data
		if(inFile.eof())
		{
			cout << "There is no data in the file. Exiting program." << endl;
			return EXIT_FUNC;
		} // end of if

		while(inFile && newNode != NULL)
		{
            inFile >> tempMLSNumber >> tempprice >> tempstatus >> tempzipCode;   //Priming read
            getline(inFile, temprealtyCompany);

			// allocate a memory for new node
			newNode = new (nothrow) ListingRec;

 			// check that memory can be allocated
			if(newNode == NULL)
			{
				cout << "Error: Cannot allocate anymore memory." << endl;
			} // end of if

			else {
				// use of temp variables to store data in the list
                newNode->MLSNumber = tempMLSNumber;
                newNode->price = tempprice;
                newNode->status = tempstatus;
                newNode->realtyCompany = temprealtyCompany;
                newNode->zipCode = tempzipCode;
                newNode->next = NULL;

                if (first == NULL){
                    last = newNode;
                    first = newNode;
               	 } // end of if

				else {
                	if(!inFile.eof()){			// if end of file do not allocate more memory
	                	last->next = newNode;
	                    last = newNode;
                	}

                }	// end of else

            } // end of outter else

		} // end of while

		DisplayListing(first);	// Display Data after read from file
		PriceChanges(first);    // Compare data from store in the list with PriceChanges file

	}	// end of outter else

    return 1;

} // end of ReadData

//***********************************************************************************************************************
//	Function Name:	DeleteListing.
//	Description:	deletes a listing record base on the MLSNumber enter by the user.
//
//	parameters:
//		input:	MLSToDel 	- listing number to be deleted from list.
//				first 		- first Element of the linked list to search MLSToDel.
//				last 		- will store the last element of the list.
//
//		this function will display messages whether the listing was deleted or was not found to the user.
//************************************************************************************************************************
void DeleteListing(ListingRec *&first, int MLSToDel, bool &success){

	ListingRec 	*here,					// node being checked
				*prev;					// node prior to node being checked

	success = false;					// MLS not Found

	if(isEmpty(first)){				// check if the list is empty or not
		cout << "List is Empty. " << endl;
		ExitProgram();
	}
	else
	{
		// check if the item is the first element
		if(first->MLSNumber == MLSToDel) {
			here = first;
			first = first->next;
			delete here;
			success = true;

		}	// end of if

		else
		{
			prev = first;			// node prior to node being checked
			here = first->next; 	// node being checked

			// look for the item to be deleted (while not end of list and number not found)
			while((here != NULL) && (here->MLSNumber != MLSToDel)){
				prev = here;
				here = here->next;
			} // end of while

			if(here != NULL){
				prev->next = here->next;
				delete here;
				success = true;
			}
			else
				cout << endl << "MLS # " << MLSToDel << " not found in list." << endl;

		} // end of else

	} // end of outter else

} // end of DeleteListing

//***********************************************************************************************************************
//	Function Name:	AddListing.
//	Description:	Creates new Listing of Homes.
//
//	parameters:
//		input:	first	- if there is an existing list.
//
//		output:	Displays if the listing was added succefully. it also displays error checking messages to verify
//				entry from the user.
//***********************************************************************************************************************
void AddListing(ListingRec *&first){

	int exitValue = 0; // used to exit from

	char selection; // stores selection for home status

	bool stat;	// use to exit condition for home status

	ListingRec *newNode; // new node to be added to the list

	newNode = new (nothrow) ListingRec;	// allocates memory for new listing

	// Prompt user for data
	cout << "Please Enter MLS#, must be 6 digits number: ";
	cin >> newNode->MLSNumber;

	// check MLS# is six digits
	while(newNode->MLSNumber < 100000 || newNode->MLSNumber > 999999) {
		cout << "Invalid Entry! Please Enter MLS#, must be 6 digits number: ";
		cin >> newNode->MLSNumber;
	}

	// Prompt for home price
	cout << "Please Enter Home Price: ";
	cin >> newNode->price;
	cout << endl;

	do{
		// prompt for home status
		cout << setw(4) << "A - AVAILABLE" << endl;
		cout << setw(4) << "C - CONTRACT" << endl;
		cout << setw(4) << "S - SOLD" << endl;
		cout <<"Please Select from the above Home Statuses: ";
		cin >> selection;
		cout << endl;

		// check selection
			switch(selection){
				case 'a':
				case 'A':
					newNode->status = AVAILABLE;
						stat = true;
					break;
				case 'c':
				case 'C':
					newNode->status = CONTRACT;
						stat = true;
					break;
				case 's':
				case 'S':
					newNode->status = SOLD;
						stat = true;
					break;
				default:
					cout << "Wrong Choice. try again." << endl;
					stat = false;
					break;
			}; // end of switch

	}	while(stat == false);	// end of do while

	// prompt for zip code input
	cout << "Please Enter Home's zipcode: ";
	getline(cin, newNode->zipCode);

	// check for correct zipcode again
	ZipCodeInput(newNode->zipCode, exitValue);

		// if not correct prompt until corrected zipcode is enter
		while(exitValue != EXIT_SUCCESSFUL)
		{
			getline(cin, newNode->zipCode);
			ZipCodeInput(newNode->zipCode, exitValue);
			cout << endl;

		}	// end of while

	// prompt for realty Company;
	cout << "Enter Realty Company: ";
	getline(cin, newNode->realtyCompany);
	cout << "\nListing Added Successfully. " << endl;

	// creates a new node
	newNode->next = first;
	first = newNode;

} // end of AddListing

//***********************************************************************************************************************
//	Function Name:	Display.
//	Description:	displays the list of listing to the user.
//
//	parameters:
//		input:	first - passes the begining of the linked list.
//				last - passes the end of the link list.
//
//		output:	displays the existing data list to the user, either from the file or user input.
//************************************************************************************************************************
void DisplayListing(ListingRec *&first){

	int num;				// stores value of home status to be use in ValidateHomeStatus Function
	string valueStatus;		// gets the value of home status and displays it in string type to the screen
	ListingRec *tempPtr;	// temporary pointer use to traverse the list

	// check if the list is empty
	if(isEmpty(first))
		cout << "The List is Empty. " << endl;

	else
	{
		// display header of listing
		cout << "	 "<< "Asking" <<"	  " << "Listing" << endl;
		cout << "MLS#" << "	 " << "Price" << "	  "<< "Status" << "     " << "Zip Code" << "    " << "Realtor" << endl;
		cout << "------" << "   " << "-------" << "  " << "--------" << "   " << "----------" << "  " << "--------" << endl;

		tempPtr = first;	// start reading for the begining of the list

		// read data until the end of the list
		while(tempPtr != NULL){
			num = tempPtr->status;

			ValidateHomeStatus(num, valueStatus);		// convert home status into string
			cout << left << setw(9) << tempPtr->MLSNumber << setw(9) << tempPtr->price << setw(11) << valueStatus
			<< setw(12) << tempPtr->zipCode << setw(15) << tempPtr->realtyCompany << endl;

			tempPtr = tempPtr->next;

		}	// end of while

	} // end of else

} // end of DisplayListing

//***********************************************************************************************************************
//	Function Name:	SaveDataToFile.
//	Description:	save data from the linked list to file of user's choice.
//
//	parameters:
//		input:	first - the entire list is pass to be save.
//
//			ouput:	it prompt user for name of file to be enter, if file exist, then it prompts the user to override
//					existing file.
//
//		output:	stores the listing record to file name entered by user.
//************************************************************************************************************************
void SaveDataToFile(ListingRec *&first){

	ofstream outFile;		// stream use to save data to file

	string nameOfFile;		// to prompt user to enter name of file to be save

	ListingRec *tempPtr;	// temp listing to traverse the list
	char ch;				// use to check if the user wants to override existing file or not

	// if there is no data in the list
	if(isEmpty(first))
		cout << "There is no data to be save. List is Empty." << endl;

	else{

		cin.ignore();	// clear cin buffer

		// prompt to enter the name of file to be save
		cout << "Please Enter name of File to store Data (eg. FILENAME.txt): ";
		getline(cin, nameOfFile);

		// if the file does not exist
		if(!CheckIfFileExist(nameOfFile))
		{
			cout << "File Created. " << endl;
			outFile.open(nameOfFile.c_str());	// open file
		}

		// if file exist prompt user they are about to override existing file
		else
		{
			outFile.open(nameOfFile.c_str());	// open file
			cout << "You are about to override the data from file Name: " << nameOfFile << endl;
			cout << "Do you want to continue (Y/N): ";
			cin >> ch;
			toupper(ch);

				// if  not override, program will exit without saving data
				if (ch == 'N')	{
					cout << "Data was not save! " << endl;
					outFile.close();
					ExitProgram();
				}

			cout << "Data was Save! " << endl;

		}	// end if

		tempPtr = first;	// temporary pointer to traverse the list

		// write in the list in the file until reaches the last element
		while(tempPtr != NULL)
		{
			outFile << tempPtr->MLSNumber<< " " << tempPtr->price << " " << tempPtr->status << " " << tempPtr->zipCode
					<< " " << tempPtr->realtyCompany << endl;
			tempPtr = tempPtr->next;

		}	//  end of while

	}	// end of else

	// close file
	outFile.close();

} // end of SaveDataToFile

//************************************************************************************************************************************
//	Function Name:	isEmpty.
//	Description:	Checks if the list is empty or not.
//
//		Parameters:	None.
//
//************************************************************************************************************************************
bool isEmpty(ListingRec *first)
{
	if(first == NULL)
		return true;
	else
		return false;

} // end of isEmpty

//************************************************************************************************************************
//	Function Name:	ValidateHomeStatus.
//	Description:	validates the status of the home, it converts the integer home status to string to output to user.
//
//	parameters:
//		input:	num - gets the integer value to be converted to string.
//
//			ouput:
//				valueStatus - returns the string value of the proper integer association to the home listing.
//
//		output:	passes the string value to display the enum type base on the integer value of the home.
//************************************************************************************************************************
void ValidateHomeStatus(int num, string& valueStatus){

	// checks for validation of home status, converts int value to string to display to screen
	switch (num) {
		case AVAILABLE:	// variable from enum Home_Status
			valueStatus = "AVAILABLE";
			break;
		case CONTRACT:	// variable from enum Home_Status
			valueStatus = "CONTRACT";
			break;

		case SOLD:	// variable from enum Home_Status
			valueStatus = "SOLD";
			break;

		default:
			break;
		}

} // end of ValidateHomeStatus

//*************************************************************************************************************************
//	Function Name:	ZipCodeInput.
//	Description:	validates the entry of zipcode and enforces proper format.
//
//	parameters:
//		input:	target - the string to be verify.
//
//			ouput:
//				intVar - if the zipcode was enter correct, this variable passes the ok to the caling function
//						 to continue with data entry.
//
//		output:	prompts user to reenter the zipcode and displays an example format to user.
//*************************************************************************************************************************
int ZipCodeInput(string target, int& intVar)
{

	int firstFiveDigits = 0,		// for the first 3 digits number
		secondFourDigits = 0;		// send 3 digit after first dash

	    // Step through the user input to see if it matches
	    for (int index = 0; index < target.length(); index++)
	    {
	    	// check the first 5 digits of the zipcode
	    	while (firstFiveDigits < target[4]){
	    		isdigit(target[index]);

	    		// if number is not of type int display wrong zipcode
		    	if(!isdigit(target[index])){
					cout << "\nZipCode " << target << " is formatted incorrectly." << endl;
					cout << "10 characters must formatted as: #####-####" << endl;
					return EXIT_FUNC;

		    	} // end of if

		    	firstFiveDigits++;	// increase counter to keep reading digits

		    }	// end of while

		    isprint(target[5]);		// see if there is a dash after area code

		    // if the next character is not a dash display wrong number
	    	if (target[5] != '-'){
					cout << "\nZipCode " << target << " is formatted incorrectly." << endl;
					cout << "10 characters must formatted as: #####-####" << endl;
					return EXIT_FUNC;

			} // end of if

			// continue reading the phone number
			while((secondFourDigits >= target[6]) && (secondFourDigits < target[11])){
				isdigit(target[index]);

				// if number is not of type int display wrong phone
		    	if(!isdigit(target[index]) || (secondFourDigits > target[11])){
					cout << "\nZipCode " << target << " is formatted incorrectly." << endl;
					cout << "10 characters must formatted as: #####-####" << endl;
					return EXIT_FUNC;

		    	}	// end of if

		    	secondFourDigits++;	// increase counter in the second set of 3 digits

			} // end of while

			intVar = EXIT_SUCCESSFUL;
		} // end of for

    return 1;

} // end of ZipCodeInput verification

//*************************************************************************************************
//	Function Name:	ExitProgram.
//	Description:	Function Exits the program early when the user prompts to.
//
//		Parameters: None.
//*************************************************************************************************
int ExitProgram(){
	cout << "Exiting program. " << endl;
	return EXIT_PROGRAM;

} // end of ExitProgram Func

//*************************************************************************************************
//	Function Name:	CheckIfFileExist.
//	Description:	Function to verify if file name exist before saving data.
//
//		Parameters: name of file to be pass by reference by the calling function.
//
//			outputs: a return statement whether or not the file exist.
//*************************************************************************************************
bool CheckIfFileExist(string& name) {

    ifstream file(name.c_str());	// try to open file

    if (file.good()) {		// check if the file exist
        file.close();
        return true;
    }
	else {					// if there is no file
        file.close();
        return false;
    }
}	// end of CheckIfFileExist

//*************************************************************************************************
//	Function Name:	DisplayMLSList.
//	Description:	Function to Display the list of MLS from the list to make selection by user.
//
//		input:
//			first - the entire list is pass to read read the MLS from the entire list.
//
//			outputs: the list of MLS numbers for the user to make selection.
//*************************************************************************************************
void DisplayMLSList(ListingRec *&first)
{

	ListingRec *tempPtr;	// temp variable to traverse the list

	int counter = 0,		// to keep track of the data in the list
		itemPerRow = 9;		// displays number of the MLS per row

	tempPtr = first;		// read from the beginning of the list

	cout << "\nPlease Select a MLS# from one of the following: " << endl;

	while(tempPtr != NULL){

		for (int row = 0; row <= counter; row++)	// display the data in rows of 4 listing
		{
			cout << tempPtr->MLSNumber << " ";
			tempPtr = tempPtr->next;	// continue reading the next item in the list

			if(row == itemPerRow){
				cout << endl;		// go to next line to keep displaying
			}

			if(tempPtr != NULL)
				counter++;
		}
		cout << endl << endl;

	}	// end of while


}	// end of DisplayMLSToBeDel

//*************************************************************************************************
//	Function Name:	PriceChanges.
//	Description:	Function to compare the prices of homes in the linked list and the file.
//
//		input:
//			first - the entire list is pass to read read the MLS from the entire list.
//
//			outputs: the list of MLS numbers and the new listing prices that were changed if any.
//*************************************************************************************************
int PriceChanges(ListingRec *&first)
{

	ListingRec 	*tempPtr; 				// temporary pointer for list

	int tempMLS[MAX_ARRAY],				// array to hold MLS listing from file
		newTempMLS[MAX_ARRAY],			// array to hold prices for MLS listing from file
		index = 0,						// use for indexes for the array
		tempDispInd = 0;				// Keeps track of size of the array

	double	tempCharges[2000],			// array to hold charges from file
			newCharges = 0;				// stores the new charges

	ifstream inFile;					// stream to read data from file

	inFile.open(TEMP_FILE.c_str());		// open file

	if(!inFile)	//check if exist
	{
		cout <<"Charges File does not exist. " << endl << endl;
		return EXIT_FUNC;
	}

	else
	{
		while(inFile)
		{
			// store the data from file into array
			inFile >> tempMLS[index] >> tempCharges[index];
			index++;
		}

		inFile.close();		// close file after usage

		tempPtr = first;	// point to the beginning of the list and loop until done

		while(tempPtr != NULL){

			for(int tempIdx = 0; tempIdx <= index; tempIdx++){

				// check if listing MLS # match
				if( tempMLS[tempIdx] == tempPtr->MLSNumber){

					//check if price match
					if(tempPtr->price != tempCharges[tempIdx]){

						if((tempCharges[tempIdx] < 0) || (tempCharges[tempIdx] > 0)){		// if there are changes in price

							newCharges = (tempPtr->price) + (tempCharges[tempIdx]);
							tempPtr->price = newCharges;
							first->price = newCharges;
							tempCharges[tempIdx] = newCharges;
							tempDispInd++;

						} // end of if


					} // end of inner if

				}	// end of outer if

			} // end of for

			tempPtr = tempPtr->next;	// go to next item in the list

		}
			// Display all MLS and price changes from file
			if(tempDispInd > 0){
					cout << endl;
					cout << "MLS number" << "	" << "New Asking price" << endl;
					cout << "----------" << "	" << "----------------" << endl;

				for(int count = 0; count <= tempDispInd; count++){
					cout << tempMLS[count] <<"		" << tempCharges[count] << endl;
					count++;

				} // end of while
			}
			else
				cout << "\nNO matches were found from Charges File. " << endl;

	}

    return 1;

}	// end of priceChanges

//*************************************************************************************************************
//	Function Name:	MakeChanges.
//	Description:	Function to make changes to listing. user can make any type of changes to the listing.
//
//		input:
//			first - the entire list is pass to read read the MLS from the entire list.
//
//			outputs: the list of MLS numbers and menu of choices to make changes to those listings, it will
//					 prompt the user to continue changes until user exit.
//*************************************************************************************************************
int MakeChanges(ListingRec *&first){


	ListingRec *tempPtr;		// temp pointer to access the list

	int tempMLSNumber,			// holds temporary MLS
		tempStatus,				// holds temporary status
		exitValue = 0;			// use to verify if zipCode was enter correctly in ZipCodeVerification Function

	char tempChar;				// holds selection for new home status

	string 	tempZipCode,		// holds temporary zipCode to be change
			tempRealtyComp;		// holds temporary realty Company to be change

	char 	choice,				// selection for item to be change from listing
			Selection;			// check with user to see if the want to make any other changes

	double tempPrice;			// holds temporary price to be change

	tempPtr = first;			// make temporary pointer point to beginning of list

	bool	changed = false,	// use if data was change successfully
			flag = false;		// use to find MLS listing

	if(isEmpty(first))			// Display if list is empty (will exit function if true)
	{
		cout << "List is Empty. " << endl;
		return EXIT_FUNC;
	}

	DisplayMLSList(first);			// Call function to display MLS Listings

	cout << "MLS # : ";				// prompt user for MLS to make changes to
	cin >> tempMLSNumber;
	cout << endl;

		// look for the item to be deleted (while not end of list and number not found)
		while(tempPtr != NULL){

			if(tempPtr->MLSNumber == tempMLSNumber){
				flag = true;
			}

			tempPtr = tempPtr->next;

		} // end of while

	if(!flag)
		cout << endl << "MLS # " << tempMLSNumber << " not found in list." << endl;

	if(!isEmpty(first) && (flag))						// if list is not empty and MLS # enter is in the list
	{

		do
		{
			tempPtr = first;							// point to the beginning of the list again

			// Menu of choices to make changes
			cout <<"\nPlease Select item to be change: " << endl;
			cout <<"Press L - for MLS Number. " << endl;
			cout <<"Press P - for price. " << endl;
			cout <<"Press S - for Status." << endl;
			cout <<"Press Z - for zip code." << endl;
			cout <<"Press R - for Realty Company." << endl;
			cin >> choice;
			cout << endl;

				switch(toupper(choice)){
					case 'L':
						while(tempPtr != NULL)			// look for listing to change
						{
							if(tempPtr->MLSNumber == tempMLSNumber) {
								cout << "Enter new MLS #: ";
								cin >> tempMLSNumber;

									// validate MLS to be 6 Digits
									while(tempPtr->MLSNumber < 100000 || tempPtr->MLSNumber > 999999) {
										cout << "Invalid Entry! Please Enter MLS#, must be 6 digits number: ";
										cin >> tempPtr->MLSNumber;
									}

								tempPtr->MLSNumber = tempMLSNumber;			// make changes to MLS number
								changed = true;

							}	// end of if

							tempPtr = tempPtr->next;						// go to next item in the list

						}	// end of while

						if(changed)
							cout << "MLS Number for MLS # " << tempMLSNumber << " Updated sucessfully. " << endl;

						break;	// break for case L

					case 'P':
						while(tempPtr != NULL)								// look for listing to change
						{
							if(tempPtr->MLSNumber == tempMLSNumber) {
								cout << "Enter new Price: ";
								cin >> tempPrice;

								tempPtr->price = tempPrice;					// Make changes to price
								changed = true;

							}	// end of if

							tempPtr = tempPtr->next;						// go to next item in the list

						}	// end of while

						if(changed)
							cout << "Price for MLS # " << tempMLSNumber << " Updated sucessfully. " << endl;

						break;	// break for case P

					case 'S':
						while(tempPtr != NULL)								// look for listing to change
						{
							if(tempPtr->MLSNumber == tempMLSNumber)
							{
								cout << "Select New Status:  " << endl;
								cout << "C - Contract. " << endl;
								cout << "A - Available. " << endl;
								cout << "S - Sold. " << endl;
								cin >> tempChar;

								if(toupper(tempChar) == 'A'){
									tempPtr->status = AVAILABLE;			// Make changes to status
								}// end of if

								if(toupper(tempChar) == 'C'){
									tempPtr->status = CONTRACT;				// Make changes to status
								}// end of if

								if(toupper(tempChar) == 'S'){
									tempPtr->status = SOLD;					// Make changes to status
								} // end of if

								changed = true;

							}	// end of if

							tempPtr = tempPtr->next;						// go to next item in the list

						}	// end of while

						if(changed)
							cout << "Status for MLS # " << tempMLSNumber << " Updated sucessfully. " << endl;

						break;	// break for case S

					case 'Z':
						while(tempPtr != NULL)								// look for listing to change
						{
							if(tempPtr->MLSNumber == tempMLSNumber)
							{
								cin.ignore();
								cout << "Enter new Zip Code: ";				// prompt user for zipcode to be change
								getline(cin, tempZipCode);

								ZipCodeInput(tempZipCode, exitValue);		// validate zipCode entry

								while(exitValue != EXIT_SUCCESSFUL)
								{
									getline(cin, tempZipCode);
									ZipCodeInput(tempZipCode, exitValue);
									cout << endl;

								}	// end of while

								tempPtr->zipCode = tempZipCode;				// make changes to zip Code
								changed = true;

							}	// end of if

							tempPtr = tempPtr->next;						// go to next item in the list

						}	// end of while

						if(changed)
							cout << "Zip Code for MLS # " << tempMLSNumber << " Updated sucessfully. " << endl;

						break;	// break for case Z

					case 'R':
						while(tempPtr != NULL)								// look for listing to change
						{
							if(tempPtr->MLSNumber == tempMLSNumber)
							{
								cin.ignore();
								cout << "Enter new Realty Company: ";		// prompt for company name to be change
								getline(cin, tempRealtyComp);

								tempPtr->realtyCompany = tempRealtyComp;	// make changes to realty company
								changed = true;

							}	// end of if

							tempPtr = tempPtr->next;						// go to next item in the list

						}	// end of while

						if(changed)
							cout << "Realty Company for MLS # " << tempMLSNumber << " Updated sucessfully. " << endl;

						break;	// break for case R

					default:
						break;

				} // end of switch

			cout << "Do You want to make any other Changes (Y/N): ";		// prompt to make additional changes
			cin >> Selection;
			cout << endl;

		}while(toupper(Selection) == 'Y'); 			// end of do while

	} // end of else

    return 1;

}	// end of MakeChanges Function
