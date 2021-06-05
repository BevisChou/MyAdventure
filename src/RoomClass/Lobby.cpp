//
//  Lobby.cpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#include "Lobby.hpp"

Lobby::Lobby(int id, Difficulty d) : AbstractRoom(id, d, "Lobby") {}

void Lobby::ShowRoomDescription(Difficulty d){
    cout << "This is the lobby." << endl;
}
