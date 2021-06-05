//
//  Bedroom.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#ifndef Bedroom_hpp
#define Bedroom_hpp

#include <stdio.h>
#include "AbstractRoom.hpp"

class Bedroom : public AbstractRoom{
public:
    Bedroom(int id, Difficulty d);
    void ShowRoomDescription(Difficulty d);
};

#endif /* Bedroom_hpp */
