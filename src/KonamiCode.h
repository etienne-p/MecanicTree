//
//  KonamiCode.h
//  ofForest
//
//  Created by Etienne on 2014-12-18.
//
//

#ifndef __ofForest__KonamiCode__
#define __ofForest__KonamiCode__

#include <stdio.h>
#include <vector>

using namespace std;

class KonamiCode {

public:
    KonamiCode();
    void setCode(const vector<int> & value);
    void reset();
    bool pushKey(int key);
    
private:
    vector<int> code;
    vector<int> input;

};

#endif /* defined(__ofForest__KonamiCode__) */
