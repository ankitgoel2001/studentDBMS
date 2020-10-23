// Implementation file for the Student class
// Written By : Michael Davis
// Code Reused From : A.Student
// IDE : Visual Studio


#include <iostream>
#include <iomanip>
#include <string>

#include "Student.h"

using namespace std;

//**************************************************
// Constructor
//**************************************************
Student::Student()
{
    stuID = "";
    stuName = "";
    major = "";
    age = -1;
    cost = -1;
}

//**************************************************
// Overloaded Constructors
//**************************************************
Student::Student(string id, string nm, string mj, int ag, int ct)
{
    stuID = id;
    stuName = nm;
    major = mj;
    age = ag;
    cost = ct;
}

Student::Student(string id, string nm)
{
    stuID = id;
    stuName = nm;
    major = "";
    age = -1;
    cost = -1;
}

Student::Student(string id)
{
    stuID = id;
    stuName = "";
    major = "";
    age = -1;
    cost = -1;
}
/*
//***********************************************************
// Displays the values of the Student object member variables
// on one line (horizontal display)
//***********************************************************
void Student::hDdisplay() const
{
    cout << left;
    cout << " " << setw(4) << code << "  ";
    cout << " " << setw(2) << rank << "  ";
    cout << " " << setw(27) << name << "  ";
    cout << right;
    cout << " " << setw(7) << cost << " ";
    cout << left << endl;
}

//***********************************************************
// Displays the values of the Student object member variables
// one per line (vertical display)
//***********************************************************
void Student::vDisplay() const
{
    cout << "              Rank: " << rank << endl;
    cout << "       School Name: " << name << endl;
    cout << "Cost of Attendance: $" << cost << endl;
}
*/

// overloaded operators
/* Write your code here to define the following oveloaded operator:
    - the stream insertion operator ( << )
    - the comparision operators (==, <, >)
 */

ostream& operator<<(ostream& out, const Student& obj)
{
   /* out << left;
    out << " " << setw(4) << obj.getCode() << "  ";
    out << " " << setw(2) << obj.getRank() << "  ";
    out << " " << setw(27) << obj.getName() << "  ";
    out << right;
    out << " " << setw(7) << obj.getCost() << " ";
    out << left << endl;*/

    out << left;
    out << "Name: " << obj.stuName << endl;
    out << "ID Num: " << obj.stuID << endl;
    out << "Age: " << obj.age << endl;
    out << "Major: " << obj.major << endl;
    out << "Cost of Tuition: " << obj.cost << endl;

    return out;
}
