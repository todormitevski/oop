#include <iostream>
using namespace std;

class Kvadrat{
protected:
    double strana;
public:
    Kvadrat(double strana=0.0){
        this->strana=strana;
    }

    Kvadrat(const Kvadrat &k){
        this->strana=k.strana;
    }

    double perimetar(){
        return 4*strana;
    }

    double plostina(){
        return strana*strana;
    }

    void pecati(){
        cout<<"Kvadrat so dolzina a="<<strana<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
    }
};

class Pravoagolnik: public Kvadrat{
    double x;
    double y;
public:
    Pravoagolnik(){
        this->x=x;
        this->y=y;
    }

    Pravoagolnik (const Kvadrat &k, double x, double y): Kvadrat(k){
        this->x=x;
        this->y=y;
    }

    Pravoagolnik(const Pravoagolnik &k){
        this->x=k.x;
        this->y=k.y;
    }

    double perimetar(){
        if(x==y){
            Kvadrat::perimetar();
        } else return 2*(x+strana)+2*(y+strana);
    }

    double plostina(){
        if(x==y){
            Kvadrat::plostina();
        } else return (x+strana)*(y+strana);
    }

    void pecati(){
        if(x+strana==y+strana){
            strana+=x;
            return Kvadrat::pecati();
        } else{
            cout<<"Pravoagolnik so strani: "<<x+strana<<" i "<<y+strana<<" ima plostina P="<<plostina()<<" i perimetar L="<<perimetar()<<endl;
        }
    }
};

int main() {
    int n;
    double a,x,y;
    Kvadrat * kvadrati;
    Pravoagolnik * pravoagolnici;

    cin>>n;

    kvadrati = new Kvadrat [n];
    pravoagolnici = new Pravoagolnik [n];

    for (int i=0;i<n;i++){
        cin>>a;

        kvadrati[i] = Kvadrat(a);
    }

    for (int i=0;i<n;i++){
        cin>>x>>y;

        pravoagolnici[i]=Pravoagolnik(kvadrati[i],x,y);
    }

    int testCase;
    cin>>testCase;

    if (testCase==1){
        cout<<"===Testiranje na klasata Kvadrat==="<<endl;
        for (int i=0;i<n;i++)
            kvadrati[i].pecati();
    }
    else {
        cout<<"===Testiranje na klasata Pravoagolnik==="<<endl;
        for (int i=0;i<n;i++)
            pravoagolnici[i].pecati();
    }
}