#include <iostream>
#include <string.h>
using namespace std;

class Film{
    char ime[100];
    char reziser[50];
    char zanr[50];
    int godina;
public:
    Film(char *ime="", char *reziser="", char *zanr="", int godina=0){
        strcpy(this->ime,ime);
        strcpy(this->reziser,reziser);
        strcpy(this->zanr,zanr);
        this->godina=godina;
    }

    void setIme(char *imeto){
        strcpy(this->ime,imeto);
    }

    void setReziser(char *rez){
        strcpy(this->reziser,rez);
    }

    void setZanr(char *zanrot){
        strcpy(this->zanr,zanrot);
    }

    void setGodina(int god){
        this->godina=god;
    }

    int getGodina(){
        return godina;
    }

    void print(){
        cout<<"Ime: "<<ime<<endl;
        cout<<"Reziser: "<<reziser<<endl;
        cout<<"Zanr: "<<zanr<<endl;
        cout<<"Godina: "<<godina<<endl;
    }
};

void pecati_po_godina(Film *f, int n, int godina){
    for(int i=0;i<n;i++){
        if(f[i].getGodina()==godina){
            f[i].print();
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