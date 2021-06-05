#include "Key.hpp"

Key::Key(void) : AbstractObject(0, -1, "Key"){}

void Key::PrintDescription(void){
    cout << "This is a key. Don't know which door it could unlock." << endl;
}

bool Key::IsMatched(const pair<int, int>& needed){
    return Match.first == needed.first && Match.second == needed.second;
}

ActionType Key::Action(){
    string input;
    PrintDescription();
    cout << "Do you want to eat it, or hold it in hand, or do nothing?" << endl;
    getline(cin, input);
    return GenerateAction(input);
    // There could be more customized actions.
}
