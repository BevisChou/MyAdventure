#ifndef AbstractRoom_hpp
#define AbstractRoom_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Sword.hpp"
#include "Key.hpp"
#include "Book.hpp"
#include "Food.hpp"
#include "AbstractObject.hpp"
#include "Util.hpp"

using namespace std;

class AbstractRoom{
public:
    AbstractRoom(int id, Difficulty d, string name);
    int GetNeighbour(Direction d);
    bool RequiresKey(Direction d);
    void ShowExits(void);
    void ShowExits(int dummy); // debug
    virtual void ShowRoomDescription(Difficulty d) = 0;
    AbstractObject* GetItem(int id);
    void ShowItemsInRoom(void);
    void AddItemToRoom(AbstractObject* obj);
    void RemoveItem(int id);
    void SetNeighbour(Direction d, int neighbourId, bool isKeyNeeded);
    int GetRoomID(void);
protected:
    int RoomID;
    string Name;
    int Neighbours[NumOfDirection];
    bool KeyRequirements[NumOfDirection];
    vector<AbstractObject*> Items;
    AbstractObject* GetRandomObject(Difficulty d);
    float GetItemPossibility(Difficulty d);
};

#endif /* AbstractRoom_hpp */
