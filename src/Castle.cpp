#include "Castle.hpp"

const int RoomGenerateRound = 2;

const int EasyRandomConnectRound = 0;
const int NormalRandomConnectRound = 3;
const int HardRandomConnectRound = 5;

const float EasyKeyRequirementRatio = 0;
const float NormalKeyRequirementRatio = 0.2;
const float HardKeyRequirementRatio = 0.3;

const int EasyLayerNum = 2;
const int NormalLayerNum = 3;
const int HardLayerNum = 5;

Castle::Castle(Difficulty d){
    SetRandSeed();
    int layerNum = GetLayerNum(d);
    queue<AbstractRoom*> oldRoomQueue;
    queue<AbstractRoom*> newRoomQueue;
    Rooms.push_back(new Lobby(0, d)); // Only one lobby, whose id is 0.
    oldRoomQueue.push(Rooms[0]);
    AbstractRoom *oldRoom, *newRoom;
    for(int i = 0; i < layerNum; i++){
        SetRandSeed();
        while(!oldRoomQueue.empty()){
            oldRoom = oldRoomQueue.front();
            oldRoomQueue.pop();
            for(int i = 0; i < RoomGenerateRound; i++){
                Direction randomD = GetRandomDirection();
                if(oldRoom->GetNeighbour(randomD) == -1){
                    newRoom = GetRandomRoom(d);
                    Rooms.push_back(newRoom);
                    ConnectRooms(oldRoom, newRoom, randomD, d);
                    newRoomQueue.push(newRoom);
                }
            }
        }
        while(!newRoomQueue.empty()){
            oldRoomQueue.push(newRoomQueue.front());
            newRoomQueue.pop();
        }
    }
    // Randomly connect rooms.
    SetRandSeed();
    int iteration = GetRandomConnectRound(d);
    for(int i = 0; i < iteration; i++){
        ConnectRoomsRandomly(d);
    }
}

AbstractRoom* Castle::GetRoom(int roomId){
    AbstractRoom* ret = nullptr;
    if(roomId >= 0 && roomId < GetRoomNum()){
        ret = Rooms[roomId];
    }
    return ret;
}

int Castle::GetRoomNum(void){
    return (int)Rooms.size();
}

int Castle::GetLayerNum(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = EasyLayerNum;
            break;
        case Normal:
            ret = NormalLayerNum;
            break;
        case Hard:
            ret = HardLayerNum;
            break;
        default:
            break;
    }
    return ret;
}

AbstractRoom* Castle::GetRandomRoom(Difficulty d){
    AbstractRoom* ret = nullptr;
    int newRoomId = (int) Rooms.size();
    RoomType roomType = (RoomType) GetRand(0, NumOfRoomType - 1);
    switch (roomType) {
        case StudyType:
            ret = new Study(newRoomId, d);
            break;
        case KitchenType:
            ret = new Kitchen(newRoomId, d);
            break;
        case BedroomType:
            ret = new Bedroom(newRoomId, d);
            break;
        default:
            break;
    }
    return ret;
}

void Castle::ConnectRoomsRandomly(Difficulty d){
    int room1Id = GetRandomRoomID(), room2Id = GetRandomRoomID();
    if(room1Id != room2Id){
        vector<Direction> possibleDirFromRoom1;
        for(int i = 0; i < NumOfDirection; i++){
            if(GetRoom(room1Id)->GetNeighbour((Direction)i) == -1 && GetRoom(room2Id)->GetNeighbour(GetOppositeDirection((Direction)i)) == -1){
                possibleDirFromRoom1.push_back((Direction)i);
            }
        }
        if(possibleDirFromRoom1.size() > 0){
            Direction dir = possibleDirFromRoom1[GetRand(0, (int)possibleDirFromRoom1.size() - 1)];
            ConnectRooms(GetRoom(room1Id), GetRoom(room2Id), dir, d);
        }
    }
}

int Castle::GetRandomRoomID(void){
    return GetRand(0, (int)Rooms.size() - 1);
}

bool Castle::GetRandomKeyRequirement(Difficulty d){
    float ratio;
    switch (d) {
        case Easy:
            ratio = EasyKeyRequirementRatio;
            break;
        case Normal:
            ratio = NormalKeyRequirementRatio;
            break;
        case Hard:
            ratio = HardKeyRequirementRatio;
        default:
            break;
    }
    return GetRandPercentage() < ratio;
}

void Castle::ConnectRooms(AbstractRoom* room1, AbstractRoom* room2, Direction dFromRoom1, Difficulty d){
    room1->SetNeighbour(dFromRoom1, room2->GetRoomID(), GetRandomKeyRequirement(d));
    room2->SetNeighbour(GetOppositeDirection(dFromRoom1), room1->GetRoomID(), GetRandomKeyRequirement(d));
}

int Castle::GetRandomConnectRound(Difficulty d){
    int ret;
    switch (d) {
        case Easy:
            ret = EasyRandomConnectRound;
            break;
        case Normal:
            ret = NormalRandomConnectRound;
            break;
        case Hard:
            ret = HardRandomConnectRound;
            break;
        default:
            break;
    }
    return ret;
}
