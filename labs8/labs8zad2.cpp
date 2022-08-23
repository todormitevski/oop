#include <iostream>
#include <string.h>
#define pi 3.14
using namespace std;

class Igrachka {
public:
    virtual float getVolumen() = 0;
    virtual float getMasa() = 0;
    //дополнително барање 1
    virtual float getPlostina()=0;
};

class Forma {
protected:
    char boja[100];
    int gustina;
public:
    // да се имплементираат потребните методи
    Forma(char *boja="", int gustina=0){
        strcpy(this->boja,boja);
        this->gustina=gustina;
    }
};

class Topka: public Forma, public Igrachka{
    int radius;
public:
    Topka(char *boja="", int gustina=0, int radius=0): Forma(boja,gustina), Igrachka(){
        this->radius=radius;
    }

    float getVolumen(){
        return 4.0/3 * pi * radius*radius*radius;
    }

    float getMasa(){
        return getVolumen()*gustina;
    }

    float getPlostina(){
        return 4*pi*radius*radius;
    }
};

class Kocka: public Forma, public Igrachka{
    int visina;
    int sirina;
    int dlabocina;
public:
    Kocka(char *boja="", int gustina=0, int visina=0, int sirina=0, int dlabocina=0): Forma(boja,gustina), Igrachka(){
        this->visina=visina;
        this->sirina=sirina;
        this->dlabocina=dlabocina;
    }

    float getVolumen(){
        return (float)visina * (float)sirina * (float)dlabocina;
    }

    float getMasa(){
        return getVolumen()*gustina;
    }

    float getPlostina(){
        return 2*visina*sirina + 2*sirina*dlabocina + 2*visina*dlabocina;
    }
};

int main(){
    //vnesi informacii za kupche
    char boja[100];
    int gustina,radius,visina,sirina,dlabocina,tip;
    int n;
    cin>>n;

    Igrachka **kupche=new Igrachka *[n];

    for(int i=0;i<n;i++){
        cin>>tip; //1-topka, 2-kocka
        if(tip==1){
            cin>>boja>>gustina>>radius;
            kupche[i]= reinterpret_cast<Igrachka *>(new Topka(boja, gustina, radius));
        } else if(tip==2){
            cin>>boja>>gustina>>visina>>sirina>>dlabocina;
            kupche[i]= reinterpret_cast<Igrachka *>(new Kocka(boja, gustina, visina, sirina, dlabocina));
        }
    }

    //vnesi informacii za igrachkata na Petra
    cin>>boja>>gustina>>visina>>sirina>>dlabocina;
    Kocka petra(boja,gustina,visina,sirina,dlabocina);

    //baranje 1
    float vkMasa=0.0;
    for(int i=0;i<n;i++){
        vkMasa+=kupche[i]->getMasa();
    }
    if(vkMasa>petra.getMasa()){
        cout<<"DA\n";
    } else cout<<"NE\n";

    //baranje 2
    float maxVolumen=0.0;
    float minPlostina=99999;
    for(int i=0;i<n;i++){
        if(kupche[i]->getVolumen()>maxVolumen){
            maxVolumen=kupche[i]->getVolumen();
        }
        //minPlostina=kupche[i]->getPlostina();
        if(kupche[i]->getPlostina()<minPlostina){
            minPlostina=kupche[i]->getPlostina();
        }
    }
    cout<<"Razlikata e: "<<abs(maxVolumen-petra.getVolumen())<<endl;

    //дополнително барање 2
    cout<<"Razlikata e: "<<abs(petra.getPlostina()-minPlostina)<<endl;

    return 0;
}