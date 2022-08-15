#include <iostream>
#include <string.h>
using namespace std;

class Potpisuvac{
    char ime[20];
    char prezime[20];
    char embg[14];

    void copy(const Potpisuvac &p){
        strcpy(this->ime,p.ime);
        strcpy(this->prezime,p.prezime);
        strcpy(this->embg,p.embg);
    }
public:
    Potpisuvac(char *ime="", char *prezime="", char *embg=""){
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        strcpy(this->embg,embg);
    }

    Potpisuvac(const Potpisuvac &p){
        copy(p);
    }

    char *getEmbg(){
        return embg;
    }
};

class Dogovor{
    int brDogovor;
    char kategorija[50];
    Potpisuvac potpisuvaci[3];
public:
    Dogovor(){}

    Dogovor(int brDogovor, char *kategorija, Potpisuvac *potpisuvaci){
        this->brDogovor=brDogovor;
        strcpy(this->kategorija,kategorija);
        for(int i=0;i<3;i++){
            this->potpisuvaci[i]=potpisuvaci[i];
        }
    }

    bool proverka(){
        bool flag=false;
        for(int i=0;i<brDogovor;i++){
            if(!strcmp(potpisuvaci[i].getEmbg(),potpisuvaci[i+1].getEmbg())){
                flag=true;
                return flag;
            }
        }
        return flag;
    }
};

int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin>>n;
    for(int i = 0; i < n; i++){
        cin>>embg>>ime>>prezime;
        Potpisuvac p1(ime, prezime, embg);
        cin>>embg>>ime>>prezime;
        Potpisuvac p2(ime, prezime, embg);
        cin>>embg>>ime>>prezime;
        Potpisuvac p3(ime, prezime, embg);
        cin>>broj>>kategorija;
        Potpisuvac p[3];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        Dogovor d(broj, kategorija, p);
        cout<<"Dogovor "<<broj<<":"<< endl;
        if(d.proverka() == true)
            cout<<"Postojat potpishuvaci so ist EMBG"<<endl;
        else
            cout<<"Ne postojat potpishuvaci so ist EMBG"<<endl;
    }
    return 0;
}