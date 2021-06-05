//
//  Food.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#ifndef Food_hpp
#define Food_hpp

#include <stdio.h>
#include "AbstractObject.hpp"
#include "Util.hpp"

class Food : public AbstractObject{
public:
    Food(Difficulty d);
    ActionType Action();
    void PrintDescription(void);
private:
    int InitializeAttack(Difficulty d);
    int InitializeHealthValue(Difficulty d);
};

#endif /* Food_hpp */
