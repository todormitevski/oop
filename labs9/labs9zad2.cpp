#include <iostream>
using namespace std;

//exceptions
class ArithmeticException{
public:
    void message(){
        cout<<"Division by zero is not allowed"<<endl;
    }
};

class NumbersNotDivisibleException{
    int delitel;
public:
    NumbersNotDivisibleException(int delitel){
        this->delitel=delitel;
    }

    void message(){
        cout<<"Division by "<<delitel<<" is not supported"<<endl;
    }
};

class ArrayFullException{
public:
    void message(){
        cout<<"The array is full. Increase the capacity"<<endl;
    }
};

class IndexOutOfBoundsException{
    int index;
public:
    IndexOutOfBoundsException(int index){
        this->index=index;
    }

    void message(){
        cout<<"Index "<<index<<" is out of bounds"<<endl;
    }
};

class NumberIsNotPositiveException{
    int broj;
public:
    NumberIsNotPositiveException(int broj){
        this->broj=broj;
    }

    void message(){
        cout<<"Number "<<broj<<" is not positive integer"<<endl;
    }
};


class PositiveIntegers{
    int *integers;
    int brIntegers;
    int capacity;

    void copy(const PositiveIntegers &p){
        this->capacity=p.capacity;
        this->brIntegers=p.brIntegers;
        this->integers=new int[p.brIntegers];
        for(int i=0;i<p.brIntegers;i++){
            this->integers[i]=p.integers[i];
        }
    }
public:
    PositiveIntegers(int capacity=0){
        this->capacity=capacity;
        brIntegers=0;
        integers=new int[0];
    }

    PositiveIntegers(const PositiveIntegers &p){
        copy(p);
    }

    PositiveIntegers &operator=(const PositiveIntegers &p){
        if(this!=&p){
            delete [] integers;
            copy(p);
        }
        return *this;
    }

    ~PositiveIntegers(){
        delete [] integers;
    }

    void increaseCapacity(int c){
        int *tmp=new int[brIntegers+c];
        for(int i=0;i<brIntegers;i++){
            tmp[i]=integers[i];
        }
        delete [] integers;
        integers=tmp;
        capacity+=c;
    }

    PositiveIntegers &operator+=(int number){
        if(brIntegers==capacity){
            throw ArrayFullException();
        }
        if(number<=0){
            throw NumberIsNotPositiveException(number);
        }

        integers[brIntegers++]=number;
        return *this;
    }

    PositiveIntegers operator*(int number){
        PositiveIntegers nov(*this);
        for(int i=0;i<nov.brIntegers;i++){
            nov.integers[i]*=number;
        }
        return nov;
    }

    PositiveIntegers operator/(int number){
        if(number==0){
            throw ArithmeticException();
        }
        for(int i=0;i<brIntegers;i++){
            if(integers[i]%number!=0){
                throw NumbersNotDivisibleException(number);
            }
        }

        PositiveIntegers nov(*this);
        for(int i=0;i<nov.brIntegers;i++){
            nov.integers[i]/=number;
        }
        return nov;
    }

    int &operator[](int index){
        if(index<0 || index>brIntegers){
            throw IndexOutOfBoundsException(index);
        }
        return integers[index];
    }

    void print(){
        cout<<"Size: "<<brIntegers<<" Capacity: "<<capacity<<" Numbers:";
        for(int i=0;i<brIntegers;i++){
            cout<<" "<<integers[i];
        }
        cout<<"\n";
    }
};

int main() {

    int n, capacity;
    cin >> n >> capacity;
    PositiveIntegers pi(capacity);
    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        try{
            pi += number;
        }
        catch(ArrayFullException &e){
            e.message();
        }
        catch(NumberIsNotPositiveException &e){
            e.message();
        }
    }
    cout << "===FIRST ATTEMPT TO ADD NUMBERS===" << endl;
    pi.print();
    int incCapacity;
    cin >> incCapacity;
    pi.increaseCapacity(incCapacity);
    cout << "===INCREASING CAPACITY===" << endl;
    pi.print();

    int n1;
    cin >> n1;
    for (int i = 0; i < n1; i++) {
        int number;
        cin >> number;
        try{
            pi += number;
        }
        catch(ArrayFullException &e){
            e.message();
        }
        catch(NumberIsNotPositiveException &e){
            e.message();
        }
    }
    cout << "===SECOND ATTEMPT TO ADD NUMBERS===" << endl;

    pi.print();
    PositiveIntegers pi1;

    cout << "===TESTING DIVISION===" << endl;

    try {
        pi1 = pi / 0;
        pi1.print();
    }
    catch (ArithmeticException &e) {
        e.message();
    }
    catch (NumbersNotDivisibleException &e){
        e.message();
    }

    try {
        pi1 = pi / 1;
        pi1.print();
    }
    catch (ArithmeticException &e) {
        e.message();
    }
    catch (NumbersNotDivisibleException &e){
        e.message();
    }

    try{
        pi1 = pi / 2;
        pi1.print();
    }
    catch(ArithmeticException &e){
        e.message();
    }
    catch (NumbersNotDivisibleException &e){
        e.message();
    }

    cout<<"===TESTING MULTIPLICATION==="<<endl;
    pi1 = pi*3;
    pi1.print();


    cout<<"===TESTING [] ==="<<endl;

    try{
        cout<<"PositiveIntegers[-1] = "<<pi[-1]<<endl;
    }
    catch(IndexOutOfBoundsException &e){
        e.message();
    }

    try{
        cout<<"PositiveIntegers[2] = "<<pi[2]<<endl;
    }
    catch(IndexOutOfBoundsException &e){
        e.message();
    }

    try{
        cout<<"PositiveIntegers[3] = "<<pi[3]<<endl;
    }
    catch(IndexOutOfBoundsException &e){
        e.message();
    }

    try{
        cout<<"PositiveIntegers[12] = "<<pi[12]<<endl;
    }
    catch(IndexOutOfBoundsException &e){
        e.message();
    }

    return 0;
}