#include <iostream>
using namespace std;

/*
class Broj{
    int x;
public:
    Broj(int xx=1){
        x=xx; cout<<x;
    }

    Broj(const Broj &b){
        cout<<b.x;
    }
};

int main(){

    Broj br1;
    Broj br2(br1);
    br1=br2;

    return 0;
}
*/

/*
int main(){

    const int a=3;
    const int *b=&a;
    int c=4;

    //b++; no error
    //c=*b; no error
    //*b=c; read-only variable is not assignable
    //b=100; Incompatible integer to pointer conversion assigning to 'const int *' from 'int'

    return 0;
}
*/

/*
void f(int x){
    cout<<"x"; return;
}

int f(int x){
    return x/2;
}

int main(){

    int x=5;
    f(x);
    return 0;
}
*/

//class OOPTest{
//    int a;
//    static int x;
//public:
//    OOPTest(int a){this->a=a;}
//
//    static void print(int x){
//        cout<<"A: "<<a<<" X: "<<x; Invalid use of member 'a' in static member function (nema pristap)
//    }
//
//    //static void print(){cout<<"X: "<<x;} //tocno, do x ima pristap oti i x e static
//    //static void print(){cout<<"A: "<<a<<" X: "<<OOPTest::x;} //nema pristap do a
//    //static void print(){cout<<"A: "<<a;} //nema pristap do a
//};


//class A{
//    int a;
//public:
//    int b;
//};
//
//class B: A{ //ako imase tuka : public A, ke imase pristap do b
//public:
//    int c;
//};
//
//int main(){
//
//    B obj;
//    cout<<obj.b; //'b' is a private member of 'A' (nema pristap do b)
//    cout<<obj.c;
//
//    return 0;
//}

//class A{
//public:
//    void pecati(){
//        cout<<'K';
//    }
//};
//
//class B: public A{
//public:
//    void pecati(){
//        cout<<'N';
//    }
//};
//
//int main(){
//
//    A a;
//    A *ab;
//    B b;
//    ab=&b;
//
//    a.pecati(); //dava K
//    ab->pecati(); //dava K
//    b.pecati(); //dava N
//
//    return 0;
//}