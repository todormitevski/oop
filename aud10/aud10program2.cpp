#include <cstring>
#include <iostream>
using namespace std;

class Product{
protected:
    char name[50];
    float price;
public:
    Product(char *name="", float price=0.0){
        strcpy(this->name,name);
        this->price=price;
    }
};

//apstraktna klasa za popust (interface)
class Discountable{
public:
    virtual float getPrice()=0;
    virtual float getPriceWithDiscount()=0;
    virtual void print()=0;
};

class FoodProduct: public Product, public Discountable{
private:
    int calories;
public:
    FoodProduct(char *name="", float price=0.0, int calories=0): Product(name,price){
        this->calories=calories;
    }

    float getPrice(){
        return price;
    }

    float getPriceWithDiscount(){
        if(calories>500){
            return 0.8*price; //popust 20%
        } else if(calories>100){
            return 0.9*price; //popust 10%
        } else{
            return 0.95*price; //popust 5%
        }
    };

    void print(){
        cout<<"Food Product "<<name<<" with number of calories "<<calories<<" Price: "<<getPrice()<<", price with discount: "<<getPriceWithDiscount()<<endl;
    }
};

class DigitalProduct: public Product, public Discountable{
private:
    float sizeInMb;
public:
    DigitalProduct(char *name="", float price=0.0, float sizeInMb=1.0): Product(name,price){
        this->sizeInMb=sizeInMb;
    }

    float getPrice(){
        return price;
    }

    float getPriceWithDiscount(){
        if(sizeInMb>1024){
            return 0.7*price; //30% popust
        } else if(sizeInMb>512){
            return 0.85*price; //15% popust
        } else{
            return 0.925*price; //7.5% popust
        }
    }

    void print(){
        cout<<"Digital Product "<<name<<" with size in MB "<<sizeInMb<<" Price: "<<getPrice()<<", price with discount: "<<getPriceWithDiscount()<<endl;
    }
};

//globalna funkcija totalDiscount()
float totalDiscount(Discountable **discountableProducts, int n){
    float totalDiscount=0.0;
    for(int i=0;i<n;i++){
        totalDiscount+=(discountableProducts[i]->getPrice()-discountableProducts[i]->getPriceWithDiscount());
    }
    return totalDiscount;
}

int countFoodProducts(Discountable **discountableProducts, int n){
    int counter=0;
    for(int i=0;i<n;i++){
        FoodProduct *casted=dynamic_cast<FoodProduct *>(discountableProducts[i]);
        if(casted!=0){
            ++counter;
        }
    }
    return counter;
}

int main(){

    int n;
    cin>>n;
    Discountable **discountableProducts=new Discountable *[n];

    for(int i=0;i<n;i++){
        int type;
        char name[50];
        float price;
        float sizeInMb;
        int calories;
        cin>>type;
        if(type==1){ //FoodProduct
            cin>>name>>price>>calories;
            discountableProducts[i]=new FoodProduct(name,price,calories);
        } else{ //DigitalProduct
            cin>>name>>price>>sizeInMb;
            discountableProducts[i]=new DigitalProduct(name,price,sizeInMb);
        }
    }

    for(int i=0;i<n;i++){
        discountableProducts[i]->print();
    }

    cout<<"Total discount for the products is: "<<totalDiscount(discountableProducts,n)<<endl;
    cout<<"Total number of food products is: "<<countFoodProducts(discountableProducts,n)<<endl;
    cout<<"Total number of digital products is: "<<n- countFoodProducts(discountableProducts,n)<<endl;

    return 0;
}