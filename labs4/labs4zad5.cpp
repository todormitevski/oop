#include <iostream>
#include <string.h>
using namespace std;

class Pica{
    char ime[15];
    int cena;
    char *sostojki;
    int namaluvanje;

    void copy(const Pica &p){
        strcpy(this->ime,p.ime);
        this->cena=p.cena;
        this->sostojki=new char[strlen(p.sostojki)+1];
        strcpy(this->sostojki,p.sostojki);
        this->namaluvanje=p.namaluvanje;
    }
public:
    Pica(char *ime="", int cena=0, char *sostojki="", int namaluvanje=0){
        strcpy(this->ime,ime);
        this->cena=cena;
        this->sostojki=new char[strlen(sostojki)+1];
        strcpy(this->sostojki,sostojki);
        this->namaluvanje=namaluvanje;
    }

    Pica(const Pica &p){
        copy(p);
    }

    Pica &operator=(const Pica &p){
        if(this!=&p){
            delete [] sostojki;
            copy(p);
        }
        return *this;
    }

    ~Pica(){
        delete [] sostojki;
    }

    void pecati(){
        cout<<ime<<" - "<<sostojki<<", "<<cena;
    }

    bool istiSe(Pica p){
        return !strcmp(this->sostojki,p.sostojki);
    }

    int getNamaluvanje(){
        return namaluvanje;
    }

    int getCena(){
        return cena;
    }
};

class Picerija{
    char ime[15];
    Pica *pici;
    int brPici;

    void copy(const Picerija &p){
        strcpy(this->ime,p.ime);
        this->brPici=p.brPici;
        this->pici=new Pica[p.brPici];
        for(int i=0;i<brPici;i++){
            this->pici[i]=p.pici[i];
        }
    }
public:
    Picerija(char *ime=""){
        strcpy(this->ime,ime);
        brPici=0;
        pici=NULL;
    }

    Picerija(const Picerija &p){
        copy(p);
    }

    Picerija &operator=(const Picerija &p){
        if(this!=&p){
            delete [] pici;
            copy(p);
        }
        return *this;
    }

    ~Picerija(){
        delete [] pici;
    }

    char *getIme(){
        return ime;
    }

    void setIme(char *ime){
        strcpy(this->ime,ime);
    }

    void dodadi(Pica p){
        bool isti=false;
        for(int i=0;i<brPici;i++){
            if(pici[i].istiSe(p)){
                isti=true;
                break;
            }
        }
        if(!isti){
            Pica *tmp=new Pica[brPici+1];
            for(int i=0;i<brPici;i++){
                tmp[i]=pici[i];
            }
            tmp[brPici++]=p;
            delete [] pici;
            pici=tmp;
        }
    }

    void piciNaPromocija(){
        for(int i=0;i<brPici;i++){
            if(pici[i].getNamaluvanje()>0){
                int popust=(pici[i].getCena() * pici[i].getNamaluvanje())/100;
                int cenaPoslePopust=pici[i].getCena()-popust;
                pici[i].pecati();
                cout<<" "<<cenaPoslePopust<<endl;
            }
        }
    }
};

int main () {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for(int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp,100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki,100);
        int popust;
        cin >> popust;
        Pica p(imp,cena,sostojki,popust);
        p1.dodadi(p);
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp,100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki,100);
    int popust;
    cin >> popust;
    Pica p(imp,cena,sostojki,popust);
    p2.dodadi(p);

    cout<<p1.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p1.piciNaPromocija();

    cout<<p2.getIme()<<endl;
    cout<<"Pici na promocija:"<<endl;
    p2.piciNaPromocija();

    return 0;
}