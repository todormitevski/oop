#include <iostream>
#include <string.h>
using namespace std;

//EXCEPTIONS
class InvalidDateException{
    int day,month,year;
public:
    InvalidDateException(int day=0, int month=0, int year=0){
        this->day=day;
        this->month=month;
        this->year=year;
    }
    void message(){
        cout<<"Invalid Date "<<day<<"/"<<month<<"/"<<year<<endl;
    }
};

class NotSupportedCurrencyException{
    char neDozvolenaValuta[3];
public:
    NotSupportedCurrencyException(char *neDozvolenaValuta=""){
        strcpy(this->neDozvolenaValuta,neDozvolenaValuta);
    }

    void message(){
        cout<<neDozvolenaValuta<<" is not a supported currency"<<endl;
    }
};

class Transakcija{
protected:
    int den,mesec,godina;
    double paricenIznos;

    void copy(const Transakcija &t){
        this->den=t.den;
        this->mesec=t.mesec;
        this->godina=t.godina;
        this->paricenIznos=t.paricenIznos;
    }

    static double EUR;
    static double USD;
public:
    Transakcija(int den=0, int mesec=0, int godina=0, double paricenIznos=0.0){
        if((den<1||den>31)||(mesec<1||mesec>12)){
            throw(InvalidDateException(den,mesec,godina));
        }
        this->den=den;
        this->mesec=mesec;
        this->godina=godina;
        this->paricenIznos=paricenIznos;
    }

//    Transakcija(const Transakcija &t){
//        copy(t);
//    }
//
//    Transakcija &operator=(const Transakcija &t){
//        if(this!=&t){
//            copy(t);
//        }
//        return *this;
//    }
//
//    ~Transakcija(){}

    virtual double voDenari()=0;
    virtual double voEvra()=0;
    virtual double voDolari()=0;
    virtual void pecati()=0;

    static double setEUR(double newEUR){
        EUR=newEUR;
    }

    static double setUSD(double newUSD){
        USD=newUSD;
    }

    static double getEUR(){
        return EUR;
    }

    static double getUSD(){
        return USD;
    }
};
double Transakcija::EUR=61;
double Transakcija::USD=50;

class DenarskaTransakcija: public Transakcija{
public:
    DenarskaTransakcija(int den, int mesec, int godina, double paricenIznos): Transakcija(den,mesec,godina,paricenIznos){}
//    DenarskaTransakcija(const DenarskaTransakcija &t): Transakcija(t.den,t.mesec,t.godina,t.paricenIznos){};
//    DenarskaTransakcija &operator=(const DenarskaTransakcija &t){
//        if(this!=&t){
//            Transakcija::copy(t);
//        }
//        return *this;
//    }
//    ~DenarskaTransakcija(){}

    double voDenari(){
        return paricenIznos;
    }

    double voEvra(){
        return paricenIznos/Transakcija::EUR;
    }

    double voDolari(){
        return paricenIznos/Transakcija::USD;
    }

    void pecati(){
        cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<paricenIznos<<" MKD"<<endl;
    }
};


class DeviznaTransakcija: public Transakcija{
    char valuta[3]; //dozvoleni valuti se EUR i USD
public:
    DeviznaTransakcija(int den=0, int mesec=0, int godina=0, double paricenIznos=0.0, char *valuta=""): Transakcija(den,mesec,godina,paricenIznos){
        if(strcmp(valuta,"USD")&&strcmp(valuta,"EUR")){
            throw(NotSupportedCurrencyException(valuta));
        }
        strcpy(this->valuta,valuta);
    }
//    DeviznaTransakcija(const DeviznaTransakcija &t): Transakcija(t.den,t.mesec,t.godina,t.paricenIznos){
//        strcpy(this->valuta,t.valuta);
//    }
//    DeviznaTransakcija &operator=(const DeviznaTransakcija &t){
//        if(this!=&t){
//            Transakcija::copy(t);
//            strcpy(this->valuta,t.valuta);
//        }
//        return *this;
//    }
//    ~DeviznaTransakcija(){}

    double voDenari(){
        if(!strcmp(valuta,"EUR")){
            return 1.0*paricenIznos*Transakcija::EUR;
        } else /*if(!strcmp(valuta,"USD"))*/{
            return 1.0*paricenIznos*Transakcija::USD;
        }
        // else{
        //     return paricenIznos;
        // }
    }

    double voEvra(){
        if(!strcmp(valuta,"EUR")){
            return 1.0*paricenIznos;
        } else /*if(!strcmp(valuta,"USD"))*/{
            return (paricenIznos*Transakcija::USD*1.0)/Transakcija::EUR;
        }
        // else{
        //     return paricenIznos/EUR;
        // }
    }

