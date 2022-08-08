#include <cstring>
#include <iostream>
using namespace std;

class DebitAccount{
protected:
    char owner[50];
    char accountNumber[16];
    double balance;
public:
    DebitAccount(char *owner="No owner", char *accountNumber="111111111111111", double balance=1005.45){
        strcpy(this->owner,owner);
        strcpy(this->accountNumber,accountNumber);
        this->balance=balance;
    }

    DebitAccount(const DebitAccount &d){
        strcpy(this->owner,d.owner);
        strcpy(this->accountNumber,d.accountNumber);
        this->balance=d.balance;
    }

    void printReport(){
        cout<<"Owner: "<<owner<<endl;
        cout<<"Account number: "<<accountNumber<<endl;
        cout<<"Balance: "<<balance<<endl;
    }

    void deposit(double amount){
        balance+=amount;
    }

    void withdraw(double amount){
        if(amount<=balance){
            balance-=amount;
        } else{
            cout<<"You don't have sufficient funds. Withdrawing "<<balance<<endl;
            balance=0;
        }
    }
};

class CreditAccount: public DebitAccount{
    double limit;
    double interest=0.05;
    double debt;
public:
    CreditAccount(char *owner="No owner", char *accountNumber="111111111111111", double balance=1005.45, double limit=10000): DebitAccount(owner, accountNumber, balance){
        this->limit=limit;
    }

    CreditAccount(const DebitAccount &d, double limit=10000): DebitAccount(d){
        this->limit=limit;
        this->debt=0;
    }

    void printReport(){
        DebitAccount::printReport();
        cout<<"Debt: "<<debt<<endl;
        cout<<"Limit "<<limit<<endl;
    }

    void deposit(double amount){
        if(amount<=debt){
            debt-=amount;
        } else{
            balance+=(amount-debt);
            debt=0;
        }
    }

    void withdraw(double amount){
        if(balance>=amount){
            DebitAccount::withdraw(amount);
        } else{ //balance<amount (pr 1000, 2000)
            double diff=amount-balance;
            if((diff+debt)<limit){
                balance=0;
                debt+=(diff*(1+interest));
            } else{
                cout<<"You have exceeded your credit card limit!"<<endl;
            }
        }
    }
};

int main(){

    DebitAccount db("Todor");
    DebitAccount db1("Todor", "123451234512345");
    DebitAccount db2("Todor", "123451234512345", 1005.45);

//    db.printReport();
//    db1.printReport();
//    db2.printReport();
//
//    db2.withdraw(2000);

    CreditAccount ca(db2, 1000);
    db.printReport();

    ca.withdraw(900);
    ca.printReport();

    ca.withdraw(300);
    ca.printReport();

    ca.withdraw(300);
    ca.printReport();

    ca.withdraw(300);
    ca.printReport();

    ca.withdraw(300);
    ca.printReport();

    return 0;
}