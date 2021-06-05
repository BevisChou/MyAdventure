#include "Adventure.hpp"

const int EasyMonsterNum = 1;
const int NormalMonsterNum = 3;
const int HardMonsterNum = 5;

Adventure::Adventure(Difficulty d) : DifficultyLevel(d), MyStatus(InProgress), MyCastle(d), MyPlayer(d), MyPrincess(d, MyCastle.GetRoomNum()) {
    int monsterNum;
    switch (d) {
        case Easy:
            monsterNum = EasyMonsterNum;
            break;
        case Normal:
            monsterNum = NormalMonsterNum;
            break;
        case Hard:
            monsterNum = HardMonsterNum;
            break;
    }
    for(int i = 0; i < monsterNum; i++){
        MyMonsters.push_back(Monster(d, MyCastle.GetRoomNum()));
    }
}

void Adventure::GetSetPlayerName(void){
    string buf;
    cout << "Please enter your name: ";
    cin >> buf;
    MyPlayer.SetName(buf);
    getline(cin, buf);
}

void Adventure::PrintWelcomeMsg(void){
    cout << "Welcome to the adventure, " << MyPlayer.GetName() << "!" << endl;
    cout << "If you don't know what to do, simply input \"help\"!" << endl;
}

void Adventure::PrintEndingMsg(void){
    cout << endl << "---" << endl;
    switch (MyStatus) {
        case Died:
            cout << "It's very unfortunate that you are defeated by monster before you found your way out with the princess. Before you finally close your eyes, you see that the monster is eating your body, and the princess is screaming in deep fear." << endl;
            break;
        case DiedAlone:
            cout << "You are defeated by the monster. Before you close your eyes, you see that the monster is eating your body. You feel somewhat relieved that the princess is not seeing this." << endl;
            break;
        case OutWithPrincess:
            cout << "You finally find your way out with the princess. You look into each others\' eyes, and at the same time, you come up with the names for your children." << endl;
            break;
        default:
            break;
    }
}

void Adventure::PrintHelpMsg(void){
    cout << endl << "---" << endl;
    cout << "Tips:" << endl;
    cout << "1. To go to a direction, say, north, input \"go north\"." << endl;
    cout << "2. To pick an item, say, item 1, input \"pick 1\"." << endl;
    cout << "3. To drop an item in your knapsack, say, item 2, input \"drop 2\"." << endl;
    cout << "4. To inspect on an item in your knapsack, say, item 3, input \"inspect 3\". There are further actions, for example, hold the item in your hand, or eat the item, simply input \"hold\" or \"eat\", after being prompted." << endl;
}

bool Adventure::HasEnded(void){
    return !(MyStatus == InProgress || MyStatus == FoundPrincess);
}

void Adventure::PromptOpt(void){
    AbstractRoom* curRoom = MyCastle.GetRoom(MyPlayer.GetPosition());
    cout << endl << "---" << endl;
    curRoom->ShowRoomDescription(DifficultyLevel);
    curRoom->ShowExits();
    curRoom->ShowItemsInRoom();
    MyPlayer.ViewAssets();
    MyPlayer.ShowHealthPoint();
    cout << endl << "Please enter your option: ";
}

