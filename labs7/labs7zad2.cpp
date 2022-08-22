#include <iostream>
#include <string.h>
using namespace std;

class Number{ //apstraktna klasa samo so cisto virtuelnite funkcii
public:
    virtual double doubleValue()=0;
    virtual int intValue()=0;
    virtual void print()=0;
};

class Integer: public Number{
    int integer;
public:
    Integer(int integer=0){
        this->integer=integer;
    }

    double doubleValue(){
        return integer;
    }
    int intValue(){
        return integer;
    }
    void print(){
        cout<<"Integer: "<<integer<<endl;
    }
};

class Double: public Number{
    double dabl;
public:
    Double(double dabl=0.0){
        this->dabl=dabl;
    }

    double doubleValue(){
        return dabl;
    }
    int intValue(){
        return dabl;
    }
    void print(){
        cout<<"Double: "<<dabl<<endl;
    }
};

bool operator==(Number &n, Number &n1){
    return n.doubleValue()==n.doubleValue();
}

class Numbers{
    Number **numbers;
    int brNumbers;
public:
    Numbers(){
        this->brNumbers=0;
        this->numbers=new Number *[brNumbers];
    }

    Numbers &operator+=(Number *n){
        Number **tmp=new Number *[brNumbers+1];
        for(int i=0;i<brNumbers;i++){
            if(numbers[i]->doubleValue()==n->doubleValue()){
                return *this;
            } else tmp[i]=numbers[i];
        }
        tmp[brNumbers++]=n;
        delete [] numbers;
        numbers=tmp;
        return *this;
    }

    void statistics(){


        double suma=0.0;
        int brInt=0, brDouble=0;
        int sumInt=0;
        double sumDouble=0;
        for(int i=0;i<brNumbers;i++){
            suma+=numbers[i]->doubleValue();
            if(dynamic_cast<Integer *>(numbers[i])){
                brInt++;
                sumInt+=numbers[i]->intValue();
            } else{
                brDouble++;
                sumDouble+=numbers[i]->doubleValue();
            }
        }

        cout<<"Count of numbers: "<<brNumbers<<endl;
        cout<<"Sum of all numbers: "<<suma<<endl;
        cout<<"Count of integer numbers: "<<brInt<<endl;
        cout<<"Sum of integer numbers: "<<sumInt<<endl;
        cout<<"Count of double numbers: "<<brDouble<<endl;
        cout<<"Sum of double numbers: "<<sumDouble<<endl;
    }

    void integersLessThan (Integer n){
        int flag=0;
        for(int i=0;i<brNumbers;i++){
            if(dynamic_cast<Integer *>(numbers[i])){
                if(numbers[i]->intValue()<n.intValue()){
                    numbers[i]->print();
                    flag=1;
                }
            }
        }
        if(flag==0){
            cout<<"None"<<endl;
        }
    }

    void doublesBiggerThan (Double n){
        int flag=0;
        for(int i=0;i<brNumbers;i++){
            if(dynamic_cast<Double *>(numbers[i])){
                if(numbers[i]->doubleValue()>n.doubleValue()){
                    numbers[i]->print();
                    flag=1;
                }
            }
        }
        if(flag==0){
            cout<<"None"<<endl;
        }
    }
};

int main() {

    int n;
    cin>>n;
    Numbers numbers;
    for (int i=0;i<n;i++){
        int type;
        double number;
        cin>>type>>number;
        if (type==0){//Integer object
            Integer * integer = new Integer((int) number);
            numbers+=integer;
        }
        else {
            Double * doublee = new Double(number);
            numbers+=doublee;
        }
    }

    int lessThan;
    double biggerThan;

    cin>>lessThan;
    cin>>biggerThan;

    cout<<"STATISTICS FOR THE NUMBERS\n";
    numbers.statistics();
    cout<<"INTEGER NUMBERS LESS THAN "<<lessThan<<endl;
    numbers.integersLessThan(Integer(lessThan));
    cout<<"DOUBLE NUMBERS BIGGER THAN "<<biggerThan<<endl;
    numbers.doublesBiggerThan(Double(biggerThan));

    return 0;
}