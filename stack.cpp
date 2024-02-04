#include <iostream>
#include <string>
#include <cctype>
#include <array>
#include <ios>
#include <limits>

bool validateSelection(const std::string&);
bool validateEntry(std::string&);
void push(const std::string&, std::string*, int&);
void pop(std::string*, int&);

int main() {
    bool validInput = false;
    std::string selection;
    std::string stackInput;
    int index = 0;
    std::string stack[5];

    while (true) {
        // get user selection
        while (validInput != true) {
            std::cout<<"Push to or pop from the stack? (push/pop)\n";
            std::cin>>selection;
            validInput = validateSelection(selection);
        };
        validInput = false;

        // perform pop operation
        if (selection.length() == 3) {
            pop(stack, index);
        }

        if (selection.length() == 4) {
            // get chars to push
            while (validInput != true) {
                std::cout<<"Enter up to 2 characters to push: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, stackInput);
                validInput = validateEntry(stackInput);
            }
            validInput = false;
            push(stackInput, stack, index);
            std::cout<<"index: "<<index<<"\n";
        }
    }
}

bool validateSelection(const std::string& s) {
    // validate all characters are letters or spaces
    for (const char c : s) {
        if (!isalpha(c) && !isspace(c)) {
            std::cout<<"Please enter valid characters!\n";
            return false;
        }
    }

    // validate the number of characters input by user
    if (s.length() > 4 || s.length() < 3) {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }

    // valide user selection
    if (s.at(0) != 'p' && s.at(0) != 'P') {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }
    if (s.at(1) != 'u' && s.at(1) != 'U' && s.at(1) != 'o' && s.at(1) != 'O') {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }
    if (s.at(2) != 's' && s.at(2) != 'S' && s.at(2) != 'p' && s.at(2) != 'P') {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }
    if (s.length() == 4 && s.at(3) != 'h' && s.at(3) != 'H') {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }

    return true;
}

bool validateEntry(std::string& s) {
    // validate all characters are letters or spaces
    for (const char c : s) {
        if (!isalpha(c) && !isspace(c) && c != '.') {
            std::cout<<"Please enter valid characters!\n";
            return false;
        }
    }

    // validate the number of characters input by user
    if (s.length() > 2) {
        std::cout<<"Too many chars! Try agian.\n";
        return false;
    }

    // convert . to space
    if (s.length() == 1 && s == "."){
        s = " ";
    }
    if (s.length() == 2 && (s[0] == '.' || s[1] == '.')) {
        if (s[0] == '.') {
            s[0] = ' ';
        }
        if (s[1] == '.') {
            s[1] = ' ';
        }
    }

    return true;
}

void push(const std::string& s, std::string *stack, int& index) {
    // catch overflow case
    if (index == 4) {
        std::cout<<"Overflow! Cannot push to stack...\n";
        return;
    }

    stack[index] = s;
    ++index;
    return;
}

void pop(std::string *stack, int& index) {
    // catch underflow case
    if (index == 0) {
        std::cout<<"Underflow! Cannot pop from stack...\n";
        return;
    }

    std::string entry = stack[index-1];
    std::cout<<"Popped from stack: \""<<entry<<"\"\n";
    stack[index-1] = stack[index];
    --index;
    return;
}
