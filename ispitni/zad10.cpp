#include <iostream>
#include <string.h>
using namespace std;

//место за вашиот код
class NegativnaVrednost{
public:
    void message(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};

class Oglas{
    char naslov[50];
    char kategorija[30];
    char opis[100];
    double cena; //vo evra
public:
    Oglas(char *naslov="", char *kategorija="", char *opis="", double cena=0.0){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }

    bool operator>(Oglas &o){
        return cena>o.cena;
    }

    friend ostream &operator<<(ostream &out, Oglas &o){
        return out<<o.naslov<<endl<<o.opis<<endl<<o.cena<<" evra"<<endl;
    }

    double getCena(){
        return cena;
    }

    char *getKategorija(){
        return kategorija;
    }
};

class Oglasnik{
    char imeOglasnik[20];
    Oglas *oglasi;
    int brOglasi;

    void copy(const Oglasnik &o){
        strcpy(this->imeOglasnik,o.imeOglasnik);
        this->brOglasi=o.brOglasi;
        this->oglasi=new Oglas[brOglasi];
        for(int i=0;i<brOglasi;i++){
            this->oglasi[i]=o.oglasi[i];
        }
    }
public:
    Oglasnik(char *imeOglasnik=""){
        strcpy(this->imeOglasnik,imeOglasnik);
        brOglasi=0;
        oglasi=new Oglas[brOglasi];
    }

    Oglasnik(const Oglasnik &o){
        copy(o);
    }

    Oglasnik &operator=(const Oglasnik &o){
        if(this!=&o){
            delete [] oglasi;
            copy(o);
        }
        return *this;
    }

    ~Oglasnik(){
        delete [] oglasi;
    }

    Oglasnik &operator+=(Oglas &o){
        if(o.getCena()<0){
            throw NegativnaVrednost();
        }
        Oglas *tmp=new Oglas[brOglasi+1];
        for(int i=0;i<brOglasi;i++){
            tmp[i]=oglasi[i];
        }
        tmp[brOglasi++]=o;
        delete [] oglasi;
        oglasi=tmp;
        return *this;
    }

    friend ostream &operator<<(ostream &out, Oglasnik &o){
        out<<o.imeOglasnik<<endl;
        for(int i=0;i<o.brOglasi;i++){
            cout<<o.oglasi[i]<<endl;
        }
        return out;
    }

    void oglasiOdKategorija(const char *k){
        for(int i=0;i<brOglasi;i++){
            if(!strcmp(oglasi[i].getKategorija(),k)){
                cout<<oglasi[i]<<endl;
            }
        }
    }

    void najniskaCena(){
        double max=oglasi[0].getCena();
        int minIndex=0;
        for(int i=0;i<brOglasi;i++){
            if(oglasi[i].getCena()<max){
                max=oglasi[i].getCena();
                minIndex=i;
            }
        }
        cout<<oglasi[minIndex];
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            try{
                Oglas o(naslov, kategorija, opis, cena);
                ogl+=o;
            }
            catch(NegativnaVrednost &n){
                n.message();
            }
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}