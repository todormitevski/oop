#include <iostream>
#include <string.h>
using namespace std;

class Category{
    char name[20];
public:
    Category(char *name="unnamed"){
        strcpy(this->name,name);
    }

    void print(){
        cout<<"Category: "<<name<<endl;
    }
};

class NewsArticle{
    Category kategorija;
    char title[30];
public:
    NewsArticle(){
        strcpy(this->title,"untitled");
    }

    NewsArticle(Category kategorija, char *title="untitled"){
        this->kategorija=kategorija;
        strcpy(this->title,title);
    }

    void print(){
        cout<<"Article title: "<<title<<endl;
        kategorija.print();
    }
};

class FrontPage{
    NewsArticle naslovnaVest;
    float price;
    int editionNumber;
public:
    FrontPage(){
        price=0;
        editionNumber=0;
    }

    FrontPage(NewsArticle naslovnaVest, float price=0, int editionNumber=0){
        this->naslovnaVest=naslovnaVest;
        this->price=price;
        this->editionNumber=editionNumber;
    }

    void print(){
        cout<<"Price: "<<price<<", Edition number: "<<editionNumber<<endl;
        naslovnaVest.print();
    }
};

int main() {
    char categoryName[20];
    char articleTitle[30];
    float price;
    int editionNumber;

    int testCase;
    cin >> testCase;


    if (testCase == 1) {
        int iter;
        cin >> iter;
        while (iter > 0) {
            cin >> categoryName;
            cin >> articleTitle;
            cin >> price;
            cin >> editionNumber;
            Category category(categoryName);
            NewsArticle article(category, articleTitle);
            FrontPage frontPage(article, price, editionNumber);
            frontPage.print();
            iter--;
        }
    }
    else if (testCase == 2) {
        cin >> categoryName;
        cin >> price;
        cin >> editionNumber;
        Category category(categoryName);
        NewsArticle article(category);
        FrontPage frontPage(article, price, editionNumber);
        frontPage.print();
    }// test case 3
    else if (testCase == 3) {
        cin >> categoryName;
        cin >> articleTitle;
        cin >> price;
        Category category(categoryName);
        NewsArticle article(category, articleTitle);
        FrontPage frontPage(article, price);
        frontPage.print();
    }
    else {
        FrontPage frontPage = FrontPage();
        frontPage.print();
    }
    return 0;
}
