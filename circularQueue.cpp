#include <iostream>
#include <string>
#include <cstring>
#include <limits>

struct QueueEntry {
    char payload[6] = "";
    int dest = 0;
};

struct CircularQueue {
private:
    QueueEntry *head;
    QueueEntry *tail;
    int tailIndex = 0; // keep track of tail position
    int headIndex = -1;

public:
    QueueEntry *queue = new QueueEntry[6];

    // constructor
    CircularQueue() {
        head = nullptr; // init to null to indicate q empty
        tail = &queue[0];
    }

    int enqueue(char *entry, int destination) {
        // update destination
        queue[tailIndex].dest = destination;

        // add user input to the queue
        strcpy(queue[tailIndex].payload, entry);

        // update head index and pointer if previously null
        if (head == nullptr) {
            head = tail;
            if (tailIndex == 5) {
                tailIndex = 0;
                headIndex = 0;
                tail = &queue[0];
            } else {
                headIndex = tailIndex;
                tailIndex += 1;
                tail = &queue[tailIndex];
            }
        } else {
            // update the tail pointer
            QueueEntry *temp = head;
            int index = tailIndex;
            while (temp != tail) {
                if (index == 5) {
                    index = 0;
                    temp = &queue[0];
                } else {
                    index += 1;
                    temp += 1;
                }
            }

            // temp now points to tail. update struct values
            if (index == 5) {
                tailIndex = 0;
                tail = &queue[0];
            } else {
                tailIndex += 1;
                tail = &queue[tailIndex];
            }
        }

        return true;
    }

    int dequeue() {
        // queue is empty
        if (head == nullptr) {
            return -1;
        }

        std::cout << "Dequeued: " << head->payload << ", " << head->dest << std::endl;
        const char *str = "";
        strcpy(queue[headIndex].payload, str);

        if (tail == head + 1) {
            // delete head pointer/index if queue now empty
            head = nullptr;
            headIndex = -1;
        } else {
            head += 1;
            headIndex += 1;
        }

        return 0;
    }

    // print the contents of the queue to the terminal
    void echo() {
        std::cout << "Queue Contents:\n|";
        for (int i = 0; i < 6; i++) {
            if (queue[i].payload[0] == '\0') {
                std::cout << " |";
            } else {
                for (int j = 0; j < strlen(queue[i].payload); j++) {
                    std::cout << queue[i].payload[j];
                }
                std::cout << "|";
            }
            
        }
        std::cout << std::endl << std::endl;

        return;
    }

    // get the value at location pointed to by head
    QueueEntry *getHead() {
        return head;
    }

    // get the value at location pointed to by tail
    QueueEntry *getTail() {
        return tail;
    }
    
    // destructor
    ~CircularQueue() {
        delete head;
        delete tail;
        delete queue;
    }
};

class Queue {
private:
    std::string selection;
    int rValue;
    CircularQueue circularQueue = CircularQueue();

public:
    int start();

    int enqueue();

    int dequeue();

    void printQueue();

    bool validateSelection(const std::string &s);

    bool validateEntry(const std::string &entry);
};

//bool validateSelection(const std::string &);

int main() {
    Queue q = Queue();
    q.start();
}

int Queue::start() {
    std::cout << "* * * * * * * * * * * * * * * *\n";
    std::cout << "* Welcome to circular queue!  *\n";
    std::cout << "* Type \"q\" to exit.           *\n";
    std::cout << "* * * * * * * * * * * * * * * *\n\n";

    while (true) {
        // get user selection
        bool validInput = false;
        while (validInput != true) {
            std::cout << "Enqueue, dequeue, or print? (e/d/p): ";
            std::cin >> selection;
            validInput = validateSelection(selection);
        };
        validInput = false;

        // terminate the program
        if (selection.at(0) == 'q' || selection.at(0) == 'Q') {
            break;
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

        if (rValue == -1) {
            std::cout << "Something went wrong!" << std::endl;
        }
    }

    return 0;
}

bool Queue::validateSelection(const std::string &s) {
    // validate all characters are letters or spaces
    for (const char c : s) {
        if (!isalpha(c)) {
            std::cout << "Please enter valid characters!\n";
            return false;
        }
    }

    // validate the number of characters input by user
    if (s.length() != 1 && s.length() != 4) {
        std::cout << "Choice not recognized, try agian!\n";
        return false;
    }

    // valide user selection
    if (s.at(0) != 'e' && s.at(0) != 'E' && s.at(0) != 'd' && s.at(0) != 'D' && s.at(0) != 'p' && s.at(0) != 'P' && s.at(0) != 'q' && s.at(0) != 'Q') {
        std::cout << "Choice not recognized, try agian!\n";
        return false;
    }
    if (s.length() == 4) {
        if (s.at(1) != 'u' && s.at(1) != 'U') {
            std::cout << "Choice not recognized, try agian!\n";
            return false;
        }
        if (s.at(2) != 'i' && s.at(2) != 'I') {
            std::cout << "Choice not recognized, try agian!\n";
            return false;
        }
        if (s.length() == 4 && s.at(3) != 'h' && s.at(3) != 'H' && s.at(3) != 't' && s.at(3) != 'T') {
            std::cout << "Choice not recognized, try agian!\n";
            return false;
        }
    }

    return true;
}

bool Queue::validateEntry(const std::string &entry) {
    // validate that all characters are letters
    for (const char c : entry) {
        if (!isalpha(c)) {
            std::cout<<"Please enter valid characters!\n";
            return false;
        }
    }

    // validate the number of characters input by user
    if (entry.length() > 5) {
        std::cout<<"Too many chars! Try agian.\n";
        return false;
    }

    return true;
}

void Queue::printQueue() {
    circularQueue.echo();
}

int Queue::enqueue() {
    // check if queue is full
    if (circularQueue.getHead() == circularQueue.getTail()) {
        std::cout << "Queue is Full!" << std::endl;
        return true;
    }
    
    // payload: get the user input to enqueue
    std::string entry;
    bool validEntry = false;
    while (!validEntry) {
        std::cout << "Enter an entry for the queue: ";
        std::cin >> entry;
        validEntry = validateEntry(entry);
    }

    // create a cstring from user entry
    char *cString;
    cString = new char[entry.length() + 1]; //leave room for null terminator

    for (int i = 0; i < entry.length(); i++) {
        cString[i] = entry[i];
    }
    cString[entry.length()] = '\0';

    // dest: get the user input to destination
    int destination;
    validEntry = false;
    while (!validEntry) {
        std::cout << "Destination (1-99): ";
        std::cin >> destination;
        if (std::cin.good()) {
            if (destination < 100 && destination > 0) {
                validEntry = true;
            } else {
                std::cout << "Number must be in the range 1-99!" << std::endl;
            }
        } else {
            std::cout << "Only numbers please!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
    }

    bool success = circularQueue.enqueue(cString, destination);
    if (success) {
        circularQueue.echo();
        return true;
    } else {
        return -1;
    }
}

int Queue::dequeue() {
    int rValue = circularQueue.dequeue();
    if (rValue != -1) {
        circularQueue.echo();
    } else {
        std::cout << "Queue is Empty!" << std::endl << std::endl;
        return 1;
    }
    return 0;
}