// Specification file for the Hash class
// Written By: A. Student
// Changed by: Ankit Goel


#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "HashNode.h"
#include <iostream>

using namespace std;

template<class ItemType>
class HashTable
{
private:
    HashNode<ItemType>* hashAry;
    int hashSize;
    int count;

public:
    HashTable() { count = 0; hashSize = 53; hashAry = new HashNode<ItemType>[hashSize]; }
    HashTable(int n)    { count = 0; hashSize = n;    hashAry = new HashNode<ItemType>[hashSize]; }
    ~HashTable(){ delete [] hashAry; }

    int getCount() const    { return count; }
    int getSize() const { return hashSize; }
    double getLoadFactor() const {return 100.0 * count / hashSize; }
    bool isEmpty() const    { return count == 0; }
    bool isFull()  const    { return count == hashSize; }

    bool insert( const ItemType &itemIn, int h(const ItemType &key, int size) );
    bool remove( ItemType &itemOut, ItemType &key, int h(const ItemType &key, int size));
    int  search( ItemType &itemOut, string &key, int h(const ItemType &key, int size));
    /*friend ostream &operator<< (ostream &on, const HashTable& object)
    {
        on << left;
        on << object.hashAry  << endl;
    }*/
    void display();
    int getTotalCollisions();
    int getMaxCollisions();

};

/*~*~*~*
   Insert an item into the hash table
   It does not reject duplicates
*~**/
template<class ItemType>
bool HashTable<ItemType>::insert( const ItemType &itemIn, int h(const ItemType &key, int size) )
{
    if ( count == hashSize)
        return false;

   /* Write your code here */
   int bucket = h(itemIn, hashSize);
   int bucketsProbed = 0;

   while (bucketsProbed < hashSize)
   {
      if (hashAry[bucket].getItem().getID() == "")
         {
            hashAry[bucket].setItem(itemIn);
            hashAry[bucket].setNoCollisions(bucketsProbed);
            count++;
            return true;
         }
      bucket = (bucket + 1) % hashSize;

      bucketsProbed++;
   }
    return true;
}

/*~*~*~*
   Removes the item with the matching key from the hash table
     - copies data in the hash node to itemOut
     - replaces data in the hash node with an empty record
*~**/
template<class ItemType>
bool HashTable<ItemType>::remove( ItemType &itemOut, ItemType &key, int h(const ItemType &key, int size))
{
 /* Write your code here */
    int bucket = h(key, hashSize);
    int bucketsProbed = 0;

    while(key.getID() != "" && bucketsProbed < hashSize)
    {
       if (hashAry[bucket].getItem() == key)
       {
           itemOut = hashAry[bucket].getItem();
           ItemType s;
           hashAry[bucket].setItem(s);
           count--;
           return true;
       }
       bucket = (bucket + 1) % hashSize;
       bucketsProbed++;
    }
    return false;
}

/*~*~*~*
   hash search - linear probe
   if found:
      - copy data to itemOut
      - returns the number of collisions for this key
   if not found, returns -1
*~**/
template<class ItemType>
int HashTable<ItemType>::search(ItemType &itemOut, string &key, int h(const ItemType &key, int size))
{
   /* Write your code here */
   int bucket = h(key, hashSize);
   int bucketsProbed = 0;
   int coll = 0;

   while (key != "" && bucketsProbed < hashSize)
   {
      if (hashAry[bucket].getItem().getID() == key)
      {
         itemOut = hashAry[bucket].getItem();
         return coll;
      }

      bucket = (bucket + 1) % hashSize;
      coll++;
      bucketsProbed++;
   }
    return -1;
}

/*
  Function to display the entire hash array
  table which will be saved to the output file
*/
template<class ItemType>
void HashTable<ItemType>::display()
{
    for (int i = 0; i < hashSize; i++)
    {
        if (hashAry[i].getItem().getID() != "")
            cout << hashAry[i].getItem() << endl;
    }
}

/*
 Function to display the total number of collisions
 int the hash array
*/
template<class ItemType>
int HashTable<ItemType>::getTotalCollisions()
{
    int coll = 0;

    for (int i = 0; i < hashSize; i++)
        coll += hashAry[i].getNoCollisions();

    return coll;
}

/*
 Function to get the maximum number collisions
 in the hash array
*/
template<class ItemType>
int HashTable<ItemType>::getMaxCollisions()
{
    int max_coll = 0;

    for (int i = 0; i < hashSize; i++)
    {
        if (hashAry[i].getNoCollisions() > max_coll)
             max_coll = hashAry[i].getNoCollisions();
    }

    return max_coll;
}
#endif // HASHTABLE_H_