    double voDolari(){
        // if(!strcmp(valuta,"EUR")){
        //     return (paricenIznos*EUR)/USD;
        // } else if(!strcmp(valuta,"USD")){
        //     return paricenIznos;
        // } else{
        //     return paricenIznos/USD;
        // }
        if(!strcmp(valuta,"USD")){
            return paricenIznos*1.0;
        } else{
            return (paricenIznos*Transakcija::EUR*1.0)/Transakcija::USD;
        }
    }

    void pecati(){
        cout<<den<<"/"<<mesec<<"/"<<godina<<" "<<paricenIznos<<" "<<valuta<<endl;
    }
};


class Smetka{
    Transakcija **transakcii;
    int brTransakcii;
    char brojSmetka[15];
    double balance; //saldo vo denari

    void copy(const Smetka &s){
        this->brTransakcii=s.brTransakcii;
        //this->transakcii=new Transakcija *[s.brTransakcii];
        for(int i=0;i<s.brTransakcii;i++){
            this->transakcii[i]=s.transakcii[i];
        }
        strcpy(this->brojSmetka,s.brojSmetka);
        this->balance=s.balance;
    }
public:
    // Smetka(){}
    Smetka(char *brojSmetka="", double balance=0.0){
        strcpy(this->brojSmetka,brojSmetka);
        this->balance=balance;
        this->brTransakcii=0;
        this->transakcii=new Transakcija *[0];
    }
    Smetka(const Smetka &s){
        copy(s);
    }
    Smetka &operator=(const Smetka &s){
        if(this!=&s){
            delete [] transakcii;
            copy(s);
        }
        return *this;
    }
    ~Smetka(){
        delete [] transakcii;
    }

    Smetka &operator+=(Transakcija *t){
        Transakcija **tmp=new Transakcija *[brTransakcii+1];
        for(int i=0;i<brTransakcii;i++){
            tmp[i]=transakcii[i];
        }
        tmp[brTransakcii++]=t;
        delete [] transakcii;
        transakcii=tmp;
        return *this;
    }

    void izvestajVoDenari(){
        double finalBalance=balance;
        for(int i=0;i<brTransakcii;i++){
            finalBalance+=transakcii[i]->voDenari();
        }
        cout<<"Korisnikot so smetka: "<<brojSmetka<<" ima momentalno saldo od "<<finalBalance<<" MKD"<<endl;
    }

    void izvestajVoEvra(){
        double finalBalance=balance/transakcii[0]->voEvra();
        for(int i=0;i<brTransakcii;i++){
            finalBalance+=transakcii[i]->voEvra();
        }
        cout<<"Korisnikot so smetka: "<<brojSmetka<<" ima momentalno saldo od "<<finalBalance<<" EUR"<<endl;
    }

    void izvestajVoDolari(){
        double finalBalance=balance/transakcii[0]->voDolari();
        for(int i=0;i<brTransakcii;i++){
            finalBalance+=transakcii[i]->voDolari();
        }
        cout<<"Korisnikot so smetka: "<<brojSmetka<<" ima momentalno saldo od "<<finalBalance<<" USD"<<endl;
    }

    void pecatiTransakcii(){
        for(int i=0;i<brTransakcii;i++){
            transakcii[i]->pecati();
        }
    }
};

int main () {

    Smetka s ("300047024112789",1500);

    int n, den, mesec, godina, tip;
    double iznos;
    char valuta [3];

    cin>>n;
    cout<<"===VNESUVANJE NA TRANSAKCIITE I SPRAVUVANJE SO ISKLUCOCI==="<<endl;
    for (int i=0;i<n;i++){
        cin>>tip>>den>>mesec>>godina>>iznos;
        if (tip==2){
            cin>>valuta;
            try{
                Transakcija * t = new DeviznaTransakcija(den,mesec,godina,iznos,valuta);
                s+=t;
            }
            catch(InvalidDateException &i){
                i.message();
            }
            catch(NotSupportedCurrencyException &i){
                i.message();
            }
            //delete t;
        }
        else {
            try{
                Transakcija * t = new DenarskaTransakcija(den,mesec,godina,iznos);
                s+=t;
            }
            catch(InvalidDateException &i){
                i.message();
            }
            //delete t;
        }

    }
    cout<<"===PECHATENJE NA SITE TRANSAKCII==="<<endl;
    s.pecatiTransakcii();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.izvestajVoEvra();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.izvestajVoDolari();

    cout<<"\n===PROMENA NA KURSOT NA EVROTO I DOLAROT===\n"<<endl;


    double newEUR, newUSD;
    cin>>newEUR>>newUSD;
    Transakcija::setEUR(newEUR);
    Transakcija::setUSD(newUSD);

    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DENARI==="<<endl;
    s.izvestajVoDenari();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO EVRA==="<<endl;
    s.izvestajVoEvra();
    cout<<"===IZVESHTAJ ZA SOSTOJBATA NA SMETKATA VO DOLARI==="<<endl;
    s.izvestajVoDolari();



    return 0;
}