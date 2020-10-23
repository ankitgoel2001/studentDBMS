// Binary Search Tree ADT
// Created by A. Student
// Modified by: Michael Davis

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <iostream>
#include "BinaryTree.h"

template<class ItemType, class ItemType2>
class BinarySearchTree : public BinaryTree<ItemType, ItemType2>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType& item, const ItemType2& secKey, int compare(const ItemType2& name1, const ItemType2& name2));
    // remove a node if found
    bool remove(ItemType& returnedItem, const ItemType2 &item, int compare(const ItemType2& name1, const ItemType2& name2));
    // find a target node
    //bool search(const ItemType2 &target, ItemType &returnedItem, int compare(const ItemType2& name1, const ItemType2& name2)) const;
    // find the smallest node
    //bool findSmallest(ItemType2 &returnedItem) const;
    // find the largest node
    //bool findLargest(ItemType2 &returnedItem) const;

private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType, ItemType2>* _insert(BinaryNode<ItemType, ItemType2>* nodePtr, BinaryNode<ItemType, ItemType2>* newNode,
                                              int compare(const ItemType2& name1, const ItemType2& name2));

    // search for target node
    /*BinaryNode<ItemType, ItemType2>* _search(BinaryNode<ItemType, ItemType2>* treePtr, const ItemType2 &target,
                                              int compare(const ItemType2& name1, const ItemType2& name2)) const;*/

    // find the smallest node
    //BinaryNode<ItemType, ItemType2>* _findSmallest(BinaryNode<ItemType, ItemType2>* nodePtr, ItemType2 &smallest) const;

    // find the largest node
    //BinaryNode<ItemType, ItemType2>* _findLargest(BinaryNode<ItemType, ItemType2>* nodePtr, ItemType2 &largest) const;

    // internal remove node: locate and delete target node under nodePtr subtree
    ItemType _remove(BinaryNode<ItemType, ItemType2>* nodePtr, BinaryNode<ItemType, ItemType2>* parent,
                                             const ItemType2 target, bool &success,
                                             int compare(const ItemType2& name1, const ItemType2& name2));

    // delete target node from tree, called by internal remove node
    //BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    //BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor);

};


///////////////////////// public function definitions ///////////////////////////
//Wrapper for _insert - Inserting items within a tree
template<class ItemType, class ItemType2>
bool BinarySearchTree<ItemType, ItemType2>::insert(const ItemType& item, const ItemType2& secKey,
                                                   int compare(const ItemType2& name1, const ItemType2& name2))
{
    BinaryNode<ItemType, ItemType2>* newNodePtr = new BinaryNode<ItemType, ItemType2>(item, secKey);
    this->rootPtr = _insert(this->rootPtr, newNodePtr, compare);
    return true;
}

//Wrapper for _delete - Removing items within a tree
template<class ItemType, class ItemType2>
bool BinarySearchTree<ItemType, ItemType2>::remove(ItemType& returnedItem, const ItemType2& item, int compare(const ItemType2& name1, const ItemType2& name2))
{
    bool isRemoved;
    BinaryNode<ItemType, ItemType2>* parent = NULL;
    //BinaryNode<ItemType, ItemType2>* removedNode = _remove(this->rootPtr, parent, item, isRemoved, compare);
    //returnedItem = removedNode->getItem();
    returnedItem = _remove(this->rootPtr, parent, item, isRemoved, compare);
    return isRemoved;
}

////Wrapper for _search
//// - it calls the private _search function that returns a Node pointer or NULL
//// - if found, it copies data from that node and sends it back to the caller
////   via the output parameter, and returns true, otherwise it returns false.
//template<class ItemType, class ItemType2>
//bool BinarySearchTree<ItemType, ItemType2>::search(const ItemType2& anEntry, ItemType& returnedItem,
//                                                   int compare(const ItemType2& name1, const ItemType2& name2)) const
//{
//    BinaryNode<ItemType, ItemType2>* temp = nullptr;
//
//    temp = _search(this->rootPtr, anEntry, compare);
//
//    if (temp != nullptr)
//    {
//       returnedItem = temp->getItem();
//       return true;
//    }
//
//    return false;
//}

//Wrapper for _findSmallest
// - it calls the private _findSmallest function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
//template<class ItemType, class ItemType2>
//bool BinarySearchTree<ItemType, ItemType2>::findSmallest(ItemType2& returnedItem) const
//{
//    BinaryNode<ItemType, ItemType2>* temp = nullptr;
//    BinaryNode<ItemType, ItemType2> smallest;
//
//    temp = _findSmallest(this->rootPtr, smallest);
//
//    if (temp != nullptr)
//    {
//        returnedItem = smallest;
//        return true;
//    }
//
//    return false;
//}

