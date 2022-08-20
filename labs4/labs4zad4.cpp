#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

/*
enum zanr {akcija, komedija, drama};

class Film {
    char * ime;
    int size;
    zanr zanrFilm;

public:
    Film(char * ime = " ", int size = 0, zanr zanrFilm = (zanr)0) {
        this->size = size;
        this->zanrFilm = zanrFilm;

        this->ime = new char [strlen(ime)+1];
        strcpy(this->ime, ime);
    }

    Film(const Film & other) {
        this->size = other.size;
        this->zanrFilm = other.zanrFilm;

        this->ime = new char [strlen(other.ime)+1];
        strcpy(this->ime, other.ime);
    }

    Film & operator=(const Film & other) {
        if( this != &other) {
            this->size = other.size;
            this->zanrFilm = other.zanrFilm;

            delete [] ime;

            this->ime = new char [strlen(other.ime)+1];
            strcpy(this->ime, other.ime);
        }
        return *this;
    }

    int getSize() {
        return size;
    }

    zanr getZanr() {
        return zanrFilm;
    }

    ~Film() {
        delete [] ime;
    }


    void pecati() {
        cout<<size<<"MB-\""<<ime<<"\""<<endl;
    }
};


class DVD {
    Film filmovi[5];
    int brFilmovi;
    int cap;

public:
    DVD(int cap =0) {
        this->brFilmovi = 0;

        this->cap = cap;
    }

    DVD(const DVD & other) {
        this->brFilmovi = other.brFilmovi;
        this->cap = other.cap;

        for(int i = 0; i<brFilmovi; i++) {
            filmovi[i] = other.filmovi[i];
        }
    }

    DVD & operator=(const DVD & other) {
        if( this != &other) {
            this->brFilmovi = other.brFilmovi;
            this->cap = other.cap;

            for(int i = 0; i<brFilmovi; i++) {
                filmovi[i] = other.filmovi[i];
            }
        }
        return *this;
    }

    ~DVD () {}

    Film getFilm(int i) {
        return filmovi[i];
    }

    int getBroj() {
        return brFilmovi;
    }

    void dodadiFilm(Film & f) {

        // nov < vkupno-zbir && pomalce od 5 filmovi
        int zbirSize = 0;
        for(int i = 0; i<brFilmovi; i++) {
            zbirSize += filmovi[i].getSize();
        }

        if( brFilmovi < 5 && (f.getSize() < cap - zbirSize)) {
            filmovi[brFilmovi++] = f;
        }
    }

    void pecatiFilmoviDrugZanr(zanr  z) {
        // koi ne se od toj zanr
        for(int i = 0; i< brFilmovi ;i++) {
            if(filmovi[i].getZanr() != z) {
                filmovi[i].pecati();
            }
        }
    }

    float procentNaMemorijaOdZanr(zanr  z) {
        //zbir / vkupno * 100 // samo od toj zanr
        float procent = 0;
        for(int i = 0 ; i<brFilmovi; i++) {
            zanr filmZanr = filmovi[i].getZanr();
            if( filmZanr = z) {
                procent += filmovi[i].getSize();
            }
        }

        procent = procent / this->cap * 100;

        return procent;

    }
};
*/

enum zanr{
    akzija=0,
    komedija,
    drama
};

class Film{
    char *ime;
    int sizeInMb;
    zanr zanrFilm;

    void copy(const Film &f){
        this->ime=new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->sizeInMb=f.sizeInMb;
        this->zanrFilm=f.zanrFilm;
    }
public:
    Film(char *ime="", int sizeInMb=0, zanr zanrFilm=(zanr)0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->sizeInMb=sizeInMb;
        this->zanrFilm=zanrFilm;
    }

    Film(const Film &f){
        copy(f);
    }

    Film &operator=(const Film &f){
        if(this!=&f){
            delete [] ime;
            copy(f);
        }
    }

    ~Film(){
        delete [] ime;
    }

    void pecati(){
        cout<<sizeInMb<<"MB"<<"-"<<"\""<<ime<<"\""<<endl;
    }

    int getSizeInMb(){
        return sizeInMb;
    }

    zanr getZanr(){
        return zanrFilm;
    }
};

class DVD{
    Film filmovi[5];
    int brFilmovi;
    int capacity;

    void copy(const DVD &d){
        this->brFilmovi=d.brFilmovi;
        this->capacity=d.capacity;
        for(int i=0;i<brFilmovi;i++){
            this->filmovi[i]=d.filmovi[i];
        }
    }
public:
    DVD(int capacity=0){
        brFilmovi=0;
        this->capacity=capacity;
    }

    DVD(const DVD &d){
        copy(d);
    }

    DVD &operator=(const DVD &d){
        if(this!=&d){
            copy(d);
        }
        return *this;
    }

    ~DVD(){}

    void dodadiFilm (Film f){
        int vkSize=0;
        for(int i=0;i<brFilmovi;i++){
            vkSize+=filmovi[i].getSizeInMb();
        }

        if(brFilmovi<5&&(f.getSizeInMb()<capacity-vkSize)){
            filmovi[brFilmovi++]=f;
        }

//        Film *tmp=new Film[brFilmovi+1];
//        for(int i=0;i<brFilmovi;i++){
//            tmp[i]=filmovi[i];
//        }
//        tmp[brFilmovi++]=f;
//        delete [] filmovi;
//        filmovi=tmp;
    }

    void pecatiFilmoviDrugZanr(zanr z){
        for(int i=0;i<brFilmovi;i++){
            if(z!=filmovi[i].getZanr()){
                filmovi[i].pecati();
            }
        }
    }

    float procentNaMemorijaOdZanr(zanr z){
        float procent=0.0;
        float total=0.0;
        for(int i=0;i<brFilmovi;i++){
            if(filmovi[i].getZanr()==z){
                total+=filmovi[i].getSizeInMb();
            }
        }
        procent=(total/capacity)*100;
        return procent;
    }

    int getBroj(){
        return brFilmovi;
    }

    Film getFilm(int i){
        return filmovi[i];
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, memorija, kojzanr;
    char ime[50];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Film ======" << endl;
        cin >> ime;
        cin >> memorija;
        cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
        Film f(ime, memorija, (zanr) kojzanr);
        f.pecati();
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < n; i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 3) {
        cout << "===== Testiranje na metodot dodadiFilm() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        for (int i = 0; i < omileno.getBroj(); i++)
            (omileno.getFilm(i)).pecati();
    } else if (testCase == 4) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot pecatiFilmoviDrugZanr() od klasata DVD ======" << endl;
        DVD omileno(50);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        omileno.pecatiFilmoviDrugZanr((zanr) kojzanr);

    } else if (testCase == 6){
        cout<<"===== Testiranje na metodot procentNaMemorijaOdZanr() od klasata DVD =====" <<endl;
        DVD omileno(40);
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> ime;
            cin >> memorija;
            cin >> kojzanr; //se vnesuva 0 za AKCIJA,1 za KOMEDIJA i 2 za DRAMA
            Film f(ime, memorija, (zanr) kojzanr);
            omileno.dodadiFilm(f);
        }
        cin >> kojzanr;
        cout<<"Procent na filmovi od dadeniot zanr iznesuva: "<<omileno.procentNaMemorijaOdZanr((zanr) kojzanr)<<"%\n";

    }

    return 0;
}