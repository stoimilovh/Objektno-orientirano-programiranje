//Да се креира класа која претставува слика (Image) во рамките на еден компјутер. За секоја датотека се чуваат (5 поени):
//
//име на сликата (дин. алоцирана низа од знаци). Предефинирано поставено на untitled.
//име на корисникот кој е сопственик на датотеката (низа од макс. 50 знаци). Предефинирано поставено на unknown.
//димензии на сликата (2 цели броеви кои претставуваат ширина и висина во пиксели). Предефинирано поставени на 800.
//Од класата Imageда се изведе класата TransparentImage, која претставува слика која содржи поддржува транспарентност.
//За транспарентна слика дополнително се чува :
//
//дали поддржува нивоа на транспарентност (bool променлива, предефинирано не поддржува транспарентност).
//За класите Image и TransparentImage да биде достапна метода (fileSize)за пресметка на големината на сликата (во бајти).
//Големината се пресметува на сл. начин (5 поени):
//
//за објектите од класата Image, големината на датотеката е еднаква на:висината * ширината * 3.
//за TransparentImage, доколку поддржува нивоа на транспарентност, големината на датотеката е еднаква на ширина * висина * 4.
//Доколку не поддржува транспарентност, големината на сликата се пресметува како ширина * висина + бр._на_пиксели_присутни_во_сликата / 8.
//За класите Image и TransparentImage да се преоптоварат следниве оператори (5 поени):
//
//оператор << кој ги печати податоците од датотеката во сл. формат:
//
//ime_fajl avtor golemina_na_fajlot_vo_bajti
//
//        оператор > кој ги споредува сликите според нивната големина.
//
//Да се дефинира класа Folder, што репрезентира директориум во кој може да се поставуваат слики. За секој фолдер се чува (5 поени):
//
//име на фолдерот (низа од макс 255 знаци)
//име на корисникот кој е сопственик на фолдерот (низа од макс. 50 знаци). Предефинирано поставено на unknown.
//низа од покажувачи кон Image објекти (макс. 100 во рамките на еден фолдер).
//Да се имплементираат следниве методи (5 поени):
//метода за пресметка на големината на фолдерот (folderSize). Големината на фолдерот е сума од големините од сите слики во рамките на фолдерот.
//метода за пронаоѓање на наголемата слика во рамките на фолдерот (getMaxFile). Методата враќа покажувач кон најголемата слика во фолдерот (сметано во бајти).
//За класата Folder да се имплементира и оператор += кој додава објекти од типот Image/TransparentImage во рамките на фолдерот (5 поени).
//Да се креираат следниве функционалности за класите (5 поени):
//operator << - со кој се печатат податоците за фолдерот во формат (5 поени):
//ime_folder sopstvenik --
//imeslika avtor goleminanafajlotvo_bajti
//        imeslika avtor goleminanafajlotvobajti -- goleminanafoldervo_bajti
//        operator [] - кој враќа покажувач кон соодветната слика во фолдерот. Доколку не постои слика на тој индекс, треба да се врати NULL (5 поени).
//
//Да се креира и глобална функција max_folder_size која го прима низа од објекти од типот Folder и го
//враќа фолдерот кој има зафаќа најмногу простор (во бајти). (5 поени)
//
//Да се овозможи правилно функционирање на класите (потребни set или get методи/оператори/конструктори/деструктори)
//според изворниот код кој е веќе зададен. Сите податочни членови на класите се protected. (5 поени)

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// TODO...
class Image{
protected:
    char *name;
    char korisnik[50];
    int visina, sirina;
public:
    Image(const char *name="untitled", const char *korisnik="unknown", int visina=800, int sirina=800){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->korisnik, korisnik);
        this->visina=visina;
        this->sirina=sirina;
    }
    virtual ~Image(){
        delete[]name;
    }
    virtual int filesize(){
        return (visina*sirina)*3;
    }
    friend ostream &operator<<(ostream &out, Image &i){
        return out<<i.name<<" "<<i.korisnik<<" "<<i.filesize()<<endl;
    }
};

class TransparentImage:public Image{
private:
    bool dali;
public:
    TransparentImage(const char *name="untitled", const char *korisnik="unknown", int visina=800, int sirina=800, bool dali= true):Image(name, korisnik, visina, sirina){
        this->dali=dali;
    }
    int filesize(){
        if(dali){
            return visina*sirina*4;
        }
        else{
            return visina*sirina+(visina*sirina/8);
        }
    }
    friend ostream &operator<<(ostream &out, TransparentImage &ti){
        return out<<ti.name<<" "<<ti.korisnik<<" "<<ti.filesize()<<endl;
    }
};

class Folder{
private:
    char name[300], korisnik[50];
    Image **im;
    int num;
public:
    Folder(const char *name="", const char *korisnik="unknown", Image **im= nullptr, int num=0){
        strcpy(this->name, name);
        strcpy(this->korisnik, korisnik);
        this->im=im;
        this->num=0;
    }
    ~Folder(){
        for(int i=0; i<num; i++){
            delete im[i];
        }
        delete[]im;
    }
    int foldersize(){
        int broj=0;
        for(int i=0; i<num; i++){
            broj+=im[i]->filesize();
        }
        return broj;
    }
    Image *getMaxFile(){
        int max=0, ind=0;
        for(int i=0; i<num; i++){
            if(im[i]->filesize()>max){
                max=im[i]->filesize();
                ind=i;
            }
        }
        return im[ind];
    }
    Image *operator[](int n){
        if(n>=0&&n<num){
            return im[n];
        }
        else{
            return nullptr;
        }
    }
    Folder &operator+=(Image &img){
        Image **imm=new Image * [num+1];
        for(int i=0; i<num; i++){
            imm[i]=im[i];
        }
        imm[num]=&img;
        delete[]im;
        im=imm;
        num++;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Folder &f){
        out<<f.name<<" "<<f.korisnik<<endl;
        out<<"--"<<endl;
        for(int i=0; i<f.num; i++){
            cout<<*f.im[i];
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.foldersize()<<endl;
        return out;
    }
};

Folder &max_folder_size(Folder *dir, int n){
    int max=0, ind=0;
    for(int i=0; i<n; i++){
        if(dir[i].foldersize()>max){
            max=dir[i].foldersize();
            ind=i;
        }
    }
    return dir[ind];
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
