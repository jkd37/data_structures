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

class Asgard {
private:
    Link* norse_gods;
    Link* link;
    float m = 1;
    float x = 0;

public:
    Asgard(const char* leaf);

    int addGod(const char* name);
    int input(int i);
    float traverse();

    ~Asgard() {
        delete link;
        delete norse_gods;
    }
};

// default constructor
Asgard::Asgard(const char* leaf) {
    norse_gods = new Link{leaf};
    link = norse_gods;
}

// creates a new Link node and adds to linked list
int Asgard::addGod(const char* name) {
    norse_gods = insert(norse_gods, new Link{name});
    link = norse_gods;
    return 0;
}

// assign int value to first node in linked list
int Asgard::input(int i) {
    norse_gods->input = i;
    link = norse_gods;
    return 0;
}

// recurse through the successors until leaf node is found,
// dividing by 2 each recursion
float Asgard::traverse() {
    if (link->succ != nullptr) {
        cout << link->value << ": " << link->input << "\n";
        link->succ->input = link->input / 2;
        link = link->succ;
        return traverse();
    }

    float result = link->input;
    cout << link->value << ": " << result << "\n";
    link = norse_gods;
    return result / 2;
}
