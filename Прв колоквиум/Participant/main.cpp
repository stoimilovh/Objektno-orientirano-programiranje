//Да се дефинира класа Ucesnik за учесник во маратон за кој ќе се чуваат информации за:
//
//име (динамички алоцирана низа од знаци)
//пол (bool)
//возраст (цел број) (5 поени).
//За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор. (10 поени)
//
//Дополнително за оваа класа да се преоптоварат:
//оператор за споредување > (споредува двајца учесници според возраста) (5 поени)
//операторот за проследување на излезен тек << кој ќе ги печати името, полот (машки/женски) и возраста, секој во посебен ред. (5 поени)
//Да се дефинира класа Maraton за кој се чуваат:
//
//локација (низа од максимум 100 знаци)
//низа од Ucesnik објекти (динмички алоцирана низа од објекти од класата Ucesnik)
//број на учесници (цел број) (5 поени).
//За потребите на оваа класа да се преоптоварат потребните конструктори и да се напише соодветен деструктор.
//(10 поени) Исто така да се имплементираат следните методи:
//
//оператор += за додавање нов Ucesnik на маратонот Maraton. (10 поени)
//prosecnoVozrast() вреќа просечена возраст на учесниците на маратонот (5 поени)
//pecatiPomladi(Ucesnik &u) ги печати сите учесници помлади од учесникот проследен како аргумент на методот. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde
class Ucesnik{
private:
    char *name;
    bool pol;
    int age;
    void copy(const Ucesnik &u){
        this->name=new char[strlen(u.name)+1];
        strcpy(this->name, u.name);
        this->pol=u.pol;
        this->age=u.age;
    }
public:
    Ucesnik (const char *name="kiko", bool pol=true, int age=25){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->pol=pol;
        this->age=age;
    }
    Ucesnik(char *name, bool pol, int age){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        this->pol=pol;
        this->age=age;
    }
    Ucesnik(const Ucesnik &u){
        copy(u);
    }
    Ucesnik &operator=(const Ucesnik &u){
        if(this!=&u){
            delete[]name;
            copy(u);
        }
        return *this;
    }
    ~Ucesnik(){
        delete[]name;
    }
    friend bool operator>(const Ucesnik &u1, const Ucesnik &u2){
        return (u1.age>u2.age);
    }
    friend ostream& operator<<(ostream &out, const Ucesnik &u){
        out<<u.name<<endl;
        if(u.pol==0){
            out<<"zhenski"<<endl;
        }
        else{
            out<<"mashki"<<endl;
        }
        out<<u.age<<endl;
        return out;
    }
    int getAge(){return age;}
};

class Maraton{
private:
    char lokacija[100];
    Ucesnik *u;
    int num;
    void copy(const Maraton &m){
        strcpy(this->lokacija, m.lokacija);
        this->num=m.num;
        for(int i=0; i<num; i++){
            u[i]=m.u[i];
        }
    }
public:
    Maraton(char *lokacija){
        strcpy(this->lokacija, lokacija);
        this->num=0;
        u=NULL;
    }
    Maraton(const Maraton &m){
        copy(m);
    }
    Maraton &operator=(const Maraton &m){
        if(this!=&m){
            delete[]u;
            copy(m);
        }
        return *this;
    }
    ~Maraton(){
        delete[]u;
    }
    Maraton &operator+=(const Ucesnik &urr){
        Ucesnik *uu=new Ucesnik[num+1];
        for(int i=0; i<num; i++){
            uu[i]=u[i];
        }
        uu[num]=urr;
        delete[]u;
        u=uu;
        num++;
        return *this;
    }
    double prosecnoVozrast(){
        double broj=0;
        for(int i=0; i<num; i++){
            broj+=u[i].getAge();
        }
        return (double)broj/num;
    }
    void pecatiPomladi(const Ucesnik &ur){
        for(int i=0; i<num; i++){
            if(ur>u[i]){
                cout<<u[i];
            }
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
    	u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
	m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
	return 0;
}