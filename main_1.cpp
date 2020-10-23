/* CIS22C
Team Project #6
---

This is a program that creates a Student Database Management System
based on one's ID, name, major, age and tuition cost
*/

#include "BinarySearchTree.h"
#include "Student.h"
#include "HashTable.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

//Function Prototype

void buildBSTandHash(ifstream& fin, const string& filename, BinarySearchTree<Student, string>& bst, HashTable<Student>& hash); // File Input
void insertBSTandHash(BinarySearchTree<Student, string>& bst, Student& aStudent, HashTable<Student>& hash); // Insert into BST and Hash Table
//void outputList(BinarySearchTree<Student, string> namesTree, char userInput/*, HashTable<Student> IDList*/); // File Output
void iDisplay(Student&, int); // Indented Tree Printing
void vDisplay(Student&); // Displays One Item per Line
//void oDisplay(Student&); // Displays One Item per Line (for the output.txt)
int compareNames(const string&, const string&); // Used in BST to Compare Last Names
int key_to_index(const Student &key, int size); // Hash Function
void displayMenu(); // Displays Menu
void printTreeBST(BinarySearchTree<Student, string>& bst); // Prints BST as Indented List
void searchHash(HashTable<Student>& hash, Student aStudent); // Searches Hash Table for Student Object
void searchBST(HashTable<Student>& hash, Student aStudent);
void displayHash(HashTable<Student>& hash); //to display the hash table
void deleteManager(Student aStudent, HashTable<Student>& hash, BinarySearchTree<Student, string>& bst); // Deletes Student Object from BST and Hash Table
void displayBST(Student aStudent, BinarySearchTree<Student, string>& bst); // Display Data Sorted by BST
void editData(Student aStudent, HashTable<Student>& hash); // Edit Student Major
void displayStatistics (HashTable<Student>& hash); // Displays Statistics of Hash Table

