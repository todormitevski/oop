#include <iostream>
using namespace std;

class Matrica{
    float elementi[10][10];
    int brRed;
    int brKolona;
public:
    Matrica(int brRed=0, int brKolona=0){
        this->brRed=brRed;
        this->brKolona=brKolona;
    }

    Matrica operator+(float broj){
        Matrica tmp; //tmp matrica kade sto posle presmetkata se smestuva vrednosta koja ja pecatis
        tmp.brRed=brRed;
        tmp.brKolona=brKolona;
        for(int i=0;i<brRed;i++){
            for(int j=0;j<brKolona;i++){
                tmp.elementi[i][j]+=elementi[i][j]+broj;
            }
        }
        return tmp;
    }

    Matrica operator-(const Matrica &m){
        Matrica tmp;
        tmp.brRed=brRed;
        tmp.brKolona=brKolona;
        for(int i=0;i<brRed;i++){
            for(int j=0;j<brKolona;j++){
                tmp.elementi[i][j]+=elementi[i][j]-m.elementi[i][j];
            }
        }
        return tmp;
    }

    Matrica operator*(const Matrica &m){
        Matrica tmp;
        tmp.brRed=brRed;
        tmp.brKolona=brKolona;
        for(int i=0;i<brRed;i++){
            for(int j=0;j<brKolona;j++){
                for(int k=0;j<brKolona;k++){
                    tmp.elementi[i][j]+=elementi[i][k]*m.elementi[k][j];
                }
            }
        }
        return tmp;
    }

    friend istream &operator>>(istream &in, Matrica &m){
        in>>m.brRed;
        in>>m.brKolona;
        for(int i=0;i<m.brRed;i++){
            for(int j=0;j<m.brKolona;j++){
                in>>m.elementi[i][j];
            }
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, Matrica &m){
        for(int i=0;i<m.brRed;i++){
            for(int j=0;j<m.brKolona;j++){
                out<<m.elementi[i][j];
            }
            out<<endl;
        }
        return out;
    }
};

int main()
{
    Matrica A,B,C;
    cin>>A>>B>>C;
    Matrica D=B*C;
    Matrica R=A-D+2;
    cout<<R;
}