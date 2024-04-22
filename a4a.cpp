#include <string>
#include <iostream>
#include <limits>

using std::string;
using std::cout;
using std::cin;

struct Link {
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} { }

    string value;
    int val;
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

int main() {    
    // create the initial list of norse gods
    Link* norse_gods = new Link{"Thor"};
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Freja"});
    norse_gods = insert(norse_gods, new Link{"Loki"});

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

    // loop through the successors and devide the input by 2
    while (p) {
        p->val = input;
        cout << p->value << ": " << p->val << "\n";
        p = p->succ;
        input = input/2;
    }

    return 0;
}
