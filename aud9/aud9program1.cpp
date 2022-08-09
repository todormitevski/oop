#include <cstring>
#include <iostream>
using namespace std;

class Animal{
protected:
    char name[30];
public:
    Animal(char *name=""){
        strcpy(this->name,name);
    }

    virtual void makeSound(){
        cout<<name<<" is making the sound bla bla"<<endl;
    }
};

class Dog: public Animal{
public:
    Dog(char *name): Animal(name){}

    void makeSound(){
        cout<<name<<" is making the sound bark bark"<<endl;
    }
};

class Cat: public Animal{
public:
    Cat(char *name): Animal(name){}

    void makeSound(){
        cout<<name<<" is making the sound meow meow"<<endl;
    }
};

int main(){

    //Ako sakame niza od zivotni, se deklarira niza od pokazuvaci
//    Animal **animals=new Animal *[3];
//
//    animals[0]=new Animal("Chicken");
//    animals[1]=new Dog("Cerberus");
//    animals[2]=new Cat("Rengar");
//
//    for(int i=0;i<3;i++){
//        animals[i]->makeSound();
//    }

//    Animal *a=new Animal("Chicken");
//    a->makeSound();
//    Animal *dog=new Dog("Cerberus");
//    dog->makeSound();
//    Animal *cat=new Cat("Rengar");
//    cat->makeSound();

    int n;
    cin>>n;

    Animal **animals=new Animal *[n];
    for(int i=0;i<n;i++){
        int type;
        char name[30];
        cin>>type>>name;
        if(type==1) {
            animals[i] = new Cat(name);
        } else{
            animals[i]=new Dog(name);
        }
    }

    for(int i=0;i<n;i++){
        animals[i]->makeSound();
    }

    return 0;

}