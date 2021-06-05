#include "Princess.hpp"

//const float EasyPositionRangeForPrincess = 1 / 6;
//const float NormalPositionRangeForPrincess = 1 / 6;
//const float HardPositionRangeForPrincess = 1 / 6;

Princess::Princess(Difficulty d, int roomNum)  : AbstractRole(InitializePosition(d, roomNum), InitializeHealthPoint(d)) {}

void Princess::Interact(void) {}

int Princess::InitializePosition(Difficulty d, int roomNum){
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

int Princess::InitializeHealthPoint(Difficulty d){
    return 0;
}
