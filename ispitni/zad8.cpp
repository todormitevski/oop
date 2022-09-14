#include <iostream>
#include <string.h>
using namespace std;

class Koncert{
private:
    char naziv[20];
    char lokacija[20];
    double cenaBilet;

    static double SEZONSKI_POPUST;
public:
    void copy(const Koncert &k){
        strcpy(this->naziv,k.naziv);
        strcpy(this->lokacija,k.lokacija);
        this->cenaBilet=k.cenaBilet;
    }

    Koncert(char *naziv="", char *lokacija="", double cenaBilet=0.0){
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet=cenaBilet;
    }

    static double getSezonskiPopust(){
        return SEZONSKI_POPUST;
    }

    static void setSezonskiPopust(double newPopust){
        SEZONSKI_POPUST=newPopust;
    }

    virtual double cena(){
        return cenaBilet*(1-SEZONSKI_POPUST);
    }

    char *getNaziv(){
        return naziv;
    }

    char *getLokacija(){
        return lokacija;
    }

    double getCenaBilet(){
        return cenaBilet;
    }
};
double Koncert::SEZONSKI_POPUST=0.2;

class ElektronskiKoncert: public Koncert{
    char *imeDj;
    double vremetraenje; //vo casovi
    bool DenIliNokj; //den==true, Nokj==false

    void copy(const ElektronskiKoncert &k){
        this->imeDj=new char[strlen(k.imeDj)+1]; //+1 se stava za dinamicka alokacija
        strcpy(this->imeDj,k.imeDj);
        this->vremetraenje=k.vremetraenje;
        this->DenIliNokj=k.DenIliNokj;
    }
public:
    ElektronskiKoncert(char *naziv="", char *lokacija="", double cenaBilet=0.0, char *imeDj="", double vremetraenje=0.0, bool DenIliNokj=true): Koncert(naziv,lokacija,cenaBilet){
        this->imeDj=new char[strlen(imeDj)+1]; //+1 se stava za dinamicka alokacija
        strcpy(this->imeDj,imeDj);
        this->vremetraenje=vremetraenje;
        this->DenIliNokj=DenIliNokj;
    }

    ElektronskiKoncert(const ElektronskiKoncert &k): Koncert(k){
        copy(k);
    }

    ElektronskiKoncert &operator=(const ElektronskiKoncert &k){
        if(this!=&k){
            delete [] imeDj;
            Koncert::copy(k);
            copy(k);
        }
        return *this;
    }

    ~ElektronskiKoncert(){
        delete [] imeDj;
    }

    double cena(){
        double newCena=Koncert::cena();
        if(vremetraenje>7){
            newCena+=360;
        } else if(vremetraenje>5){
            newCena+=150;
        }
        if(DenIliNokj==true){
            newCena-=50;
        } else newCena+=100;
        return newCena;
    }
};

void najskapKoncert(Koncert ** koncerti, int n){
    double max=0.0;
    int maxIndex=0, brElek=0;
    for(int i=0;i<n;i++){
        if(koncerti[i]->cena()>max){
            max=koncerti[i]->cena();
            maxIndex=i;
        }
        if(dynamic_cast<ElektronskiKoncert *>(koncerti[i])){
            brElek++;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[maxIndex]->getNaziv()<<" "<<koncerti[maxIndex]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<brElek<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    for(int i=0;i<n;i++){
        if(elektronski==true){
            if(dynamic_cast<ElektronskiKoncert *>(koncerti[i])){
                if(!strcmp(koncerti[i]->getNaziv(),naziv)){
                    cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                    return true;
                }
            }
        } else{
            if(!strcmp(koncerti[i]->getNaziv(),naziv)){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
        }
    }
    return false;
}

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
