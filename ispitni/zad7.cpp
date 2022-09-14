#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundsException{
public:
    void message(){
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(char* smetka,int pin){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    // дополниете ја класата
    bool getDopolnitelenPin(){
        return povekjePin;
    }

    char *getSmetka(){
        return smetka;
    }

    virtual int tezinaProbivanje(){
        int tezina=0;
        int tmp=pin;
        while(tmp){
            tezina++;
            tmp/=10;
        }
        return tezina;
    }

    friend ostream &operator<<(ostream &out, Karticka &k){
        out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
    }
};

//вметнете го кодот за SpecijalnaKarticka
class SpecijalnaKarticka: public Karticka{
    int *dopolnitelenPin;
    int brDopolnitelen;

    const static int P;
public:
    SpecijalnaKarticka(char* smetka,int pin, int *dopolnitelenPin=0, int brDopolnitelen=0): Karticka(smetka,pin){
        this->brDopolnitelen=brDopolnitelen;
        this->dopolnitelenPin=new int[brDopolnitelen];
        for(int i=0;i<brDopolnitelen;i++){
            this->dopolnitelenPin[i]=dopolnitelenPin[i];
        }
    }

    int tezinaProbivanje(){
        return Karticka::tezinaProbivanje()+brDopolnitelen;
    }

    SpecijalnaKarticka &operator+=(int newPin){
        if(brDopolnitelen+1>P){
            throw OutOfBoundsException();
        }
        int *tmp=new int[brDopolnitelen+1];
        for(int i=0;i<brDopolnitelen;i++){
            tmp[i]=dopolnitelenPin[i];
        }
        delete [] dopolnitelenPin;
        tmp[brDopolnitelen]=newPin;
        dopolnitelenPin=tmp;
        return *this;
    }
};
const int SpecijalnaKarticka::P=4;

class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;

    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    //да се дополни класата
    static void setLIMIT(int newLimit){
        LIMIT=newLimit;
    }

    void pecatiKarticki(){
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++){
            if(karticki[i]->tezinaProbivanje()<=LIMIT){
                cout<<*karticki[i];
            }
        }
    }

    void dodadiDopolnitelenPin(char *smetka, int novPin){
        for(int i=0;i<broj;i++){
            int flag=0, index=0;
            if(!strcmp(karticki[i]->getSmetka(),smetka)){
                flag=1;
                index=i;
            }
            if(flag){
                SpecijalnaKarticka *s=dynamic_cast<SpecijalnaKarticka *>(karticki[index]);
                if(s!=0){
                    *s+=novPin;
                }
            }
        }
    }
};
int Banka::LIMIT=7;

int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;

        komercijalna.dodadiDopolnitelenPin(smetka,pin);

    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
