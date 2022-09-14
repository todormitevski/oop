#include <iostream>
#include <string.h>
using namespace std;

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int brTrki;
    bool isVeteran;
public:
    Vozac(const char *ime="", int vozrast=0, int brTrki=0, bool isVeteran=false){
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brTrki=brTrki;
        this->isVeteran=isVeteran;
    }

    friend ostream &operator<<(ostream &out, Vozac &v){
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.brTrki<<endl;
        if(v.isVeteran==true){
            out<<"VETERAN"<<endl;
        }
        return out;
    }

    virtual double zarabotuvacka()=0;
    virtual double danok()=0;

    bool operator==(Vozac &v){
        return zarabotuvacka()==v.zarabotuvacka();
    }
};

class Avtomobilist: public Vozac{
    double cenaAvto;
public:
    Avtomobilist(const char *ime="", int vozrast=0, int brTrki=0, bool isVeteran=false, double cenaAvto=0.0): Vozac(ime,vozrast,brTrki,isVeteran){
        this->cenaAvto=cenaAvto;
    }

    double zarabotuvacka(){
        return cenaAvto/5;
    }

    double danok(){
        if(brTrki>10){
            return zarabotuvacka()*0.15;
        } else return zarabotuvacka()*0.1;
    }
};

class Motociklist: public Vozac{
    int enginePower;
public:
    Motociklist(const char *ime="", int vozrast=0, int brTrki=0, bool isVeteran=false, int enginePower=0): Vozac(ime,vozrast,brTrki,isVeteran){
        this->enginePower=enginePower;
    }

    double zarabotuvacka(){
        return enginePower*20;
    }

    double danok(){
        if(isVeteran==true){
            return zarabotuvacka()*0.25;
        } else return zarabotuvacka()*0.2;
    }
};

int soIstaZarabotuvachka(Vozac **vozaci, int n, Vozac *v){
    int br=0;
    for(int i=0;i<n;i++){
        if(vozaci[i]->zarabotuvacka()==v->zarabotuvacka()){
            br++;
        }
    }
    return br;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}