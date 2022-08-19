#include <iostream>
using namespace std;

class List{
    int *broevi;
    int brBroevi;

    void copy(const List &l){
        this->brBroevi=l.brBroevi;
        this->broevi=new int[l.brBroevi];
        for(int i=0;i<l.brBroevi;i++){
            this->broevi[i]=l.broevi[i];
        }
    }
public:
    List(int *broevi=nullptr, int brBroevi=0){
        this->brBroevi=brBroevi;
        this->broevi=new int[brBroevi];
        for(int i=0;i<brBroevi;i++){
            this->broevi[i]=broevi[i];
        }
    }

    List(const List &l){
        copy(l);
    }

    List &operator=(const List &l){
        if(this!=&l){
            delete [] broevi;
            copy(l);
        }
        return *this;
    }

    ~List(){
        delete [] broevi;
    }

    int getBrBroevi(){
        return brBroevi;
    }

    int sum(){
        int sum=0;
        for(int i=0;i<brBroevi;i++){
            sum+=broevi[i];
        }
        return sum;
    }

    double average(){
        return (double)sum()/brBroevi;
    }

    void pecati(){
        int suma=sum();
        int avg=average();
        cout<<brBroevi<<": ";
        for(int i=0;i<brBroevi;i++){
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<suma<<" average: "<<avg<<endl;
    }
};

class ListContainer{
    List *listi;
    int brListi;
    int brObidi;

    void copy(const ListContainer &l){
        this->brListi=l.brListi;
        this->listi=new List[l.brListi];
        for(int i=0;i<l.brListi;i++){
            this->listi[i]=l.listi[i];
        }
        this->brObidi=l.brObidi;
    }
public:
//    ListContainer(List *listi=nullptr, int brListi=0, int brObidi=0){
//        this->brListi=brListi;
//        this->listi=new List[brListi];
//        for(int i=0;i<brListi;i++){
//            this->listi[i]=listi[i];
//        }
//        this->brObidi=brObidi;
//    }

    ListContainer(){
        this->brListi=0;
        this->brObidi=0;
        listi=nullptr;
    }

    ListContainer(List *listi, int brListi, int brObidi){
        this->brListi=brListi;
        this->brObidi=brObidi;
        this->listi=new List[brListi];
        for(int i=0;i<brListi;i++){
            this->listi[i]=listi[i];
        }
    }

    ListContainer(const ListContainer &l){
        copy(l);
    }

    ListContainer &operator=(const ListContainer &l){
        if(this!=&l){
            delete [] listi;
            copy(l);
        }
        return *this;
    }

    ~ListContainer(){
        delete [] listi;
    }

    int sum(){
        int sumaTotal=0;
        for(int i=0;i<brListi;i++){
            sumaTotal+=listi[i].sum();
        }
        return sumaTotal;
    }

    double average(){
        double averageTotal=0.0;
        int brElemTotal=0;
        for(int i=0;i<brListi;i++){
            averageTotal+=listi[i].average();
            brElemTotal+=listi[i].getBrBroevi();
        }
        return averageTotal/brElemTotal;
    }

    void addNewList(List l){
        List *tmp=new List[brListi+1];
        for(int i=0;i<brListi;i++){
            if(listi[i].sum()==l.sum()){
                brObidi++;
                return;
            }
            tmp[i]=listi[i];
        }
        tmp[brListi++]=l;
        delete [] listi;
        listi=tmp;
    }

    void print(){
        if(brListi==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0;i<brListi;i++){
            cout<<"List number: "<<i+1<<" List info: ";
            listi[i].pecati();
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average();
        cout<<endl<<"Successful attempts: "<<brListi<<" Failed attempts: "<<brObidi;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}