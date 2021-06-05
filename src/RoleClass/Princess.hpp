#ifndef Princess_hpp
#define Princess_hpp

#include <stdio.h>
#include "AbstractRole.hpp"
#include "Util.hpp"

class Princess : public AbstractRole{
public:
    Princess(Difficulty d, int roomNum);
    void Interact(void);
private:
    int InitializePosition(Difficulty d, int roomNum);
    int InitializeHealthPoint(Difficulty d);
};



#endif /* Princess_hpp */
