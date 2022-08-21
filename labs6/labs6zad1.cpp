#include <iostream>
#include <string.h>
using namespace std;

class NBAPlayer{
protected:
    char *name;
    char team[40];
    double points;
    double assists;
    double rebounds;

    void copy(const NBAPlayer &n){
        this->name=new char[strlen(n.name)+1];
        strcpy(this->name,n.name);
        strcpy(this->team,n.team);
        this->points=n.points;
        this->assists=n.assists;
        this->rebounds=n.rebounds;
    }
public:
    NBAPlayer(char *name="", char *team="", double points=0.0, double assists=0.0, double rebounds=0.0){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->team,team);
        this->points=points;
        this->assists=assists;
        this->rebounds=rebounds;
    }

    NBAPlayer(const NBAPlayer &n){
        copy(n);
    }

    NBAPlayer &operator=(const NBAPlayer &n){
        if(this!=&n){
            delete [] name;
            copy(n);
        }
        return *this;
    }

    ~NBAPlayer(){
        delete [] name;
    }

    double rating(){
        return (((double)45/100)*points)+(((double)30/100)*assists)+(((double)25/100)*rebounds);
//        double rating;
//        rating=(points*0.45)+(assists*0.30)+(rebounds*0.25);
//        return rating;
    }

    void print(){
        cout<<name<<" - "<<team<<endl;
        cout<<"Points: "<<points<<endl;
        cout<<"Assists: "<<assists<<endl;
        cout<<"Rebounds: "<<rebounds<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }
};

class AllStarPlayer: public NBAPlayer{
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    void copy(const AllStarPlayer &player){
        this->allStarPoints=player.allStarPoints;
        this->allStarAssists=player.allStarAssists;
        this->allStarRebounds=player.allStarRebounds;
    }
public:
    AllStarPlayer(): NBAPlayer(){
        allStarPoints=0;
        allStarAssists=0;
        allStarRebounds=0;
    }

    AllStarPlayer(NBAPlayer &player, double allStarPoints, double allStarAssists, double allStarRebounds): NBAPlayer(player){
        this->allStarPoints=allStarPoints;
        this->allStarAssists=allStarAssists;
        this->allStarRebounds=allStarRebounds;
    }

    AllStarPlayer(char *name, char *team, double points, double assists, double rebounds, double allStarPoints, double allStarAssists, double allStarRebounds): NBAPlayer(name,team,points,assists,rebounds){
        this->allStarPoints=allStarPoints;
        this->allStarAssists=allStarAssists;
        this->allStarRebounds=allStarRebounds;
    }

    AllStarPlayer(const AllStarPlayer &player): NBAPlayer(player){
        copy(player);
    }

    AllStarPlayer &operator=(const AllStarPlayer &player){
        if(this!=&player){
            NBAPlayer::copy(player);
            copy(player);
        }
        return *this;
    }

    ~AllStarPlayer(){}

    double allStarRating(){
        //return ((((double)30/100)*allStarPoints)+(((double)40/100)*allStarAssists)+(((double)30/100)*allStarRebounds));
        double asRating=0.0;
        asRating= 0.3*allStarPoints+0.4*allStarAssists+0.3*allStarRebounds;
        return asRating;
    }

    double rating(){
        return (NBAPlayer::rating()+allStarRating())/2;
    }

    void print(){
        NBAPlayer::print();
        cout<<"All Star Rating: "<<allStarRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }
};

int main() {

    char name[50];
    char team[40];
    double points;
    double assists;
    double rebounds;
    double allStarPoints;
    double allStarAssists;
    double allStarRebounds;

    NBAPlayer * players = new NBAPlayer[5];
    AllStarPlayer * asPlayers = new AllStarPlayer[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> team >> points >> assists >> rebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            players[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            players[i] = NBAPlayer(name,team,points,assists,rebounds);
            asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
        }

        cout << "NBA PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            players[i].print();

        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> team >> points >> assists >> rebounds;
            cin >> allStarPoints >> allStarAssists >> allStarRebounds;
            asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                         allStarPoints,allStarAssists,allStarRebounds);
        }
        cout << "ALL STAR PLAYERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}