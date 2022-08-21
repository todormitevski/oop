#include <iostream>
#include <string.h>
using namespace std;

class Ekipa{
protected:
    char ime[15];
    int brWin;
    int brLoss;
public:
    Ekipa(char *ime="", int brWin=0, int brLoss=0){
        strcpy(this->ime,ime);
        this->brWin=brWin;
        this->brLoss=brLoss;
    }

    void pecati(){
        cout<<"Ime: "<<ime<<" Pobedi: "<<brWin<<" Porazi: "<<brLoss;
    }
};

class FudbalskaEkipa: public Ekipa{
    int brCrveni;
    int brZolti;
    int brDraw;
public:
    FudbalskaEkipa(char *ime="", int brWin=0, int brLoss=0, int brCrveni=0, int brZolti=0, int brDraw=0): Ekipa(ime,brWin,brLoss){
        this->brCrveni=brCrveni;
        this->brZolti=brZolti;
        this->brDraw=brDraw;
    }

    void pecati(){
        Ekipa::pecati();
        cout<<" Nereseni: "<<brDraw<<" Poeni: ";
        int points=3*brWin+1*brDraw;
        cout<<points<<endl;
    }
};

int main(){
    char ime[15];
    int pob,por,ck,zk,ner;
    cin>>ime>>pob>>por>>ck>>zk>>ner;
    FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
    f1.pecati();
    return 0;
}