//Wrapper for _findLargest
// - it calls the private _findLargest function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
//template<class ItemType, class ItemType2>
//bool BinarySearchTree<ItemType, ItemType2>::findLargest(ItemType2& returnedItem) const
//{
//    BinaryNode<ItemType, ItemType2>* temp = nullptr;
//    BinaryNode<ItemType, ItemType2> largest;
//
//    temp = _findLargest(this->rootPtr, largest);
//
//    if (temp != nullptr)
//    {
//        returnedItem = largest;
//        return true;
//    }
//
//    return false;
//}

//////////////////////////// private functions ////////////////////////////////////////////

//Implementation of the remove operation
template<class ItemType, class ItemType2>
ItemType BinarySearchTree<ItemType, ItemType2>::_remove(BinaryNode<ItemType, ItemType2>* nodePtr,
                                                        BinaryNode<ItemType, ItemType2>* parent,
                                                        const ItemType2 target, bool& success,
                                                        int compare(const ItemType2& name1, const ItemType2& name2))
{
    ItemType returnedItem;
    ItemType dummyItem;

    if (!nodePtr) // == NULL
    {
        success = false;
        return dummyItem;
    }
    else
    {
        while (nodePtr != NULL)
        {
            if (compare(nodePtr->getSec(), target) == 3) //If the target matches the node
            {
                if (nodePtr->getLeftPtr() == NULL && nodePtr->getRightPtr() == NULL) //Remove a leaf node
                {
                    if (!parent) //If the Node is the root of the tree
                    {
                        returnedItem = nodePtr->getItem();
                        //return nodePtr;
                        delete nodePtr;
                        nodePtr = NULL;
                        success = true;
                        //return returnedItem;
                    }
                    else if (parent->getLeftPtr() == nodePtr) //If it is the left child of the root
                    {
                        returnedItem = nodePtr->getItem();
                        //return nodePtr;
                        parent->setLeftPtr(NULL);
                        delete nodePtr;
                        success = true;
                        //return returnedItem;
                    }
                    else //If it is the right child of the root
                    {
                        returnedItem = nodePtr->getItem();
                        //return nodePtr;
                        parent->setRightPtr(NULL);
                        delete nodePtr;
                        success = true;
                        //return returnedItem;
                    }
                }
                else if (nodePtr->getLeftPtr() && nodePtr->getRightPtr() == NULL) //Remove node with only a left child
                {
                    if (!parent) //If the Node is the root of the tree
                    {
                        returnedItem = nodePtr->getItem();
                        this->rootPtr = nodePtr->getLeftPtr();
                        //return nodePtr;
                        //nodePtr = nodePtr->getLeftPtr();
                        delete nodePtr;
                        success = true;
                        //return returnedItem;
                    }
                    else if (parent->getLeftPtr() == nodePtr) //If it is the left child of the root
                    {
                        returnedItem = nodePtr->getItem();
                        //return nodePtr;
                        parent->setLeftPtr(nodePtr->getLeftPtr());
                        delete nodePtr;
                        success = true;
                        //return returnedItem;
                    }
                    else //If it is the right child of the root
                    {
                        returnedItem = nodePtr->getItem();
                        //return nodePtr;
                        parent->setRightPtr(nodePtr->getLeftPtr());
                        delete nodePtr;
                        success = true;
                        //return returnedItem;
                    }
                }
                else if (nodePtr->getLeftPtr() == NULL && nodePtr->getRightPtr()) //Remove node with only a right child
                {
                    if (compare(target, nodePtr->getRightPtr()->getSec()) == 3) /*If the right child of nodePtr happens to have the same last name,
                                                                                then see if that is the correct node to remove*/
                    {
                        nodePtr = nodePtr->getRightPtr();

                        if (parent->getLeftPtr() == nodePtr) //If it is the left child of the root
                        {
                            returnedItem = nodePtr->getItem();
                            //return nodePtr;
                            parent->setLeftPtr(nodePtr->getRightPtr());
                            delete nodePtr;
                            success = true;
                            //return returnedItem;
                        }
                        else //If it is the right child of the root
                        {
                            returnedItem = nodePtr->getItem();
                            //return nodePtr;
                            parent->setRightPtr(nodePtr->getRightPtr());
                            delete nodePtr;
                            success = true;
                            //return returnedItem;
                        }
                    }
                    else //If the correct node was found initially
                    {
                        if (!parent) //If the Node is the root of the tree
                        {
                            returnedItem = nodePtr->getItem();
                            //return nodePtr;
                            this->rootPtr = nodePtr->getRightPtr();
                            //nodePtr = nodePtr->getRightPtr();
                            delete nodePtr;
                            success = true;
                            //return returnedItem;
                        }
                        else if (parent->getLeftPtr() == nodePtr) //If it is the left child of the root
                        {
                            returnedItem = nodePtr->getItem();
                            //return nodePtr;
                            parent->setLeftPtr(nodePtr->getRightPtr());
                            delete nodePtr;
                            success = true;
                            //return returnedItem;
                        }
                        else //If it is the right child of the root
                        {
                            returnedItem = nodePtr->getItem();
                            //return nodePtr;
                            parent->setRightPtr(nodePtr->getRightPtr());
                            delete nodePtr;
                            success = true;
                            //return returnedItem;
                        }
                    }
                }
                else //Remove a node with two chidlren
                {
                    //Find successor of nodePtr (leftmost child of right subtree)
                    BinaryNode<ItemType, ItemType2>* successor = nodePtr->getRightPtr();

                    while (successor->getLeftPtr() != NULL)
                    {
                        successor = successor->getLeftPtr();
                    }

                    //Create a copy of successor's data
                    ItemType2 successorDataSec = successor->getSec();
                    ItemType successorDataItem = successor->getItem();

                    _remove(this->rootPtr, parent, successorDataSec, success, compare); //Remove the successor

                    //Assign nodePtr's data with successors data
                    nodePtr->setSec(successorDataSec);
                    nodePtr->setItem(successorDataItem);
                }
                return returnedItem;
            }
            else if (compare(nodePtr->getSec(), target) == 2) //Search the Right
            {
                parent = nodePtr;
                nodePtr = nodePtr->getRightPtr();
            }
            else //Search the Left
            {
                parent = nodePtr;
                nodePtr = nodePtr->getLeftPtr();
            }
        }
    }
    success = false;
    return dummyItem;
}

