#include<iostream>
#include<string.h>
using namespace std;

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;

    static int PISMENA_OCENKA;

    void copy(const StudentKurs &s){ //za vo dr klasa
        strcpy(this->ime,s.ime);
        this->ocenka=s.ocenka;
        this->daliUsno=s.daliUsno;
    }
public:
    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }

    ~StudentKurs(){}
    //дополни ја класата
    static void setMAX(int newOcenka){
        PISMENA_OCENKA=newOcenka;
    }

    virtual int getOcenka(){
        return ocenka;
    }

    bool getDaliUsno(){
        return daliUsno;
    }
};
int StudentKurs::PISMENA_OCENKA=10;

//вметни го кодот за StudentKursUsno
class StudentKursUsno: public StudentKurs{
    char *opisnaOcenka;
    int brOcenki;
public:
    StudentKursUsno(char* ime="",int finalenIspit=0, char *opisnaOcenka="", int brOcenki=0): StudentKurs(ime,ocenka){
        this->opisnaOcenka=new char[strlen(opisnaOcenka)];
        strcpy(this->opisnaOcenka,opisnaOcenka);
        this->brOcenki=brOcenki;
    }

    StudentKursUsno(const StudentKursUsno &s): StudentKurs(s){
        this->opisnaOcenka=new char[strlen(s.opisnaOcenka)];
        strcpy(this->opisnaOcenka,s.opisnaOcenka);
        this->brOcenki=s.brOcenki;
    }

    StudentKursUsno &operator=(const StudentKursUsno &s){
        if(this!=&s){
            delete [] opisnaOcenka;
            StudentKurs::copy(s);
            this->opisnaOcenka=new char[strlen(s.opisnaOcenka)];
            strcpy(this->opisnaOcenka,s.opisnaOcenka);
            this->brOcenki=s.brOcenki;
        }
        return *this;
    }

    ~StudentKursUsno(){
        delete [] opisnaOcenka;
    }

    int getOcenka(){
        if(!strcmp(opisnaOcenka,"odlicen")){
            return StudentKurs::getOcenka()+2;
        } else if(!strcmp(opisnaOcenka,"dobro")){
            return StudentKurs::getOcenka()+1;
        } else if(!strcmp(opisnaOcenka,"losho")){
            return StudentKurs::getOcenka()-1;
        } else return StudentKurs::getOcenka();
    }

    friend ostream &operator<<(ostream &out, StudentKursUsno &s){
        return out<<s.ime<<" --- "<<s.getOcenka()<<endl;
    }

    StudentKursUsno &operator+=(StudentKurs &s){
        StudentKurs *tmp=new StudentKurs[brOcenki+1];
    }
};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }

    //дополни ја класата
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        programiranje.postaviOpisnaOcenka(ime,opisna);
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
