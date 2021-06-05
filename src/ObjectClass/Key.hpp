//
//  Key.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/1.
//

#ifndef Key_hpp
#define Key_hpp

#include <stdio.h>
#include "AbstractObject.hpp"

class Key : public AbstractObject{
public:
    Key(void);
    void PrintDescription(void);
    bool IsMatched(const pair<int, int>& needed);
    ActionType Action();
private:
    pair<int, int> Match;
};

#endif /* Key_hpp */
