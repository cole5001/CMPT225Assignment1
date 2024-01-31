/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * 
 * Class Invariant: Data collection with the following characteristics:
 *                  - This is a value-oriented data collection and 
 *                    the elements are kept in ascending sort order of search key.
 *                  - Each element is unique (no duplicates). 
 *                  - Its data structure (CDT) is not expandable. This signifies that 
 *                    when this data collection becomes full, you do not have to resize 
 *                    its data structure (not in this Assignment 1). 
 *
 * Author: AL and <Cole Ackerman>
 * Last modified on: Jan. 2024
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"     // Header file of MyADT file
#include "Profile.h"   // Header file of Profile class

using std::cout;
using std::endl;
    
// Default constructor.
MyADT::MyADT() {
   // cout << "MyADT::default constructor executed!" << endl;   // For testing purposes ...
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
 
   /* Put your code here */
   for (int i=0; static_cast<unsigned int>(i) < MAX_ALPHA; i++){
      elements[i]=new Profile[MAX_ELEMENTS];
      if (elements[i] == nullptr){
         cout << "Memory error." << endl;
         exit(0);
      }
      elementCount[i] = 0;
      for (int j=0; static_cast<unsigned int>(j) < MAX_ELEMENTS; j++){
         elements[i][j]=Profile();
      }
   }
}  

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   // cout << "MyADT::copy constructor executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

   /* Put your code here */
   Profile * newElements[MAX_ALPHA];
   //unsigned int newElementCount[MAX_ALPHA];
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      newElements[i] = new Profile[MAX_ELEMENTS];
      //newElementCount[i]=0;
      if (newElements[i] == nullptr){
         cout << "Memory error." << endl;
         exit(0);
      }
      //newElementCount[i] = rhs.elementCount[i];
      for (int j=0; static_cast<unsigned int>(j)<MAX_ELEMENTS; j++){
         newElements[i][j] = Profile(elements[i][j].getUserName(), elements[i][j].getName(), elements[i][j].getEmail(), elements[i][j].getBirthday());
      }
   }
}  

// Overloaded assignment operator - Covered in Lab 5
// Therefore, we shall not be overloading this operator in our Assignment 1
// MyADT & MyADT::operator=(const MyADT& rhs) {
   // cout << "MyADT::operator= executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this overloaded assignment = operator is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
   
   /* Put your code here */

//}
    
// Destructor
// Description: Destroys this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   // cout << "MyADT::destructor" << endl;  // For testing purposes ...
   // You can also use the above to figure out when this destructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
  
   /* Put your code here */
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      elementCount[i]=0;
      delete[] elements[i];
      /*
      for (int j=0; static_cast<unsigned int>(j)<MAX_ELEMENTS; j++){
         delete[] elements[i];
      }*/
   }
}  


// Description: Returns the total number of elements currently stored in the data collection MyADT.  
unsigned int MyADT::getElementCount() const {

   /* Put your code here */
   unsigned int sum=0;
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      sum+=elementCount[i];
   }
   return sum;
}


// Description: Inserts an element in the data collection MyADT.
// Precondition: newElement must not already be in the data collection MyADT.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull, otherwise "false".
bool MyADT::insert(const Profile& newElement) {
 
   /* Put your code here */
   char key = newElement.getSearchKey();
   key = toupper(key);
   int ind = key - 65;

   int pos;
   for (int i=0; static_cast<unsigned int>(i)<MAX_ELEMENTS; i++){
      if (elements[ind][i].getUserName() == "tbd"){
         pos = i;
         break;
      }
      if (elements[ind][i] == newElement){
         cout << "Unable to create profile due to it already existing" << endl;
         return false;
      }
   }
   elements[ind][pos] = newElement;
   elementCount[ind]++;
   return true;
}  

// Description: Removes an element from the data collection MyADT. 
// Postcondition: toBeRemoved (if found) is removed and the appropriate elementCount is decremented.
//                Returns "true" when the removal is successfull, otherwise "false".  
bool MyADT::remove(const Profile& toBeRemoved) {

   /* Put your code here */
   Profile* blankProfile = new Profile;

   char key = toBeRemoved.getSearchKey();
   key = toupper(key);
   int ind = key - 65;

   if (search(toBeRemoved)!=nullptr){
      for (int i=0; static_cast<unsigned int>(i)<MAX_ELEMENTS; i++){
         if (elements[ind][i] == toBeRemoved){
            elements[ind][i] = *blankProfile;
            elementCount[ind]--;
            return true;
         }
      }
   }
      delete blankProfile;
      return false;
}  


// Description: Removes all elements from the data collection MyADT. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
void MyADT::removeAll() {
    
    /* Put your code here */
   Profile* blankProfile = new Profile();

   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      elementCount[i]=0;
      for (int j=0; static_cast<unsigned int>(j)<MAX_ELEMENTS; j++){
         elements[i][j] = *blankProfile;
      }
   }
}   

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
    
    /* Put your code here */
   char key = target.getSearchKey();
   key = toupper(key);
   int ind = key - 65;
   for (int i=0; static_cast<unsigned int>(i)<MAX_ELEMENTS; i++){
      if (elements[ind][i] == target){
        return &elements[ind][i];
      }
   }
   return nullptr;
}  


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
void MyADT::print() {
  
    /* Put your code here */  
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      for (int j=0; static_cast<unsigned int>(j)<MAX_ELEMENTS; j++){
         if (elements[i][j].getUserName() != "tbd"){
            cout << elements[i][j] << endl;
         }
      }
   }
}

//  End of implementation file