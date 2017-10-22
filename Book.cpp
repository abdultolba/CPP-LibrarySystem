//
//  Book.cpp
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#include <iostream>
#include <string>
#include "Book.h"

using namespace std;

Book::Book() : Item(), Author_Name{""}{}

Book::Book(string a, string b, bool c, string d) : Item(a, b, c), Author_Name(d){ }

string Book::getAuthorName(){
    return Author_Name;
}

void Book::setAuthorName(string a){
    Author_Name = a;
}

