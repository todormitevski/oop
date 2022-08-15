#include <iostream>
#include <string.h>
using namespace std;

class Rabotnik{
    char ime[30];
    char prezime[30];
    int plata;
public:
    Rabotnik(char *ime="", char *prezime="", int plata=0){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->plata=plata;
    }

    int getPlata(){
        return plata;
    }

    void pecati(){
        cout<<ime<<" "<<prezime<<" "<<plata<<endl;
    }
};

class Fabrika{
    Rabotnik rabotnici[100];
    int brVraboteni;
public:
    Fabrika(){}

    Fabrika(Rabotnik rabotnici[100], int brVraboteni){
        for(int i=0;i<brVraboteni;i++){
            this->rabotnici[i]=rabotnici[i];
        }
        this->brVraboteni=brVraboteni;
    }

    void pecatiVraboteni(){
        cout<<"Site vraboteni:"<<endl;
        for(int i=0;i<brVraboteni;i++){
            rabotnici[i].pecati();
        }
    }

    void pecatiSoPlata(int plata){
        cout<<"Vraboteni so plata povisoka od "<<plata<<" :"<<endl;
        for(int i=0;i<brVraboteni;i++){
            if(rabotnici[i].getPlata()>=plata){
                rabotnici[i].pecati();
            }
        }
    }
};

int main(){

    int n;
    cin>>n;
    Rabotnik rabotnik[n];

    int minPlata;

    for(int i=0;i<n;i++){
        char ime[30], prezime[30];
        int plata;
        cin>>ime;
        cin>>prezime;
        cin>>plata;
        Rabotnik r(ime,prezime,plata);
        rabotnik[i]=r;
    }

    cin>>minPlata;

    Fabrika fabrika(rabotnik,n);
    fabrika.pecatiVraboteni();
    fabrika.pecatiSoPlata(minPlata);

    return 0;
}