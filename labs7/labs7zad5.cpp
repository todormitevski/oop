#include <iostream>
#include <string.h>
using namespace std;

class ZicanInstrument{
protected:
    char ime[20];
    int brZici;
    int osnovnaCena;
public:
    ZicanInstrument(char *ime="", int brZici=0, int osnovnaCena=0){
        strcpy(this->ime,ime);
        this->brZici=brZici;
        this->osnovnaCena=osnovnaCena;
    }

    virtual double cena()=0;

    int getBrZici(){
        return brZici;
    }

    bool operator==(ZicanInstrument &z){
        return getBrZici()==z.getBrZici();
    }
};

class Mandolina: public ZicanInstrument{
    char forma[20];
public:
    Mandolina(char *ime="", int brZici=0, int osnovnaCena=0, char *forma=""): ZicanInstrument(ime, brZici, osnovnaCena){
        strcpy(this->forma,forma);
    }

    double cena(){
        if(!strcmp(forma,"Neapolitan")){
            return osnovnaCena*1.15; //se zgolemuva za 15% ako e vo Neapolitan forma
        } else return osnovnaCena;
    }
};

class Violina: public ZicanInstrument{
    double golemina;
public:
    Violina(char *ime="", int brZici=0, int osnovnaCena=0, double golemina=0.0): ZicanInstrument(ime,brZici,osnovnaCena){
        this->golemina=golemina;
    }

    double cena(){
        if(golemina==0.25){
            return osnovnaCena*1.1;
        } else if(golemina==1){
            return osnovnaCena*1.2;
        } else return osnovnaCena;
    }
};

// bool operator==(ZicanInstrument &z, ZicanInstrument &z1){
//     return z.getBrZici()==z1.getBrZici();
// }

void pecatiInstrumenti(ZicanInstrument &zi, ZicanInstrument **instruments, int n){
    for(int i=0;i<n;i++){
        if(*instruments[i]==zi){
            cout<<instruments[i]->cena()<<endl;
        }
    }
}

int main() {
	char ime[20];
	int brojZici;
	float cena;
	char forma[20];
	cin >> ime >> brojZici >> cena >> forma;
	Mandolina m(ime, brojZici, cena, forma);
	int n;
	cin >> n;
	ZicanInstrument **zi = new ZicanInstrument*[2 * n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> brojZici >> cena >> forma;
		zi[i] = new Mandolina(ime, brojZici, cena, forma);
	}
	for(int i = 0; i < n; ++i) {
		float golemina;
		cin >> ime >> brojZici >> cena >> golemina;
		zi[n + i] = new Violina(ime, brojZici, cena, golemina);
	}
	pecatiInstrumenti(m, zi, 2 * n);
	for(int i = 0; i < 2 * n; ++i) {
		delete zi[i];
	}
	delete [] zi;
	return 0;
}