int main()
{
    // Read in file, and inputs into BST and Hash
    string filename;
    BinarySearchTree<Student, string> namesTree;
    int numOfElements;

    cout << "What is the input file's name? ";
    cin >> filename;
    cout << endl;

    ifstream fin(filename.c_str());

    if (!fin) //input file validation
    {
        cout << "Error opening the input file: \"" << filename << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    fin >> numOfElements;
    numOfElements *= 2;


    HashTable<Student> hash(numOfElements);
    buildBSTandHash(fin, filename, namesTree, hash);

    // Student Database Menu
    cout << "Welcome to the Student Database!" << endl;
    displayMenu();

    Student aStudent;
    string input;

    do
    {
      cout << "Please choose a menu option to continue" << endl << endl;
      cout << "Enter '\H\' to display menu again or \'Q\' to exit the program" << endl;
      cin >> input;
      switch (toupper(input[0])) {
         case 'N':
                 cout << "Display Data Sorted by Student's last name" << endl << endl;
                 displayBST(aStudent, namesTree);
                 break;
         case 'I':
                 //cout << "Display Data Sorted by Student ID" << endl << endl;
                 cout << "(TEMPORARY) Display the entire data for saving to output file" << endl;
                 // code to display
                 displayHash(hash);
                 break;
         case 'A':
                 cout << "Add New Student to Database" << endl << endl;
                 insertBSTandHash(namesTree, aStudent, hash);
                 break;
         case 'P':
                 cout << "Search by Student ID" << endl << endl;
                 searchHash(hash, aStudent);
                 break;
         case 'S':
                 cout << "Search by Student Name" << endl << endl;
                 searchBST(hash, aStudent); // search bst not working
                 break;
         case 'D':
                 cout << "Delete Student from Database"  << endl << endl;
                 deleteManager(aStudent, hash, namesTree);
                 break;
         case 'E':
                 cout << "Edit Student Information" << endl << endl;
                 editData(aStudent, hash);    // not inserting into bst and hash
                 break;
         case 'L':
                 cout << "Display Statistics" << endl << endl;
                 displayStatistics (hash);  // collisions not working
                 break;
         case 'M':
                 cout << "Display Student Names in Indented List" << endl << endl;
                 printTreeBST(namesTree);
                 break;
         case 'O':
                 cout << "Write Data into File without Quitting Program" << endl << endl;
                 // code to write data into file
                 break;
         case 'H':
                 cout << "Help Option: Display Menu Again" << endl << endl;
                 displayMenu();
                 break;
         case 'Q':
                 cout << endl << "Thank you for visiting the Student Database! Have a nice day!" << endl << endl;
                 // exit program
                 break;
         default:
                 cout << endl << "Please enter a valid option." << endl << endl;
        }
    } while (toupper(input[0]) != 'Q');

    return 0;
}

/*================================================================================================
The buildBSTandHashb Function takes in the filename and BST object, reads in data, and inserts
the newly made object into both the BST and Hash Table
================================================================================================*/
void buildBSTandHash(ifstream& fin, const string& filename, BinarySearchTree<Student, string>& bst, HashTable<Student>& hash)
{
    string stuID, stuName, major;
    int age, cost;

    while (fin >> stuID)
    {
        fin.ignore();
        getline(fin, stuName, ',');
        fin >> age;
        fin >> major;
        fin >> cost;

        // Create Student Object and initialize with data from file
        Student aStudent(stuID, stuName, major, age, cost);

        // Insert into BST and Hash
        bst.insert(aStudent, stuName, compareNames);
        hash.insert(aStudent, key_to_index);
    }
    fin.close();
}

/*================================================================================================
The compareNames Function compares two student's last names using the priority numbers
calculated in the function.
================================================================================================*/
int compareNames(const string& stuName1, const string& stuName2)
{
    // Gets the last name out of the whole name
    int space = stuName1.find(' ', 0); // Finds the space inbetween the first and last name
    int readpos = (space + 1); // Finds start of the last name of string
    string lastName1 = stuName1.substr(readpos, (space - readpos)); //Sets lastName1 to the last name (substring the whole name)

    space = stuName2.find(' ', 0);
    readpos = (space + 1);
    string lastName2 = stuName2.substr(readpos, (space - readpos));

    //Test if substringing worked
    //cout << "Last Name 1: " << lastName1 << endl;
    //cout << "Last Name 2: " << lastName2 << endl;

    // Compares the last names and return values
    if (lastName1 == lastName2) //If two students have the same last name, function compares student full names to find correct student
    {
        if (stuName1 > stuName2)
        {
            return 1;
        }
        else if (stuName1 < stuName2)
        {
            return 2;
        }
        else if (stuName1 == stuName2)
        {
            return 3;
        }
    }
    else if (lastName1 > lastName2)
    {
        return 1;
    }
    else if (lastName1 < lastName2)
    {
        return 2;
    }

    return -1;
}

/*================================================================================================
The insertBSTandHash Function asks user for student information for new student,
creates a new student object, and inserts the object into BST and Hash Table
================================================================================================*/
void insertBSTandHash(BinarySearchTree<Student, string>& bst, Student& aStudent, HashTable<Student>& hash)
{
    string stuName = "", stuMajor = "", stuID = "";
    int stuAge, cost;

    cout << "Please enter the Student ID of the student:" << endl;
    cin >> stuID;

    if (hash.search(aStudent, stuID, key_to_index) != -1) {
       cout << endl << "Duplicate key: " << aStudent.getID() << " - rejected! " << endl;
       cout << endl << "Please enter another Student ID:" << endl;
       cin >> stuID;
    }

    aStudent.setID(stuID);

    cout << endl << "Please enter the name of the student:" << endl;
    cin.ignore();
    getline (cin, stuName);
    aStudent.setStuName(stuName);

    cout << endl << "Please enter the age of the student:" << endl;
    cin >> stuAge;
    aStudent.setAge(stuAge);

    cout << endl << "Please enter the major of the student:" << endl;
    cin >> stuMajor;
    aStudent.setMajor(stuMajor);

    cout <<  endl << "Please enter the tuition cost of the student:" << endl;
    cin >> cost;
    aStudent.setCost(cost);

    bst.insert(aStudent, stuName, compareNames);
    hash.insert(aStudent, key_to_index);
    //bst.printTree(iDisplay);
    // hash.display();

    cout << endl << stuName << " has been added to the Student Database!" << endl << endl;
}

/*================================================================================================
Vertical Display (for the output.txt): one item per line
================================================================================================*/
void oDisplay(Student& item)
{
    ofstream fon("output.txt");

    fon << left;
    fon << "Name: " << item.getName() << endl;
    fon << "ID Num: " << item.getID() << endl;
    fon << "Age: " << item.getAge() << endl;
    fon << "Major: " << item.getMajor() << endl;
    fon << "Cost of Tuition: " << item.getCost() << endl;

    //fon.close();
}

/*================================================================================================
Vertical Display: one item per line
================================================================================================*/
void vDisplay(Student& item)
{
    cout << left;
    cout << "Name: " << item.getName() << endl;
    cout << "ID Num: " << item.getID() << endl;
    cout << "Age: " << item.getAge() << endl;
    cout << "Major: " << item.getMajor() << endl;
    cout << "Cost of Tuition: " << item.getCost() << endl << endl;
}

/*================================================================================================
 Indented Tree Display: one item per line, includes level number
================================================================================================*/
void iDisplay(Student& item, int level)
{
    for (int i = 1; i < level; i++)
        cout << "..";
    cout << level << "). " << item.getName() << endl;
}

/*================================================================================================
 Hash function: takes the key and returns the index in the Hash Table
================================================================================================*/
int key_to_index(const Student &key, int size)
{
    string k = key.getID();
    int sum = 0;
    for (int i = 0; k[i]; i++)
        {
            sum += k[i];
            sum *= 2;
        }
    return sum % size;
};

/*================================================================================================
The displayMenu Function displays the menu for the user
================================================================================================*/
void displayMenu()
{
    cout << "    (N) Display Data Sorted by Student's Last Name" << endl;
    cout << "    (I) Display Data Sorted by Student ID" << endl;
    cout << "    (A) Add New Student to Database" << endl;
    cout << "    (P) Search by Student ID" << endl;
    cout << "    (S) Search by Student Name" << endl;
    cout << "    (D) Delete a Student from Database"  << endl;
    cout << "    (E) Edit Student Information" << endl;
    cout << "    (L) Display Statistics" << endl;
    cout << "    (M) Display Student Names in Indented List" << endl;
    cout << "    (O) Write Data into File without Quitting Program" << endl;
    cout << "    (H) Help Option: Diplay Menu Again" << endl;
    cout << "    (Q) Exit Program" << endl << endl;
}

/*================================================================================================
The printTreeBST Function prints the BST as indented tree
================================================================================================*/
void printTreeBST(BinarySearchTree<Student, string>& bst)
{
    bst.printTree(iDisplay);
}

/*================================================================================================
The searchHash Function searches the Hash Table for student object
If found prints student data, otherwise returns not found
================================================================================================*/
void searchHash(HashTable<Student>& hash, Student aStudent)
{
    string stuID = "";

    cout << "Please enter the Student ID of the student you wish to search for:" << endl;
    cin >> stuID;

    if (hash.search(aStudent, stuID, key_to_index) != -1)
       cout << endl << "Found: " << aStudent << endl;
    else
       cout << endl << "Sorry, Student ID " << stuID << " was not found in this Database." << endl << endl;
}

/*================================================================================================
The searchBST Function searches the Hash Table for student object
If found prints student data, otherwise returns not found
================================================================================================*/
void searchBST(HashTable<Student>& hash, Student aStudent)
{
    string stuName = "";

    cout << "Please enter the name of the student:" << endl;
    cin.ignore();
    getline (cin, stuName);

    if (hash.search(aStudent, stuName, key_to_index) != -1)
       cout << endl << "Found: " << aStudent << endl;
    else
       cout << endl << "Sorry, Student " << stuName << " was not found in this Database." << endl << endl;
}

/*================================================================================================
The deleteManager Function deletes student from both BST and Hash
================================================================================================*/
void deleteManager(Student aStudent, HashTable<Student>& hash, BinarySearchTree<Student, string>& bst)
{
    string stuID = "", stuName = "";
    cout << "Please enter the Student ID of the student you wish to delete from the Student Database: " << endl;
    cin >> stuID;

    cout << "Please enter the name of the student:" << endl;
    cin.ignore();
    getline (cin, stuName);

    if (hash.search(aStudent, stuID, key_to_index) != -1) {
       Student delStudent;

       if (!bst.remove(delStudent, stuName, compareNames)) {
          cout << "Sorry could not delete student " << aStudent.getName() << " with Student ID " << aStudent.getID() << " from Binary Search Tree." << endl;
       }
       if (!hash.remove(delStudent, aStudent, key_to_index)) {
          cout << "Sorry could not delete student " << aStudent.getName() << " with Student ID " << aStudent.getID() << " from Hash Table." << endl;
       }
       cout << endl << "Student " << delStudent.getName() << " with Student ID " << delStudent.getID() << " has been deleted!" << endl;
   } else
       cout << endl << "Sorry, Student ID " << stuID << " was not found in this Database."  << endl << endl;
}

/*================================================================================================
The displayBST Function displays data sorted by student name (BST)
================================================================================================*/
void displayBST(Student aStudent, BinarySearchTree<Student, string>& bst)
{
    bst.inOrder(vDisplay);
}

/*================================================================================================
The editData Function allows user to update student major
================================================================================================*/
void editData(Student aStudent, HashTable<Student>& hash)
{
    string stuID = "", stuMajor = "";
    cout << "Please enter the ID of the student whose data you wish to edit:" << endl;
    cin >> stuID;

    if (hash.search(aStudent, stuID, key_to_index) != -1)
    {
       cout << "Please enter the major you wish to change to:" << endl;
       cin >> stuMajor;
       aStudent.setMajor(stuMajor);
    }
    else
       cout << endl << "Sorry, Student ID " << stuID << " was not found in this Database." << endl << endl;
}

/*================================================================================================
The displayStatistics Function displays the load factor, total collisions and maximum collisions
================================================================================================*/
void displayStatistics (HashTable<Student>& hash)
{
    cout << "Load Factors is " << hash.getLoadFactor() << endl;
    cout << "Number of Collisions is " << hash.getTotalCollisions() << endl;
    cout << "Longest Collision path is " << hash.getMaxCollisions() << endl;
}

/*====================================================================================================
The displayHash function displays the data sorted by student ID
=======================================================================================================*/
void displayHash(HashTable<Student>& hash)
{
    cout << "HI" << endl;
    hash.display();
}
