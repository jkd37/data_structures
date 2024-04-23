#include <string>
#include <iostream>
#include <limits>

using std::string;
using std::cout;
using std::cin;

struct Link {
    Link(const string& v, Link* p = nullptr, Link* s = nullptr, int i = 0)
        : value{v}, prev{p}, succ{s}, input{i} { }

    string value;
    int input;
    Link* prev;
    Link* succ;
};

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
int traverse(Link* link) {
    if (link->succ != nullptr)
        return traverse(link->succ);

    cout << "Leaf is: " << link->value << "\n";
    return link->input / 2;
}

int main() {    
    // create the initial list of norse gods
    Link* norse_gods = new Link{"Loki"};
    norse_gods = insert(norse_gods, new Link{"Thor"});
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Freja"});
    norse_gods = insert(norse_gods, new Link{"Asgard"});

    // grab user input
    int input;
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
    Link* p = find(norse_gods, "Loki");
    if (!p) {
        cout << "Could not find Loki!\n";
        return -1;
    }

    // insert the user input in Loki's node
    p->input = input;

    // recursively traverse the list
    int result = traverse(norse_gods);
    cout << "Result: " << result << "\n";

    return 0;
}
