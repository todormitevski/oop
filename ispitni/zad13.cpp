#include <iostream>
#include <cstring>
using namespace std;

class Image{
protected:
    char *imeSlika;
    char imeUser[50];
    int sirina,visina;
public:
    Image(char *imeSlika="untitled", char *imeUser="unknown", int sirina=800, int visina=800){
        this->imeSlika=new char[strlen(imeSlika)];
        strcpy(this->imeSlika,imeSlika);
        strcpy(this->imeUser,imeUser);
        this->sirina=sirina;
        this->visina=visina;
    }

    virtual int fileSize(){
        return visina*sirina*3;
    }

    friend ostream &operator<<(ostream &out, Image &i){
        return out<<i.imeSlika<<" "<<i.imeUser<<" "<<i.fileSize()<<endl;
    }

    bool operator>(Image &i){
        return fileSize()>i.fileSize();
    }
};

class TransparentImage: public Image{
protected:
    bool transparent;
public:
    TransparentImage(char *imeSlika="untitled", char *imeUser="unknown", int sirina=800, int visina=800, bool transparent=true): Image(imeSlika,imeUser,sirina,visina){
        this->transparent=transparent;
    }

    int fileSize(){
        if(transparent==true){
            return visina*sirina*4;
        } else return visina*sirina+(visina*sirina)/8;
    }

    friend ostream &operator<<(ostream &out, TransparentImage &i){
        return out<<i.imeSlika<<" "<<i.imeUser<<" "<<i.fileSize()<<endl;
    }

    bool operator>(TransparentImage &i){
        return fileSize()>i.fileSize();
    }
};

class Folder{
protected:
    char imeFolder[255];
    char imeKorisnikFolder[50];
    Image *images[100];
    int brImages;
public:
    Folder(char *imeFolder="", char *imeKorisnikFolder="unknown"){
        strcpy(this->imeFolder,imeFolder);
        strcpy(this->imeKorisnikFolder,imeKorisnikFolder);
    }

    int folderSize(){
        int sum=0;
        for(int i=0;i<brImages;i++){
            sum+=images[i]->fileSize();
        }
        return sum;
    }

    Image *getMaxFile(){
        int max=0;
        int maxIndex=0;
        for(int i=0;i<brImages;i++){
            if(images[i]->fileSize()>max){
                max=images[i]->fileSize();
                maxIndex=i;
            }
        }
        return images[maxIndex];
    }

    Folder &operator+=(Image &f){
        images[brImages]=&f;
        brImages++;
        return *this;
    }

    friend ostream &operator<<(ostream &out, Folder &f){
        out<<f.imeFolder<<" "<<f.imeKorisnikFolder<<endl;
        out<<"--"<<endl;
        for(int i=0;i<f.brImages;i++){
            out<<*f.images[i];
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }

    Image *operator[](int index){
        if(index<0 || index>=brImages){
            return NULL;
        } else return images[index];
    }
};

Folder &max_folder_size(Folder *folderi, int n){
    int maxSize=0, maxIndex=0;
    for(int i=0;i<n;i++){
        if(folderi[i].folderSize()>maxSize){
            maxSize=folderi->folderSize();
            maxIndex=i;
        }
    }
    return folderi[maxIndex];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};