//
//  Bedroom.cpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#include "Bedroom.hpp"

Bedroom::Bedroom(int id, Difficulty d) : AbstractRoom(id, d, "Bedroom") {}

void Bedroom::ShowRoomDescription(Difficulty d){
    if(d != Hard){
        cout << "Room ID is " << RoomID << ". ";
    }
    cout << "This is a bedroom." << endl;
}
