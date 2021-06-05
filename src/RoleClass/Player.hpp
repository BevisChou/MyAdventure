#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "AbstractRole.hpp"
#include "AbstractObject.hpp"
#include "Key.hpp"
#include "Util.hpp"

class Player : public AbstractRole{
public:
    Player(Difficulty d);
    void ViewAssets(void);
    void ShowHealthPoint(void);
    void SetName(string name);
    string GetName(void);
    bool HasKey(const pair<int, int>& roomIdPair);
    bool IsKnapsackFull(void);
    void AddItemToKnapsack(AbstractObject* obj);
    AbstractObject* GetItem(int id);
    AbstractObject* GetItemInHand(void);
    void RemoveItem(int id);
    void AddHealthPoint(int hp);
    void HoldInHand(AbstractObject* obj);
    int GetAttack(void);
    void Interact(void);
private:
    string Name;
    int KnapsackSize;
    bool FoundPrincess;
    AbstractObject* ItemInHand;
    int InitializePosition(Difficulty d, int roomNum = 0);
    int InitializeHealthPoint(Difficulty d);
    int InitializeKnapsackSize(Difficulty d);
};

#endif /* Player_hpp */
