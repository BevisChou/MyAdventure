#ifndef Castle_hpp
#define Castle_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include "Lobby.hpp"
#include "Kitchen.hpp"
#include "Study.hpp"
#include "Bedroom.hpp"
#include "Util.hpp"

class Castle{
public:
    Castle(Difficulty d);
    AbstractRoom* GetRoom(int roomId);
    int GetRoomNum(void);
private:
    vector<AbstractRoom*> Rooms;
    int GetLayerNum(Difficulty d);
    AbstractRoom* GetRandomRoom(Difficulty d);
    void ConnectRoomsRandomly(Difficulty d);
    int GetRandomRoomID(void);
    bool GetRandomKeyRequirement(Difficulty d);
    void ConnectRooms(AbstractRoom* room1, AbstractRoom* room2, Direction dFromRoom1, Difficulty d);
    int GetRandomConnectRound(Difficulty d);
};

#endif /* Castle_hpp */
