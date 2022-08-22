#include <iostream>
using namespace std;

class Vozilo{
protected:
    double mass;
    int width;
    int height;

//    void copy(const Vozilo &v){
//        this->mass=v.mass;
//        this->width=v.width;
//        this->height=v.height;
//    }
public:
    Vozilo(double mass=0.0, int width=0, int height=0){
        this->mass=mass;
        this->width=width;
        this->height=height;
    }

//    Vozilo(const Vozilo &v){
//        copy(v);
//    }

    double getMass(){
        return mass;
    }

    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }

    virtual int vratiDnevnaCena()=0;
};

class Avtomobil: public Vozilo{
    int brVrati;
public:
    Avtomobil(double mass=0.0, int width=0, int height=0, int brVrati=0): Vozilo(mass,width,height){
        this->brVrati=brVrati;
    }

    int getBrVrati(){
        return brVrati;
    }

    void setBrVrati(int vrati){
        this->brVrati=vrati;
    }

    int vratiDnevnaCena(){
        if(brVrati<5){
            return 100;
        } else return 130;
    }
};

class Avtobus: public Vozilo{
    int brPatnici;
public:
    Avtobus(double mass=0.0, int width=0, int height=0, int brPatnici=0): Vozilo(mass,width,height){
        this->brPatnici=brPatnici;
    }

    int getBrPatnici(){
        return brPatnici;
    }

    void setBrPatnici(int patnici){
        this->brPatnici=patnici;
    }

    int vratiDnevnaCena(){
        return 5*brPatnici;
    }
};

class Kamion: public Vozilo{
    double maxMasa;
public:
    Kamion(double mass=0.0, int width=0, int height=0, double maxMasa=0.0): Vozilo(mass,width,height){
        this->maxMasa=maxMasa;
    }

    double getMaxMasa(){
        return maxMasa;
    }

    void setMaxMasa(double masa){
        this->maxMasa=masa;
    }

    int vratiDnevnaCena(){
        return (getMass()+maxMasa)*0.02;
    }
};

class ParkingPlac{
    Vozilo **vozila;
    int brVozila;

    void copy(const ParkingPlac &p){
        this->brVozila=p.brVozila;
        this->vozila=new Vozilo *[p.brVozila];
        for(int i=0;i<brVozila;i++){
            this->vozila[i]=p.vozila[i];
        }
    }
public:
    ParkingPlac(){
        this->brVozila=0;
        this->vozila=new Vozilo *[brVozila];
    }

    ParkingPlac(const ParkingPlac &p){
        copy(p);
    }

    ParkingPlac &operator=(const ParkingPlac &p){
        if(this!=&p){
            delete [] vozila;
            copy(p);
        }
        return *this;
    }

    ~ParkingPlac(){
        delete [] vozila;
    }

    ParkingPlac &operator+=(Vozilo *p){
        Vozilo **tmp=new Vozilo *[brVozila+1];
        for(int i=0;i<brVozila;i++){
            tmp[i]=vozila[i];
        }
        tmp[brVozila++]=p;
        delete [] vozila;
        vozila=tmp;
        return *this;
    }

    float presmetajVkupnaMasa(){
        double vkMass=0.0;
        for(int i=0;i<brVozila;i++){
            vkMass+=vozila[i]->getMass();
        }
        return vkMass;
    }

    int brojVozilaPoshirokiOd(int l){
        int brPosiroki=0;
        for(int i=0;i<brVozila;i++){
            if(vozila[i]->getWidth()>l){
                brPosiroki++;
            }
        }
        return brPosiroki;
    }

    void pecati(){
        int brAvtomobili=0, brAvtobusi=0, brKamioni=0;
        for(int i=0;i<brVozila;i++){
            if(dynamic_cast<Avtomobil *>(vozila[i])){
                brAvtomobili++;
            } else if(dynamic_cast<Avtobus *>(vozila[i])){
                brAvtobusi++;
            } else if(dynamic_cast<Kamion *>(vozila[i])){
                brKamioni++;
            }
        }
        cout<<"Brojot na avtomobili e "<<brAvtomobili<<", brojot na avtobusi e "<<brAvtobusi<<" i brojot na kamioni e "<<brKamioni<<"."<<endl;
    }

    int pogolemaNosivostOd(Vozilo& v){
        int brPogolemi=0;
        for(int i=0;i<brVozila;i++){
            if(dynamic_cast<Kamion *>(vozila[i]) && vozila[i]->getMass()>v.getMass()){
                brPogolemi++;
            }
        }
        return brPogolemi;
    }

    int vratiDnevnaZarabotka(){
        int zarabotka=0;
        for(int i=0;i<brVozila;i++){
            zarabotka+=vozila[i]->vratiDnevnaCena();
        }
        return zarabotka;
    }
};

int main(){
    ParkingPlac p;

    int n;
    cin>>n;
    int shirina,visina, broj;
    float masa,nosivost;
    for (int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>masa>>shirina>>visina>>broj;
            Avtomobil *a=new Avtomobil(masa,shirina,visina,broj);
            p+=a;
        }
        if(type==2){
            cin>>masa>>shirina>>visina>>broj;
            p+=new Avtobus(masa,shirina,visina,broj);
        }
        if(type==3){
            cin>>masa>>shirina>>visina>>nosivost;
            p+=new Kamion(masa,shirina,visina,nosivost);
        }
    }

    p.pecati();

    cout<<"\nZarabotkata e "<<p.vratiDnevnaZarabotka()<<endl;
    cout<<"Vkupnata masa e "<<p.presmetajVkupnaMasa()<<endl;
    cout<<"Brojot poshiroki od 5 e "<<p.brojVozilaPoshirokiOd(5)<<endl;
    Avtomobil a(1200,4,3,5);
    cout<<"Brojot na kamioni so nosivost pogolema od avtomobilot e "<<p.pogolemaNosivostOd(a)<<endl;


}