#include <iostream>
#include <string.h>
using namespace std;

class Person{
    char ime[20];
    char prezime[20];
public:
    Person(char *ime="not specified", char *prezime="not specified"){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
    }

    void print(){
        cout<<ime<<" "<<prezime<<endl;
    }
};

class Date{
    int year,month,day;

    void copy(const Date &d){
        this->year=d.year;
        this->month=d.month;
        this->day=d.day;
    }
public:
    Date(int year=0, int month=0, int day=0){
        this->year=year;
        this->month=month;
        this->day=day;
    }

    Date(const Date &d){
        copy(d);
    }

    void print(){
        cout<<year<<"."<<month<<"."<<day<<endl;
    }
};

class Car{
    Person sopstvenik;
    Date datumNaKupuvanje;
    float cena;
public:
    Car(){
        cena=0;
    }

    Car(Person sopstvenik, Date datumnaKupuvanje, float cena){
        this->sopstvenik=sopstvenik;
        this->datumNaKupuvanje=datumnaKupuvanje;
        this->cena=cena;
    }

    float getPrice(){
        return cena;
    }

    void print(){
        sopstvenik.print();
        datumNaKupuvanje.print();
        cout<<"Price: "<<cena;
    }
};

Car cheaperThan(Car* cars, int numCars, float price){
    for(int i=0;i<numCars;i++){
        if(cars[i].getPrice()<price){
            cars[i].print();
        }
    }
}

int main() {
    char name[20];
    char lastName[20];
    int year;
    int month;
    int day;
    float price;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(year, month, day);

        cin >> price;
        Car car(lik, date,  price);

        car.print();
    }
    else if (testCase == 2) {
        cin >> name;
        cin >> lastName;
        Person lik(name, lastName);

        cin >> year;
        cin >> month;
        cin >> day;
        Date date(Date(year, month, day));

        cin >> price;
        Car car(lik, date,  price);
        car.print();
    }
    else {
        int numCars;
        cin >> numCars;

        Car cars[10];
        for (int i = 0; i < numCars; i++) {
            cin >> name;
            cin >> lastName;
            Person lik(name, lastName);

            cin >> year;
            cin >> month;
            cin >> day;
            Date date(year, month, day);

            cin >> price;
            cars[i] = Car(lik, date,  price);
        }
        float priceLimit;
        cin >> priceLimit;
        cheaperThan(cars, numCars, priceLimit);
    }


    return 0;
}