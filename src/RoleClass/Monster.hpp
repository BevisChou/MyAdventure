#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>
#include "AbstractRole.hpp"
#include "Util.hpp"

class Monster : public AbstractRole{
public:
    Monster(Difficulty d, int roomNum);
    void Interact(void);
private:
    int InitializePosition(Difficulty d, int roomNum);
    int InitializeHealthPoint(Difficulty d);
};

#endif /* Monster_hpp */
