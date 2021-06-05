#include "AbstractObject.hpp"

AbstractObject::AbstractObject(int attack, int healthValue, string name) : Attack(attack), HealthValue(healthValue), ObjectName(name) {}

int AbstractObject::GetAttack(void){
    return Attack;
}

int AbstractObject::GetHealthValue(void){
    return HealthValue;
}

void AbstractObject::PrintName(void){
    cout << ObjectName << endl;
}
