#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#ifndef STACKCLASS_HPP
#define STACKCLASS_HPP

class StackClass {
private:
    bool validInput = false;
    std::string selection;
    std::string userInput;
    char *stackInput;
    int index = 0;
    bool hasLooped;
    std::vector<char*> stack;


    /*
        Remarks: Takes the user input and checks that it matches one of the two options (push/pop)
        Params: std::string - A string that will be checked
        Returns: bool - Returns true if the input string matches one of the selections, otherwise returns false
    */
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
        if (s.at(0) != 'p' && s.at(0) != 'P' && s.at(0) != 'q' && s.at(0) != 'Q') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }
        if (s.at(1) != 'u' && s.at(1) != 'U' && s.at(1) != 'o' && s.at(1) != 'O') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }
        if (s.at(2) != 's' && s.at(2) != 'S' && s.at(2) != 'p' && s.at(2) != 'P' && s.at(2) != 'i' && s.at(2) != 'I') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }
        if (s.length() == 4 && s.at(3) != 'h' && s.at(3) != 'H' && s.at(3) != 't' && s.at(3) != 'T') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }

        return true;
    }

    /*
        Remarks: Takes the user input and runs a series of checks and modifications.
            1) All characters must be in the alphabet, spaces, or periods.
            2) Only 2 characters allowed
            3) Convert all periods to spaces
            4) Left justification
            5) Convert lowercase to uppercase
        Params: std::string - The string to run the checks/modifications on
        Returns: bool - true if all checks pass (1 and 2), false otherwise
    */
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

    /*
        Remarks: Converts the given input string to a cstring
        Params: std::string - input string
        Returns: char* - the cstring created from the input string
    */
    char *convertToCstring(const std::string& s) {
        char *cString;
        cString = new char[s.length() + 1]; //leave room for null terminator

        for (int i = 0; i < s.length(); i++) {
            cString[i] = s[i];
        }
        cString[s.length()] = '\0';

        return cString;
    }    
    
public:
    StackClass() {
        std::cout<<"* * * * * * * * * * * * * * *\n";
        std::cout<<"* Welcome to push and pop!  *\n";
        std::cout<<"* Type \"quit\" to exit.      *\n";
        std::cout<<"* * * * * * * * * * * * * * *\n\n";
    }

    void start() {
        while (true) {
            // get user selection
            while (validInput != true) {
                std::cout<<"Push or pop? (push/pop): ";
                std::cin>>selection;
                validInput = validateSelection(selection);
            };
            validInput = false;

            // perform pop operation
            if (selection.length() == 3) {
                pop(stack, index);
            }

            if (selection.length() == 4 && selection.at(0) != 'q' && selection.at(0) != 'Q') {
                // get chars to push
                while (validInput != true) {
                    std::cout<<"Enter up to 2 characters to push: ";

                    if (!hasLooped) {
                        std::cin.get();
                    }

                    std::getline(std::cin, userInput);
                    validInput = validateEntry(userInput);
                    hasLooped = true;
                }
                validInput = false;
                hasLooped = false;

                stackInput = convertToCstring(userInput);
                push(stackInput, stack, index);
            }

            if (selection.length() == 4 && (selection.at(0) == 'q' || selection.at(0) == 'Q')) {
                // quit was entered
                break;
            }
        }
    }

    /*
        Remarks: Inserts the given cstring to the next available vector location, marked by the index. Checks the index for overflow case where index is 4. Increments the index
        Params: char* - the input cstring to be inserted into the vector
                std::vector<char*>& - the vector of cstrings
                int& - the index for the vector
    */
    void push(char *s, std::vector<char*>& stack, int& index) {
        // catch overflow case
        if (index == 4) {
            std::cout<<"Overflow! Cannot push to stack...\n";
            return;
        }

        stack.resize(index + 1); // index + 1 since index starts at 0
        stack.insert(stack.begin() + index, s); // pushes to the vector position at index
        ++index;
        return;
    }

    /*
        Remarks: Deletes the vector entry at the location marked by the index. Checks for underflow case where index is 0. Decrements the index
        Params: char** - the vector of cstrings
                int - the index
    */
    void pop(std::vector<char*>& stack, int& index) {
        // catch underflow case
        if (index == 0) {
            std::cout<<"Underflow! Cannot pop from stack...\n";
            return;
        }

        char *temp = stack.at(index-1); // will throw an exception if out of range

        // print the cstring
        std::cout<<"Popped from stack: \"";
        for (int i = 0; i < strlen(temp); i++) {
            std::cout<<temp[i];
        }
        std::cout<<"\"\n";

        stack.at(index-1) = nullptr; // delete the last entry
        --index;
        return;
    }
};

#endif