//Implementation of the insert operation
template<class ItemType, class ItemType2>
BinaryNode<ItemType, ItemType2>* BinarySearchTree<ItemType, ItemType2>::_insert(BinaryNode<ItemType, ItemType2>* nodePtr,
                                                                                BinaryNode<ItemType, ItemType2>* newNode,
                                                                                int compare(const ItemType2& name1, const ItemType2& name2))
{
    BinaryNode<ItemType, ItemType2>* pWalk = nodePtr, *parent = NULL;

    if( !nodePtr) // == NULL
    {
        nodePtr = newNode;
        return nodePtr;
    }
    else
    {
       parent = pWalk;

       if (compare(parent->getSec(), newNode->getSec()) == 1)
       {
          if (parent->getLeftPtr() == NULL)
          {
             parent->setLeftPtr(newNode);
          }
          else
          {
             _insert(parent->getLeftPtr(), newNode, compare);
          }
       }
       else if (compare(parent->getSec(), newNode->getSec()) == 2)
       {
          if (parent->getRightPtr() == NULL)
          {
             parent->setRightPtr(newNode);
          }
          else
          {
             _insert(parent->getRightPtr(), newNode, compare);
          }
       }
    }

    return nodePtr;
}

//Implementation for the search operation
// - return NULL if target not found, otherwise
// - returns a pointer to the node that matched the target
//template<class ItemType, class ItemType2>
//BinaryNode<ItemType, ItemType2>* BinarySearchTree<ItemType, ItemType2>::_search(BinaryNode<ItemType, ItemType2>* nodePtr,
//                                                                                const ItemType &target,
//                                                                                int compare(const ItemType& name1, const ItemType& name2)) const
//{
//   BinaryNode<ItemType, ItemType2>* found = nullptr;
//
//   if (nodePtr != nullptr)
//   {
//      if (compare(target, nodePtr->getItem()) == 3)
//      {
//         found = nodePtr;
//      }
//
//      else if (compare(target, nodePtr->getItem()) == 2)
//      {
//         return _search(nodePtr->getLeftPtr(), target, compare);
//      }
//      else
//      {
//         return _search(nodePtr->getRightPtr(), target, compare);
//      }
//   }
//
//   return found;
//}

//Implementation of the findSmallest operation
//template<class ItemType, class ItemType2>
//BinaryNode<ItemType, ItemType2>* BinarySearchTree<ItemType, ItemType2>::_findSmallest(BinaryNode<ItemType, ItemType2>* nodePtr,
//                                                                                      ItemType& smallest) const
//{
//    BinaryNode<ItemType, ItemType2>* found = nullptr;
//
//    if (nodePtr->getLeftPtr() != nullptr)
//    {
//        _findSmallest(nodePtr->getLeftPtr(), smallest);
//    }
//    else
//    {
//        found = nodePtr;
//        smallest = nodePtr->getItem();
//    }
//
//    return found;
//}

//Implementation of the findLargest operation
//template<class ItemType, class ItemType2>
//BinaryNode<ItemType, ItemType2>* BinarySearchTree<ItemType, ItemType2>::_findLargest(BinaryNode<ItemType, ItemType2>* nodePtr,
//                                                                                     ItemType& largest) const
//{
//    BinaryNode<ItemType, ItemType2>* found = nullptr;
//
//    if (nodePtr->getRightPtr() != nullptr)
//    {
//        _findLargest(nodePtr->getRightPtr(), largest);
//    }
//    else
//    {
//        found = nodePtr;
//        largest = nodePtr->getItem();
//    }
//
//    return found;
//}

#endif
