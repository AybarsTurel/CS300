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
	
	string inputTxt; // It stores whole char in file into string.
	char ch = 'A';
	ifstream input("compin.txt"); // given documentation, I added txt because without txt extension VS 2012 does not open folder.
	ofstream output("compout.txt");
	while(!input.eof())
	{
			input.get(ch);
			if(input.eof()) // It prevents to write selected char again when input get EOF. 
			{
				break; // Loop will terminated immedately when input encounters with EOF.
			}
			inputTxt += ch; 
		
	}
	input.close();

	int code = 0; // This for the code that represents the key for compression.
	HashedObj ITEM_NOT_FOUND(-1,""); // for declaration of ITEM_NOT_FOUND.
	HashTable TABLE(ITEM_NOT_FOUND,4096); //for creating hash table.


	for(int i = 0; i < 256; i++) // Insertion of all ASCII elements in a hash table.
	{
		string str;
		char chr = char(i);
		str += chr; // Conversion of char to string
		HashedObj forInsertion(code++,str);
		TABLE.insert(forInsertion);
	}

	int i = 0; // counter; i will store the index of char lastly visited.
	string p = inputTxt.substr(0,1); // longest prefix; p will store the longst prefix that is in hash table.
	int size = inputTxt.size();
	while(i != size) // Until all char in string will be checked
	{
		string n = inputTxt.substr(i+1,1); // recently checked char
		string all = p + n; // all string that includes prefix and currently checked char
		HashedObj allObj(-1,all); // it creates hash object to check string all in the hash table
		if(TABLE.find(allObj).code != ITEM_NOT_FOUND.code && TABLE.find(allObj).key != ITEM_NOT_FOUND.key ) // It will be checked whether all string key in the table or not.
		{
			p = all; // Updated p with longest prefix which is in the hash table
		}
		else // If it is not in table
		{
			HashedObj temp(code++,all); // Creating object that will be insert into hash table
			HashedObj temp1(-1,p); // It is used to find the latest code for p string.
			int hashCode = TABLE.find(temp1).code;
			//cout << hashCode << endl;
			output << hashCode << " ";
			TABLE.insert(temp);
			p = n; // We will get rif of from prefix and start new search by adding char n.
		}
		i++;
		
	}
	HashedObj temp1(-1,p);
	int hashCode = TABLE.find(temp1).code;
	//cout << hashCode << endl; 
	output << hashCode << " ";// This is for edge case because after while loop is finished we were not able to write latest prefix.
	return 0;
}