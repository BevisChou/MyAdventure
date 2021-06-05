#include "Sword.hpp"

const int EasySwordAttack = 1;
const int NormalSwordAttack = 3;
const int HardSwordAttack = 2;

Sword::Sword(Difficulty d) : AbstractObject(InitializeAttack(d), 0, "Sword"){}

ActionType Sword::Action(){
    string input;
    PrintDescription();
    cout << "Do you want to hold it in hand, or do nothing?" << endl;
    getline(cin, input);
    return GenerateAction(input);
    // There could be more customized actions.
}

void Sword::PrintDescription(void){
    cout << "This is a sword." << endl;
}

int Sword::InitializeAttack(Difficulty d){
    int attack;
    switch (d) {
        case Easy:
            attack = EasySwordAttack;
            break;
        case Normal:
            attack = NormalSwordAttack;
            break;
        case Hard:
            attack = HardSwordAttack;
            break;
        default:
            break;
    }
    return GetRand(0, attack);
}
