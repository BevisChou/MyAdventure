#include "Book.hpp"

Book::Book(void) : AbstractObject(0, 0, "Book") {}

ActionType Book::Action(){
    string input;
    PrintDescription();
    cout << "Do you want to eat it, or hold it in hand, or do nothing?" << endl;
    getline(cin, input);
    return GenerateAction(input);
    // There could be more customized actions.
}

void Book::PrintDescription(void){
    cout << "This is a book." << endl;
}
