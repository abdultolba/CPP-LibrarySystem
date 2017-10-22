//
//  Item.cpp
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#include <iostream>
#include <string>
#include "Item.h"

using namespace std;

Item::Item() : ID{""), name{""}, status{false}{ }

Item::Item(string a, string b, bool c) : ID{a}, name{b}, status{c}{ }

string Item::getID(){
    return ID;
}

void Item::setID(string a){
    ID = a;
}

string Item::getName(){
    return name;
}

void Item::setName(string a){
    name = a;
}

bool Item::getStatus(){
    return status;
}

void Item::setStatus(bool a){
    status = a;
}
