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

   //go through 26 iterations of each letter in the alpha to set array pointer to null and element count to 0
   for (int i=0; static_cast<unsigned int>(i)< MAX_ALPHA; i++){
      elements[i] = nullptr;
      elementCount[i] = 0;
   }
   
}  

// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   // cout << "MyADT::copy constructor executed!" << endl; // For testing purposes ... 
   // You can also use the above to figure out when this constructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.

   /* Put your code here */

   //initialize new 2d array
   Profile * newElements[MAX_ALPHA];

   //create the memory for the new adt's array
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      newElements[i] = new Profile[MAX_ELEMENTS];
      if (newElements[i] == nullptr){
         cout << "Memory error." << endl;
         exit(0);
      }
      //copy over each element
      for (int j=0; static_cast<unsigned int>(j)<MAX_ELEMENTS; j++){
         newElements[i][j] = rhs.elements[i][j];
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
    //cout << "MyADT::destructor" << endl;  // For testing purposes ...
   // You can also use the above to figure out when this destructor is executed.
   // If you do uncomment it, make sure to comment it out again before you submit your Assignment 1.
  
   /* Put your code here */

   //call function to reset adt
   removeAll();
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

   //get first letter of word make upper case then subract to get corresponding number
   char key = newElement.getSearchKey();
   key = toupper(key);
   int ind = key - 65;
   //check if array still has space
   if (elementCount[ind] == MAX_ELEMENTS){
      return false;
   }
   //check to see if its the first element in the character's array
   if (elements[ind] == nullptr){
      elements[ind] = new Profile[MAX_ELEMENTS];
      for (int j=0; static_cast<unsigned int>(j)<MAX_ELEMENTS; j++){
         elements[ind][j] = Profile();
      }
      elements[ind][0] = newElement;
      elementCount[ind]++;
      return true;
   }
   //find correct position for new element
   int pos = 0;
   while (elements[ind][pos]<newElement && static_cast<unsigned int>(pos) < (elementCount[ind] + 1) && elements[ind][pos].getName() != "tbd"){
      if (elements[ind][pos] == newElement){
         return false;
      }
      pos++;
   }
   //shift elements to the right to sort
   for (int i = elementCount[ind]; i > pos; i--) {
        elements[ind][i] = elements[ind][i-1];
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

   //create defaulted value profile
   Profile* blankProfile = new Profile;

   //find index
   char key = toBeRemoved.getSearchKey();
   key = toupper(key);
   int ind = key - 65;

   //use search function to know if remove is possible
   if (search(toBeRemoved)!=nullptr){
      for (int i=0; static_cast<unsigned int>(i)<MAX_ELEMENTS; i++){
         if (elements[ind][i] == toBeRemoved){
            //when found set toberemoved profile to blank profile lower element count by 1
            elements[ind][i] = *blankProfile;
            elementCount[ind]--;
            return true;
         }
      }
   }
      //if toberemoved not found must delete the blank profile memory since not used
      delete blankProfile;
      return false;
}  


// Description: Removes all elements from the data collection MyADT. 
// Postcondition: MyADT reverts back to its initialization state, i.e., 
//                the state it is in once it has been constructed (once
//                the default constructor has executed). 
void MyADT::removeAll() {
    
    /* Put your code here */
   
   //delete all memory used for the elements array and set count to 0
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      if (elements[i] != nullptr){
         delete[] elements[i];
         elementCount[i] = 0;
      }
   }
}   

// Description: Searches for target element in the data collection MyADT. 
//              Returns a pointer to the element if found, otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
    
    /* Put your code here */

    //find index
   char key = target.getSearchKey();
   key = toupper(key);
   int ind = key - 65;

   //if no elements are in that letter group yet its impossible to find here
   if (elements[ind] == nullptr){
      return nullptr;

   }else{
      //look through list and return the profile if found
      for (int i=0; static_cast<unsigned int>(i)<MAX_ELEMENTS; i++){
         if (elements[ind][i] == target){
          return &elements[ind][i];
         }
      }
   }   
   return nullptr;
}  


// Description: Prints all elements stored in the data collection MyADT in ascending order of search key.
// ***For Testing Purposes - Not part of this class' public interface.***
void MyADT::print() {
  
    /* Put your code here */  

    //print profiles alphabetically
   for (int i=0; static_cast<unsigned int>(i)<MAX_ALPHA; i++){
      for (int j=0; static_cast<unsigned int>(j)<elementCount[i]; j++){
         cout << elements[i][j] << endl;
      }
   }
}

//  End of implementation file