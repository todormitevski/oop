#include <iostream>
#include <string.h>
using namespace std;

class Book{
protected:
    char ISBN[20];
    char title[50];
    char author[30];
    double osnovnaCena;

    void copy(const Book &o){
        strcpy(this->ISBN,o.ISBN);
        strcpy(this->title,o.title);
        strcpy(this->author,o.author);
        this->osnovnaCena=o.osnovnaCena;
    }
public:
    Book(char *ISBN="", char *title="", char *author="", double osnovnaCena=0.0){
        strcpy(this->ISBN,ISBN);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->osnovnaCena=osnovnaCena;
    }

    void setISBN(char *newISBN){
        strcpy(this->ISBN,newISBN);
    }

    virtual double bookPrice()=0; //makes the class abstract

    bool operator>(Book &o){
        return bookPrice()>o.bookPrice();
    }

    friend ostream &operator<<(ostream &out, Book &o){
        return out<<o.ISBN<<": "<<o.title<<", "<<o.author<<" "<<o.bookPrice()<<endl;
    }
};

class OnlineBook: public Book{
    char *url;
    int goleminaMB;

    void copy(const OnlineBook &o){
        this->goleminaMB=o.goleminaMB;
        this->url=new char[goleminaMB];
        strcpy(this->url,o.url);
    }
public:
    OnlineBook(char *ISBN="", char *title="", char *author="", double osnovnaCena=0.0, char *url="", int goleminaMB=0): Book(ISBN,title,author,osnovnaCena){
        this->goleminaMB=goleminaMB;
        this->url=new char[goleminaMB];
        strcpy(this->url,url);
    }

    OnlineBook(const OnlineBook &o): Book(o){
        copy(o);
    }

    OnlineBook &operator=(const OnlineBook &o){
        if(this!=&o){
            delete [] url;
            Book::copy(o);
            copy(o);
        }
        return *this;
    }

    ~OnlineBook(){
        delete [] url;
    }

    double bookPrice(){
        if(goleminaMB>20){
            return osnovnaCena*1.2;
        } else return osnovnaCena;
    }
};

class PrintBook: public Book{
    double massKG;
    bool naZaliha;
public:
    PrintBook(char *ISBN="", char *title="", char *author="", double osnovnaCena=0.0, double massKG=0.0, bool naZaliha=false): Book(ISBN,title,author,osnovnaCena){
        this->massKG=massKG;
        this->naZaliha=naZaliha;
    }

    double bookPrice(){
        if(massKG>0.7){
            return osnovnaCena*1.15;
        } else return osnovnaCena;
    }
};

void mostExpensiveBook (Book** books, int n){
    int brOnline=0, brPrint=0, maxIndex=0;
    double maxPrice=0.0;
    for(int i=0;i<n;i++){
        if(dynamic_cast<OnlineBook *>(books[i])){
            brOnline++;
        } else if(dynamic_cast<PrintBook *>(books[i])){
            brPrint++;
        }
        if(books[i]->bookPrice()>maxPrice){
            maxPrice=books[i]->bookPrice();
            maxIndex=i;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<brOnline<<endl;
    cout<<"Total number of print books: "<<brPrint<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[maxIndex];
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
