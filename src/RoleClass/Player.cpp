#include "Player.hpp"

const int EasyKnapsackSize = 10;
const int NormalKnapsackSize = 5;
const int HardKnapsackSize = 3;

const int EasyHealthPointForPlayer = 10;
const int NormalHealthPointForPlayer = 5;
const int HardHealthPointForPlayer = 3;

Player::Player(Difficulty d) : AbstractRole(InitializePosition(d), InitializeHealthPoint(d)), FoundPrincess(false), KnapsackSize(InitializeKnapsackSize(d)), ItemInHand(nullptr) {}

void Player::ViewAssets(void){
    int numOfItems = (int)Assets.size();
    if(numOfItems > 0){
        cout << "The items in the knapsack are as follows:" << endl;
        for(int i = 1; i <= numOfItems; i++){
            cout << "Item " << i << ": ";
            Assets[i - 1]->PrintName();
        }
    }
}

void Player::ShowHealthPoint(void){
    cout << "Current health point is " << CurrentHealthPoint << "/" << TotalHealthPoint << endl;
}

void Player::SetName(string name){
    Name = name;
}

string Player::GetName(void){
    return Name;
}

bool Player::HasKey(const pair<int, int>& roomIdPair){
    bool ret = false;
    for(auto itor = Assets.begin(); itor != Assets.end(); itor++){
        Key* ptrKey = dynamic_cast<Key*>(*itor);
        if(ptrKey != NULL && ptrKey->IsMatched(roomIdPair)){
            ret = true;
            break;
        }
    }
    return ret;
}

bool Player::IsKnapsackFull(void){
    return Assets.size() == KnapsackSize;
}

void Player::AddItemToKnapsack(AbstractObject* obj){
    Assets.push_back(obj);
}

AbstractObject* Player::GetItem(int id){
    // id is 1-indexed.
    AbstractObject* ret = nullptr;
    if(id > 0 && id <= Assets.size()){
        ret = Assets[id - 1];
    }
    return ret;
}

AbstractObject* Player::GetItemInHand(void){
    return ItemInHand;
}

void Player::RemoveItem(int id){
    if(id > 0 && id <= Assets.size()){
        Assets.erase(Assets.begin() + id - 1);
    }
}

void Player::AddHealthPoint(int hp){
    CurrentHealthPoint += hp;
    if(CurrentHealthPoint > TotalHealthPoint){
        CurrentHealthPoint = TotalHealthPoint;
    }
}

void Player::HoldInHand(AbstractObject* obj){
    ItemInHand = obj;
}

int Player::GetAttack(void){
    int ret = 0;
    if(ItemInHand != nullptr){
        ret = ItemInHand->GetAttack();
    }
    return ret;
}

int Player::InitializePosition(Difficulty d, int roomNum){
    return 0;
}

int Player::InitializeHealthPoint(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = EasyHealthPointForPlayer;
            break;
        case Normal:
            ret = NormalHealthPointForPlayer;
            break;
        case Hard:
            ret = HardHealthPointForPlayer;
            break;
        default:
            break;
    }
    return ret;
}

int Player::InitializeKnapsackSize(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = EasyKnapsackSize;
            break;
        case Normal:
            ret = NormalKnapsackSize;
            break;
        case Hard:
            ret = HardKnapsackSize;
            break;
        default:
            break;
    }
    return ret;
}

void Player::Interact(void) {}

