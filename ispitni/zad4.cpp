#include <cstring>
#include <iostream>
using namespace std;

//Your Code goes here
enum Size{
    mala=0,
    golema,
    familijarna
};

class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    double osnovnaCena;
public:
    Pizza(const char *ime="", const char *sostojki="", double osnovnaCena=0.0){
        strcpy(this->ime,ime);
        strcpy(this->sostojki,sostojki);
        this->osnovnaCena=osnovnaCena;
    }

    virtual double price()=0;

    bool operator<(Pizza &p){
        return price()<p.price();
    }
};

class FlatPizza: public Pizza{
    Size golemina;
public:
    FlatPizza(const char *ime="", const char *sostojki="", double osnovnaCena=0.0, Size golemina=(Size)0): Pizza(ime,sostojki,osnovnaCena){
        this->golemina=golemina;
    }

    double price(){
        if(golemina==0){
            return osnovnaCena*1.1;
        } else if(golemina==1){
            return osnovnaCena*1.5;
        } else if(golemina==2){
            return osnovnaCena*1.3;
        }
    }

    friend ostream &operator<<(ostream &out, FlatPizza &p){
        out<<p.ime<<": "<<p.sostojki<<", ";
        if(p.golemina==0){
            out<<"small";
        } else if(p.golemina==1){
            out<<"large";
        } else out<<"family";
        out<<" - "<<p.price()<<endl;
        return out;
    }
};

class FoldedPizza: public Pizza{
    bool beloBrasno;
public:
    FoldedPizza(const char *ime="", const char *sostojki="", double osnovnaCena=0.0, bool beloBrasno=true): Pizza(ime,sostojki,osnovnaCena){
        this->beloBrasno=beloBrasno;
    }

    double price(){
        if(beloBrasno==true){
            return osnovnaCena*1.1;
        } else return osnovnaCena*1.3;
    }

    void setWhiteFlour(bool flour){
        this->beloBrasno=flour;
    }

    friend ostream &operator<<(ostream &out, FoldedPizza &p){
        out<<p.ime<<": "<<p.sostojki<<", ";
        if(p.beloBrasno==true){
            out<<"wf - ";
        } else out<<"nwf - ";
        out<<p.price()<<endl;
        return out;
    }
};

void expensivePizza(Pizza **pizzas, int n){
    Pizza *tmp=pizzas[0];
    for(int i=0;i<n;i++){
        if(pizzas[i]->price()>tmp->price()){
            tmp=pizzas[i];
        }
    }
    FlatPizza *p1=dynamic_cast<FlatPizza *>(tmp);
    if(p1!=0){ //neuspesno dinamicko kastiranje vrakja 0
        cout<<*p1;
    } else{
        FoldedPizza *p2=dynamic_cast<FoldedPizza *>(tmp);
        cout<<*p2;
    }
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}