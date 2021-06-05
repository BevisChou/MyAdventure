#include "AbstractRoom.hpp"

const int ItemGenerateRound = 3;

const float EasyItemPossibility = 0.4;
const float NormalItemPossibility = 0.2;
const float HardItemPossibility = 0.1;

AbstractRoom::AbstractRoom(int id, Difficulty d, string name) : RoomID(id), Name(name) {
    for(int i = 0; i < NumOfDirection; i++){
        Neighbours[i] = -1;
    }
    for(int i = 0; i < ItemGenerateRound; i++){
        if(GetRandPercentage() <= GetItemPossibility(d)){
            Items.push_back(GetRandomObject(d));
        }
    }
}

void AbstractRoom::ShowExits(void){
    cout << "This room has the following exits: ";
    for(int i = 0; i < NumOfDirection; i++){
        if(GetNeighbour((Direction)i) != -1){
            cout << GetDirectionString((Direction)i) << " ";
        }
    }
    cout << endl;
}

void AbstractRoom::ShowExits(int dummy){
    cout << "This room's id: " << RoomID << endl;
    for(int i = 0; i < NumOfDirection; i++){
        if(GetNeighbour((Direction)i) != -1){
            cout << GetDirectionString((Direction)i) << "'s id: " << GetNeighbour((Direction)i) << endl;
        }
    }
    cout << endl;
}

int AbstractRoom::GetNeighbour(Direction d){
    return Neighbours[d];
}

bool AbstractRoom::RequiresKey(Direction d){
    return KeyRequirements[d];
}

AbstractObject* AbstractRoom::GetItem(int id){
    AbstractObject* ret = nullptr;
    if(id > 0 && id <= Items.size()){
        ret = Items[id - 1];
    }
    return ret;
}

void AbstractRoom::ShowItemsInRoom(void){
    int numOfItems = (int)Items.size();
    if(numOfItems > 0){
        cout << "This room has the following items: " << endl;
        for(int i = 1; i <= numOfItems; i++){
            cout << "Item " << i << ": ";
            Items[i - 1]->PrintName();
        }
    }
}

void AbstractRoom::AddItemToRoom(AbstractObject* obj){
    Items.push_back(obj);
}

void AbstractRoom::RemoveItem(int id){
    if(id > 0 && id <= Items.size()){
        Items.erase(Items.begin() + id - 1);
    }
}

void AbstractRoom::SetNeighbour(Direction d, int neighbourId, bool isKeyNeeded){
    Neighbours[d] = neighbourId;
    KeyRequirements[d] = isKeyNeeded;
}

int AbstractRoom::GetRoomID(void){
    return RoomID;
}

AbstractObject* AbstractRoom::GetRandomObject(Difficulty d){
    AbstractObject* ret = nullptr;
    ItemType itemType = (ItemType) GetRand(0, NumOfItemType - 1);
    switch (itemType) {
        case KeyType:
            ret = new Key();
            break;
        case BookType:
            ret = new Book();
            break;
        case FoodType:
            ret = new Food(d);
            break;
        case SwordType:
            ret = new Sword(d);
        default:
            break;
    }
    return ret;
}

float AbstractRoom::GetItemPossibility(Difficulty d){
    float ret;
    switch (d) {
        case Easy:
            ret = EasyItemPossibility;
            break;
        case Normal:
            ret = NormalItemPossibility;
            break;
        case Hard:
            ret = HardItemPossibility;
            break;
        default:
            break;
    }
    return ret;
}

