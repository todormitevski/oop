#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

class SMS{
protected:
    char pretplatnickiBroj[12];
    double osnovnaCena;

    const static double danok;
    static double PROCENT_REGULARNI;
    static double PROCENT_SPECIJALNI;
public:
    SMS(char *pretplatnickiBroj="", double osnovnaCena=0.0){
        strcpy(this->pretplatnickiBroj,pretplatnickiBroj);
        this->osnovnaCena=osnovnaCena;
    }

    virtual double SMS_cena()=0;

    static void set_rProcent(double newProcent){
        PROCENT_REGULARNI=newProcent/100+1;
    }

    static void set_sProcent(double newProcent){
        PROCENT_SPECIJALNI=newProcent/100+1;
    }

    friend ostream &operator<<(ostream &out, SMS &s){
        return out<<"Tel: "<<s.pretplatnickiBroj<<" - "<<"cena: "<<s.SMS_cena()<<"den."<<endl;
    }
};
const double SMS::danok=1.18; //18%
double SMS::PROCENT_REGULARNI=4; //300%
double SMS::PROCENT_SPECIJALNI=2.5; //150%

class RegularSMS: public SMS{
    char poraka[1000];
    bool roaming;
public:
    RegularSMS(char *pretplatnickiBroj="", double osnovnaCena=0.0, char *poraka="", bool roaming=true): SMS(pretplatnickiBroj,osnovnaCena){
        strcpy(this->poraka,poraka);
        this->roaming=roaming;
    };

    double SMS_cena(){
        double sumCena=0.0;
        if(roaming==true){
            sumCena+=osnovnaCena*PROCENT_REGULARNI;
        } else sumCena+=osnovnaCena*danok;
        return sumCena*=ceil((double)strlen(poraka)/160);
    }
};

class SpecialSMS: public SMS{
    bool daliHumanitarniCeli;
public:
    SpecialSMS(char *pretplatnickiBroj="", double osnovnaCena=0.0, bool daliHumanitarniCeli=true): SMS(pretplatnickiBroj,osnovnaCena){
        this->daliHumanitarniCeli=daliHumanitarniCeli;
    }

    double SMS_cena(){
        double sumCena=0.0;
        if(daliHumanitarniCeli==false){
            sumCena+=osnovnaCena*PROCENT_SPECIJALNI;
        } else sumCena+=osnovnaCena;
        return sumCena;
    }
};

void vkupno_SMS(SMS** poraka, int n){
    int vkReg=0, vkSpec=0;
    double vkCenaReg=0.0, vkCenaSpec=0.0;
    for(int i=0;i<n;i++){
        if(dynamic_cast<RegularSMS *>(poraka[i])){
            vkReg++;
            vkCenaReg+=poraka[i]->SMS_cena();
        } else if(dynamic_cast<SpecialSMS *>(poraka[i])){
            vkSpec++;
            vkCenaSpec+=poraka[i]->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<vkReg<<" regularni SMS poraki i nivnata cena e: "<<vkCenaReg<<endl;
    cout<<"Vkupno ima "<<vkSpec<<" specijalni SMS poraki i nivnata cena e: "<<vkCenaSpec<<endl;
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}