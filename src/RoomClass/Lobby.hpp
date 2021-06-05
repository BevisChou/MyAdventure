//
//  Lobby.hpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#ifndef Lobby_hpp
#define Lobby_hpp

#include <stdio.h>
#include "AbstractRoom.hpp"

class Lobby : public AbstractRoom{
public:
    Lobby(int id, Difficulty d);
    void ShowRoomDescription(Difficulty d);
};

#endif /* Lobby_hpp */
