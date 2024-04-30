#include <string>
#include <iostream>
#include <limits>
#include "a4b.hpp"

using std::string;
using std::cout;
using std::cin;

int main() {
    float input;
    float m;
    char choice;

    // create the initial list of norse gods
    Asgard asgard = Asgard("Loki");
    asgard.addGod("Thor");
    asgard.addGod("Odin");
    asgard.addGod("Freja");

    while (true) {
        // grab user input
        while (true) {
            cout << "Enter a number: ";
            cin >> input;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter only numbers!\n";
            } else {
                break;
            }
        }

        // grab value for m
        while (true) {
            cout << "Enter starting value for m: ";
            cin >> m;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter only numbers!\n";
            } else {
                break;
            }
        }

        // add the user input to class
        asgard.setInput(input);

        // set the m parameter
        asgard.setM(m);

        // recursively traverse the list
        float r = asgard.traverse();
        cout << "Return: " << r << "\n";

        // ask the user to run program again
        while (true) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nGo again? (y/n): ";
            std::cin.get(choice);
            if (!std::cin.good() || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
                std::cout << "Choice not recognized, try again!" << std::endl;
            } else {
                if (choice == 'y' || choice == 'Y')
                    break;
                return 0;
            }
        }
    }
}
