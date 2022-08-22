#include <iostream>
#include <string.h>
using namespace std;

class Employee{
protected:
    char *ime;
    int godini;
    int iskustvo;

    void copy(const Employee &e){
        this->ime=new char[strlen(e.ime)+1];
        strcpy(this->ime,e.ime);
        this->godini=e.godini;
        this->iskustvo=e.iskustvo;
    }
public:
    Employee(char *ime="", int godini=0, int iskustvo=0){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->godini=godini;
        this->iskustvo=iskustvo;
    }

    Employee(const Employee &e){
        copy(e);
    }

    Employee &operator=(const Employee &e){
        if(this!=&e){
            delete [] ime;
            copy(e);
        }
    }

    ~Employee(){
        delete [] ime;
    }

    virtual double plata()=0;
    virtual double bonus()=0;

    int getGodini(){
        return godini;
    }
};

class SalaryEmployee: public Employee{
    int salary;
public:
    SalaryEmployee(char *ime="", int godini=0, int iskustvo=0, int salary=0): Employee(ime,godini,iskustvo){
        this->salary=salary;
    }

    SalaryEmployee(const SalaryEmployee &e): Employee(e){
        this->salary=e.salary;
    }

    double bonus(){
        //return (salary/iskustvo)*100;
        return salary*(iskustvo/100.0);
    }

    double plata(){
        return salary+bonus();
    }
};

class HourlyEmployee: public Employee{
    int casovi;
    int salaryPerHour;
public:
    HourlyEmployee(char *ime="", int godini=0, int iskustvo=0, int casovi=0, int salaryPerHour=0): Employee(ime,godini,iskustvo){
        this->casovi=casovi;
        this->salaryPerHour=salaryPerHour;
    }

    HourlyEmployee(const HourlyEmployee &e): Employee(e){
        this->casovi=e.casovi;
        this->salaryPerHour=e.salaryPerHour;
    }

//    double bonus(){
//        int tmp = this->hoursWorked - 320;
//        double sum = 0.00;
//        if (tmp > 0){
//            while (tmp){
//                sum += this->hourlyPay * 0.5;
//                tmp--;
//            }
//        }
//        return sum;
//    }

    double bonus(){
        int tmp=casovi;
        double suma=0.0;
        if(casovi>320){
            tmp-=320;
            while(tmp){
                suma+=salaryPerHour*0.5; //se dobiva 50% od salaryPerHour
                tmp--;
            }
        }
        return suma;
    }

    double plata(){
        return casovi*salaryPerHour+bonus();
    }
};

class Freelancer: public Employee{
    int brProekti;
    double *projects;
public:
    Freelancer(){}

    Freelancer(char *ime, int godini, int iskustvo, int brProekti, double *projects): Employee(ime,godini,iskustvo){
        this->brProekti=brProekti;
        this->projects=new double[brProekti];
        for(int i=0;i<brProekti;i++){
            this->projects[i]=projects[i];
        }
    }

    Freelancer(const Freelancer &e): Employee(e){
        this->brProekti=e.brProekti;
        this->projects=new double[e.brProekti];
        for(int i=0;i<e.brProekti;i++){
            this->projects[i]=e.projects[i];
        }
    }

    double bonus(){
        double bonusot=0.0;
        int tmp=brProekti;
        if(brProekti>5){
            tmp-=5;
            while(tmp){
                bonusot+=1000;
                tmp--;
            }
        }
        return bonusot;
    }

    double plata(){
        double suma=0.0;
        for(int i=0;i<brProekti;i++){
            suma+=projects[i];
        }
        return suma+bonus();
    }
};

bool operator==(Employee &e, Employee &e1){ //2 objekti da prima, mora da bide globalna funkcija i zatoa treba i getGodini() metod
    return e.getGodini()==e1.getGodini();
}

class Company{
    char *imeCompany;
    int brVraboteni;
    Employee **employees;
public:
    Company(char *imeCompany=""){
        this->imeCompany=new char[strlen(imeCompany)+1];
        strcpy(this->imeCompany,imeCompany);
        this->brVraboteni=0;
        this->employees=new Employee *[brVraboteni];
    }

    ~Company(){
        delete [] imeCompany;
        delete [] employees;
    }

    Company &operator+=(Employee *e){
        Employee **tmp= new Employee *[brVraboteni+1];
        for(int i=0;i<brVraboteni;i++){
            tmp[i]=employees[i];
        }
        tmp[brVraboteni++]=e;
        delete [] employees;
        employees=tmp;
        return *this;
    }

    double vkupnaPlata(){
        double vkPlata=0.0;
        for(int i=0;i<brVraboteni;i++){
            vkPlata+=employees[i]->plata();
        }
        return vkPlata;
    }

    double filtriranaPlata(Employee * emp){
        double vkPlata=0.0;
        for(int i=0;i<brVraboteni;i++){
            if(*employees[i]==*emp){
                vkPlata+=employees[i]->plata();
            }
        }
        return vkPlata;
    }

    void pecatiRabotnici(){
        int brSalary=0, brHourly=0, brFreelance=0;
        for(int i=0;i<brVraboteni;i++){
            if(dynamic_cast<SalaryEmployee *>(employees[i])){
                brSalary++;
            } else if(dynamic_cast<HourlyEmployee *>(employees[i])){
                brHourly++;
            } else brFreelance++;
        }

        cout<<"Vo kompanijata "<<imeCompany<<" rabotat:"<<endl;
        cout<<"Salary employees: "<<brSalary<<endl;
        cout<<"Hourly employees: "<<brHourly<<endl;
        cout<<"Freelancers: "<<brFreelance<<endl;
    }
};

int main() {

    char name[50];
    cin >> name;
    Company c(name);

    int n;
    cin >> n;

    char employeeName[50];
    int age;
    int experience;
    int type;

    for (int i=0; i <n; ++i) {
        cin >> type;
        cin >> employeeName >> age >> experience;

        if (type == 1) {
            int basicSalary;
            cin >> basicSalary;
            c += new SalaryEmployee(employeeName, age, experience, basicSalary);
        }

        else if (type == 2) {
            int hoursWorked;
            int hourlyPay;
            cin >> hoursWorked >> hourlyPay;
            c += new HourlyEmployee(employeeName, age, experience, hoursWorked, hourlyPay);
        }

        else {
            int numProjects;
            cin >> numProjects;
            double projects[10];
            for (int i=0; i < numProjects; ++i) {
                cin >> projects[i];
            }
            c += new Freelancer(employeeName, age, experience, numProjects, projects);
        }
    }

    c.pecatiRabotnici();
    cout << "Vkupnata plata e: " << c.vkupnaPlata() << endl;
    Employee * emp = new HourlyEmployee("Petre_Petrov",31,6,340,80);
    cout << "Filtriranata plata e: " << c.filtriranaPlata(emp);

    delete emp;
}