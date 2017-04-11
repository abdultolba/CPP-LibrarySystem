//
//  CinError.cpp
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/24/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#include <iostream>
#include <string>
#include "CinError.h"

using namespace std;

CinError::CinError(){
    message = "Error: Invalid input. Input must be a number.";
}

CinError::CinError(string m) : message(m){ }

string CinError::what(){
    return message;
}
