//
//  Magazine.cpp
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#include <iostream>
#include <string>
#include "Magazine.h"

using namespace std;

Magazine::Magazine() : Item(), Issue_Number{0}{}

Magazine::Magazine(string a, string b, bool c, int d) : Item(a, b, c), Issue_Number(d){ }

int Magazine::getIssueNumber(){
    return Issue_Number;
}

void Magazine::setIssueNumber(int a){
    Issue_Number = a;
}
