#include "AbstractRole.hpp"

AbstractRole::AbstractRole(int pos, int hp) : Position(pos), TotalHealthPoint(hp), CurrentHealthPoint(hp) {}

int AbstractRole::GetPosition(void){
    return Position;
}

void AbstractRole::SetPosition(int pos){
    Position = pos;
}

int AbstractRole::GetHealthPoint(void){
    return CurrentHealthPoint;
}
