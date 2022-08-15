#include <iostream>
#include <string.h>
using namespace std;

class Masa{
    int sirina;
    int dolzina;
public:
    Masa(int sirina=0, int dolzina=0){
        this->sirina=sirina;
        this->dolzina=dolzina;
    }

    void pecati(){
        cout<<"Masa: "<<sirina<<" "<<dolzina<<endl;
    }
};

class Soba{
    int sobaSirina;
    int sobaDolzina;
    Masa masa;
public:
    Soba(int sobaSirina=0, int sobaDolzina=0, Masa masa=0){
        this->sobaSirina=sobaSirina;
        this->sobaDolzina=sobaDolzina;
        this->masa=masa;
    }

    void pecati(){
        cout<<" Soba: "<<sobaSirina<<" "<<sobaDolzina<<" ";
        masa.pecati();
    }
};

class Kukja{
    Soba soba;
    char adresa[50];
public:
    Kukja(){}

    Kukja(Soba soba, char *adresa){
        this->soba=soba;
        strcpy(this->adresa,adresa);
    }

    ~Kukja(){}

    void print(){
        cout<<"Adresa: "<<adresa;
        soba.pecati();
    }
};

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int masaSirina,masaDolzina;
        cin>>masaSirina;
        cin>>masaDolzina;
        Masa m(masaSirina,masaDolzina);
        int sobaSirina,sobaDolzina;
        cin>>sobaSirina;
        cin>>sobaDolzina;
        Soba s(sobaSirina,sobaDolzina,m);
        char adresa[30];
        cin>>adresa;
        Kukja k(s,adresa);
        k.print();
    }

    return 0;
}