void Adventure::ExecuteCommand(pair<Command, int>& cmdPair){
    Command cmd = cmdPair.first;
    Direction tarDirection = None;
    int curRoomId = MyPlayer.GetPosition();
    AbstractRoom* curRoom = MyCastle.GetRoom(curRoomId);
    AbstractObject* obj;
    switch (cmd) {
        case GoUp:
            tarDirection = Up;
            break;
        case GoDown:
            tarDirection = Down;
            break;
        case GoNorth:
            tarDirection = North;
            break;
        case GoSouth:
            tarDirection = South;
            break;
        case GoWest:
            tarDirection = West;
            break;
        case GoEast:
            tarDirection = East;
            break;
        case Help:
            PrintHelpMsg();
            break;
        case PickItem:
        {
            obj = curRoom->GetItem(cmdPair.second);
            if(obj == nullptr){
                cout << endl << "---" << endl;
                cout << "No such item." << endl;
            }
            else if(MyPlayer.IsKnapsackFull()){
                cout << endl << "---" << endl;
                cout << "Knapsack full, please drop some items first." << endl;
            }
            else{
                MyPlayer.AddItemToKnapsack(obj);
                curRoom->RemoveItem(cmdPair.second);
            }
        }
            break;
        case InspectItem:
        {
            obj = MyPlayer.GetItem(cmdPair.second);
            if(obj == nullptr){
                cout << endl << "---" << endl;
                cout << "No such item." << endl;
            }
            else{
                ActionType act = obj->Action();
                HandleAction(act, cmdPair.second);
            }
        }
            break;
        case DropItem:
        {
            obj = MyPlayer.GetItem(cmdPair.second);
            if(obj == nullptr){
                cout << endl << "---" << endl;
                cout << "No such item." << endl;
            }
            else{
                MyPlayer.RemoveItem(cmdPair.second);
                curRoom->AddItemToRoom(obj);
            }
        }
            break;
        default:
            cout << endl << "---" << endl;
            cout << "No such option." << endl;
            break;
    }
    if(tarDirection != None){
        int tarRoomId = curRoom->GetNeighbour(tarDirection);
        if(tarRoomId != -1){
            if(!curRoom->RequiresKey(tarDirection) || MyPlayer.HasKey(make_pair(curRoomId, tarRoomId))){
                MyPlayer.SetPosition(tarRoomId);
            }
            else{
                cout << endl << "---" << endl;
                cout << "The door requires a key to open." << endl;
            }
        }
        else{
            cout << endl << "---" << endl;
            cout << "No room at this direction." << endl;
        }
    }
}

void Adventure::Update(void){
    if(MyStatus == FoundPrincess){
        cout << endl << "Princess: I'm scared, please help me get out." << endl;
    }
    int curRoomId = MyPlayer.GetPosition(), monsterNum = (int)MyMonsters.size(), totalMonsterHP = 0;
    if(MyPrincess.GetPosition() == curRoomId){
        MyStatus = FoundPrincess;
    }
    for(int i = 0; i < monsterNum; i++){
        if(MyMonsters[i].GetPosition() == curRoomId){
            totalMonsterHP += MyMonsters[i].GetHealthPoint();
        }
    }
    if(totalMonsterHP > 0 && totalMonsterHP > MyPlayer.GetAttack()){
        MyStatus = MyStatus == FoundPrincess ? Died : DiedAlone;
    }
    else if(curRoomId == 0 && MyStatus == FoundPrincess){
        MyStatus = OutWithPrincess;
    }
}

void Adventure::HandleAction(ActionType& act, int itemIndex){
    AbstractObject* obj;
    switch (act) {
        case FeedPlayer:{
            obj = MyPlayer.GetItem(itemIndex);
            MyPlayer.AddHealthPoint(obj->GetHealthValue());
            MyPlayer.RemoveItem(itemIndex);
            break;
        }
        case HoldInHand:{
            obj = MyPlayer.GetItem(itemIndex);
            AbstractObject* itemPreviouslyInHand = MyPlayer.GetItemInHand();
            if(itemPreviouslyInHand != nullptr){
                MyPlayer.AddItemToKnapsack(itemPreviouslyInHand);
            }
            MyPlayer.RemoveItem(itemIndex);
            MyPlayer.HoldInHand(obj);
            break;
        }
        default:
            break;
    }
}

void Adventure::PrintRoleLocations(void){
    cout << "Princess is at room " << MyPrincess.GetPosition() << endl;
    for(auto itor = MyMonsters.begin(); itor != MyMonsters.end(); itor++){
        cout << "A monster is at room " << itor->GetPosition() << endl;
    }
}
