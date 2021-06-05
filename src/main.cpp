#include <iostream>
#include <string>
#include "Adventure.hpp"
#include "Util.hpp"

using namespace std;

int main() {
    string buf;
    pair<Command, int> cmd;
    Difficulty difficultyLevel = PromptDifficulty();
    Adventure myAdventure(difficultyLevel);
    myAdventure.GetSetPlayerName();
    myAdventure.PrintWelcomeMsg();
//    myAdventure.PrintRoleLocations(); // debug
    while(!myAdventure.HasEnded()){
        myAdventure.PromptOpt();
        getline(cin, buf);
        GenerateCommand(buf, cmd);
        myAdventure.ExecuteCommand(cmd);
        myAdventure.Update();
    }
    myAdventure.PrintEndingMsg();
    return 0;
}
