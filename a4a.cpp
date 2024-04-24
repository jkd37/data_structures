#include <string>
#include <iostream>
#include <limits>

using std::string;
using std::cout;
using std::cin;

struct Link {
    Link(const string& v, Link* p = nullptr, Link* s = nullptr, float i = 0)
        : value{v}, prev{p}, succ{s}, input{i} { }

    string value;
    float input;
    Link* prev;
    Link* succ;
};

// inserts link n before p
Link* insert(Link* p, Link* n) {
    if (n==nullptr)
        return p;
    if (p==nullptr)
        return n;
    n->succ = p;
    if (p->prev)
        p->prev->succ = n;
    n->prev = p->prev;
    p->prev = n;

    return n;
}

// search for a node with string value s
// return the Link pointer
Link* find(Link* p, const string& s) {
    while (p) {
        if (p->value == s)
            return p;
        p = p->succ;
    }

    return nullptr;
}


// recurse through the successors until leaf node is found,
// then return the integer / 2
float traverse(Link* link) {
    if (link->prev != nullptr) {
        cout << link->value << ": " << link->input << "\n";
        link->prev->input = link->input / 2;
        return traverse(link->prev);
    }

    float result = link->input / 2;
    cout << link->value << ": " << result << "\n\n";
    return result;
}

int main() {
    float input;
    char choice;

    // create the initial list of norse gods
    Link* norse_gods = new Link{"Loki"};
    norse_gods = insert(norse_gods, new Link{"Thor"});
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Freja"});
    norse_gods = insert(norse_gods, new Link{"Asgard"});

    while (true) {
        // grab user input
        while (true) {
            cout << "Enter an integer: ";
            cin >> input;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Please enter only integers!\n";
            } else {
                break;
            }
        }

        // grab Loki's link as the starting point
        Link* loki = find(norse_gods, "Loki");
        if (!loki) {
            cout << "Could not find Loki!\n";
            return -1;
        }

        // insert the user input in Loki's node
        loki->input = input;

        // recursively traverse the list
        float r = traverse(loki);

        // ask the user to run program again
        while (true) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Go again? (y/n): ";
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
