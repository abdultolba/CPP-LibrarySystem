//
//  Magazine.h
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#ifndef Magazine_h
#define Magazine_h

#include <iostream>
#include <string>
#include "Item.h"

class Magazine : public Item{
public:
    // Default constructor
    // Post condition: ID = 0, name = "", status = false, Issue_Number = 0
    Magazine();
    // Constructor with parameters
    // Post condition: assigns ID, name, status, and Issue_Number to respective values
    Magazine(string, string, bool, int);
    // Accessor function that return Issue_Number
    int getIssueNumber();
    // Mutator function that sets Issue_Number
    void setIssueNumber(int);
    
private:
    int Issue_Number;
};

#endif /* Magazine_h */
