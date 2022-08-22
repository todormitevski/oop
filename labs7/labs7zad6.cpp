#include <iostream>
#include <string.h>
using namespace std;

class Task{
protected:
    //deklariranje na promenlivite
    char ID[5];
public:
    //konstruktor
    Task(char *ID=""){
        strcpy(this->ID,ID);
    }
    //destruktor
    ~Task(){}
    //2 chisto virtuelni metodi (print i getOrder)
    virtual int getOrder()=0;
    virtual void print()=0;

    char *getID(){
        return ID;
    }
};

//Preoptovaruvanje na operatorot za sporedba == (prima 2 argumenti bidejki se definira nadvor od klasata Task)
bool operator==(Task *t, Task &t1){
    return (!strcmp(t->getID(),t1.getID())) && (t->getOrder()==t1.getOrder());
}

class TimedTask: public Task{//izraz za nasleduvanje od Task
private:
    //deklariranje na dopolnitelni promenlivi
    int time;
public:
    //konstruktor
    TimedTask(char *ID="", int time=0): Task(ID){
        this->time=time;
    }
    //prepokrivanje na 2ta metodi shto se nasleduvaat od Task
    int getOrder(){
        return time;
    }

    void print(){
        cout<<"TT->"<<ID<<":"<<time<<endl;
    }
};

class PriorityTask: public Task{
private:
    //deklariranje na dopolnitelni promenlivi
    int priority;
public:
    //konstruktor
    PriorityTask(char *ID="", int priority=0): Task(ID){
        this->priority-priority;
    }
    //prepokrivanje na 2ta metodi shto se nasleduvaat od Task
    int getOrder(){
        return priority;
    }

    void print(){
        cout<<"PT->"<<ID<<":"<<priority<<endl;
    }
};

void _sort(Task** ptr_arr, int n) {
    for (unsigned int i = 0; i < n - 1; i++) {
        for (unsigned int j = i + 1; j < n - 1; j++) {
            if (ptr_arr[i]->getOrder() > ptr_arr[j]->getOrder()) {
                Task* tmp = ptr_arr[i]; ptr_arr[i] = ptr_arr[j]; ptr_arr[j] = tmp;
            }
        }
    }
}

//wtf.
void scheduleTimedTasks(Task** ptr_arr, int n, int var) {
    _sort(ptr_arr, n); for (unsigned int i = 0; i < n; i++) { if (dynamic_cast<PriorityTask*>(ptr_arr[i]) == NULL && ptr_arr[i]->getOrder() < var) { ptr_arr[i]->print(); } }
}

void schedulePriorityTasks(Task** ptr_arr, int n, int var) {
    _sort(ptr_arr, n); for (unsigned int i = 0; i < n; i++) { if (dynamic_cast<TimedTask*>(ptr_arr[i]) == NULL && ptr_arr[i]->getOrder() < var) { ptr_arr[i]->print(); } }
}

int main () {
    int testCase;
    int n;
    cin>>testCase;

    if (testCase==0){
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }

        cout<<"SCHEDULING PRIORITY TASKS WITH PRIORITY DEGREE LESS THAN 10"<<endl;
        schedulePriorityTasks(tasks,n,10);

    }
    else if (testCase==1) {
        cin>>n;
        Task ** tasks;
        tasks = new Task * [n];
        for (int i=0;i<n;i++){
            char id [5];
            int timeOrPriority;
            int type; //0 za timed, 1 za priority
            cin >> type >>id >> timeOrPriority;
            if (type==0)
                tasks[i] = new TimedTask(id,timeOrPriority);
            else
                tasks[i] = new PriorityTask(id,timeOrPriority);
            //tasks[i]->print();
        }


        cout<<"SCHEDULING TIMED TASKS WITH EXECUTION TIME LESS THAN 50"<<endl;
        scheduleTimedTasks(tasks,n,50);
    }
    else {
        TimedTask * tt1 = new TimedTask("11",10);
        TimedTask * tt2 = new TimedTask("11",11);
        TimedTask * tt3 = new TimedTask("11",11);
        PriorityTask * pp1 = new PriorityTask("aa",10);
        PriorityTask * pp2 = new PriorityTask("11",10);

        cout << (tt1==(*tt2))<<endl;
        cout << (tt2==(*tt3))<<endl;
        cout << (pp1==(*pp2))<<endl;
        cout << (pp2==(*tt1))<<endl;
    }

    return 0;
}