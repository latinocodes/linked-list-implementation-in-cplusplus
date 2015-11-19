void priceChanges(Listing *&first){
	
	Listing *tempPtr, *traversePtr;
	
	int tempMLS[2000],
		newTempMLS[2000],
		index = 0,			// use for indexes for the array
		tempDispInd = 0,
		newCounterToDisp = 0;
		
	double tempCharges[2000],	
			newCharges,
			newTempCharges[2000];
	
	ofstream inFile;
	
	inFile.open(TEMP_FILE.c_str());			
	
	if(!inFile)	//check if exist
	{
		cout <<"Charges File does not exist. " << endl;
		return EXIT_FUNC;
	}
	
	else
	{		
		while(inFile)
		{
			// store the data from file into array
			inFile >> tempMLS[index] >> tempCharges[index];
			index++;
			cout << endl;
		}
		
		inFile.close();		// close file after usage
		
		tempPtr = first;
		while(tempPtr != NULL){
			
			for(int tempIdx = 0; tempIdx <= index; tempIdx++){
				
				// check if listing MLS # match
				if(tempPtr->MLSNumber == tempMLS[tempIdx]){
					
					//check if price match
					if(tempPtr->price != tempPrice[tempIdx]){
							newCharges = tempPrice[tempIdx];
							tempPtr->price = newCharges;
							first->price = newCharges;
							newTempCharges[tempDispInd] = newCharges;
							tempDispInd++;
					} // end of inner if
									
				}	// end of outer if
				
			} // end of for
			
			tempPtr = tempPtr->next;	// go to next item in the list
		
		}
			if(tempDispInd > 0){
					cout << "MLS number" << "		" << "New Asking price" << endl;
					cout << "----------" << "		" << "----------------" << endl;
				
				newCounterToDisp = 0;	// temp index for displaying data to user
				
				while(newTempCharges[tempDispInd] != 0){
					cout << newTempCharges[newCounterToDisp] <<"		" << newTempCharges[newCounterToDisp] << endl;
					newCounterToDisp++;
					
				} // end of while	
			}
			else
				cout << "NO matches were found. " << endl;
			
	}
	
}	// end of priceChanges

