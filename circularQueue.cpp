#include <iostream>
#include <string>

struct CircularQueue {
private: 
    char *head;
    char *tail;
    
public: 
    int dest;
    char payload[6];
    char ring[6];
    

    // constructor
    CircularQueue() {

    }

    int enqueue() {

    }

    int dequeue() {

    }

    // print the contents of the queue to the terminal
    void echo() {
        // check for empty queue
        if (head - tail == 0) {
            std::cout<<"Queue is Empty!\n";
            return;
        }

        std::cout<<"Queue Contents:\n";
        for (int i = 0; i < (tail - head); i++) {
            std::cout<<ring[i];
        }
        std::cout<<"\n";

        return;
    }

    // get the value at location pointed to by head
    char head() {
        return *head;
    }

    // get the value at location pointed to by tail
    char tail() {
        return *tail;
    }

};

bool validateSelection(const std::string&);
int enqueue();
int dequeue();
void printQueue();

int main() {
    std::cout<<"* * * * * * * * * * * * * * * *\n";
    std::cout<<"* Welcome to circular queue!  *\n";
    std::cout<<"* Type \"quit\" to exit.        *\n";
    std::cout<<"* * * * * * * * * * * * * * * *\n\n";

    int destination;
    char payload[6];
    std::string selection;
    CircularQueue circularQueue = CircularQueue();
    CircularQueue *structp;
    int rValue;

    bool validInput = false;
    while (true) {
        // get user selection
        while (validInput != true) {
            std::cout<<"Enqueue, dequeue, or print? (e/d/p): ";
            std::cin>>selection;
            validInput = validateSelection(selection);
        };
        validInput = false;
    }

    // terminate the program
    if (selection.at(0) == 'q' || selection.at(0) == 'Q') {
        return 0;
    }

    // handle enqueue
    if (selection.at(0) == 'e' || selection.at(0) == 'E') {
        rValue = enqueue();
    }

    // handle dequeue
    if (selection.at(0) == 'd' || selection.at(0) == 'D') {
        rValue = dequeue();
    }

    // handle printing the queue
    if (selection.at(0) == 'p' || selection.at(0) == 'P') {
        printQueue();
    }
}

bool validateSelection(const std::string& s) {
    // validate all characters are letters or spaces
    for (const char c : s) {
        if (!isalpha(c)) {
            std::cout<<"Please enter valid characters!\n";
            return false;
        }
    }

    // validate the number of characters input by user
    if (s.length() != 1 && s.length() != 4) {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }

    // valide user selection
    if (s.at(0) != 'e' && s.at(0) != 'E' && s.at(0) != 'd' && s.at(0) != 'D' && s.at(0) != 'p' && s.at(0) != 'P' && s.at(0) != 'q' && s.at(0) != 'Q') {
        std::cout<<"Choice not recognized, try agian!\n";
        return false;
    }
    if (s.length() == 4) {
        if (s.at(1) != 'u' && s.at(1) != 'U') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }
        if (s.at(2) != 'i' && s.at(2) != 'I') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }
        if (s.length() == 4 && s.at(3) != 'h' && s.at(3) != 'H' && s.at(3) != 't' && s.at(3) != 'T') {
            std::cout<<"Choice not recognized, try agian!\n";
            return false;
        }
    }

    return true;
}

int enqueue() {

}

int dequeue() {

}

void printQueue() {

}
