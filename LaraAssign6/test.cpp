
#include <iostream>     // Header is to access the cin and cout objects.
#include <iomanip>      // Header is for output manipulation.
#include <string>		// Header for String usage

using namespace std;	// this is to avoid the std prefix when writting the code.

int main()		// Main Function
{


	int numArr[5] = {31, 22, 44, 97, 100};
	int *ptr = numArr;
	ptr += 3;
	int *ptr2 = &numArr[3];
	
	ptr2--;
	
	cout << *ptr2 << endl;
	
	cout << *ptr << endl;


	cout << endl << endl;
	return 0;	// finishes the program.

}

