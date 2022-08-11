#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

//exception
class NotValidUsernameException{
private:
    char notValidUsername[50]; //ako treba da se ispecati informacijata sto dava exception ova se pravi
public:
    NotValidUsernameException(char *email="test@test.com"){
        strcpy(this->notValidUsername,email);
    }

    void showMessage(){
        cout<<notValidUsername<<" is not valid! Try again!"<<endl;
    }
};

class User{
protected:
    int id;
    char username[50];
    static int ID_TRACKER; //staticki clen, non-constant
public:
    User(char *username="test", int id=0){
        bool atSignFound=false;
        bool dotSignFound=false; //flags
        for(int i=0;i<strlen(username);i++){
            if(username[i]=='@'){
                atSignFound=true;
            }
            if(atSignFound){
                if(username[i]=='.'){
                    dotSignFound=true;
                }
            }
        }
        //go frla exceptionot ako if uslovot e ispolnet
        if(atSignFound==false||dotSignFound==false){
            throw NotValidUsernameException(username);
        }

        strcpy(this->username,username);
        this->id=ID_TRACKER++;
    }

    void print(){
        cout<<id<<" "<<username<<endl;
    }
};
int User::ID_TRACKER=1; //pocetna inicijalizacija na staticki clen

int main(){
    try{
        User u1("todor"); //ID=1
        User u2("risto"); //ID=2
        User u3("petko"); //ID=3

        u1.print();
        u2.print();
        u3.print();
    }
    catch(NotValidUsernameException e){
        e.showMessage();
    }

    return 0;
}