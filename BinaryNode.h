#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType, class ItemType2> //ItemType2 = secKey, ItemType = Student Object (Needs to be reference later)
class BinaryNode
{
private:
    ItemType2                        secKey;         // Data portion (Student Name)
    ItemType                         item;           // Data Portion (Student Object)
    BinaryNode<ItemType, ItemType2>* leftPtr;        // Pointer to left child
    BinaryNode<ItemType, ItemType2>* rightPtr;       // Pointer to right child

public:
    // constructors
    BinaryNode(const ItemType& obj , const ItemType2& sec)
    {
       secKey = sec;
       item = obj;
       leftPtr = 0;
       rightPtr = 0;
    }
    BinaryNode(const ItemType& obj, const ItemType2& sec, BinaryNode<ItemType, ItemType2>* left, BinaryNode<ItemType, ItemType2>* right)
    {
       secKey = sec;
       item = obj;
       leftPtr = left;
       rightPtr = right;
    }
    
    // setters
    void setSec(const ItemType2 & sec)
    {
       secKey = sec;
    }
    void setItem(const ItemType& obj)
    {
        item = obj;
    }
    void setLeftPtr(BinaryNode<ItemType, ItemType2>* left)
    {
       leftPtr = left;
    }
    void setRightPtr(BinaryNode<ItemType, ItemType2>* right)
    {
       rightPtr = right;
    }
    
    // getters
    ItemType2 getSec() const
    {
       return secKey;
    }
    ItemType getItem() const
    {
       return item;
    }
    BinaryNode<ItemType, ItemType2>* getLeftPtr() const
    {
       return leftPtr;
    }
    BinaryNode<ItemType, ItemType2>* getRightPtr() const
    {
       return rightPtr;
    }

    // other functions
    bool isLeaf() const
    {
       return (leftPtr == 0 && rightPtr == 0);
    }
    
};

#endif
