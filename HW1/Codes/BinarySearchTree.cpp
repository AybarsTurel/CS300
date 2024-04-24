#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "BinarySearchTree.h"


using namespace std;

class BinarySearchTree;


BinarySearchTree::BinarySearchTree() : root(NULL)
{}

void BinarySearchTree::insert(const int & x, const int & y, const string & city)
{
	cityNode node(x,y,city,NULL,NULL,NULL,NULL);
	insert(node, root);
}

void BinarySearchTree::insert(const cityNode & node, cityNode * & r) const
{
	
	if(r == NULL)
	{
		r = new cityNode(node.xCoordinate,node.yCoordinate,node.cityName,NULL,NULL,NULL,NULL);
	}
	else if((r->xCoordinate != node.xCoordinate) || (r->yCoordinate != node.yCoordinate))
	{
		int operation = compare(node,r);
		if(operation == 0) // SW = 0
		{
			insert(node, r->SW);
		}
		else if(operation == 1) // SE = 1
		{
			insert(node, r->SE);
		}
		else if(operation == 2) // NW = 2
		{
			insert(node, r->NW);
		}
		else if(operation == 3) // NE= 3
		{
			insert(node, r->NE);
		}
		//*r = tempRoot;
	}


}

int BinarySearchTree::compare(const cityNode & node,  cityNode * & r)const
{
	cityNode tempRoot = *r;
	int operation;
	
	if(node.xCoordinate < tempRoot.xCoordinate )
	{
		if(node.yCoordinate < tempRoot.yCoordinate)
		{
			operation = 0; // SW
		}
		else
		{
			operation = 2; // NW
		}

	}
	else if(node.yCoordinate < tempRoot.yCoordinate)
	{
		operation = 1;//SE
	}
	else
	{
		operation = 3;//NE
	}
	return operation;
}

void BinarySearchTree::print()
{
	cityNode *tempNode = root;
	
	print(tempNode);
}

void BinarySearchTree::print(cityNode * r) const
{
	
	if(r != NULL)
	{
		cout << r->cityName << endl;
		print(r->SE);
		print(r->SW);
		print(r->NE);
		print(r->NW);
	}

	
		
}

void BinarySearchTree::getParameterSearch(const int & x, const int & y, const int & r)
{
	queryX = x;
	queryY = y;
	radius = r;
}


void BinarySearchTree::printQueryInformation()
{
	cout << "X coordinate: " << queryX << " Y coordinate: " << queryY << " Radius: " << radius << endl;
	//cout << pow(queryX,2) << endl;
}


void BinarySearchTree::boundaryFinder(cityNode * r)
{
	// X value for left boundary
	if(queryX - radius < 0)
	{
		leftBoundary = 0;
	}
	if(queryX - radius > 0)
	{
		leftBoundary = queryX - radius;
	}
	
	//***********
	
	if(queryY + radius > endPointCoordinateY)
	{
		upperBoundary = endPointCoordinateY;
	}
	
	if(queryY + radius < endPointCoordinateY)
	{
		upperBoundary = radius + queryY;
	}

	//***********
	
	if(queryX + radius > endPointCoordinateX)
	{
		rightBoundary = endPointCoordinateX;
	}
	
	if(queryX + radius < endPointCoordinateX)
	{
		rightBoundary = queryX + radius;
	}

	//***********
	
	if(queryY - radius < 0)
	{
		lowerBoundary = 0;
	}
	if(queryY - radius > 0)
	{
		lowerBoundary = queryY - radius;
	}

}
void BinarySearchTree::searchQuery()
{
	searchQuery(root);
}


