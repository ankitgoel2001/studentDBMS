// Binary tree abstract base class
// Created by A. Student
// Modified by: Michael Davis
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType, class ItemType2>
class BinaryTree
{
protected:
    BinaryNode<ItemType, ItemType2>* rootPtr;        // ptr to root node
    int count;                            // number of nodes in tree

public:
    // "admin" functions
     BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<ItemType, ItemType2> & tree){ }
    virtual ~BinaryTree()
    {
        destroyTree(rootPtr);
    }
   
    // common functions for all binary trees
     bool isEmpty() const
     {
        return count == 0;
     }
    int getCount() const
    {
       return count;
    }
    void clear()
    {
       destroyTree(rootPtr);
       rootPtr = 0;
       count = 0;
    }
    void inOrder(void visit(ItemType &)) const
    {
       _inorder(visit, rootPtr);
    }
    void printLeaves(void visit(ItemType &)) const
    {
       _printLeaves(visit, rootPtr);
    }
    void printTree(void visit(ItemType &, int)) const
    {
       _printTree(visit, rootPtr, 1);
    }

    // abstract functions to be implemented by derived class
    virtual bool insert(const ItemType& item, const ItemType2& secKey, int compare(const ItemType2& name1, const ItemType2& name2)) = 0;
    virtual bool remove(ItemType& returnedItem, const ItemType2 &data, int compare(const ItemType2& name1, const ItemType2& name2)) = 0;
    //virtual bool search(const ItemType &target, ItemType & returnedItem, int compare(const ItemType2& name1, const ItemType2& name2)) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType, ItemType2>* nodePtr);

    // internal traverse
    void _inorder(void visit(ItemType &), BinaryNode<ItemType, ItemType2>* nodePtr) const;
    void _printLeaves(void visit(ItemType &), BinaryNode<ItemType, ItemType2>* nodePtr) const;
    void _printTree(void visit(ItemType &, int), BinaryNode<ItemType, ItemType2>* nodePtr, int level) const;
   
};

//Destroy the entire tree
template<class ItemType, class ItemType2>
void BinaryTree<ItemType, ItemType2>::destroyTree(BinaryNode<ItemType, ItemType2>* nodePtr)
{
    if(nodePtr) // != NULL
    {
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
        //cout << "DEBUG - Destructor: Now deleting " << nodePtr->getItem().getName() << endl;
        delete nodePtr;
    }
}

//Inorder Traversal
template<class ItemType, class ItemType2>
void BinaryTree<ItemType, ItemType2>::_inorder(void visit(ItemType &), BinaryNode<ItemType, ItemType2>* nodePtr) const
{
    if (nodePtr) // != NULL
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

//Prints the leaves of the tree
template<class ItemType, class ItemType2>
void BinaryTree<ItemType, ItemType2>::_printLeaves(void visit(ItemType &), BinaryNode<ItemType, ItemType2>* nodePtr) const
{
    if (nodePtr) //if node is not null
    {
       if (nodePtr->isLeaf()) // if node is a leaf
       {
          //Print node
          ItemType item = nodePtr->getItem();
          visit(item);
       }
       else
       {
          if (nodePtr->getLeftPtr()) //if left child exist
          {
             _printLeaves(visit, nodePtr->getLeftPtr()); //run recursivly with left
          }
          
          if (nodePtr->getRightPtr()) //if right child exist
          {
             _printLeaves(visit, nodePtr->getRightPtr()); //run recursivly with right
          }
       }
    }
}

//Prints tree as an indented list
template<class ItemType, class ItemType2>
void BinaryTree<ItemType, ItemType2>::_printTree(void visit(ItemType &, int), BinaryNode<ItemType, ItemType2>* nodePtr, int level) const
{
   if (nodePtr) // != NULL
   {
      ItemType item = nodePtr->getItem();
      visit(item, level); //Root
      _printTree(visit, nodePtr->getRightPtr(), level + 1); //Right
      _printTree(visit, nodePtr->getLeftPtr(), level + 1); //Left
   }
}

#endif


