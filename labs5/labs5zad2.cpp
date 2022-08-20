#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

class ComplexNumber{
    double real;
    double imaginary;
public:
    ComplexNumber(double real=0.0, double imaginary=0.0){
        this->real=real;
        this->imaginary=imaginary;
    }

    ComplexNumber(const ComplexNumber &c){
        this->real=c.real;
        this->imaginary=c.imaginary;
    }

    ComplexNumber &operator=(const ComplexNumber &c){
        if(this!=&c){
            this->real=c.real;
            this->imaginary=c.imaginary;
        }
        return *this;
    }

    double module(){
        return sqrt(pow(real,2)+pow(imaginary,2));
    }

    friend ostream &operator<<(ostream &out, ComplexNumber &c){
        if(c.real==0){
            out<<c.imaginary<<"i"<<endl;
        } else if(c.imaginary==0){
            out<<c.real<<endl;
        } else out<<c.real<<"+"<<c.imaginary<<"i"<<endl;
        return out;
    }

    ComplexNumber operator+(ComplexNumber &c){
        ComplexNumber tmp(real+c.real, imaginary+c.imaginary);
        return tmp;
    }

    ComplexNumber operator-(ComplexNumber &c){
        ComplexNumber tmp(real-c.real, imaginary-c.imaginary);
        return tmp;
    }

    ComplexNumber operator*(ComplexNumber &c){
        ComplexNumber tmp(real*c.real, imaginary*c.imaginary);
        return tmp;
    }

    ComplexNumber operator/(ComplexNumber &c){
        ComplexNumber tmp(real/c.real, imaginary/c.imaginary);
        return tmp;
    }

    bool operator==(ComplexNumber &c){
        return ((real==c.real)&&(imaginary==c.imaginary));
    }

    bool operator>(ComplexNumber &c){
        if(real==c.real){
            return imaginary>c.imaginary;
        }
        return real>c.real;
    }

    bool operator<(ComplexNumber &c){
        if(real==c.real){
            return imaginary<c.imaginary;
        }
        return real<c.real;
    }
};

class Equation{
    ComplexNumber *numbers;
    char *aritmetiki;
    int brNum;

    void copy(const Equation &e){
        this->brNum=e.brNum;
        this->numbers=new ComplexNumber[e.brNum];
        for(int i=0;i<brNum;i++){
            this->numbers[i]=e.numbers[i];
        }
        strcpy(this->aritmetiki,e.aritmetiki);
    }
public:
    Equation(int brNum=0){
        this->brNum=brNum;
        numbers=NULL;
        aritmetiki=NULL;
    }

    Equation(const Equation &e){
        copy(e);
    }

    Equation &operator=(const Equation &e){
        if(this!=&e){
            delete [] numbers;
            delete [] aritmetiki;
            copy(e);
        }
        return *this;
    }

    ~Equation(){
        delete [] numbers;
        delete [] aritmetiki;
    }

    friend istream& operator>> (istream & in, Equation & e) {
        int i=0;
        double broevi[2];
        while(true) {
            in>>broevi[0]>>broevi[1];
            in>>e.aritmetiki[i];
            e.numbers[i]=ComplexNumber(broevi[0], broevi[1]);
            i++;
            if(e.aritmetiki[i] == '=') {
                break;
            }
        }
        e.brNum = i;
        return in;
    }

    ComplexNumber result(){
        ComplexNumber tmp=numbers[0];
        for(int i=0;i<brNum;i++){
            switch(aritmetiki[i]){
                case'*':
                    tmp=tmp*numbers[i+1];
                    break;
                case'/':
                    tmp=tmp/numbers[i+1];
                    break;
                case'+':
                    tmp=tmp+numbers[i+1];
                    break;
                case'-':
                    tmp=tmp-numbers[i+1];
                    break;
            }
        }
        return tmp;
    }

    double sumModules(){
        double vkModul=0.0;
        for(int i=0;i<brNum;i++){
            vkModul+=numbers[i].module();
        }
        return vkModul;
    }
};

int main() {
    int testCase;
    double real, imaginary;
    ComplexNumber first, second, result;

    cin >> testCase;

    if (testCase <= 8) {
        cin >> real;
        cin >> imaginary;
        first = ComplexNumber(real, imaginary);
        cin >> real;
        cin >> imaginary;
        second = ComplexNumber(real, imaginary);
    }

    if (testCase == 1) {
        cout << "===== OPERATOR + =====" << endl;
        result = first + second;
        cout << result;
    }
    else if (testCase == 2) {
        cout << "===== OPERATOR - =====" << endl;
        result = first - second;
        cout << result;
    }
    else if (testCase == 3) {
        cout << "===== OPERATOR * =====" << endl;
        result = first * second;
        cout << result;
    }
    else if (testCase == 4) {
        cout << "===== OPERATOR / =====" << endl;
        result = first / second;
        cout << result;
    }
    else if (testCase == 5) {
        cout << "===== OPERATOR == =====" << endl;
        cout << first;
        cout << second;
        if (first == second)
            cout << "EQUAL" << endl;
        else
            cout << "NOT EQUAL" << endl;
    }
    else if (testCase == 6) {
        cout << "===== OPERATOR > =====" << endl;
        cout << first;
        cout << second;
        if (first > second)
            cout << "FIRST GREATER THAN SECOND" << endl;
        else
            cout << "FIRST LESSER THAN SECOND" << endl;
    }
    else if (testCase == 7) {
        cout << "===== OPERATOR < =====" << endl;
        cout << first;
        cout << second;
        if (first < second)
            cout << "FIRST LESSER THAN SECOND" << endl;
        else
            cout << "FIRST GREATER THAN SECOND" << endl;
    }
    else if (testCase == 8) {
        cout << "===== MODULE =====" << endl;
        double module = first.module();
        cout << first;
        cout << "Module: " << module << endl;
        cout << second;
        module = second.module();
        cout << "Module: " << module << endl;
    }
    else if (testCase == 9) {
        cout << "===== OPERATOR >> & SUM OF MODULES =====" << endl;
        Equation equation;
        cin >> equation;
        cout << equation.sumModules();
    }
    else if (testCase == 10) {
        cout << "===== EQUATION RESULT =====" << endl;
        Equation equation;
        cin >> equation;
        result = equation.result();
        cout << result;
    }
    return 0;
}