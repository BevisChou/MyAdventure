#include "Util.hpp"

void GenerateCommand(const string& input, pair<Command,int>& cmdPair){
    stringstream ss;
    string paramStr;
    ss << input;
    ss >> paramStr;
    cmdPair.first = DefaultCmd;
    if(paramStr == "go"){
        ss >> paramStr;
        if(paramStr == "up"){
            cmdPair.first = GoUp;
        }
        else if(paramStr == "down"){
            cmdPair.first = GoDown;
        }
        else if(paramStr == "north"){
            cmdPair.first = GoNorth;
        }
        else if(paramStr == "south"){
            cmdPair.first = GoSouth;
        }
        else if(paramStr == "west"){
            cmdPair.first = GoWest;
        }
        else if(paramStr == "east"){
            cmdPair.first = GoEast;
        }
        else{
            cmdPair.first = DefaultCmd;
        }
    }
    else if(paramStr == "pick" || paramStr == "inspect" || paramStr == "drop"){
        int paramInt;
        if(ss >> paramInt){
            if(paramStr == "pick"){
                cmdPair.first = PickItem;
            }
            else if(paramStr == "inspect"){
                cmdPair.first = InspectItem;
            }
            else if(paramStr == "drop"){
                cmdPair.first = DropItem;
            }
            cmdPair.second = paramInt;
        }
    }
    else if(paramStr == "help"){
        cmdPair.first = Help;
    }
}

ActionType GenerateAction(const string& input){
    ActionType ret = DefaultAction;
    if(input == "eat"){
        ret = FeedPlayer;
    }
    else if(input == "hold"){
        ret = HoldInHand;
    }
    return ret;
}

void SetRandSeed(void){
    srand((unsigned int)time(NULL));
}

int GetRand(int min, int max){
    if(max < min){
        max = min;
    }
    return min + rand() % (max - min + 1);
}

float GetRandPercentage(){
    return GetRand(0, 100) * 1.0 / 100;
}

Direction GetRandomDirection(void){
    Direction ret = (Direction) GetRand(0, NumOfDirection - 1);
    return ret;
}

Direction GetOppositeDirection(Direction d){
    Direction ret = None;
    switch (d) {
        case Up:
            ret = Down;
            break;
        case Down:
            ret = Up;
            break;
        case North:
            ret = South;
            break;
        case South:
            ret = North;
            break;
        case West:
            ret = East;
            break;
        case East:
            ret = West;
            break;
        default:
            break;
    }
    return ret;
}

string GetDirectionString(Direction d){
    string tab[NumOfDirection] = {"Up", "Down", "North", "South", "West", "East"}; // Must be aligned with the enum in the header file.
    return tab[d];
}

Difficulty PromptDifficulty(void){
    int d;
    string buf;
    cout << "Please select difficulty level: " << endl;
    cout << "0: Easy" << endl <<  "1: Normal" << endl << "2: Hard" << endl;
    do{
        cout << "Please enter corresponding number: ";
        cin >> d;
    } while(d < 0 || d > 2);
    getline(cin, buf);
    return (Difficulty) d;
}
