#include <iostream>
#include <string.h>
#define MAX 100
using namespace std;

class UserExistsException{
public:
    void message(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

enum typeC{
    standard,
    loyal,
    vip
};

class Customer{
    char ime[50];
    char email[50];
    typeC tip;
    int brKupeniProizvodi;

    static int OSNOVEN_POPUST;
    const static int DOPOLNITELEN_POPUST;
public:
    Customer(const char *ime="", const char *email="", typeC tip=(typeC)0, int brKupeniProizvodi=0){
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->tip=tip;
        this->brKupeniProizvodi=brKupeniProizvodi;
    }

    void setDiscount1(int discount){
        OSNOVEN_POPUST=discount;
    }

    friend ostream &operator<<(ostream &out, Customer &c){
        out<<c.ime<<endl<<c.email<<endl<<c.brKupeniProizvodi<<endl;
        if(c.tip==0){
            out<<"standard 0"<<endl;
        } else if(c.tip==1){
            out<<"loyal "<<c.OSNOVEN_POPUST<<endl;
        } else if(c.tip==2) out<<"vip "<<c.OSNOVEN_POPUST + c.DOPOLNITELEN_POPUST<<endl;
        return out;
    }

    char *getEmail(){
        return email;
    }

    typeC getTip(){
        return tip;
    }

    void setType(typeC newType){
        tip=newType;
    }

    int getBrKupeniProizvodi(){
        return brKupeniProizvodi;
    }
};
int Customer::OSNOVEN_POPUST=10;
const int Customer::DOPOLNITELEN_POPUST=20;

class FINKI_bookstore{
    Customer *kupuvaci;
    int brKupuvaci;
public:
    FINKI_bookstore(Customer *kupuvaci=0, int brKupuvaci=0){
        this->brKupuvaci=brKupuvaci;
        this->kupuvaci=new Customer[brKupuvaci];
    }

    FINKI_bookstore &operator+=(Customer &c){
        for(int i=0;i<brKupuvaci;i++){
            if(!strcmp(kupuvaci[i].getEmail(),c.getEmail())){
                throw UserExistsException();
            }
        }
        Customer *tmp=new Customer[brKupuvaci+1];
        for(int i=0;i<brKupuvaci;i++){
            tmp[i]=kupuvaci[i];
        }
        tmp[brKupuvaci++]=c;
        delete [] kupuvaci;
        kupuvaci=tmp;
        return *this;
    }

    void setCustomers(Customer *customers, int n){
        brKupuvaci=n;
        delete [] kupuvaci;
        kupuvaci=new Customer[brKupuvaci];
        for(int i=0;i<n;i++){
            kupuvaci[i]=customers[i];
        }
    }

    void update(){
        for(int i=0;i<brKupuvaci;i++){
            if(kupuvaci[i].getTip()==0 && kupuvaci[i].getBrKupeniProizvodi()>5){
                kupuvaci[i].setType(loyal);
            } else if(kupuvaci[i].getTip()==1 && kupuvaci[i].getBrKupeniProizvodi()>10){
                kupuvaci[i].setType(vip);
            }
        }
    }

    friend ostream &operator<<(ostream &out, FINKI_bookstore &f){
        for(int i=0;i<f.brKupuvaci;i++){
            out<<f.kupuvaci[i];
        }
        return out;
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        try{
            Customer c(name, email, (typeC) tC, numProducts);
            fc+=c;
        }
        catch(UserExistsException &e){
            e.message();
        }
        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}