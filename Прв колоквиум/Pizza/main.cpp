//Да се дефинира класа Пица за која ќе се чуваат податоци за:
//
//име на пицата (низа од 15 знаци)
//цена (цел број)
//состојки (динамички алоцирана низа од знаци)
//намалување на цената во проценти (цел број) - ако пицата не е на промоција намалувањето има вредност нула,
//во спротивно,вредност поголема од нула и не поголема од 100.
//За потребите на оваа класа да се креираат потребните конструктори и да се напише соодветен деструктор.
//Дополнително за оваа класа да се дефинира функцијата:
//
//pecati() - функција во која ќе се печатат податоците за пицата во следниот формат: име - состојки, цена.
//istiSe(Pica p) - функција за споредба на две пици според состојките :
//Да се дефинира класа Picerija во која се чуваат:
//
//име (низа од максимум 15 знаци)
//динмички алоцирана низа од објекти од класата Pica
//број на пици (цел број)
//За потребите на оваа класа да се дефинираат потребните конструктори и да се напише соодветен деструктор.
//Да се имплементираат и следниве методи:
//
//dodadi(Pica P) - за додавање нова пица во пицеријата, но само ако не постои иста во низата
//(нема пица со исти состојки со пицата што треба да се додаде).
//void piciNaPromocija() - се печатат сите пици од пицеријата што се на промоција во формат : име - состојки, цена, цена со попуст.

#include <iostream>
#include <cstring>
using namespace std;

class Pica{
private:
    char imp[15];
    int cena;
    char *sostojki;
    int popust;
    void copy(const Pica &p){
        strcpy(this->imp, p.imp);
        this->cena=p.cena;
        this->sostojki=new char [strlen(p.sostojki)+1];
        strcpy(this->sostojki, p.sostojki);
        this->popust=p.popust;
    }
public:
    Pica(char *imp="pica", int cena=0, const char *sostojki="", int popust=0){
        strcpy(this->imp, imp);
        this->cena=cena;
        this->sostojki=new char [strlen(sostojki)+1];
        strcpy(this->sostojki, sostojki);
        this->popust=popust;
    }
    Pica(const Pica &p){
        copy(p);
    }
    Pica & operator=(const Pica &p){
        if(this!=&p){
            delete[]sostojki;
            copy(p);
        }
        return *this;
    }
    ~Pica(){
        delete[]sostojki;
    }
    int getCena(){return cena;}
    void *getSostojki(){return sostojki;}
    int getProcent(){return popust;}
    void pecati(){
        cout<<imp<<" - "<<sostojki<<", "<<cena;
    }
    bool istiSe(Pica p){
        return strcmp(sostojki, p.sostojki)==0;
    }
};

class Picerija{
private:
    char ime[15];
    Pica *p;
    int n;
    void copy(const Picerija &pp){
        strcpy(ime, pp.ime);
        n=pp.n;
        p=new Pica[n];
        for(int i=0; i<n; i++){
            p[i]=pp.p[i];
        }
    }
public:
    Picerija(const char *ime=""){
        strcpy(this->ime, ime);
        p=NULL;
        n=0;
    }
    Picerija(Picerija &pp){
        copy(pp);
    }
    Picerija & operator=(const Picerija &pp){
        if(this!=&pp){
            delete[]p;
            copy(pp);
        }
        return *this;
    }
    ~Picerija(){
        delete[]p;
    }
    char *getIme(){return ime;}
    void setIme(const char *ime){
        strcpy(this->ime, ime);
    }
    void dodadi(Pica r){
        int temp=1;
        for(int i=0; i<n; i++){
            if(p[i].istiSe(r)){
                temp=0;
            }
        }
        if(temp){
            Pica *tmp = new Pica[n+1];
            for(int i=0; i<n; i++){
                tmp[i]=p[i];
            }
            tmp[n]=r;
            delete[]p;
            p=tmp;
            n++;
        }
    }
    void piciNaPromocija(){
        for(int i=0; i<n; i++){
            if(p[i].getProcent()>0){
                p[i].pecati();
                cout<<" "<<p[i].getCena()*(1-p[i].getProcent()/100.0)<<endl;
            }
        }
    }
};

int main(){
    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1.dodadi(p);
    }
    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2.dodadi(p);

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();
    return 0;
}