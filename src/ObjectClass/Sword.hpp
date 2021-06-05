//
//  Sword.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/1.
//

#ifndef Sword_hpp
#define Sword_hpp

#include <stdio.h>
#include "AbstractObject.hpp"
#include "Util.hpp"

class Sword : public AbstractObject{
public:
    Sword(Difficulty d);
    ActionType Action(void);
    void PrintDescription(void);
private:
    int InitializeAttack(Difficulty d);
};

#endif /* Sword_hpp */
