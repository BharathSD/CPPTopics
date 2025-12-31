#include <iostream>

/*
Delegating constructor :
Description: A constructor that calls another constructor in the same class.

Inheriting constructor :
Description: A constructor in a derived class that calls a constructor in the base class.

*/

class Cbase {
public:
    Cbase(int x, int y) : x_(x), y_(y) {
    }
    Cbase() : Cbase(0, 0) { // Delegating constructor
    }
private:
    int x_;
    int y_;
};

class Cderived : public Cbase {
public:
    using Cbase::Cbase; // Inherit constructors
};

int main() {
    Cbase obj(5, 10);
    Cderived derivedObj(15, 20);
    return 0;
}