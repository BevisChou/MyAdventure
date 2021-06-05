//
//  Kitchen.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#ifndef Kitchen_hpp
#define Kitchen_hpp

#include <stdio.h>
#include "AbstractRoom.hpp"

class Kitchen : public AbstractRoom{
public:
    Kitchen(int id, Difficulty d);
    void ShowRoomDescription(Difficulty d);
};

#endif /* Kitchen_hpp */
