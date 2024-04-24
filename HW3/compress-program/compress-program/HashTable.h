#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <vector>
using namespace std;

class HashedObj // It is the node that will hold key and code in hash table.
{
	
	public:
		int code;
		string key;
	HashedObj::HashedObj(){}

	HashedObj::HashedObj(const int & c, const string & k) : code(c),key(k)
	{}
	friend class HashTable;
};


class HashTable // Taken from lecture slied
{
	public:
        explicit HashTable( const HashedObj & notFound, int size = 4096 );
		HashTable( const HashTable & rhs ): ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
        array( rhs.array ), currentSize( rhs.currentSize ) { }

        const HashedObj & find( const HashedObj & x ) const;

        void makeEmpty( );
        void insert( const HashedObj & x );
        void remove( const HashedObj & x );

		

        enum EntryType { ACTIVE, EMPTY, DELETED };
			
		private:

            struct HashEntry
            {
                HashedObj element;
                EntryType info;

                HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };
			
            
            vector<HashEntry> array;
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;
			int hashedKey;
            bool isActive( int currentPos ) const;
            int findPos( const HashedObj & x ) const;
            void rehash( );
        };


bool operator==(const HashedObj & lhs, const HashedObj &rhs); // operation overload

bool operator!=(const HashedObj &lhs, const HashedObj &rhs);  // operation overload



#endif