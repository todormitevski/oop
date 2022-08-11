#include <cstring>
#include <iostream>
using namespace std;

class NegativeValueException{
private:
    char productName[50];
public:
    NegativeValueException(char *productName=""){
        strcpy(this->productName,productName);
    }

    void showMessage(){
        cout<<"The product "<<productName<<" cannot have a negative value for price"<<endl;
    }
};

//abstract klasa
class Discount{
public:
    static float EUR_TO_MKD;
    static float USD_TO_MKD;
    virtual float discount_price()=0;
    virtual float getPrice()=0;
    virtual void print_rule()=0;
};
float Discount::EUR_TO_MKD=61.5;
float Discount::USD_TO_MKD=58.4;

class Product{
protected:
    char name[50];
    float price;
public:
    Product(char *name="", float price=0.0){
        strcpy(this->name,name);
        this->price=price;
    }

    void changePrice(float newPrice){
        if(newPrice<0){
            throw NegativeValueException(this->name);
        }
        this->price=newPrice;
    }
};

class FoodProduct: public Product, public Discount{
public:
    FoodProduct(char *name="", float price=0.0): Product(name,price){

    }

    float discount_price(){
        return getPrice();
    }

    float getPrice(){
        return price*Discount::EUR_TO_MKD;
    }

    void print_rule(){
        cout<<"No discount for food products"<<endl;
    }
};

class Drinks: public Product, public Discount{
    bool isAlcohol;
public:
    Drinks(char *name="", float price=0.0, bool isAlcohol=false): Product(name,price){
        this->isAlcohol=isAlcohol;
    }

    float discount_price(){
        if(isAlcohol==true&&price>20.0){
            return getPrice()*0.95;
        }
        if(isAlcohol==false&&!strcmp(name,"coca-cola")){
            return getPrice()*0.9;
        }
    }

    float getPrice(){
        return price*Discount::EUR_TO_MKD;
    }

    void print_rule(){
        cout<<"Alcohol products with price larger than 20EUR-> 5%, Coca-cola 10%"<<endl;
    }
};

class Cosmetics: public Product, public Discount{
public:
    Cosmetics(char *name="", float price=0.0): Product(name,price){

    }

    float discount_price(){
        float priceInUSD=price*Discount::EUR_TO_MKD/Discount::USD_TO_MKD;
        if(priceInUSD>20.0){
            return getPrice()*0.86;
        }
        if(priceInUSD>5.0){
            return getPrice()*0.88;
        }
        return getPrice();
    }

    float getPrice(){
        return price*Discount::EUR_TO_MKD;
    }

    void print_rule(){
        cout<<"price in USD > 20$ ->14%, price in EUR > 5EUR -> 12%"<<endl;
    }
};



int main(){

//    Product *p=new FoodProduct("leb", 0.5);
//    try{
//    p->changePrice(-5);
//    } catch(NegativeValueException e){
//        e.showMessage();
//    }

    int n=0;
    Discount **d=new Discount*[10];
    d[n++]=new FoodProduct("leb", 0.5);
    d[n++]=new Drinks("viski", 22, true);
    d[n++]=new FoodProduct("sirenje", 6.2);
    d[n++]=new Drinks("vodka", 10, true);
    d[n++]=new Cosmetics("krema", 12);
    d[n++]=new Drinks("coca-cola", 1.2, false);
    d[n++]=new Cosmetics("parfem", 60);

    for(int i=0;i<n;i++){
        cout<<i+1<<endl;
        cout<<d[i]->getPrice()<<endl;
        cout<<d[i]->discount_price()<<endl;
        d[i]->print_rule();
    }

    //Cosmetic products set price to negative value
    for(int i=0;i<n;i++){
        Cosmetics *cosmeticsTrial=dynamic_cast<Cosmetics *>(d[i]);
        if(cosmeticsTrial!=0){ //vaka znaeme dali e kastiran uspesno ili ne
        int newPrice;
        cin>>newPrice;
        try{
        cosmeticsTrial->changePrice(newPrice);
        }   catch(NegativeValueException e){
                e.showMessage();
            }
        }
    }

    for(int i=0;i<n;i++){
        cout<<i+1<<endl;
        cout<<d[i]->getPrice()<<endl;
        cout<<d[i]->discount_price()<<endl;
        d[i]->print_rule();
    }

    return 0;
}