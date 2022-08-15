#include <iostream>
using namespace std;

class Agol{
    int stepeni;
    int minuti;
    int sekundi;
public:
    Agol(int stepeni=0, int minuti=0, int sekundi=0){
        this->stepeni,stepeni;
        this->minuti,minuti;
        this->sekundi,sekundi;
    }

    void set_stepeni(int step){
        this->stepeni=step;
    }

    void set_minuti(int min){
        this->minuti=min;
    }

    void set_sekundi(int sek){
        this->sekundi=sek;
    }

    int getSekundi(){
        return sekundi;
    }

    int to_sekundi(){
        int newMinutes=0;
        int newSekundi=0;
        newMinutes=stepeni*60+minuti;
        newSekundi=newMinutes*60+sekundi;
        return newSekundi;
    }
};

int proveri(int stepeni, int minuti, int sekundi){
    if(stepeni>180||stepeni<0){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    if(stepeni==180&&(sekundi>0||minuti>0)){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    if(minuti>60||minuti<0){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    if(sekundi>60||sekundi<0){
        cout<<"Nevalidni vrednosti za agol";
        return 0;
    }
    return 1;
}

bool changeOfSeconds(Agol a, int sec){
    return a.getSekundi()!=sec;
}

int main() {

    //da se instancira objekt od klasata Agol
    Agol a1;
    int deg, min, sec;
    cin >> deg >> min >> sec;

    if (proveri(deg, min, sec)) {

        a1.set_stepeni(deg);
        a1.set_minuti(min);
        a1.set_sekundi(sec);
        cout << a1.to_sekundi();
        if (changeOfSeconds(a1,sec))
            cout << "Ne smeete da gi menuvate sekundite vo ramkite na klasata!" << endl;

    }

    return 0;
}