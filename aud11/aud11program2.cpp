#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

class Card{
protected:
    char id[16];
    double balance;
    double limit;
public:
    Card(char *id="111111111111111", double limit=1000, double balance=0){
        strcpy(this->id,id);
        this->limit=limit;
        this->balance=balance;
    }

    virtual void deposit(double amount){
        this->balance+=amount;
    }

    virtual bool withdraw(double amount){
        if(balance+limit>=amount){ //limit=future's market
            balance-=amount;
            return true;
        } else{
            return false;
        }
    }

    virtual void print(){
        cout<<"Card: "<<id<<" Balance: "<<balance<<" Limit: "<<limit<<endl;
    }
};

class MasterCard: public Card{
private:
    const static float DISCOUNT_BASIC;
    static float DISCOUNT_PREMIUM;
public:
    MasterCard(char *id="111111111111111", double limit=1000, double balance=0): Card(id,limit,balance){

    }

    static void setDiscountPremium(float newDiscountPremium){
        DISCOUNT_PREMIUM=newDiscountPremium;
    }

    bool withdraw(double amount){
        if(limit>=6000){
            amount*=(1-DISCOUNT_PREMIUM);
        } else{
            amount*=(1-DISCOUNT_BASIC);
        }
        return Card::withdraw(amount);
    }

    void print(){
        cout<<"Master";
        Card::print();
    }
};
const float MasterCard::DISCOUNT_BASIC=0.03; //3%
float MasterCard::DISCOUNT_PREMIUM=0.1; //10%

class MaestroCard: public Card{
private:
    const static float DISCOUNT;
public:
    MaestroCard(char *id="111111111111111", double limit=1000, double balance=0): Card(id,limit,balance){

    }

    bool withdraw(double amount){
        amount*=(1-DISCOUNT);
        return Card::withdraw(amount);
    }

    void print(){
        cout<<"Maestro";
        Card::print();
    }
};
const float MaestroCard::DISCOUNT=0.05; //5%

int main(){

    Card **cards=new Card *[4];
    cards[0]=new MasterCard("111111111111111", 8000,1000);
    cards[1]=new MaestroCard("111111111111112", 4000,5000);
    cards[2]=new MaestroCard("111111111111113", 2000,2000);
    cards[3]=new MaestroCard("111111111111114", 0,10000);

    for(int i=0;i<4;i++){
        cards[i]->print();
    }

    for(int i=0;i<4;i++){
        cout<<cards[i]->withdraw(8000)<<endl;
        cards[i]->print();
    }

    MasterCard::setDiscountPremium(0.15); //povik na staticki metod preku scope operator preku klasata

    for(int i=0;i<4;i++){
        cout<<cards[i]->withdraw(100)<<endl;
        cards[i]->print();
    }

    return 0;
}