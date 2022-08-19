#include <iostream>
#include <string.h>
using namespace std;

class Avtomobil{
    char boja[20];
    char brend[20];
    char model[20];

    void copy(const Avtomobil &a){
        strcpy(this->boja,a.boja);
        strcpy(this->brend,a.brend);
        strcpy(this->model,a.model);
    }
public:
    Avtomobil(char *boja="", char *brend="", char *model=""){
        strcpy(this->boja,boja);
        strcpy(this->brend,brend);
        strcpy(this->model,model);
    }

//    Avtomobil(const Avtomobil &a){
//        copy(a);
//    }

    Avtomobil &operator=(const Avtomobil &a){
        if(this!=&a){
            copy(a);
        }
        return *this;
    }

    void pecati(){
        cout<<boja<<" "<<brend<<" "<<model<<endl;
    }
};

class ParkingPlac{
    char adresa[20];
    char *id;
    int cena;
    int zarabotka;
    Avtomobil *avtomobili;
    int brAvtomobili;

    void copy(const ParkingPlac &p){
        strcpy(this->adresa,p.adresa);
        this->id=new char[strlen(p.id)+1];
        strcpy(this->id,p.id);
        this->cena=p.cena;
        this->zarabotka=p.zarabotka;
        this->avtomobili=new Avtomobil[0];
        this->brAvtomobili=p.brAvtomobili;
    }

    void freeMem(){
        delete [] id;
        delete [] avtomobili;
    }
public:
    ParkingPlac(char *adresa="", char *id="", int cena=0, int zarabotka=0, int brAvtomobili=0){
        strcpy(this->adresa,adresa);
        this->id=new char[strlen(id)+1];
        strcpy(this->id,id);
        this->cena=cena;
        this->zarabotka=zarabotka;
        this->avtomobili=new Avtomobil[0];
        this->brAvtomobili=brAvtomobili;
    }

    ParkingPlac(const ParkingPlac &p){
        copy(p);
    }

    ParkingPlac &operator=(const ParkingPlac &p){
        if(this!=&p){
            freeMem();
            copy(p);
        }
        return *this;
    }

    ~ParkingPlac(){
        freeMem();
    }

    char *getId() const{
        return id;
    }

    void pecati(){
        if(zarabotka!=0){
            cout<<id<<" "<<adresa<<" - "<<zarabotka<<" denari"<<endl;
        } else cout<<id<<" "<<adresa<<endl;
    }

    void platiCasovi(int casovi){
        zarabotka+=cena*casovi;
    }

    bool daliIstaAdresa(ParkingPlac p){
        return !strcmp(adresa,p.adresa);
    }

    void parkirajVozilo(Avtomobil novoVozilo){
        Avtomobil *tmp=new Avtomobil[brAvtomobili+1];
        for(int i=0;i<brAvtomobili;i++){
            tmp[i]=avtomobili[i];
        }
        tmp[brAvtomobili++]=novoVozilo;
        delete [] avtomobili;
        avtomobili=tmp;
    }

    void pecatiParkiraniVozila(){
        cout<<"Vo parkingot se parkirani slednite vozila:"<<endl;
        for(int i=0;i<brAvtomobili;i++){
            cout<<i+1<<".";
            avtomobili[i].pecati();
        }
    }
};

int main(){

    ParkingPlac p[100];
    int n,m;
    char adresa[50],id[50];
    int brojcasovi,cenacas;
    cin>>n;
    if(n > 0){


        for (int i=0;i<n;i++){
            cin.get();
            cin.getline(adresa,50);
            cin>>id>>cenacas;

            ParkingPlac edna(adresa,id,cenacas);

            p[i]=edna;
        }

        //plakjanje
        cin>>m;
        for (int i=0;i<m;i++){

            cin>>id>>brojcasovi;

            int findId=false;
            for (int j=0;j<m;j++){
                if (strcmp(p[j].getId(),id)==0){
                    p[j].platiCasovi(brojcasovi);
                    findId=true;
                }
            }
            if (!findId)
                cout<<"Ne e platen parking. Greshen ID."<<endl;
        }

        cout<<"========="<<endl;
        ParkingPlac pCentar("Cvetan Dimov","C10",80);
        for (int i=0;i<n;i++)
            if (p[i].daliIstaAdresa(pCentar))
                p[i].pecati();
    } else {

        ParkingPlac najdobarPlac("Mars", "1337", 1);
        int brVozila;
        cin >> brVozila;
        for(int i = 0; i < brVozila; ++i){

            char boja[20];
            char brend[20];
            char model[20];

            cin >> boja >> brend >> model;
            Avtomobil novAvtomobil(boja, brend, model);
            najdobarPlac.parkirajVozilo(novAvtomobil);
        }
        if(brVozila != 0)
            najdobarPlac.pecatiParkiraniVozila();

    }
}