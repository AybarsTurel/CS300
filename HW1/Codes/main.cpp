#include <iostream>
#include <fstream>
#include <sstream>
#include "BinarySearchTree.h"

using namespace std;

// Sevki Aybars Turel 28238


int main()
{

	int endPointCoordinateX;
    int endPointCoordinateY;
    int startPointCoordinateX = 0;
    int startPointCoordinateY = 0;
    int cityCoordinateX;
    int cityCoordinateY;
	int queryXCoordinate;
	int queryYCoordinate;
	int radius;
	int indexOfComma;
	int indexOfComma2;
	string stringQueryXCoordinate;
	string stringQueryYCoordinate;
	string stringRadius;
    string cityName;
    string line;
	

	BinarySearchTree tree;
	ifstream fileInput;
	ifstream fileInputQueries;
    string fileName = "cities.txt";
    
    fileInput.open(fileName.c_str());
    
    if(fileInput.fail())
    {
        cout << "File cannot be opened!" << endl;
    }
    else
    {
        getline(fileInput, line);
        istringstream input(line);
        input >> endPointCoordinateX >> endPointCoordinateY;
        //cout << endPointCoordinateX << " " << endPointCoordinateY << endl;

        while(getline(fileInput, line))
        {
            istringstream input(line);
            input >> cityName >> cityCoordinateX >> cityCoordinateY;
            //cout << cityName << " " << cityCoordinateX << " " << cityCoordinateY << endl;
			tree.insert(cityCoordinateX,cityCoordinateY,cityName);
        }
		tree.print();
		cout << endl;
		cout << endl;
        
    }

	fileName = "queries.txt";
    
    fileInputQueries.open(fileName.c_str());
    
    if(fileInputQueries.fail())
    {
        cout << "File cannot be opened!" << endl;
    }
    else
    {
		 while(getline(fileInputQueries, line))
        {
            istringstream input(line);
			input >> stringQueryXCoordinate >> stringQueryYCoordinate >> stringRadius;
			
			indexOfComma = stringQueryXCoordinate.find(",");  
			indexOfComma2 = stringQueryYCoordinate.find(",");
			
			stringQueryXCoordinate = stringQueryXCoordinate.substr(0,indexOfComma);
			stringQueryYCoordinate = stringQueryYCoordinate.substr(0,indexOfComma2);
			queryXCoordinate = stoi(stringQueryXCoordinate);
			queryYCoordinate = stoi(stringQueryYCoordinate);
			radius = stoi(stringRadius);

			
			tree.getEndPointCoordinate(endPointCoordinateX,endPointCoordinateY);
			tree.getParameterSearch(queryXCoordinate, queryYCoordinate, radius);
			//tree.printQueryInformation();

			tree.searchQuery();

			tree.printCitiesInRange();
			cout << endl;
	
			tree.printVisitedCities();
			cout << endl;
			cout << endl;
			
			
            //cout << queryXCoordinate << " " << queryYCoordinate << " " << radius << endl;
			
			
        }

	}
	
	


	return 0;
}