#include <iostream>
#include <string.h>
using namespace std;

class PlDrustvo{
    char *ime;
    int brTuri;
    int brClenovi;

    void copy(const PlDrustvo &p){
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->brTuri=p.brTuri;
        this->brClenovi=p.brClenovi;
    }
public:
    PlDrustvo(char *ime="", int brTuri=0, int brClenovi=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->brTuri=brTuri;
        this->brClenovi=brClenovi;
    }

    PlDrustvo(const PlDrustvo &p){
        copy(p);
    }

    PlDrustvo &operator=(const PlDrustvo &p){
        if(this!=&p){
            delete [] ime;
            copy(p);
        }
        return *this;
    }

    ~PlDrustvo(){
        delete [] ime;
    }

    PlDrustvo operator+(PlDrustvo &d){
        PlDrustvo tmp;
        if(brClenovi>d.brClenovi){
            tmp=PlDrustvo(ime,brTuri,brClenovi+d.brClenovi);
        } else tmp=PlDrustvo(d.ime,d.brTuri,brClenovi+d.brClenovi);
        return tmp;
    }

    bool operator<(PlDrustvo &d){
        return brClenovi<d.brClenovi;
    }

    bool operator>(PlDrustvo &d){
        return brClenovi>d.brClenovi;
    }

    friend ostream &operator<<(ostream &out, PlDrustvo &d){
        return out<<"Ime: "<<d.ime<<" Turi: "<<d.brTuri<<" Clenovi: "<<d.brClenovi<<endl;
    }

    int getBrClenovi(){
        return brClenovi;
    }
};

void najmnoguClenovi(PlDrustvo *drustva, int brDrustva){
    int max=0;
    int maxIndex=0;
    for(int i=0;i<brDrustva;i++){
        if(drustva[i].getBrClenovi()>max){
            max=drustva[i].getBrClenovi();
            maxIndex=i;
        }
    }
    cout<<"Najmnogu clenovi ima planinarskoto drustvo: "<<drustva[maxIndex];
}

int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
    {
        char ime[100];
        int brTuri;
        int brClenovi;
        cin>>ime;
        cin>>brTuri;
        cin>>brClenovi;
        PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

    }

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}