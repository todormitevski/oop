//NERESENA
#include <iostream>
#include <string.h>
using namespace std;

class Exception{
public:
    void message(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud{
    char vid[1];
    int godinaIzdavanje;

    static int KONFERENCISKI_TRUD;
    static int TRUD_VO_SPISANIE;
public:
    void copy(const Trud &s){
        strcpy(this->vid,s.vid);
        this->godinaIzdavanje=s.godinaIzdavanje;
    }

    Trud(const char *vid="", int godinaIzdavanje=0){
        strcpy(this->vid,vid);
        this->godinaIzdavanje=godinaIzdavanje;
    }

    //za *trudovi =
    Trud &operator=(const Trud &s){
        if(this!=&s){
            copy(s);
        }
        return *this;
    }

    char *getVid(){
        return vid;
    }

    static int getKonfTrud(){
        return KONFERENCISKI_TRUD;
    }

    static int getSpisTrud(){
        return TRUD_VO_SPISANIE;
    }

    //uni moze da gi menuva
    static void setKonfTrud(int newKonf){
        KONFERENCISKI_TRUD=newKonf;
    }

    static void setSpisTrud(int newSpis){
        TRUD_VO_SPISANIE=newSpis;
    }
};
int Trud::KONFERENCISKI_TRUD=1;
int Trud::TRUD_VO_SPISANIE=3;

class Student{
    char ime[30];
    int index;
    int godinaUpis;
    int *polozeniPredmeti;
    int brPolozeni;
public:
    void copy(const Student &s){
        strcpy(this->ime,s.ime);
        this->index=s.index;
        this->godinaUpis=s.godinaUpis;
        this->brPolozeni=s.brPolozeni;
        this->polozeniPredmeti=new int[s.brPolozeni];
        for(int i=0;i<s.brPolozeni;i++){
            this->polozeniPredmeti=s.polozeniPredmeti;
        }
    }

    Student(char *ime="", int index=0, int godinaUpis=0, int *polozeniPredmeti=0, int brPolozeni=0){
        strcpy(this->ime,ime);
        this->index=index;
        this->godinaUpis=godinaUpis;
        this->brPolozeni=brPolozeni;
        this->polozeniPredmeti=new int[brPolozeni];
        for(int i=0;i<brPolozeni;i++){
            this->polozeniPredmeti=polozeniPredmeti;
        }
    }

    Student(const Student &s){
        copy(s);
    }

    Student &operator=(const Student &s){
        if(this!=&s){
            delete [] polozeniPredmeti;
            copy(s);
        }
        return *this;
    }

    ~Student(){
        delete [] polozeniPredmeti;
    }

    virtual double rang(){
        double sum=0.0;
        for(int i=0;i<brPolozeni;i++){
            sum+=polozeniPredmeti[i];
        }
        return sum/=brPolozeni;
    }

    friend ostream &operator<<(ostream &out, Student &s){
        return out<<s.index<<" "<<s.ime<<" "<<s.godinaUpis<<" "<<s.rang();
    }
};

class PhDStudent: public Student, public Trud{
    Trud *trudovi;
    int brTrudovi;

    void copy(const PhDStudent &s){
        this->brTrudovi=s.brTrudovi;
        this->trudovi=new Trud[s.brTrudovi];
        for(int i=0;i<s.brTrudovi;i++){
            this->trudovi=s.trudovi;
        }
    }
public:
    PhDStudent(char *ime="", int index=0, int godinaUpis=0, int *polozeniPredmeti=0, int brPolozeni=0, const char *vid="", int godinaIzdavanje=0): Student(ime,index,godinaUpis,polozeniPredmeti,brPolozeni), Trud(vid,godinaIzdavanje){
        this->brTrudovi=brTrudovi;
        this->trudovi=new Trud[brTrudovi];
        for(int i=0;i<brTrudovi;i++){
            this->trudovi=trudovi;
        }
    }
    //PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);

    PhDStudent(const PhDStudent &s): Student(s){
        copy(s);
    }

    PhDStudent &operator=(const PhDStudent &s){
        if(this!=&s) {
            delete [] trudovi;
            Trud::copy(s);
            Student::copy(s);
            copy(s);
        }
        return *this;
    }

    ~PhDStudent(){
        delete [] trudovi;
    }

    double rang(){
        double sum=Student::rang();
        for(int i=0;i<brTrudovi;i++){
            if(!strcmp(trudovi[i].getVid(),"C")){
                sum+=Trud::getKonfTrud();
            } else if(!strcmp(trudovi[i].getVid(),"J")){
                sum+=Trud::getSpisTrud();
            }
        }
        return sum;
    }

    PhDStudent &operator+=(Trud &t){
        Trud *tmp=new Trud[brTrudovi+1];
        for(int i=0;i<brTrudovi;i++){
            tmp[i]=trudovi[i];
        }
        tmp[brTrudovi++]=t;
        delete [] trudovi;
        trudovi=tmp;
        return *this;
    }
};

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}