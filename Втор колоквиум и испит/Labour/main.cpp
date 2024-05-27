//Да се имплементира класа Trud во која се чуваат информации за: (5 поени)
//
//вид на труд (еден знак и тоа C за конференциски труд, J за труд во списание)
//година на издавање (цел број).
//Да се имплементира класа Student во која се чува: (5 поени)
//
//името на студентот (низа од најмногу 30 карактери)
//индекс (цел број)
//година на упис (цел број)
//листа на оцени од положени предмети (низа од цели броеви)
//број на положени предмети (цел број)
//За оваа класа да се имплементираат следните методи:
//
//функција rang() што пресметува просек од положените испити на студентот (5 поени)
//оператор << за печатење на студентот во формат: (5 поени)
//
//Индекс Име Година на упис ранг
//
//Да се имплементира класа PhDStudent во која покрај основните информации за студентот дополнително се чува: (5 поени)
//
//листа од објавени трудови (динамички резервирана низа од објекти од класата Trud)
//бројот на трудови (цел број)
//Во оваа класа да се препокрие соодветно функцијата rang() така што на просекот од положените испити ќе се додаде и
//збирот од поените од објавените трудови на PhD студентот. Во зависност од видот на трудот, секој универзитет има
//посебен начин на бодување на трудовите. Начинот на бодување е ист за сите PhD студенти. Иницијално да се смета дека
//конференциски труд се бодува со 1 поен, а труд во списание со 3 поени. Универзитетот има можност да ги менува
//вредностите на бодовите. (5 поени + 5 поени)
//
//За оваа класа да се обезбеди:
//
//оператор += за додавање нов објект од класата Trud во листата (5 поени). Ако се направи обид да се внесе труд што е
//        издаден порано од годината на упис на студентот да се фрли исклучок (објект од класата Exception).
//        Справувањето со исклучокот треба да се реализира во главната функција main каде што е потребно, но и во
//        конструктор ако е потребно. Ако бил генериран исклучок треба да се отпечати соодветна порака за грешка
//        "Ne moze da se vnese dadeniot trud", а новиот труд нема да се внесе во листата на трудови од студентот. (10 поени)
//Напомена: Сите променливи на класите се чуваат како приватни.
//
//Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

class Exception{
public:
    void print(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud{
private:
    char c;
    int year;
public:
    Trud(char c='c', int year=0){
        this->c=c;
        this->year=year;
    }
    int getYear(){return year;}
    friend istream &operator>>(istream &in, Trud &t){
        return in>>t.c>>t.year;
    }
    friend class PhDStudent;
};

class Student{
protected:
    char name[50];
    int index, godina;
    int predmeti[50];
    int polozeni;
public:
    Student(char *name, int index, int godina, int predmeti[], int polozeni){
        strcpy(this->name, name);
        this->index=index;
        this->godina=godina;
        this->polozeni=polozeni;
        for(int i=0; i<polozeni; i++){
            this->predmeti[i]=predmeti[i];
        }
    }
    virtual float rang(){
        float broj=0;
        for(int i=0; i<polozeni; i++){
            broj+=predmeti[i];
        }
        return broj/polozeni;
    }
    friend ostream &operator<<(ostream &out, Student &s){
        return out<<s.index<<" "<<s.name<<" "<<s.godina<<" "<<s.rang()<<endl;
    }
};

class PhDStudent:public Student{
private:
    Trud *t;
    int num;
    static int c;
    static int s;
public:
    PhDStudent(char *name, int index, int godina, int predmeti[], int polozeni, Trud *t, int num): Student(name, index, godina, predmeti, polozeni){
        this->num=num;
        this->t=new Trud[num];
        int j=0;
        for(int i=0; i<num; i++){
            try{
                if(t[i].getYear()<godina){
                    throw Exception();
                }
                else{
                    this->t[j]=t[i];
                    j++;
                }
            }
            catch (Exception &e){
                e.print();
            }
        }
        this->num=j;
    }
    int getIndex(){return index;}
    virtual float rang(){
        float broj=Student::rang();
        for(int i=0; i<num; i++){
            if(t[i].c=='c'){
                broj+=c;
            }
            else if(t[i].c=='C'){
                broj+=c;
            }
            else{
                broj+=s;
            }
        }
        return broj;
    }
    friend ostream &operator<<(ostream &out, PhDStudent &ps){
        return out<<ps.index<<" "<<ps.name<<" "<<ps.godina<<" "<<ps.rang()<<endl;
    }
    ~PhDStudent(){
        delete[]t;
    }
    PhDStudent &operator+=(const Trud &tr){
        if(tr.year<godina){
            throw Exception();
        }
        Trud *tt=new Trud[num+1];
        for(int i=0; i<num; i++){
            tt[i]=t[i];
        }
        tt[num]=tr;
        delete[]t;
        t=tt;
        num++;
        return *this;
    }
    static void setConf(int conf){
        c=conf;
    }
    static void setJurnal(int jurnal){
        s=jurnal;
    }
};

int PhDStudent::c=1;
int PhDStudent::s=3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        for(int i=0; i<m; i++){
            PhDStudent *ph=dynamic_cast<PhDStudent *>(niza[i]);
            if(ph){
                if(ph->getIndex()==indeks){
                    *ph+=t;
                    break;
                }
            }
            if(i==m-1){
                cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        for(int i=0; i<m; i++){
            PhDStudent *ph=dynamic_cast<PhDStudent *>(niza[i]);
            if(ph){
                if(ph->getIndex()==indeks){
                    *ph+=t;
                    break;
                }
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        for(int i=0; i<m; i++){
            PhDStudent *ph=dynamic_cast<PhDStudent *>(niza[i]);
            if(ph){
                if(ph->getIndex()==indeks){
                    try{
                        *ph+=t;
                    }
                    catch(Exception &e){
                        e.print();
                    }
                    break;
                }
            }
            if(i==m-1){
                cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setConf(conf);
        PhDStudent::setJurnal(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}