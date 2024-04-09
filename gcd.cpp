#include <iostream>
#include <limits>

/*recursive function to return the greatest common
denominator of two integer inputs
Params: int input1, int input2
Returns: int - the calculated gcd*/ 
int gcd(int input1, int input2) {
    if (input2 != 0) {
        return gcd(input2, input1%input2);
    } else {
        return input1;
    }  
}

int main() {
    int input1 = 0;
    int input2 = 0;
    char choice;
    int rVal = 0;
    bool validInput = false;

    while(true) {
        // grab user input
        while(validInput != true) {
            std::cout << "Enter your first number: ";
            std::cin >> input1;
            std::cout << "Enter your second number: ";
            std::cin >> input2;
    
            if (!std::cin.good()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter only integers!" << std::endl;
            } else {
                validInput = true;
            }
        }

        // get the greatest common denominator
        rVal = gcd(input1, input2);
        std::cout << "Greatest Common Denominator: " << gcd << std::endl;
        
        // get the users selection
        validInput = false;
        while (!validInput) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Go again? (y/n): ";
            std::cin.get(choice);
            if (!std::cin.good() || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
                std::cout << "Choice not recognized, try again!" << std::endl;
            } else {
                validInput = true;
            }
        }

        // exit the program
        if (choice == 'n' || choice == 'N') {
            return 0;
        }

        // reset input variables and bool
        input1 = 0;
        input2 = 0;
        validInput = false;
    }
}
