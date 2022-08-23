#include <iostream>
using namespace std;

class Shape {
public:
    virtual void draw() {
        cout << "Drawing a shape.\n";
    }
};

// креирајте класа Rectangle која наследува од Shape
// во неа препокријте ја функцијата draw() така што ќе се испечати: "Drawing a rectangle.\n"
class Rectangle: public Shape{
public:
    void draw(){
        cout<<"Drawing a rectangle.\n";
    }
};

int main() {
    Shape* shape;

    // тука инстанцирајте објект од класата Shape и покажувачот shape нека покажува кон него
    Shape oblik;
    shape=&oblik;
    shape->draw();

    // сега инстанцирајте објект од класата Rectangle и покажувачот shape нека покажува кон него
    // повторно повикајте ја функцијата draw() на shape
    Rectangle pravoagolnik;
    shape=&pravoagolnik;
    shape->draw();

    return 0;
}