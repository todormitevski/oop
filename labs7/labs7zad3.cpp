#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

class Shape{
protected:
    int a;
public:
    Shape()=default;

    Shape(int a){
        this->a=a;
    }

    virtual double plostina()=0;
    virtual void pecati()=0;
    virtual int getType()=0;
};

class Square: public Shape{
public:
    Square(int a=0): Shape(a){}

    double plostina(){
        return a*a;
    }

    void pecati(){
        cout<<"Kvadrat so plostina = "<<plostina()<<endl;
    }

    int getType(){ //kvadrat==1, krug==2, triagolnik==3
        return 1;
    }
};

class Circle: public Shape{
public:
    Circle(int a=0): Shape(a){}

    double plostina(){
        return 3.14*a*a;
    }

    void pecati(){
        cout<<"Krug so plostina = "<<plostina()<<endl;
    }

    int getType(){
        return 2;
    }
};

class Triangle: public Shape{
public:
    Triangle(int a=0): Shape(a){}

    double plostina(){
        return (sqrt(3)/4) * a * a;
    }

    void pecati(){
        cout<<"Triagolnik so plostina = "<<plostina()<<endl;
    }

    int getType(){
        return 3;
    }
};

void checkNumTypes(Shape** niza, int n){
    int brKvadrat=0, brKrug=0, brTriagolnik=0;
    for(int i=0;i<n;i++){
        if(niza[i]->getType()==1){
            brKvadrat++;
        } else if(niza[i]->getType()==2){
            brKrug++;
        } else if(niza[i]->getType()==3){
            brTriagolnik++;
        }
    }
    cout<<"Broj na kvadrati vo nizata = "<<brKvadrat<<endl;
    cout<<"Broj na krugovi vo nizata = "<<brKrug<<endl;
    cout<<"Broj na triagolnici vo nizata = "<<brTriagolnik<<endl;
}

int main(){


    int n;
    cin >> n;

    //inicijaliziraj niza od pokazuvachi kon klasata Shape
    //alociraj memorija so golemina n za prethodno navedenata niza
    Shape **niza=new Shape *[n];

    int classType;
    int side;

    //konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
    for(int i = 0; i < n; ++i){
        cin >> classType;
        cin >> side;
        if(classType==1){
            niza[i]=new Square(side);
        } else if(classType==2){
            niza[i]=new Circle(side);
        } else if(classType==3){
            niza[i]=new Triangle(side);
        }
    }

    for(int i = 0; i < n; ++i){
        niza[i]->pecati();
    }
    checkNumTypes(niza, n);

    return 0;
}