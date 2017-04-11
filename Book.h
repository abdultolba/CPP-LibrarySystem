//
//  Book.h
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#ifndef Book_h
#define Book_h

#include <iostream>
#include <string>
#include "Item.h"

class Book : public Item{
public:
    // Default constructor
    // Post condition: ID = 0, name = "", status = false, Author_name = ""
    Book();
    // Constructor with parameters
    // Post condition: assigns ID, name, status, and Author_name to respective values
    Book(string, string, bool, string);
    // Accessor function that returns Author_name
    string getAuthorName();
    // Mutator functions that sets Author_name
    void setAuthorName(string);
    
private:
    string Author_Name;
};

#endif /* Book_h */
