#include <iostream>
#include <cstring>
using namespace std;

class HotelReservation{
protected:
    char contact[50];
    int guests;
    int days;
public:
    HotelReservation(char *contact, int days, int guests){
        strcpy(this->contact,contact);
        this->days=days;
        this->guests=guests;
    }

    virtual double price(){
        return guests*days*25;
    }

    double price(double deposit){
        return deposit-price();
    }
};

class HalfBoardHotelReservation: public HotelReservation{
public:
    HalfBoardHotelReservation(char *contact="", int days=0, int guests=0): HotelReservation(contact, days, guests){}

    double price(){
        return HotelReservation::price()*1.2;
    }
};

class Hotel{
    char name[20];
    double balance;
public:
    Hotel(char *name="Balkan", double balance=1000){
        strcpy(this->name,name);
        this->balance=balance;
    }

    double depositReservation(HotelReservation &h, double deposit){
        double totalPrice=h.price();
        balance+=totalPrice;
        return h.price(deposit);
    }

    friend ostream &operator<<(ostream &out, const Hotel &h){
        return out<<h.name<<" "<<h.balance;
    }
};

int main(){

    Hotel hotel("Finki", 1000);

    int n; //br rezervacii
    cin>>n;

    HotelReservation **reservations=new HotelReservation *[n];
    for(int i=0;i<n;i++){
        int type; //1=obicna, 2=polupansionska
        char name[30];
        int days,guests;
        double deposit;
        cin>>type>>name>>days>>guests>>deposit;
        if(type==1){
            reservations[i]=new HotelReservation(name,days,guests);
        } else{
            reservations[i]=new HalfBoardHotelReservation(name,days,guests);
        }
        cout<<name<<" Days: "<<days<<" Guests: "<<guests<<" Price: "<<reservations[i]->price();
        cout<<" Change from payment: "<<hotel.depositReservation(*reservations[i],deposit);
    }

    cout<<endl;
    cout<<"Hotel state after all reservations were paid"<<endl;
    cout<<hotel;

    return 0;
}