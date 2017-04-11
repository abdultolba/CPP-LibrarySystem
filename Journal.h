//
//  Journal.h
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#ifndef Journal_h
#define Journal_h

#include <iostream>
#include <string>
#include "Item.h"

class Journal : public Item{
public:
    // Default constructor
    // Post condition: ID = 0, name = "", status = false, Volume = 0
    Journal();
    // Constructor with parameters
    // Post condition: assigns ID, name, status, and Volume to respective values
    Journal(string, string, bool, int);
    // Accessor function that return Volume
    int getVolume();
    // Mutator function that sets the Volume
    void setVolume(int);
    
private:
    int Volume;
};

#endif /* Journal_h */
