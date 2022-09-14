#include <iostream>
//#include <string.h>
using namespace std;


//OPERATOR[]
//Kurs operator[](int i){
//    if (i<brojKursevi&&i>=0)
//        return kursevi[i];
//    else return Kurs();
//}

//OPERATOR>> so get() i getline()
//friend istream &operator>>(istream &in, Game &g){
//    in.get();
//    in.getline(g.ime,100);
//    in>>g.cena>>g.onSale;
//    return in;
//}

//OPERATOR-= (remove)
//void izbrishi(const OperativenSistem &os) {
//    OperativenSistem * tmp = new OperativenSistem[brSistemi];
//    int brojac = 0;
//    for(int i = 0 ; i < brSistemi ; i++) {
//        if(!sistemi[i].ednakviSe(os)) {
//            tmp[brojac++] = sistemi[i];
//        }
//    }
//    brSistemi = brojac;
//    delete [] sistemi;
//    sistemi = tmp;
//}

//GLOBAL OPERATOR<<
//ostream &operator<<(ostream &out, FudbalskaEkipa &f){
//    if(dynamic_cast<Klub *>(&f)){
//        out<<dynamic_cast<Klub *>(&f)->getImeKlub()<<endl;
//    } else if(dynamic_cast<Reprezentacija *>(&f)){
//        out<<dynamic_cast<Reprezentacija *>(&f)->getImeDrzava()<<endl;
//    }
//    out<<f.getImeTrener()<<endl;
//    out<<f.uspeh()<<endl;
//    return out;
//}


class Example{
    int leftNum;
    int rightNum;
public:
    Example(int leftNum=0, int rightNum=0){
        this->leftNum=leftNum;
        this->rightNum=rightNum;
    }

    //operator+
    Example operator+(Example e){
        Example temp;
        temp.leftNum=leftNum+e.leftNum;
        temp.rightNum=rightNum+e.rightNum;
        return temp;
    }

    //operator-
    Example operator-(Example e){
        Example temp;
        temp.leftNum=leftNum-e.leftNum;
        temp.rightNum=rightNum-e.rightNum;
        return temp;
    }

    //operator++ prefix
    void operator++(){
        leftNum+=1;
    }

    //operator-- prefix
    void operator--(){
        leftNum-=1;
    }

    //operator++ postfix
    Example operator++(int){
        Example temp(*this);
        leftNum+=1;
        return temp;
    }

    //operator-- postfix
    Example operator--(int){
        Example temp(*this);
        leftNum-=1;
        return temp;
    }

    void print(){
        cout<<leftNum<<" "<<rightNum<<endl;
    }

    void getLeftNum(){
        cout<<"Your num: "<<leftNum<<endl;
    }
};

class ExampleBracketsOp{
    int elems[3];
public:
    ExampleBracketsOp(int elem1, int elem2, int elem3){
        elems[0]=elem1;
        elems[1]=elem2;
        elems[2]=elem3;
    }

    //operator[]
    int operator[](int index){
        return elems[index];
    }
};

int main(){

    //op+
//    Example ex1(10,20), ex2(30,40);
//    Example ex3=ex1+ex2;
//    ex3.print();

    //op-
//    Example ex1(50,50), ex2(30,40);
//    Example ex3=ex1-ex2;
//    ex3.print();

    //op++ & -- prefixes
//    Example ex1(70);
//
//    ex1.getLeftNum();
//    ++ex1;
//    ex1.getLeftNum();
//    --ex1;
//    ex1.getLeftNum();

    //op++ & -- postfixes
//    Example ex1(69);
//
//    ex1.getLeftNum();
//    (ex1++).getLeftNum(); //ne se zgolemuva odma
//    ex1.getLeftNum(); //tuka e zgolemeno (postfix)

    //operator[]
    ExampleBracketsOp ex1(20,30,40);
    cout<<ex1[0]<<" "<<ex1[1]<<" "<<ex1[2]<<endl;

    return 0;
}




