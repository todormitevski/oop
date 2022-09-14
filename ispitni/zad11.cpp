#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo{
    char imeDelo[50];
    int godina;
    char zemja[50];
public:
    Delo(char *imeDelo="", int godina=0, char *zemja=""){
        strcpy(this->imeDelo,imeDelo);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }

    int getGodina(){
        return godina;
    }

    char *getZemja(){
        return zemja;
    }

    char *getIme(){
        return imeDelo;
    }

    bool operator==(Delo &d){
        return !strcmp(imeDelo,d.imeDelo);
    }
};

class Pretstava{
protected:
    Delo delo;
    int brKarti;
    char dateOfAiring[15];
public:
    Pretstava(Delo delo=0, int brKarti=0, char *dateOfAiring=""){
        this->delo=delo;
        this->brKarti=brKarti;
        strcpy(this->dateOfAiring,dateOfAiring);
    }

    virtual int cena(){ //21vi vek od 2001 do 2100, bez 2000ta
        int m,n;
        //za m
        if(delo.getGodina()>1900 && delo.getGodina()<2101){ //20ti ili 21vi vek
            m=50;
        } else if(delo.getGodina()>1800 && delo.getGodina()<1901){ //19ti vek
            m=75;
        } else if(delo.getGodina()<=1800){ //<19ti vek
            m=100;
        }
        //za n
        if(!strcmp(delo.getZemja(),"Italija")){
            n=100;
        } else if(!strcmp(delo.getZemja(),"Rusija")){
            n=150;
        } else n=80;
        return m+n;
    }

    Delo getDelo(){
        return delo;
    }

    int getBrKarti(){
        return brKarti;
    }
};

class Opera: public Pretstava{
public:
    Opera(Delo delo=0, int brKarti=0, char *dateOfAiring=""): Pretstava(delo,brKarti,dateOfAiring){}
};

class Balet: public Pretstava{
    static int CENA_BALET;
public:
    Balet(Delo delo=0, int brKarti=0, char *dateOfAiring=""): Pretstava(delo,brKarti,dateOfAiring){}

    static void setCenaBalet(int newCena){
        CENA_BALET=newCena;
    }

    int cena(){
        return Pretstava::cena()+CENA_BALET;
    }
};
int Balet::CENA_BALET=150;

int prihod(Pretstava **pretstavi, int n){
    int vkPrihod=0;
    for(int i=0;i<n;i++){
        vkPrihod+=pretstavi[i]->cena()*pretstavi[i]->getBrKarti();
    }
    return vkPrihod;
}

int brojPretstaviNaDelo(Pretstava **pretstavi, int n, Delo &d){
    int br=0;
    for(int i=0;i<n;i++){
        if(!strcmp(pretstavi[i]->getDelo().getIme(),d.getIme())){
            br++;
        }
    }
    return br;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}