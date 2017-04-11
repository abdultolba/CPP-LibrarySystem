//
//  Item.h
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#ifndef Item_h
#define Item_h

#include <iostream>
#include <string>
using namespace std;

class Item{
public:
    // Default constructor
    // Post condition: ID = 0, name = "", status = false
    Item();
    //Constructor with parameters
    // Post condition: assigns ID, name, and status to respective values
    Item(string, string, bool);
    // Accessor function that returns Item ID
    string getID();
    // Mutator function that sets Item ID
    void setID(string);
    // Accessor function that returns Item name
    string getName();
    // Mutator function that sets Item name
    void setName(string);
    // Accessor function that returns Item status
    bool getStatus();
    // Mutator function that sets Item status
    void setStatus(bool);
    
private:
    string ID;
    string name;
    bool status;
};
#endif /* Item_h */
