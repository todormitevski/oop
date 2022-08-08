#include <cstring>
#include <iostream>
using namespace std;

class Student{
    char *name;
    int *grades;
    int brGrades;
    int year;

    void copy(const Student &s){
        this->name=new char[strlen(s.name)+1];
        strcpy(this->name,s.name);
        this->brGrades=s.brGrades;
        grades=new int[s.brGrades];
        for(int i=0;i<brGrades;i++){
            this->grades[i]=s.grades[i];
        }
        this->year=s.year;
    }

    void freeMem(){
        delete [] name;
        delete [] grades;
    }
public:
    Student(char *name="", int year=2001){
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        brGrades=0;
        grades=new int[brGrades];
        this->year=year;
    }

    Student(const Student &s){
        copy(s);
    }

    Student &operator=(const Student &s){
        if(this!=&s){
            freeMem();
            copy(s);
        }
        return *this;
    }

    ~Student(){
        freeMem();
    }

    Student &operator++(){ //prefix ++
        ++year;
        return *this;
    }

    Student operator++(int){ //postfix ++ so dummy int vo argument
        Student result(*this); //ista kopija so this objektot
        ++year;
        return result;
    }

    Student &operator+=(int grade){
        int *tmp=new int[brGrades+1];
        for(int i=0;i<brGrades;i++){
            tmp[i]=grades[i];
        }
        tmp[brGrades++]=grade;
        delete [] grades;
        grades=tmp;
        return *this; //oti objekt vrakja (modificiran objekt), zatoa ima i referenca &
    }

    double getAverage() const{ //metod za prosekot
        if(brGrades==0){
            return 5.0;
        }
        int sum=0;
        for(int i=0;i<brGrades;i++){
            sum+=grades[i];
        }
        return (double)sum/brGrades;
    }

    friend ostream &operator<<(ostream &out, const Student &s){
        out<<s.name<<" "<<s.year<<" "<<s.getAverage()<<endl;
        return out;
    }

    bool operator>(Student &s){
        return this->getAverage()>s.getAverage();
    }
};

class Faculty{
    Student *students;
    int n;

    void copy(const Faculty &f){
        this->n=f.n;
        students=new Student[n];
        for(int i=0;i<n;i++){
            students[i]=f.students[i];
        }
    }
public:
    Faculty(){
        n=0;
        students=new Student[n];
    }

    Faculty(const Faculty &f){
        copy(f);
    }

    Faculty &operator=(const Faculty &f){
        if(this!=&f){
            delete [] students;
            copy(f);
        }
        return *this;
    }

    ~Faculty(){
        delete [] students;
    }

    Faculty &operator+=(const Student &s){
        Student *tmp=new Student[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=students[i];
        }
        tmp[n++]=s;
        delete [] students;
        students=tmp;
        return *this;
    }

    Faculty &operator++(){
        for(int i=0;i<n;i++){
            ++students[i];
        }
        return *this;
    }

    friend ostream &operator<<(ostream &out, const Faculty &f){
        for(int i=0;i<f.n;i++){
            out<<f.students[i];
        }
        return out;
    }

    void prize(){
        for(int i=0;i<n;i++){
            if(students[i].getAverage()==10.0){
                cout<<students[i];
            }
        }
    }

    void highestAverage(){
        Student max=students[0];
        for(int i=0;i<n;i++){
            if(students[i]>max){
                max=students[i];
            }
        }
        cout<<max;
    }
};

int main(){

    Student s("Todor", 1);
    //cout<<s;
    s+=6;
    s+=8;
    s+=10;

    Faculty faculty;
    Student t("DADAD",2);
    t+=10;
    t+=10;
    t+=10;
    t+=10;
    Student r("fsafafaf", 2);
    r+=6;
    r+=8;
    r+=10;
    r+=7;
    faculty+=t;
    faculty+=r;
    cout<<faculty;

    cout<<"-----"<<endl;

    ++faculty;
    cout<<faculty;



    faculty.prize();

 

    faculty.highestAverage();

    return 0;
}
