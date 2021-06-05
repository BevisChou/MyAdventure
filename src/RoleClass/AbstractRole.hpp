#ifndef AbstractRole_hpp
#define AbstractRole_hpp

#include <stdio.h>
#include <vector>
#include "AbstractObject.hpp"

class AbstractRole{
public:
    AbstractRole(int pos, int hp);
    int GetPosition(void);
    void SetPosition(int pos);
    int GetHealthPoint(void);
    virtual void Interact(void) = 0;
protected:
    vector<AbstractObject*> Assets;
    int Position;
    int TotalHealthPoint;
    int CurrentHealthPoint;
    virtual int InitializePosition(Difficulty d, int roomNum) = 0;
    virtual int InitializeHealthPoint(Difficulty d) = 0;
};

#endif /* AbstractRole_hpp */
