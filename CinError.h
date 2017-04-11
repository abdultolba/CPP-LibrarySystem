//
//  CinError.h
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/24/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#ifndef CinError_h
#define CinError_h

#include <iostream>
#include <string>

using namespace std;

class CinError{
public:
    // Default constructor
    // Post condition: message = "Error: Invalid Input. Input must be a number."
    CinError();
    // Constructor with parameters
    // Post condition: message = the value passed in the parameter
    CinError(string m);
    // What function that returns the message to be displayed
    string what();
private:
    string message;
};

#endif /* CinError_h */
