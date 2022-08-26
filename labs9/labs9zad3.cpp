#include <iostream>
#include <string.h>
using namespace std;

class ImaMasa{
public:
    virtual double vratiMasa()=0;
    virtual void pecati()=0;
};


class PaketPijalok: public ImaMasa{
protected:
    double volumenEden;
    int kolicina;

    static double GUSTINA;
    static double MASA;
public:
    PaketPijalok(double volumenEden=0.0, int kolicina=0){
        this->volumenEden=volumenEden;
        this->kolicina=kolicina;
    }

    double vratiMasa(){
        return (volumenEden*GUSTINA*MASA) * kolicina;
    }

//    void pecati(){
//
//    }

    int getKolicina(){
        return kolicina;
    }
};
double PaketPijalok::GUSTINA=0.8;
double PaketPijalok::MASA=0.2;


class PaketSok: public PaketPijalok{
    bool daliGaziran;

    static double EXTRA_MASS;
public:
    PaketSok(double volumenEden=0.0, int kolicina=0, bool daliGaziran=false): PaketPijalok(volumenEden,kolicina){
        this->daliGaziran=daliGaziran;
    }

    double vratiMasa(){
        if(daliGaziran==false){
            return PaketPijalok::vratiMasa()+EXTRA_MASS*getKolicina();
        }
        return PaketPijalok::vratiMasa();
    }

    void pecati(){
        cout<<"Paket sok"<<endl;
        cout<<"kolicina "<<kolicina<<", so po "<<volumenEden*GUSTINA<<"l(dm3)"<<endl;
    }
};
double PaketSok::EXTRA_MASS=0.1;


class PaketVino: public PaketPijalok{
    double procentAlkohol;

    static double KOEF;
public:
    PaketVino(double volumenEden=0.0, int kolicina=0, double procentAlkohol=0.0): PaketPijalok(volumenEden,kolicina){
        this->procentAlkohol=procentAlkohol;
    }

    double getProcentAlkohol(){
        return procentAlkohol;
    }

    double vratiMasa(){
        return PaketPijalok::vratiMasa()*(KOEF+procentAlkohol);
    }

    void pecati(){
        cout<<"Paket vino"<<endl;
        cout<<"kolicina "<<kolicina<<", "<<procentAlkohol*100<<"% alkohol od po "<<volumenEden*GUSTINA<<" l(dm3)"<<endl;
    }
};
double PaketVino::KOEF=0.9;


class Kamion{
    char *registracija;
    char *vozac;
    ImaMasa **elementi;
    int brElementi;

    void copy(const Kamion &k){
        this->registracija=new char[strlen(k.registracija)+1];
        strcpy(this->registracija,k.registracija);
        this->vozac=new char[strlen(k.vozac)+1];
        strcpy(this->vozac,k.vozac);
        this->brElementi=k.brElementi;
    }

    void freeMem(){
        delete [] registracija;
        delete [] vozac;
        delete [] elementi;
    }
public:
    Kamion(char *vozac){
        this->vozac=new char[strlen(vozac)+1];
        strcpy(this->vozac,vozac);
    }

    Kamion(char *registracija, char *vozac){
        this->registracija=new char[strlen(registracija)+1];
        strcpy(this->registracija,registracija);
        this->vozac=new char[strlen(vozac)+1];
        strcpy(this->vozac,vozac);
    }

    Kamion(const Kamion &k){
        copy(k);
    }

    Kamion &operator=(const Kamion &k){
        if(this!=&k){
            freeMem();
            copy(k);
        }
        return *this;
    }

    ~Kamion(){
        freeMem();
    }

    void registriraj(char *reg){
        this->registracija=reg;
    }

    void dodadiElement(ImaMasa *m){
        ImaMasa **tmp=new ImaMasa *[brElementi+1];
        for(int i=0;i<brElementi;i++){
            tmp[i]=elementi[i];
        }
        tmp[brElementi++]=m;
        delete [] elementi;
        elementi=tmp;
    }

    double vratiVkupnaMasa(){
        double suma=0.0;
        for(int i=0;i<brElementi;i++){
            suma+=elementi[i]->vratiMasa();
        }
        return suma;
    }

    Kamion pretovar(char *registracija, char *vozac){
        Kamion novKamion(registracija,vozac);
        double max=0.0;
        int index=0;
        for(int i=0;i<brElementi;i++){
            if(elementi[i]->vratiMasa()>max){
                max=elementi[i]->vratiMasa();
                index=i;
            }
        }
        for(int i=0;i<brElementi;i++){
            if(i!=index){
                novKamion.dodadiElement(elementi[i]);
            }
        }
        return novKamion;
    }

    void pecati(){
        cout<<"Kamion so registracija "<<registracija<<" i vozac "<<vozac<<" prenesuva:"<<endl;
        for(int i=0;i<brElementi;i++){
            elementi[i]->pecati();
        }
    }
};


int main()
{
    char ime[20], reg[9];
    double vol;
    int kol;
    bool g;
    double proc;

    cin>>reg;
    cin>>ime;
    Kamion A(reg, ime);
    ImaMasa **d = new ImaMasa*[5];
    cin>>vol>>kol;
    cin>>g;
    d[0] = new PaketSok(vol, kol, g);
    cin>>vol>>kol;
    cin>>proc;
    d[1] = new PaketVino(vol, kol, proc);
    cin>>vol>>kol;
    cin>>proc;
    d[2] = new PaketVino(vol, kol, proc);
    cin>>vol>>kol;
    cin>>g;
    d[3] = new PaketSok(vol, kol, g);
    cin>>vol>>kol;
    cin>>proc;
    d[4] = new PaketVino(vol, kol, proc);

    A.dodadiElement(d[0]);
    A.dodadiElement(d[1]);
    A.dodadiElement(d[2]);
    A.dodadiElement(d[3]);
    A.dodadiElement(d[4]);
    A.pecati();
    cout<<"Vkupna masa: "<<A.vratiVkupnaMasa()<<endl;
    cin>>reg;
    cin>>ime;
    Kamion B = A.pretovar(reg, ime);
    B.pecati();
    cout<<"Vkupna masa: "<<B.vratiVkupnaMasa()<<endl;

}