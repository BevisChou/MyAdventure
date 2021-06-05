#include "Food.hpp"

const int EasyFoodHealthValue = 3;
const int NormalFoodHealthValue = 2;
const int HardFoodHealthValue = 1;

const int EasyFoodAttack = -1;
const int NormalFoodAttack = -2;
const int HardFoodAttack = -3;


Food::Food(Difficulty d) : AbstractObject(InitializeAttack(d), InitializeHealthValue(d), "Food") {}

ActionType Food::Action(){
    string input;
    PrintDescription();
    cout << "Do you want to eat it, or hold it in hand, or do nothing?" << endl;
    getline(cin, input);
    return GenerateAction(input);
    // There could be more customized actions.
}

void Food::PrintDescription(void){
    cout << "This is food." << endl;
}

int Food::InitializeAttack(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = EasyFoodAttack;
            break;
        case Normal:
            ret = NormalFoodAttack;
            break;
        case Hard:
            ret = HardFoodAttack;
            break;
        default:
            break;
    }
    return ret;
}

int Food::InitializeHealthValue(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = EasyFoodHealthValue;
            break;
        case Normal:
            ret = NormalFoodHealthValue;
            break;
        case Hard:
            ret = HardFoodHealthValue;
            break;
        default:
            break;
    }
    return ret;
}
