#ifndef Util_hpp
#define Util_hpp

#include <iostream>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;

enum Direction {Up, Down, North, South, West, East, NumOfDirection, None}; // IMPORTANT: If you want to add directions, add them before NumOfDirection.
enum Difficulty {Easy, Normal, Hard};
enum Command {GoUp, GoDown, GoNorth, GoSouth, GoWest, GoEast, PickItem, InspectItem, DropItem, Help, DefaultCmd};
enum ActionType {FeedPlayer, HoldInHand, DefaultAction};
enum Status {InProgress, DiedAlone, FoundPrincess, Died, OutWithPrincess};
enum RoomType {StudyType, BedroomType, KitchenType, NumOfRoomType, LobbyType}; // IMPORTANT: If you want to add room types, add them before NumOfRoomType.
enum ItemType {KeyType, BookType, SwordType, FoodType, NumOfItemType, }; // IMPORTANT: If you want to add item types, add them before NumOfItemType.

void SetRandSeed(void);
void GenerateCommand(const string& input, pair<Command, int>& cmdPair);
ActionType GenerateAction(const string& input);
int GetRand(int min, int max);
float GetRandPercentage(void);
Direction GetRandomDirection(void);
Direction GetOppositeDirection(Direction d);
string GetDirectionString(Direction d);
Difficulty PromptDifficulty(void);
#endif /* Util_hpp */
