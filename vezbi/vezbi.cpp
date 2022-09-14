#include <iostream>
#include <string.h>
using namespace std;

/*
class Agol{
    int stepeni, minuti, sekundi;
public:
    Agol(int stepeni=0, int minuti=0, int sekundi=0){
        this->stepeni=stepeni;
        this->minuti=minuti;
        this->sekundi=sekundi;
    }

    void set_stepeni(int stepeni){
        this->stepeni=stepeni;
    }

    void set_minuti(int minuti){
        this->minuti=minuti;
    }

    void set_sekundi(int sekundi){
        this->sekundi=sekundi;
    }

    int getSekundi(){
        return sekundi;
    }

    int to_sekundi(){
        int finalMinuti=stepeni*60;
        return sekundi+finalMinuti*60;
    }
};

int proveri(int step, int min, int sek){
    if(step>180||step<0){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    if(step==180&&(min>0||sek>0)){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    if(min>60||min<0){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    if(sek>60||sek<0){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    return 1;
}

bool changeOfSeconds(Agol a, int sec){
    return a.getSekundi()!=sec;
}

int main() {

    //da se instancira objekt od klasata Agol
    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)) {

        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }

    return 0;
}
*/

/*
class Krug{
    float radius;
    const float pi=3.14;
public:
    Krug(float radius=0.0){
        this->radius=radius;
    }

    void setRadius(float radius){
        this->radius=radius;
    }

    float perimetar(){
        return 2*radius*pi;
    }

    float plostina(){
        return radius*radius*pi;
    }

    bool ednakvi(){
        if(perimetar()==plostina()){
            return 1;
        } else return 0;
    }
};

int main() {
    float r;
    cin >> r;
    //instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
    Krug k;
    k.setRadius(r);
    cout << k.perimetar() << endl;
    cout << k.plostina() << endl;
    cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
    return 0;
}
*/

/*
class Film{
    char ime[100], reziser[100], zanr[50];
    int godina;
public:
    Film(char *ime="", char *reziser="", char *zanr="", int godina=0){
        strcpy(this->ime,ime);
        strcpy(this->reziser,reziser);
        strcpy(this->zanr,zanr);
        this->godina=godina;
    }

    void setIme(char *ime){
        strcpy(this->ime,ime);
    }

    void setReziser(char *reziser){
        strcpy(this->reziser,reziser);
    }

    void setZanr(char *zanr){
        strcpy(this->zanr,zanr);
    }

    void setGodina(int godina){
        this->godina=godina;
    }

    int getGodina(){
        return godina;
    }

    void pecati(){
        cout<<"Ime: "<<ime<<endl;
        cout<<"Reziser: "<<reziser<<endl;
        cout<<"Zanr: "<<zanr<<endl;
        cout<<"Godina: "<<godina<<endl;
    }
};

void pecati_po_godina(Film *f, int n, int godina){
    for(int i=0;i<n;i++){
        if(f[i].getGodina()==godina){
            f[i].pecati();
        }
    }
}

int main() {
    int n;
    cin >> n;
    //da se inicijalizira niza od objekti od klasata Film
    Film film[n];
    for(int i = 0; i < n; ++i) {
        char ime[100];
        char reziser[50];
        char zanr[50];
        int godina;
        cin >> ime;
        cin >> reziser;
        cin >> zanr;
        cin >> godina;
        //da se kreira soodveten objekt
        film[i].setIme(ime);
        film[i].setReziser(reziser);
        film[i].setZanr(zanr);
        film[i].setGodina(godina);
    }
    int godina;
    cin >> godina;
    //da se povika funkcijata pecati_po_godina
    pecati_po_godina(film,n,godina);
    return 0;
}
*/


class Person{
    char ime[20],prezime[20];
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
    Date datumKupuvanje;
    float price;
public:
    Car(Person sopstvenik=0, Date datumKupuvanje=0, float price=0.0){
        this->sopstvenik=sopstvenik;
        this->datumKupuvanje=datumKupuvanje;
        this->price=price;
    }

    void print(){
        sopstvenik.print();
        datumKupuvanje.print();
        cout<<"Price: "<<price<<endl;
    }

    float getPrice(){
        return price;
    }

    friend void cheaperThan(Car* cars, int numCars, float price){
        for(int i=0;i<numCars;i++){
            if(cars[i].getPrice()>price){
                cars[i].print();
            }
        }
    }
};

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