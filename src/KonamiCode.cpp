//
//  KonamiCode.cpp
//  ofForest
//
//  Created by Etienne on 2014-12-18.
//
//

#include "KonamiCode.h"

KonamiCode::KonamiCode(){}

void KonamiCode::setCode(const vector<int> & value){
    code = value;
}

void KonamiCode::reset(){
    input.clear();
}

bool KonamiCode::pushKey(int key){
    if (code[input.size()] == key){
        input.push_back(key);
    }
    if (input.size() == code.size()){
        reset();
        return true;
    }
    return false;
}
