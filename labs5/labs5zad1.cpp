#include <iostream>
#include <string.h>
using namespace std;

class Automobile{
    char *marka;
    int *registracija;
    int maxBrzina;

    void copy(const Automobile &a){
        this->marka=new char[strlen(a.marka)+1];
        strcpy(this->marka,a.marka);
        this->registracija=new int[5];
        for(int i=0;i<5;i++){
            this->registracija[i]=a.registracija[i];
        }
        this->maxBrzina=a.maxBrzina;
    }
public:
    Automobile()=default;

    Automobile(char *marka, int *registracija, int maxBrzina){
        this->marka=new char[strlen(marka)+1];
        strcpy(this->marka,marka);
        this->registracija=new int[5];
        for(int i=0;i<5;i++){
            this->registracija[i]=registracija[i];
        }
        this->maxBrzina=maxBrzina;
    }

    Automobile (const Automobile &a){
        copy(a);
    }

    Automobile &operator=(const Automobile &a){
        if(this!=&a){
            delete [] marka;
            delete [] registracija;
            copy(a);
        }
        return *this;
    }

    ~Automobile(){
        delete [] marka;
        delete [] registracija;
    }

    bool operator==(Automobile &a){
        for(int i=0;i<5;i++){
            if(registracija[i]!=a.registracija[i]){
                return false;
            } else return true;
        }
    }

    friend ostream &operator<<(ostream &out, Automobile &a){
        out<<"Marka\t"<<a.marka<<"\tRegistracija[ ";
        for(int i=0;i<5;i++){
            out<<a.registracija[i]<<" ";
        }
        out<<"]"<<endl;
        return out;
    }

    int getMaxBrzina(){
        return maxBrzina;
    }
};

class RentACar{
    char ime[100];
    Automobile *avtomobili;
    int brAutos;

    void copy(const RentACar &r){
        strcpy(this->ime,r.ime);
        this->brAutos=r.brAutos;
        this->avtomobili=new Automobile[brAutos];
        for(int i=0;i<brAutos;i++){
            this->avtomobili[i]=r.avtomobili[i];
        }
    }
public:
    RentACar(char *ime=""){
        strcpy(this->ime,ime);
        brAutos=0;
        avtomobili=new Automobile[brAutos];
    }

    RentACar(const RentACar &r){
        copy(r);
    }

    RentACar &operator=(const RentACar &r){
        if(this!=&r){
            delete [] avtomobili;
            copy(r);
        }
        return *this;
    }

    ~RentACar(){
        delete [] avtomobili;
    }

    RentACar &operator+=(const Automobile &r){
        Automobile *tmp=new Automobile[brAutos+1];
        for(int i=0;i<brAutos;i++){
            tmp[i]=avtomobili[i];
        }
        tmp[brAutos++]=r;
        delete [] avtomobili;
        avtomobili=tmp;
        return *this;
    }

    RentACar &operator-=(Automobile &a){
        Automobile *tmp=new Automobile[brAutos];
        int br=0;
        for(int i=0;i<brAutos;i++){
            if(!(avtomobili[i]==a)){
                tmp[br++]=avtomobili[i];
            }
        }
        brAutos=br;
        delete [] avtomobili;
        avtomobili=tmp;
        return *this;
    }

    void pecatiNadBrzina(int max){
        cout<<ime<<endl;
        for(int i=0;i<brAutos;i++){
            if(avtomobili[i].getMaxBrzina()>max){
                cout<<avtomobili[i];
            }
        }
    }
};

int main()
{
    RentACar agencija("FINKI-Car");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char marka[100];
        int regisracija[5];
        int maximumBrzina;

        cin>>marka;

        for (int i=0;i<5;i++)
            cin>>regisracija[i];

        cin>>maximumBrzina;

        Automobile nov=Automobile(marka,regisracija,maximumBrzina);

        //dodavanje na avtomobil
        agencija+=nov;

    }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
        cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;

    agencija.pecatiNadBrzina(150);

    return 0;
}