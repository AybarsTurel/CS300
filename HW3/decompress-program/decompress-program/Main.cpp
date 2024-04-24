#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "HashTable.h"



using namespace std;

//Sevki Aybars Turel 28238

int main()
{
	vector<int> inputVec; // Since I am getting int, I preferred to hold integers in the vector
	string inputTxt;
	char ch = 'A';
	int a;
	ifstream input("compout.txt"); // given documentation, I added txt because without txt extension VS 2012 does not open folder.
	ofstream output("decompout.txt");


	
	
	while(!input.eof())
	{
			input >> a; // It takes numbers by using spaces.
			if(input.eof())
			{
				break; // It breaks loop. Without this precaution, it prints last number twice.
			}
			inputVec.push_back(a);
			
			
	}
	input.close();






	int code = 0; // This for the code that represents the key for compression.
	HashedObj ITEM_NOT_FOUND(-1,""); // This is for declaration of ITEM_NOT_FOUND.
	HashTable TABLE(ITEM_NOT_FOUND,4096); // This is for creating hash table.


	for(int i = 0; i < 256; i++) // Insertion of all ASCII elements in a hash table.
	{
		string str;
		char chr = char(i);
		str += chr; // Conversion of char to string
		HashedObj forInsertion(code++,str);
		TABLE.insert(forInsertion);
	}

	
	
	
	int i = 0; // counter
	int p = inputVec[i++]; // It takes first element and it is edge case for my algorithm.
	HashedObj temp(p,""); // It creates object for looking certain code in hash table
	HashedObj firstDecode = TABLE.find(temp); // It takes the key by searching code.
	//cout << firstDecode.key;
	output << firstDecode.key; // It writes the first element. It has different line because it is edge case.
	int size = inputVec.size();
	while(i != size) // Until all char in string will be checked
	{   int q = (inputVec[i-1]); // previous code
		p = (inputVec[i++]); // current code
		HashedObj temp(p,""); // current code object
		HashedObj temp2(q,""); // previous code object
		string prevDecoded = TABLE.find(temp2).key; 
		string currDecoded = TABLE.find(temp).key;
		if(TABLE.find(temp).code != ITEM_NOT_FOUND.code && TABLE.find(temp).key != ITEM_NOT_FOUND.key ) // If code is known
		{
			HashedObj temp3(code++,prevDecoded+currDecoded.substr(0,1));
			TABLE.insert(temp3);
			//cout << currDecoded;
			output << currDecoded;
		}
		else // If code is not known
		{
			HashedObj temp3(code++,prevDecoded+prevDecoded.substr(0,1)); 
			TABLE.insert(temp3);
			//cout << temp3.key;
			output << temp3.key;
		}
		
	}
	
	

	
	

	













	return 0;
}