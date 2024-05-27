//Да се дефинира класа Vozac во која се чуваат информации за:
//име (низа од максимум 100 знаци)
//возраст (цел број)
//број на трки (цел број)
//дали е ветеран (да/не).
//Да се преоптоварат:
//
//операторот << за печатење кој ќе ги печати името, возраст, бројот на трки и дали е ветеран (се печати VETERAN)
//операторот == за споредување на два возачи според заработувачката по трка.
//Од оваа класа да се изведат две нови класи Avtomobilist и Motociklist.
//
//За автомобилистот дополнително се чува:
//
//цена на автомобилот (децимален број).
//За мотоциклистот дополнително се чува:
//
//моќност на мотор (цел број).
//Заработувачката по трка на возачите се пресметува како:
//
//за автомобилостот заработувачката по трка е $\frac{CENA_{AVTOMOBIL}}{5}$
//        за мотоциклистот заработувачката по трка е $MOKJNOST_NA_MOTOR * 20$
//Секој автомобилист плаќа данок на заработка. Да се напишат соодветни методи за пресметување данок:
//
//за автомобилисти: ако бројот на трки е поголем од 10 стапката на данок е 15% од заработката, инаку 10% од заработката.
//за мотоциклисти: ако е ветеран стапката на данок е 25% од заработката, инаку 20% од заработката.
//Да се напше надворешна функција soIstaZarabotuvachka која како аргументи прима низа од покажувачи од класата Vocac,
//нивниот број, како и покажувач кон ојбект од возач и враќа како резултат бројот на возачи кои имаат иста заработувачка по трка со проследениот возач.

#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

class Vozac{
protected:
    char name[100];
    int age, num;
    bool veteran;
    void copy(const Vozac &v){
        strcpy(this->name, v.name);
        this->age=v.age;
        this->num=v.num;
        this->veteran=v.veteran;
    }
public:
    Vozac(char *name, int age, int num, bool veteran){
        strcpy(this->name, name);
        this->age=age;
        this->num=num;
        this->veteran=veteran;
    }
    Vozac(const Vozac &v){
        copy(v);
    }
    Vozac &operator=(const Vozac &v){
        if(this!=&v){
            copy(v);
        }
        return *this;
    }
    ~Vozac(){}
    virtual int zarabotuvacka()=0;
    virtual int danok()=0;
    friend ostream &operator<<(ostream &out, const Vozac &v){
        out<<v.name<<endl<<v.age<<endl<<v.num<<endl;
        if(v.veteran){
            out<<"VETERAN"<<endl;
        }
        return out;
    }
    bool operator==(Vozac &v1){
        return (this->zarabotuvacka()==v1.zarabotuvacka());
    }
};

class Avtomobilist:public Vozac{
private:
    float cena;
public:
    Avtomobilist(char *name, int age, int num, bool veteran, float cena): Vozac(name, age, num, veteran){
        this->cena=cena;
    }
    Avtomobilist(const Vozac &v, float cena): Vozac(v){
        this->cena=cena;
    }
    int zarabotuvacka(){
        return cena/5;
    }
    int danok(){
        if (num > 10) {
            return (zarabotuvacka()*0.15);
        }
        else {
            return (zarabotuvacka()*0.10);
        }
    }
};

class Motociklist:public Vozac{
private:
    int power;
public:
    Motociklist(char *name, int age, int num, bool veteran, int power): Vozac(name, age, num, veteran){
        this->power=power;
    }
    Motociklist(const Vozac &v, int power): Vozac(v){
        this->power=power;
    }
    int zarabotuvacka(){
        return power*20;
    }
    int danok(){
        if(veteran){
            return (zarabotuvacka()*0.25);
        }
        else{
            return (zarabotuvacka()*0.20);
        }
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx){
    int brojach=0;
    for(int i=0; i<n; i++){
        if(*v[i]==*vx){
            brojach++;
        }
    }
    return brojach;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}