void BinarySearchTree::searchQuery(cityNode *  r)
{
	
	boundaryFinder(r);

	//cout << leftBoundary << " "  << rightBoundary << " " << upperBoundary << " " << lowerBoundary << endl;
	if(r != NULL)
	{
		if((pow(r->xCoordinate - queryX,2) +  pow(r->yCoordinate - queryY,2)) <= pow(radius,2))
		{
			visitedCities.push_back(r->cityName);
			citiesInRange.push_back(r->cityName);
			searchQuery(r->SE);
			searchQuery(r->SW);
			searchQuery(r->NE);
			searchQuery(r->NW);
		}
		else if((r->xCoordinate <= leftBoundary) && (r->yCoordinate > upperBoundary)) // 1
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SE);
		}
		else if((r->xCoordinate > leftBoundary && r->xCoordinate <= rightBoundary && r->yCoordinate > upperBoundary) || (r->xCoordinate == rightBoundary + radius && r->yCoordinate == upperBoundary)) //2
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SE);
			searchQuery(r->SW);
		}
		else if((r->xCoordinate > rightBoundary) && (r->yCoordinate > upperBoundary) ) //3
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SW);
		}
		else if(r->xCoordinate <= leftBoundary && r->yCoordinate <= upperBoundary && r->yCoordinate > lowerBoundary) //4
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SE);
			searchQuery(r->NE);
		}
		else if((r->xCoordinate > rightBoundary && r->yCoordinate <= upperBoundary && r->yCoordinate >lowerBoundary)||(r->yCoordinate == lowerBoundary + radius && r->xCoordinate == rightBoundary)) //5
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SW);
			searchQuery(r->NW);
		}
		else if((r->xCoordinate <= leftBoundary) && (r->yCoordinate <= lowerBoundary)) //6
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->NE);
		}
		else if(r->xCoordinate > leftBoundary && r->yCoordinate <= lowerBoundary && r->xCoordinate <= rightBoundary)//7
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->NE);
			searchQuery(r->NW);
		}
		else if((r->xCoordinate > rightBoundary) && (r->yCoordinate <= lowerBoundary)) //8
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->NW);
		}
		else if(r->xCoordinate > leftBoundary && r->xCoordinate < rightBoundary - radius && r->yCoordinate <=upperBoundary && r->yCoordinate > lowerBoundary + radius && (pow(r->xCoordinate - queryX,2) +  pow(r->yCoordinate - queryY,2)) > pow(radius,2))//9
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SE);
			searchQuery(r->SW);
			searchQuery(r->NE);
			//searchQuery(r->NW);
		}
		else if( r->xCoordinate > leftBoundary + radius && r->xCoordinate <=rightBoundary && r->yCoordinate <= upperBoundary && r->yCoordinate > lowerBoundary+radius && (pow(r->xCoordinate - queryX,2) +  pow(r->yCoordinate - queryY,2)) > pow(radius,2))//10
		{
			visitedCities.push_back(r->cityName);
			//searchQuery(r->NE);
			searchQuery(r->SE);
			searchQuery(r->SW);
			searchQuery(r->NW);
		}
		else if(r->xCoordinate > leftBoundary && r->xCoordinate < leftBoundary + radius && r->yCoordinate > lowerBoundary && r->yCoordinate < lowerBoundary + radius && ( (pow(r->xCoordinate - queryX,2) +  pow(r->yCoordinate - queryY,2)) > pow(radius,2) ))//11
		{
			if((queryX - radius < 0) && ((double(queryY - r->yCoordinate)/double(queryX - r->xCoordinate)) > 0) ) {//10 
				visitedCities.push_back(r->cityName);
				//searchQuery(r->NE);
				searchQuery(r->SE);
				searchQuery(r->SW);
				searchQuery(r->NW);
				
			}
			else if(queryX - radius < 0 && (double(queryY - r->yCoordinate)/double(queryX - r->xCoordinate)) < 0)
			{
				visitedCities.push_back(r->cityName);
				searchQuery(r->SW);
				searchQuery(r->NE);
				//searchQuery(r->SE);
				searchQuery(r->NW);
			}
			else //11
			{
				visitedCities.push_back(r->cityName);
				searchQuery(r->SE);
				//searchQuery(r->SW);
				searchQuery(r->NE);
				searchQuery(r->NW);
				
			}
				
		}
		else if(r->xCoordinate > leftBoundary + radius && r->xCoordinate <= rightBoundary && r->yCoordinate > lowerBoundary && r->yCoordinate < lowerBoundary + radius && ( (pow(r->xCoordinate - queryX,2) +  pow(r->yCoordinate - queryY,2)) > pow(radius,2) ))//12
		{
			visitedCities.push_back(r->cityName);
			searchQuery(r->SW);
			searchQuery(r->NE);
			//searchQuery(r->SE);
			searchQuery(r->NW);
		}
	
		
		
	}
}


void BinarySearchTree::getEndPointCoordinate(const int & x, const int & y)
{
	endPointCoordinateX = x;
	endPointCoordinateY = y;
}

void BinarySearchTree::printVisitedCities()
{
	for(int i = 0; i < visitedCities.size();i++)
	{
		cout << visitedCities[i];
		if(i != visitedCities.size()-1)
		{
			cout << ", ";
		}
	}
	visitedCities.clear();
}



void BinarySearchTree::printCitiesInRange()
{
	if(citiesInRange.size() == 0)
	{
		cout << "<None>";
	}
	else
	{
		for(int i = 0; i < citiesInRange.size();i++)
		{
			cout << citiesInRange[i];
			if(i != citiesInRange.size()-1)
			{
				cout << ", ";
			}
		}
		citiesInRange.clear();
	}
}

bool BinarySearchTree::notInVector(vector<string> v, string city)
{
	for(int i=0; i < v.size();i++)
	{
		if(city == v[i])
		{
			return true;
		}
	}
	return false;
}
