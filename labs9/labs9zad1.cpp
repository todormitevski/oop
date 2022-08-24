#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;

//exceptions
class InvalidPassword{
public:
    void message(){
        cout<<"Password is too weak."<<endl;
    }
};

class InvalidEmail{
public:
    void message(){
        cout<<"Mail is not valid."<<endl;
    }
};

class MaximumSizeLimit{
    int n;
public:
    MaximumSizeLimit(int n=0){
        this->n=n;
    }

    void message(){
        cout<<"You can't add more than "<<n<<" users."<<endl;
    }
};

class User{
protected:
    char username[50];
    char password[50];
    char email[50];
public:
    User(char *username="", char *password="", char *email=""){
        strcpy(this->username,username);
        strcpy(this->password,password);
        strcpy(this->email,email);

        bool golemaFlag=false, malaFlag=false, brojFlag=false;
        for(int i=0;i<strlen(password);i++){
            if(isupper(password[i])){
                golemaFlag=true;
            } else if(islower(password[i])){
                malaFlag=true;
            } else if(isdigit(password[i])){
                brojFlag=true;
            }
        }
        if(!golemaFlag || !malaFlag || !brojFlag){
            throw InvalidPassword();
        }

        int br=0;
        for(int i=0;i<strlen(email);i++){
            if(email[i]=='@'){
                br++;
            }
        }
        if(br!=1){
            throw InvalidEmail();
        }
    }

    virtual double popularity()=0;
};

class FacebookUser: public User{
    int brFriends;
    int brLikes;
    int brComments;

    static float LIKE_COEF;
    static float COMMENT_COEF;
public:
    FacebookUser(char *username="", char *password="", char *email="", int brFriends=0, int brLikes=0, int brComments=0): User(username,password,email){
        this->brFriends=brFriends;
        this->brLikes=brLikes;
        this->brComments=brComments;
    }

    double popularity(){
        return brFriends + brLikes*LIKE_COEF + brComments*COMMENT_COEF;
    }
};
float FacebookUser::LIKE_COEF=0.1;
float FacebookUser::COMMENT_COEF=0.5;

class TwitterUser: public User{
    int brFollowers;
    int brTweets;

    static float TWEET_COEF;
public:
    TwitterUser(char *username="", char *password="", char *email="", int brFollowers=0, int brTweets=0): User(username,password,email){
        this->brFollowers=brFollowers;
        this->brTweets=brTweets;
    }

    double popularity(){
        return brFollowers + brTweets*TWEET_COEF;
    }
};
float TwitterUser::TWEET_COEF=0.5;

class SocialNetwork{
    User **users;
    int brUsers;

    static int MAX_USERS;
public:
    SocialNetwork(){
        brUsers=0;
        users=new User *[brUsers];
    }

    ~SocialNetwork(){
        delete [] users;
    }

    SocialNetwork &operator+=(User *u){
        if(brUsers==MAX_USERS){
            throw MaximumSizeLimit(brUsers);
        }
        User **tmp=new User *[brUsers+1];
        for(int i=0;i<brUsers;i++){
            tmp[i]=users[i];
        }
        tmp[brUsers++]=u;
        delete [] users;
        users=tmp;
    }

    double avgPopularity(){
        double suma=0.0;
        for(int i=0;i<brUsers;i++){
            suma+=users[i]->popularity();
        }
        return suma/brUsers;
    }

    void changeMaximumSize(int number){
        this->MAX_USERS=number;
    }
};
int SocialNetwork::MAX_USERS=5;

int main() {

    SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
        cin >> username;
        cin >> password;
        cin >> email;
        cin >> userType;
        if (userType == 1) {
            int friends;
            int likes;
            int comments;
            cin >> friends >> likes >> comments;

            // TODO: Try-catch
            try{
            User * u = new FacebookUser(username,password,email,friends,likes,comments);
            network += u;
            }
            catch(InvalidEmail &i){
                i.message();
            }
            catch(InvalidPassword &i){
                i.message();
            }
            catch(MaximumSizeLimit &i){
                i.message();
            }
        }
        else {
            int followers;
            int tweets;
            cin >> followers >> tweets;

            // TODO: Try-catch
            try{
            User * u= new TwitterUser(username,password,email,followers,tweets);
            network += u;
            }
            catch(InvalidEmail &i){
                i.message();
            }
            catch(InvalidPassword &i){
                i.message();
            }
            catch(MaximumSizeLimit &i){
                i.message();
            }
        }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    // TODO: Try-catch
    try{
    User * u= new TwitterUser(username,password,email,followers,tweets);
    network += u;
    }
    catch(InvalidEmail &i){
        i.message();
    }
    catch(InvalidPassword &i){
        i.message();
    }
    catch(MaximumSizeLimit &i){
        i.message();
    }
    cout << network.avgPopularity();

}