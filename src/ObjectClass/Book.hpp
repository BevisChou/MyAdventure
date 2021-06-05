//
//  Book.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/1.
//

#ifndef Book_hpp
#define Book_hpp

#include <stdio.h>
#include "AbstractObject.hpp"
#include "Util.hpp"

class Book : public AbstractObject{
public:
    Book(void);
    ActionType Action();
    void PrintDescription(void);
};


#endif /* Book_hpp */
