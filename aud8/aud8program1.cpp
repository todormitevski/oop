#include <string.h>
#include <iostream>
using namespace std;

 //PRVA ZADACA
class TennisPlayer{
protected:
    char name[50];
    bool playsInLeague;
public:
    TennisPlayer(char *name="", bool playsInLeague=false){
        strcpy(this->name,name);
        this->playsInLeague=playsInLeague;
    }

    TennisPlayer(const TennisPlayer &t){
        strcpy(this->name,t.name);
        this->playsInLeague=t.playsInLeague;
    }

    void print(){
        cout<<"Tennis Player "<<name<<" "<<(playsInLeague?"plays in league":"doesn't play in league")<<endl;
    }

    friend ostream &operator<<(ostream &out, const TennisPlayer &t){
        out<<"Tennis Player "<<t.name<<" "<<(t.playsInLeague?"plays in league":"doesn't play in league");
        return out;
    }
};

class RankedTennisPlayer: public TennisPlayer{
private:
    int rank;
public:
    RankedTennisPlayer(char *name="", bool playsInLeague=false, int rank=100): TennisPlayer(name, playsInLeague){
        this->rank=rank;
    }

    RankedTennisPlayer(const TennisPlayer &t, int rank): TennisPlayer(t){ //unapreduvanje na tennis player
        this->rank=rank;
    }

    RankedTennisPlayer(const RankedTennisPlayer &t): TennisPlayer(t){ //copy constructor so nasleduvanje
        this->rank-t.rank;
    }

    friend ostream &operator<<(ostream &out, const RankedTennisPlayer &t){
        out<<"Ranked";
        TennisPlayer tmp(t);
        out<<tmp<<", is ranked "<<t.rank;
        return out;
    }
};

int main() {
    TennisPlayer tp("Novak Djokovic", true);
    cout<<tp<<endl;
    RankedTennisPlayer rtp(tp, 1);
    cout<<rtp<<endl;
    return 0;
}