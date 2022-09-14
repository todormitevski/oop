#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class FudbalskaEkipa{
protected:
    char imeTrener[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *imeTrener="", int *golovi=0){
        strcpy(this->imeTrener,imeTrener);
        for(int i=0;i<10;i++){
            this->golovi[i]=golovi[i];
        }
    }

    virtual int uspeh()=0;

    bool operator>(FudbalskaEkipa &f){
        return uspeh()>f.uspeh();
    }

    char *getImeTrener(){
        return imeTrener;
    }

    FudbalskaEkipa &operator+=(int newGol){
        for(int i=0;i<10;i++){
            golovi[i]=golovi[i+1];
        }
        golovi[9]=newGol;
        return *this;
    }
};

class Klub: public FudbalskaEkipa{
    char imeKlub[100];
    int tituli;
public:
    Klub(char *imeTrener="", int *golovi=0, char *imeKlub="", int tituli=0): FudbalskaEkipa(imeTrener,golovi){
        strcpy(this->imeKlub,imeKlub);
        this->tituli=tituli;
    }

    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++){
            sum+=golovi[i];
        }
        return sum*3+tituli*1000;
    }

    char *getImeKlub(){
        return imeKlub;
    }
};

class Reprezentacija: public FudbalskaEkipa{
    char imeDrzava[100];
    int brNastapi;
public:
    Reprezentacija(char *imeTrener="", int *golovi=0, char *imeDrzava="", int brNastapi=0): FudbalskaEkipa(imeTrener,golovi){
        strcpy(this->imeDrzava,imeDrzava);
        this->brNastapi=brNastapi;
    }

    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++){
            sum+=golovi[i];
        }
        return sum*3+brNastapi*50;
    }

    char *getImeDrzava(){
        return imeDrzava;
    }
};

ostream &operator<<(ostream &out, FudbalskaEkipa &f){
    if(dynamic_cast<Klub *>(&f)){
        out<<dynamic_cast<Klub *>(&f)->getImeKlub()<<endl;
    } else if(dynamic_cast<Reprezentacija *>(&f)){
        out<<dynamic_cast<Reprezentacija *>(&f)->getImeDrzava()<<endl;
    }
    out<<f.getImeTrener()<<endl;
    out<<f.uspeh()<<endl;
    return out;
}

void najdobarTrener(FudbalskaEkipa **ekipi, int n){
    int best=0, bestIndex=0;
    for(int i=0;i<n;i++){
        if(ekipi[i]->uspeh()>best){
            best=ekipi[i]->uspeh();
            bestIndex=i;
        }
    }
    cout<<*ekipi[bestIndex]<<endl;
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}