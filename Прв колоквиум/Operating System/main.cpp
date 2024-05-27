//Фирмата FINKI Cloud има потреба од решение за управување со image датотеките од различните оперативни системи кои ги
//користат при сетирање на нови сервери. За таа цел потребно е да се дефинираат следниве класи:
//
//OperativenSistem Во класата OperativenSistem треба да се чуваат следниве податоци:
//име на оперативниот систем (динамички алоцирана низа од знаци)
//верзија (float)
//тип (енумерација со можни вредности LINUX, UNIX, WINDOWS)
//големина (во GB) (float)
//Дополнително, во рамките на класата потребно е да се дефинира:
//
//конструктори со и без параметри
//        copy constructor
//        destructor
//преоптоварување на операторот =
//метод за печатење на информациите - void pecati() (видете го излезот од тест примерите за структурата)
//метод за проверка на еднаквост помеѓу два оперативни системи (два оперативни системи се еднакви ако имаат исто име, верзија, тип и големина)
//- bool ednakviSe(const OperativenSistem &os)
//метод за споредба на верзии помеѓу два оперативни система - int sporediVerzija(const OperativenSistem &os), кој ќе враќа 0 доколку верзиите се исти,
//-1 доколку верзијата на оперативниот систем од аргументот е поголема и 1 во преостанатиот случај.
//метод за проверка дали два оперативни системи се од иста фамилија. Два оперативни системи се од иста фамилија доколку имаат исто име и се од ист тип.
//bool istaFamilija(const OperativenSistem &sporedba)
//Repozitorium Во класата Repozitorium треба да се чуваат следниве податоци:
//име на репозиториумот (низа од 20 знака)
//динамички алоцирана низа од OperativenSistem
//број на оперативни системи кои моментално се наоѓаат во репозиториумот (int)
//Дополнително, во рамките на класата потребно е да се дефинира:
//конструктор Repozitorium(const char *ime)
//деструктор метод void pecatiOperativniSistemi() кој ќе ги печати сите оперативни системи кои се дел од репозиториумот
//метод void izbrishi(const OperativenSistem &operativenSistem) кој ќе го избрише оперативниот систем проследен како аргумент,
//доколку тој се наоѓа во репозиториумот. Да се користи методот ednakviSe за споредба на два оперативни система.
//метод за додавање на оперативен систем (void dodadi(const OperativenSistem &nov)) кој ќе го има следново однесување:
//Доколку веќе постои оперативен систем од иста фамилија (да се користи методот за проверка на фамилија) кој е постар од проследениот оперативен систем,
//тогаш постоечкиот оперативен систем се заменува со новиот.
//Во секој друг случај, проследениот оперативен систем се додава како дополнителен во репозиториумот.

#include <iostream>
#include <cstring>
using namespace std;

enum Tip{
    LINUX, UNIX, WINDOWS
};

class OperativenSistem{
private:
    char *ime;
    float verzija;
    Tip tip;
    float golemina;
    void copy(const OperativenSistem &os){
        this->ime= new char [strlen(os.ime)+1];
        strcpy(this->ime, os.ime);
        this->verzija=os.verzija;
        this->tip=os.tip;
        this->golemina=os.golemina;
    }
public:
    OperativenSistem(char *ime="ime"){
        this->ime= new char [strlen(ime)+1];
        strcpy(this->ime, ime);
        this->verzija=0;
        this->golemina=0;
    }
    OperativenSistem(char *ime, float verzija, Tip tip, float golemina){
        this->ime= new char [strlen(ime)+1];
        strcpy(this->ime, ime);
        this->verzija=verzija;
        this->tip=tip;
        this->golemina=golemina;
    }
    OperativenSistem(const OperativenSistem &os){
        copy(os);
    }
    OperativenSistem &operator=(const OperativenSistem &os){
        if(this!=&os){
            delete[]ime;
            copy(os);
        }
        return *this;
    }
    ~OperativenSistem(){
        delete[]ime;
    }
    float getVerzija(){return verzija;}
    void pecati(){
        cout<<"Ime: "<<ime<<" Verzija: "<<verzija<<" Tip: "<<tip<<" Golemina:"<<golemina<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os){
        if(strcmp(ime, os.ime)==0){
            if(verzija==os.verzija){
                if(tip==os.tip){
                    if(golemina==os.golemina){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &os){
        if(os.verzija==verzija){
            return 0;
        }
        else if(os.verzija>verzija){
            return -1;
        }
        else{
            return 1;
        }
    }
    bool istaFamilija(const OperativenSistem &sporedba){
        if(strcmp(ime, sporedba.ime)==0){
            if(tip==sporedba.tip){
                return true;
            }
        }
        return false;
    }
};

class Repozitorium{
private:
    char repoName[20];
    OperativenSistem *os;
    int brojOperativniSistemi;
    void copy(const Repozitorium &r){
        strcpy(this->repoName, r.repoName);
        brojOperativniSistemi=r.brojOperativniSistemi;
        for(int i=0; i<brojOperativniSistemi; i++){
            this->os[i]=r.os[i];
        }
    }
public:
    Repozitorium(char *repoName){
        strcpy(this->repoName, repoName);
        brojOperativniSistemi=0;
        os=NULL;
    }
    Repozitorium(const Repozitorium &r){
        copy(r);
    }
    Repozitorium &operator=(const Repozitorium &r){
        if(this!=&r){
            delete[]os;
            copy(r);
        }
        return *this;
    }
    ~Repozitorium(){
        delete[]os;
    }
    void pecatiOperativniSistemi(){
        cout<<"Repozitorium: "<<repoName<<endl;
        for(int i=0; i<brojOperativniSistemi; i++){
            os[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem){
        int j=0;
        for(int i=0; i<brojOperativniSistemi; i++){
            if(!(os[i].ednakviSe(operativenSistem))){
                os[j]=os[i];
                j++;
            }
        }
        brojOperativniSistemi=j;
    }
    void dodadi(const OperativenSistem &nov){
        for(int i=0; i<brojOperativniSistemi; i++){
            if(os[i].istaFamilija(nov)){
                if(os[i].sporediVerzija(nov)==-1){
                    os[i]=nov;
                    return;
                }
            }
        }
        OperativenSistem *oss=new OperativenSistem[brojOperativniSistemi+1];
        for(int i=0; i<brojOperativniSistemi; i++){
            oss[i]=os[i];
        }
        oss[brojOperativniSistemi]=nov;
        delete[]os;
        os=oss;
        brojOperativniSistemi++;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
     cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}