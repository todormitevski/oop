#include <iostream>
#include <string.h>
using namespace std;

class Transport{
protected:
    char destinacija[20];
    int osnovnaCena;
    int rastojanie; //vo km
public:
    Transport(char *destinacija="", int osnovnaCena=0, int rastojanie=0){
        strcpy(this->destinacija,destinacija);
        this->osnovnaCena=osnovnaCena;
        this->rastojanie=rastojanie;
    }

    virtual double cenaTransport()=0;

    bool operator<(Transport &t){
        return rastojanie<t.rastojanie;
    }

    char *getDestinacija(){
        return destinacija;
    }

    int getRastojanie(){
        return rastojanie;
    }
};

class AvtomobilTransport: public Transport{
    bool daliShofer;
public:
    AvtomobilTransport(char *destinacija="", int osnovnaCena=0, int rastojanie=0, bool daliShofer=true): Transport(destinacija,osnovnaCena,rastojanie){
        this->daliShofer=daliShofer;
    }

    void setDaliShofer(bool newShofer){
        this->daliShofer=newShofer;
    }

    bool getDaliShofer(){
        return daliShofer;
    }

    double cenaTransport(){
        if(daliShofer){
            return osnovnaCena*1.2;
        } else return osnovnaCena;
    }
};

class KombeTransport: public Transport{
    int capacity;
public:
    KombeTransport(char *destinacija="", int osnovnaCena=0, int rastojanie=0, int capacity=0): Transport(destinacija,osnovnaCena,rastojanie){
        this->capacity=capacity;
    }

    void setCapacity(int newCap){
        this->capacity=newCap;
    }

    int getCapacity(){
        return capacity;
    }

    double cenaTransport(){
        return osnovnaCena-capacity*200;
    }
};

void pecatiPoloshiPonudi(Transport **transporti, int n, Transport &t){
    Transport **tmp=new Transport *[n+1];
    int k=0; //za novata niza
    for(int i=0;i<n;i++){
        if(transporti[i]->cenaTransport()>t.cenaTransport()){
            tmp[k]=transporti[i];
            k++;
        }
    }

    for(int i=0;i<k-1;i++){
        for(int j=0;j<k-1-i;j++){
            if(tmp[j]->getRastojanie()>tmp[j+1]->getRastojanie()){
                Transport *t=tmp[j];
                tmp[j]=tmp[j+1];
                tmp[j+1]=t;
            }
        }
    }

    for(int i=0;i<k;i++){
        cout<<tmp[i]->getDestinacija()<<" "<<tmp[i]->getRastojanie()<<" "<<tmp[i]->cenaTransport()<<endl;
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}