#include <iostream>
#include <string.h>
using namespace std;

enum Extension{
    txt=0,
    pdf,
    exe
};

class File{
    char *ime;
    Extension ekstenzija;
    char *imeUser;
    int golemina;

    void copy(const File &f){
        this->ime=new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->ekstenzija=f.ekstenzija;
        this->imeUser=new char[strlen(f.imeUser)+1];
        strcpy(this->imeUser,f.imeUser);
        this->golemina=f.golemina;
    }

    void freeMem(){
        delete [] ime;
        delete [] imeUser;
    }
public:
    File(char *ime="", char *imeUser="", int golemina=0, Extension ekstenzija=Extension(0)){
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->ekstenzija=ekstenzija;
        this->imeUser=new char[strlen(imeUser)+1];
        strcpy(this->imeUser,imeUser);
        this->golemina=golemina;
    }

    File(const File &f){
        copy(f);
    }

    File &operator=(const File &f){
        if(this!=&f){
            freeMem();
            copy(f);
        }
        return *this;
    }

    ~File(){
        freeMem();
    }

    bool equals(const File &that){
        if(!strcmp(ime,that.ime) && ekstenzija==that.ekstenzija && !strcmp(imeUser,that.imeUser)){
            return true;
        } else return false;
    }

    bool equalsType(const File &that){
        if(!strcmp(ime, that.ime) && ekstenzija==that.ekstenzija){
            return true;
        } else return false;
    }

    void print(){
        cout<<"File name: "<<ime;
        if(ekstenzija==1){
            cout<<".txt"<<endl;
        } else if(ekstenzija==0){
            cout<<".pdf"<<endl;
        } else{
            cout<<".exe"<<endl;
        }
        cout<<"File owner: "<<imeUser<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
};

class Folder{
    char *imeFolder;
    int brFiles;
    File *files;

    void freeMem(){
        delete [] imeFolder;
        delete [] files;
    }
public:
    Folder(){
        brFiles=0;
        files=nullptr;
    }

    Folder(const char *imeFolder){
        this->imeFolder=new char[strlen(imeFolder)+1];
        strcpy(this->imeFolder,imeFolder);
    }

    ~Folder(){
        freeMem();
    }

//    void print(){
//        cout<<"testing"<<endl; //ne e dadeno vo primerot kako da pecatis
//    }

    void print(){
        cout<<"Folder name: "<<imeFolder<<endl;
        for(int i=0; i<brFiles; i++){
            files[i].print();
        }
    }

//    void remove(const File &file){
//        for(int i=0;i<brFiles;i++){
//            if(files[i].equals(file)){
//                delete files[i];
//                return;
//            }
//        }
//    }

    void remove(File &file){
        for(int i=0;i<brFiles;i++){
            if(files[i].equals(file)){
                --brFiles;
                for(int j=i; j<brFiles; j++){
                    this->files[j] = this->files[j+1];
                } break;
            }
        }
    }

    void add(const File &file){
        File *tmp = new File[brFiles+1];
        for(int i=0;i<brFiles;i++){
            tmp[i]=files[i];
        }
        tmp[brFiles++]=file;
        delete [] files;
        files=tmp;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS AND EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}