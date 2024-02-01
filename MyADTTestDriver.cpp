/*
* MyADTTestDriver.cpp
*
* Class Description: A linear data collection ADT.
* 
* Testing MyADT.cpp methods
*
* Author: Cole Ackerman
*
* Modified on: Jan. 2024
*/

#include <iostream>
#include <string>
#include <cctype>
#include "MyADT.h"
#include "Profile.h"

using namespace std;

bool insertSearchTest(MyADT& members){
    
    cout << "Starting first test!\n" << endl;

    Profile testmember("Code Master", "Michael Jackson", "MJ@gmail.com", "August 29, 1958");

    members.insert(testmember);

    if (members.search(testmember) != nullptr){
        cout << "Test 1 Passed - Successfully found inserted profile.\n" << endl;
        return true;
    }else{
        cout << "Test 1 Failed - Failed to find inserted profile.\n" << endl;
        return false;
    }
}

bool removeSearchTest(MyADT& members){

    cout << "Starting second test!\n" << endl;

    Profile testmember("Code Master", "Michael Jackson", "MJ@gmail.com", "August 29, 1958");

    members.insert(testmember);

    members.remove(testmember);

    Profile* result = members.search(testmember);

    if (result != &testmember){
        cout << "Test 2 Passed - Successfully removed inserted profile.\n" << endl;
        return true;
    }else{
        cout << "Test 2 Failed - Failed to remove inserted profile.\n" << endl;
        return false;
    }
}

bool elementCountTest(MyADT& members){

    cout << "Starting third test!\n" << endl;

    Profile testmember1("Cab");
    Profile testmember2("Cone");
    Profile testmember3("Bread");
   
    members.insert(testmember1);

    members.insert(testmember2);

    members.insert(testmember3);

    if (members.getElementCount() == 3){
        cout << "Test 3 Passed - Successfully counted all profiles.\n" << endl;
        return true;
    }else{
        cout << "Test 3 Failed - Failed to correctly count all profiles.\n" << endl;
        return false;
    }
}

int main(){
    MyADT T1 = MyADT();
    MyADT T2 = MyADT();
    MyADT T3 = MyADT();


    int passed = 0;

    bool test1 = insertSearchTest(T1);

    if (test1){
        passed++;
    }

    bool test2 = removeSearchTest(T2);
    if (test2){
        passed++;
    }

    bool test3 = elementCountTest(T3);
    if (test3){
        passed++;
    }

    cout << "Testing complete! You passed " << passed << " tests." << endl;
    
    return 0;
}