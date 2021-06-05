//
//  Study.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#ifndef Study_hpp
#define Study_hpp

#include <stdio.h>
#include "AbstractRoom.hpp"

class Study : public AbstractRoom{
public:
    Study(int id, Difficulty d);
    void ShowRoomDescription(Difficulty d);
};

#endif /* Study_hpp */
