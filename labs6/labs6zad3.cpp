#include <iostream>
#include <string.h>
using namespace std;

class Lekar{
protected:
    int faksimil;
    char ime[10];
    char prezime[11];
    double pocetnaPlata;
public:
    Lekar(int faksimil=0, char *ime="", char *prezime="", double pocetnaPlata=0.0){
        this->faksimil=faksimil;
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->pocetnaPlata=pocetnaPlata;
    }

    Lekar(const Lekar &l){
        this->faksimil=l.faksimil;
        strcpy(this->ime,l.ime);
        strcpy(this->prezime,l.prezime);
        this->pocetnaPlata=l.pocetnaPlata;
    }

    void pecati(){
        cout<<faksimil<<": "<<ime<<" "<<prezime<<endl;
    }

    double plata(){
        return pocetnaPlata;
    }
};

class MaticenLekar: public Lekar{
    int brPacienti;
    double *kotizacii;
public:
    MaticenLekar(): Lekar(){
        brPacienti=0;
        kotizacii=new double [brPacienti];
    }

    MaticenLekar(Lekar &lekar, int brPacienti, double *kotizacii): Lekar(lekar){
        this->brPacienti=brPacienti;
        this->kotizacii=new double[brPacienti];
        for(int i=0;i<brPacienti;i++){
            this->kotizacii[i]=kotizacii[i];
        }
    }

    MaticenLekar(const MaticenLekar &m): Lekar(m){
        this->brPacienti=m.brPacienti;
        this->kotizacii=new double[brPacienti];
        for(int i=0;i<brPacienti;i++){
            this->kotizacii[i]=m.kotizacii[i];
        }
    }

    MaticenLekar &operator=(const MaticenLekar &m){
        if(this!=&m){
            delete [] kotizacii;
            this->faksimil=m.faksimil;
            strcpy(this->ime,m.ime);
            strcpy(this->prezime,m.prezime);
            this->pocetnaPlata=m.pocetnaPlata;
            this->brPacienti=m.brPacienti;
            this->kotizacii=new double[brPacienti];
            for(int i=0;i<brPacienti;i++){
                this->kotizacii[i]=m.kotizacii[i];
            }
        }
        return *this;
    }

    void pecati(){
        Lekar::pecati();
        double prosek=0;
        for(int i=0;i<brPacienti;i++){
            prosek+=kotizacii[i];
        }
        cout<<"Prosek na kotizacii: "<<prosek/brPacienti<<endl;
    }

    double plata(){
        double prosek=0;
        for(int i=0;i<brPacienti;i++){
            prosek+=kotizacii[i];
        }
        return Lekar::plata()+(0.3*(prosek/brPacienti));
    }
};

int main() {
    int n;
    cin>>n;
    int pacienti;
    double kotizacii[100];
    int faksimil;
    char ime [20];
    char prezime [20];
    double osnovnaPlata;

    Lekar * lekari = new Lekar [n];
    MaticenLekar * maticni = new MaticenLekar [n];

    for (int i=0;i<n;i++){
        cin >> faksimil >> ime >> prezime >> osnovnaPlata;
        lekari[i] = Lekar(faksimil,ime,prezime,osnovnaPlata);
    }

    for (int i=0;i<n;i++){
        cin >> pacienti;
        for (int j=0;j<pacienti;j++){
            cin >> kotizacii[j];
        }
        maticni[i]=MaticenLekar(lekari[i],pacienti,kotizacii);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===TESTIRANJE NA KLASATA LEKAR==="<<endl;
        for (int i=0;i<n;i++){
            lekari[i].pecati();
            cout<<"Osnovnata plata na gorenavedeniot lekar e: "<<lekari[i].plata()<<endl;
        }
    }
    else {
        cout<<"===TESTIRANJE NA KLASATA MATICENLEKAR==="<<endl;
        for (int i=0;i<n;i++){
            maticni[i].pecati();
            cout<<"Platata na gorenavedeniot maticen lekar e: "<<maticni[i].plata()<<endl;
        }
    }

    delete [] lekari;
    delete [] maticni;

    return 0;
}