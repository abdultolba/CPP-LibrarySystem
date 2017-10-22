//
//  Journal.cpp
//  AbdulTolba_ProgrammingProject
//
//  Created by Abdulrahman on 3/21/17.
//  Copyright © 2017 Abdulrahman Tolba. All rights reserved.
//

#include <iostream>
#include <string>
#include "Journal.h"

using namespace std;

Journal::Journal() : Item(), Volume{0}{}

Journal::Journal(string a, string b, bool c, int d) : Item(a, b, c), Volume(d){ }

int Journal::getVolume(){
    return Volume;
}

void Journal::setVolume(int a){
    Volume = a;
}
