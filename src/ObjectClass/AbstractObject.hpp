#ifndef AbstractObject_hpp
#define AbstractObject_hpp

#include <stdio.h>
#include <string>
#include "Util.hpp"
using namespace std;

class AbstractObject{
public:
    AbstractObject(int attack, int healthValue, string name);
    virtual ActionType Action() = 0;
    int GetAttack(void);
    int GetHealthValue(void);
    void PrintName(void);
    virtual void PrintDescription(void) = 0;
private:
    int Attack;
    int HealthValue;
    string ObjectName;
};


#endif /* AbstractObject_hpp */
