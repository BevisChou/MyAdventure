#include "Monster.hpp"

const int EasyHealthPointForMonster = 2;
const int NormalHealthPointForMonster = 3;
const int HardHealthPointForMonster = 5;

//const float EasyPositionRange = 1 / 6;
//const float NormalPositionRange = 1 / 6;
//const float HardPositionRange = 1 / 6;

Monster::Monster(Difficulty d, int roomNum) : AbstractRole(InitializePosition(d, roomNum), InitializeHealthPoint(d)) {}

void Monster::Interact(void){}

int Monster::InitializePosition(Difficulty d, int roomNum){
    int ret;
    switch (d) {
        case Easy:
            ret = GetRand(1, roomNum - 1);
            break;
        case Normal:
            ret = GetRand(1, roomNum - 1);
            break;
        case Hard:
            ret = GetRand(1, roomNum - 1);
            break;
        default:
            break;
    }
    return ret;
}

int Monster::InitializeHealthPoint(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = GetRand(1, EasyHealthPointForMonster);
            break;
        case Normal:
            ret = GetRand(1, NormalHealthPointForMonster);
            break;
        case Hard:
            ret = GetRand(1, HardHealthPointForMonster);
            break;
        default:
            break;
    }
    return ret;
}
