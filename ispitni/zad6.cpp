#include <iostream>
#include <string.h>
using namespace std;

class ExistingGame{
public:
    void message(){
        cout<<"The game is already in the collection"<<endl;
    }
};

class Game{
protected:
    char imeIgra[100];
    double cenaIgra;
    bool sale;
public:
    Game(char *imeIgra="", double cenaIgra=0.0, bool sale=true){
        strcpy(this->imeIgra,imeIgra);
        this->cenaIgra=cenaIgra;
        this->sale=sale;
    }

    friend ostream &operator<<(ostream &out, Game &g){
        out<<"Game: "<<g.imeIgra<<", regular price: $"<<g.cenaIgra;
        if(g.sale){
            out<<", bought on sale"<<endl;
        } else out<<endl;
        return out;
    }

    friend istream &operator>>(istream &in, Game &g){
        in.get();
        in.getline(g.imeIgra,100);
        in>>g.cenaIgra>>g.sale;
        return in;
    }

    bool operator==(Game &g){
        return !strcmp(imeIgra,g.imeIgra);
    }

    bool getSale(){
        return sale;
    }

    double getCenaIgra(){
        return cenaIgra;
    }
};

class SubscriptionGame: public Game{
    double subscription;
    int mesec, godina;
public:
    SubscriptionGame(char *imeIgra="", double cenaIgra=0.0, bool sale=true, double subscription=0.0, int mesec=0, int godina=0): Game(imeIgra,cenaIgra,sale){
        this->subscription=subscription;
        this->mesec=mesec;
        this->godina=godina;
    }

    friend ostream &operator<<(ostream &out, SubscriptionGame &g){
        out<<"Game: "<<g.imeIgra<<", regular price: $"<<g.cenaIgra;
        if(g.sale){
            out<<", bought on sale";
        }
        out<<", monthly fee: $"<<g.subscription<<", purchased: "<<g.mesec<<"-"<<g.godina<<endl;
        return out;
    }

    friend istream &operator>>(istream &in, SubscriptionGame &g){
        in.get();
        in.getline(g.imeIgra,100);
        in>>g.cenaIgra>>g.sale>>g.subscription>>g.mesec>>g.godina;
        return in;
    }

    int getMesec(){
        return mesec;
    }

    double getSubscription(){
        return subscription;
    }
};

class User{
    char username[100];
    Game *games;
    int brGames;
public:
    User(char *username=""){
        strcpy(this->username,username);
        brGames=0;
        games=new Game[brGames];
    }

    User &operator+=(Game &g){
        for(int i=0;i<brGames;i++){
            if(games[i]==g){
                throw ExistingGame();
            }
        }
        Game *tmp=new Game[brGames+1];
        for(int i=0;i<brGames;i++){
            tmp[i]=games[i];
        }
        tmp[brGames++]=g;
        delete [] games;
        games=tmp;
        return *this;
    }

    double total_spent(){
        double sum=0.0;
        /*for(int i=0;i<brGames;i++){
            if(games[i].getSale()==true){
                sum+=games[i].getCenaIgra()*0.3;
            } else sum+=games[i].getCenaIgra();
        }*/
        for(int i=0;i<brGames;i++){
            sum+=games[i].getCenaIgra();
        }
        return sum;
    }

    friend ostream &operator<<(ostream &out, User &g){
        out<<endl<<"User: "<<g.username<<endl;
        for(int i=0;i<g.brGames;i++){
            out<<"- "<<g.games[i];
        }
        out<<endl;
//        for(int i=0;i<g.brGames;i++){
//            Game *g1=dynamic_cast<Game *>(&g.games[i]);
//            if(g1!=0){
//                out<<*g1;
//            } else{
//                delete &g1;
//                SubscriptionGame *g2=dynamic_cast<SubscriptionGame *>(g.games[i]);
//                out<<*g2;
//            }
//        }

        return out;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
