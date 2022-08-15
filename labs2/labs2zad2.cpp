#include <iostream>
using namespace std;

class Krug{
    float radius;
    const float pi=3.14;
public:
    Krug(float radius=0){
        this->radius=radius;
    }

    void setRadius(float rad){
        this->radius=rad;
    }

    float plostina(){
        return radius*radius*pi;
    }

    float perimetar(){
        return 2*radius*pi;
    }

    bool ednakvi(){
        if(plostina()==perimetar()){
            return 1;
        } else return 0;
    }
};

int main() {
    float r;
    cin >> r;
    //instanciraj objekt od klasata Krug cij radius e vrednosta procitana od tastatura
    Krug k;
    k.setRadius(r);
    cout << k.perimetar() << endl;
    cout << k.plostina() << endl;
    cout << k.ednakvi() <<endl;
    //instanciraj objekt od klasata Krug cij radius ne e definiran
    return 0;
}