#include <iostream>
#include <string.h>
using namespace std;

class Nedviznina{
protected:
    char *adresa;
    int kvadratura;
    int cenaKvadrat;

    void copy(const Nedviznina &n){
        this->adresa=new char[strlen(n.adresa)+1];
        strcpy(this->adresa,n.adresa);
        this->kvadratura=n.kvadratura;
        this->cenaKvadrat=n.cenaKvadrat;
    }
public:
    Nedviznina(char *adresa="", int kvadratura=0, int cenaKvadrat=0){
        this->adresa=new char[strlen(adresa)+1];
        strcpy(this->adresa,adresa);
        this->kvadratura=kvadratura;
        this->cenaKvadrat=cenaKvadrat;
    }

    Nedviznina(const Nedviznina &n){
        copy(n);
    }

    Nedviznina &operator=(const Nedviznina &n){
        if(this!=&n){
            delete [] adresa;
            copy(n);
        }
        return *this;
    }

    ~Nedviznina(){
        delete [] adresa;
    }

    int cena(){
        return kvadratura*cenaKvadrat;
    }

    void pecati(){
        cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<cenaKvadrat<<endl;
    }

    double danokNaImot(){
        return cena()*0.05;
    }

    char *getAdresa(){
        return adresa;
    }

    friend istream &operator>>(istream &in, Nedviznina &n){
        return in>>n.adresa>>n.kvadratura>>n.cenaKvadrat;
    }
};

class Vila: public Nedviznina{
    int danokLuksuz;
public:
    Vila(int danokLuksuz=0): Nedviznina(adresa,kvadratura,cenaKvadrat){
        this->danokLuksuz=danokLuksuz;
    }

    double danokNaImot(){
        return cena()*(danokLuksuz+5)/100.0;
    }

    void pecati(){
        cout<<adresa<<", Kvadratura: "<<kvadratura<<", Cena po Kvadrat: "<<cenaKvadrat<<", Danok na luksuz: "<<danokLuksuz<<endl;
    }

    friend istream &operator>>(istream &in, Vila &v){
        return in>>v.adresa>>v.kvadratura>>v.cenaKvadrat>>v.danokLuksuz;
    }
};

int main(){
    Nedviznina n;
    Vila v;
    cin>>n;
    cin>>v;
    n.pecati();
    cout<<"Danok za: "<<n.getAdresa()<<", e: "<<n.danokNaImot()<<endl;
    v.pecati();
    cout<<"Danok za: "<<v.getAdresa()<<", e: "<<v.danokNaImot()<<endl;
    return 0;
}