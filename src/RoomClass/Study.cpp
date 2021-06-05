//
//  Study.cpp
//  proj2
//
//  Created by Zheng Zhou on 2021/6/2.
//

#include "Study.hpp"

Study::Study(int id, Difficulty d) : AbstractRoom(id, d, "Study") {}

void Study::ShowRoomDescription(Difficulty d){
    if(d != Hard){
        cout << "Room ID is " << RoomID << ". ";
    }
    cout << "This is a study." << endl;
}
