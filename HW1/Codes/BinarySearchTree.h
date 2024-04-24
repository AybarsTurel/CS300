#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H

#include <vector>
using namespace std;


class cityNode
{
	int xCoordinate;
	int yCoordinate;
	string cityName; 
	cityNode *SW;
	cityNode *SE;
	cityNode *NE;
	cityNode *NW;

	cityNode::cityNode()
	{}

	cityNode::cityNode(const int & x, const int & y, const string & city, cityNode *sw, cityNode *se , cityNode *ne, cityNode *nw) : xCoordinate(x), yCoordinate(y), cityName(city), SW(sw), SE(se), NE(ne), NW(nw)
	{}
	friend class BinarySearchTree;

};


class BinarySearchTree
{
	
	
private:
	vector<string> visitedCities;
	vector<string> citiesInRange;
	int endPointCoordinateX;
    int endPointCoordinateY;
	int operation;
	int radius;
	int queryX;
	int queryY;
	int upperBoundary;
	int rightBoundary;
	int leftBoundary;
	int lowerBoundary;
	cityNode *root;
	void insert(const cityNode & node, cityNode * & r) const;
	int compare(const cityNode & node, cityNode * & r)const;
	void print(cityNode *  r)const;
	void boundaryFinder(cityNode *  r);
	void searchQuery(cityNode *  r);
	bool notInVector(vector<string> v, string city);


public:
	BinarySearchTree();
	void insert( const int & x, const int & y , const string & city);
	void print();
	void printQueryInformation();
	void getParameterSearch(const int & x, const int & y, const int & r);
	void getEndPointCoordinate(const int & x, const int & y);
	void printVisitedCities();
	void printCitiesInRange();
	void searchQuery();
	
};


#endif