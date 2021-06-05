#ifndef Adventure_hpp
#define Adventure_hpp

#include <iostream>
#include <vector>
#include "Player.hpp"
#include "Princess.hpp"
#include "Monster.hpp"
#include "Castle.hpp"
#include "Util.hpp"
#include "AbstractObject.hpp"

using namespace std;

class Adventure{
public:
    Adventure(Difficulty d);
    void GetSetPlayerName(void);
    void PrintWelcomeMsg(void);
    void PrintEndingMsg(void);
    bool HasEnded(void);
    void PromptOpt(void);
    void ExecuteCommand(pair<Command,int>& cmdPair);
    void Update(void);
    void PrintHelpMsg(void);
    void PrintRoomIDs(void); // debug
    void PrintRoleLocations(void); // debug
private:
    Difficulty DifficultyLevel;
    Castle MyCastle;
    Princess MyPrincess;
    Player MyPlayer;
    vector<Monster> MyMonsters;
    void HandleAction(ActionType& act, int itemIndex);
    Status MyStatus;
};

#endif /* Adventure_hpp */
