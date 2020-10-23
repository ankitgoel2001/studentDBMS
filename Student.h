// Specification file for the Student class
// Created by A. Student
// Modified by: Nikita Manoj

#ifndef STUDENT_H
#define STUDENT_H

#include<string>

using std::string;
using std::ostream;

class Student; // Forward Declaration

// Function Prototypes for Overloaded Stream Operators
ostream &operator << (ostream &, const Student &);

class Student
{
    private:
        string stuID;
        string stuName;
        string major;
        int age;
        int cost; // in USD

    public:
        //constructors
        Student();
        Student(string);
        Student(string, string);
        Student(string, string, string, int, int);

        //setters
        void setStuName(string nm) { stuName = nm; }
        void setID(string id) { stuID = id; }
        void setMajor(string mj) { major = mj; }
        void setAge(int ag) { age = ag; }
        void setCost(int ct){ cost = ct; }

        //getters
        string getName() const {return stuName;}
        string getID() const {return stuID;}
        string getMajor() const { return major;}
        int getAge() const { return age;}
        int getCost() const {return cost;}

        //other functions if any
        //void hDdisplay()const;
       // void vDisplay()const;

        // overloaded operators (Do not need due to compare function in main used with function pointers)
        //friend bool operator== (const Student &, const Student &);
        //friend bool operator< (const Student &, const Student &);
        //friend bool operator> (const Student &, const Student &);

        // Friends
        friend ostream &operator<< (ostream &, const Student &);
        bool operator > (Student &);
        bool operator < (Student &);
        bool operator == (Student &obj) { return stuID == obj.stuID; }
};

#endif

