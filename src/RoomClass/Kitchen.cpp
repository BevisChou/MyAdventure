#include "Kitchen.hpp"

Kitchen::Kitchen(int id, Difficulty d) : AbstractRoom(id, d, "Kitchen") {}

void Kitchen::ShowRoomDescription(Difficulty d){
    if(d != Hard){
        cout << "Room ID is " << RoomID << ". ";
    }
    cout << "This is a kitchen. " << endl;
}
