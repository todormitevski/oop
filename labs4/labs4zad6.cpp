#include <iostream>
#include <string.h>
using namespace std;

enum Tip{
    LINUX,
    UNIX,
    WINDOWS
};

class OperativenSistem{
    char *imeOS;
    float verzija;
    Tip tip;
    float sizeInGb;

    void copy(const OperativenSistem &o){
        this->imeOS=new char[strlen(o.imeOS)+1];
        strcpy(this->imeOS,o.imeOS);
        this->verzija=o.verzija;
        this->tip=o.tip;
        this->sizeInGb=o.sizeInGb;
    }
public:
    OperativenSistem(char *imeOS="", float verzija=0.0, Tip tip=(Tip)0, float sizeInGb=0.0){
        this->imeOS=new char[strlen(imeOS)+1];
        strcpy(this->imeOS,imeOS);
        this->verzija=verzija;
        this->tip=tip;
        this->sizeInGb=sizeInGb;
    }

    OperativenSistem(const OperativenSistem &o){
        copy(o);
    }

    OperativenSistem &operator=(const OperativenSistem &o){
        if(this!=&o){
            delete [] imeOS;
            copy(o);
        }
        return *this;
    }

    ~OperativenSistem(){
        delete [] imeOS;
    }

    void pecati(){
        cout<<"Ime: "<<imeOS<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<sizeInGb<<endl;
    }

    bool ednakviSe(const OperativenSistem &os){
        //ednakvi ako imaat isto ime,verzija,tip i golemina
        return ((!strcmp(imeOS,os.imeOS))&&(verzija==os.verzija)&&(tip==os.tip)&&(sizeInGb==os.sizeInGb));
    }

    int sporediVerzija(const OperativenSistem &os){
        if(verzija==os.verzija){
            return 0;
        } else if(os.verzija>verzija){
            return -1;
        } else{
            return 1;
        }
    }

    bool istaFamilija(const OperativenSistem &sporedba){
        //da imaat isto ime i ist tip
        return ((!strcmp(imeOS,sporedba.imeOS))&&(tip==sporedba.tip));
    }
};

class Repozitorium{
    char imeRepo[20];
    OperativenSistem *operativniSistemi;
    int brOS;
public:
    Repozitorium(){
        brOS=0;
        operativniSistemi=NULL;
    }

    Repozitorium(const char *ime){
        strcpy(this->imeRepo,ime);
        this->brOS=brOS;
        operativniSistemi=new OperativenSistem[brOS];
    }

    ~Repozitorium(){
        delete [] operativniSistemi;
    }

    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<imeRepo<<endl;
        for(int i=0;i<brOS;i++){
            operativniSistemi[i].pecati();
        }
    }

    void izbrishi(const OperativenSistem &operativenSistem){
        for(int i=0;i<brOS;i++){
            if(operativniSistemi[i].ednakviSe(operativenSistem)){
                --brOS;
                for(int j=i;j<brOS;j++){
                    this->operativniSistemi[j]=operativniSistemi[j+1];
                }
                break;
            }
        }
    }

    //...wtf
//    void dodadi(const OperativenSistem &nov){
//        OperativenSistem *tmp=new OperativenSistem[brOS+1];
//        for(int i=0;i<brOS;i++){
//            if(operativniSistemi[i].istaFamilija(nov) && operativniSistemi[i].sporediVerzija(nov)==-1){
//                //nov=operativniSistemi[i];
//            } else{
//                //...
//            }
//        }
//    }

    void dodadi(OperativenSistem &nov){
        OperativenSistem *tmp = new OperativenSistem[brOS+1];
        bool flag=false;

        for(int i=0; i<brOS; i++){
            tmp[i] = (this->operativniSistemi[i].istaFamilija(nov) && operativniSistemi[i].sporediVerzija(nov)==-1)?(flag=true),nov:this->operativniSistemi[i];
        }
        if(flag==false){
            tmp[brOS++] = nov;
        }
        delete[] operativniSistemi;
        operativniSistemi = tmp;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}