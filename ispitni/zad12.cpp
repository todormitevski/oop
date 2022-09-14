#include <iostream>
#include <string.h>
using namespace std;

class InvalidProductionDate{
public:
    void message(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

enum tip{
    smartfon, //0
    kompjuter //1
};

class Device{
    char model[100];
    tip tipDevice;
    int godina;

    static double CASOVI_ZA_PROVERKA;
public:
    Device(char *model="", tip tipDevice=(tip)0, int godina=0){
        strcpy(this->model,model);
        this->tipDevice=tipDevice;
        this->godina=godina;
    }

    static void setPocetniCasovi(double newCasovi){
        CASOVI_ZA_PROVERKA=newCasovi;
    }

    double proverka(){
        double sum=0.0;
        if(godina>2015){
            sum+=2;
        }
        if(tipDevice==1){
            sum+=2;
        }
        return CASOVI_ZA_PROVERKA+sum;
    }

    friend ostream &operator<<(ostream &out, Device &d){
        out<<d.model<<endl;
        if(d.tipDevice==0){
            out<<"Mobilen ";
        } else if(d.tipDevice==1){
            out<<"Laptop ";
        }
        out<<d.proverka()<<endl;
    }

    int getGodina(){
        return godina;
    }
};
double Device::CASOVI_ZA_PROVERKA=1;

class MobileServis{
    char adresa[100];
    Device *devices;
    int brDevices;

    void copy(const MobileServis &m){
        this->brDevices=m.brDevices;
        this->devices=new Device[brDevices];
        for(int i=0;i<brDevices;i++){
            this->devices[i]=m.devices[i];
        }
        strcpy(this->adresa,m.adresa);
    }
public:
    MobileServis(char *adresa=""){
        strcpy(this->adresa,adresa);
        brDevices=0;
        devices=new Device[0];
    }

    MobileServis(const MobileServis &m){
        copy(m);
    }

    MobileServis &operator=(const MobileServis &m){
        if(this!=&m){
            delete [] devices;
            copy(m);
        }
        return *this;
    }

    ~MobileServis(){
        delete [] devices;
    }

    MobileServis &operator+=(Device &d){
        if(d.getGodina()>2019 || d.getGodina()<2000){
            throw InvalidProductionDate();
        }
        Device *tmp=new Device[brDevices+1];
        for(int i=0;i<brDevices;i++){
            tmp[i]=devices[i];
        }
        tmp[brDevices++]=d;
        delete [] devices;
        devices=tmp;
        return *this;
    }

    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<brDevices;i++){
            cout<<devices[i];
        }
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try{
                Device tmp(ime,(tip)tipDevice,godina);
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try{
                Device tmp(ime,(tip)tipDevice,godina);
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try{
                Device tmp(ime,(tip)tipDevice,godina);
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try{
                Device tmp(ime,(tip)tipDevice,godina);
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            try{
                Device tmp(ime,(tip)tipDevice,godina);
                t+=tmp;
            }
            catch(InvalidProductionDate &i){
                i.message();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    return 0;
}