#include <iostream>
#include <vector>
#include <string>
#include "HashTable.h"

using namespace std;


int Hash(const HashedObj & o, int arraySize)
{
	string value = o.key;
	int hashedKey = 0;
	for(int i = 0; i < value.size(); i++)
	{
		hashedKey += value[i];
	}
	return hashedKey / arraySize;
}


class HashTable;

HashTable::HashTable( const HashedObj & notFound, int size ): ITEM_NOT_FOUND( notFound ), array( size )
{
    makeEmpty( );
}

void HashTable::makeEmpty()
{
	for(int i = 0; i < array.size(); i++)
	{
		HashEntry current = array[i];
		(current.element).code = -1; 
		(current.element).key = "";
		current.info = EMPTY;
		array[i] = current;
	}
}



int HashTable::findPos( const HashedObj & x ) const
{
           
	int p = Hash(x, array.size()); // current position

	while( array[p].info != EMPTY && array[p].element != x ) // It compares hashed object according to key values, it uses overloaded operations.
	{

         p += 1;  // add the difference

		 if( p >= array.size( ) )  
		 {
			  p -= array.size(); 
		 }						// perform the mod
                                     // if necessary
    }
    return p;
}

bool HashTable::isActive( int currentPos ) const
{
     return array[ currentPos ].info == ACTIVE;
}

void HashTable::remove( const HashedObj & x )
{
     int currentPos = findPos( x );

	 if( isActive( currentPos ) )
	 {
		 array[ currentPos ].info = DELETED;
	 }
}


const HashedObj & HashTable::find( const HashedObj & x ) const
{
	int currentPos = findPos( x );

	if (isActive( currentPos )) 
	{
		 return array[ currentPos ].element; 
	}
    return   ITEM_NOT_FOUND;
}

void HashTable::insert( const HashedObj & x )
{
            // Insert x as active
	int currentPos = findPos( x );

    if( isActive( currentPos ) )
	{
		 return;
	}
    array[ currentPos ] = HashEntry( x, ACTIVE );

   
}

bool operator==(const HashedObj &lhs, const HashedObj &rhs)
{
	return(lhs.key == rhs.key);
}

bool operator!=(const HashedObj &lhs, const HashedObj &rhs)
{
	return(lhs.key != rhs.key);
}



