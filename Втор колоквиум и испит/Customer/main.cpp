//Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:
//
//името (низа од 50 знаци),
//електронска адреса (низа од 50 знаци),
//вид на купувач (стандардни, лојални или вип),
//основен попуст (цел број изразен во проценти),
//        дополнителен попуст (цел број изразен во проценти) и
//        број на купени производи. (5 поени)
//Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата.
//Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата.
//Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).
//
//За оваа класа да се имплементира оператор << за печатење на купувач во формат:
//
//[ime_na_kupuvac]
//[email_na_kupuvac]
//[broj_na_proizvodi]
//[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
//каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот
//и дополнителниот попуст, ако купувачот е вип. (5 поени)
//
//Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи
//(динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:
//
//operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа
//(ако во листата нема купувач со иста електронска адреса). Ако во листата постои корисник со иста електронска адреса,
//треба да се генерира исклучок UserExistsException. Потребно е да се обезбеди справување со исклучокот во функцијата main
//на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
//Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални,
//а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
//Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
//Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)

#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;

enum typeC{
    standarden, lojalen, vip
};

class Exception{
public:
    void print(){
        cout<<"The user already exists in the list!"<<endl;
    }
};

class Customer{
protected:
    char name[50], mail[50];
    typeC c;
    int procenti, dopolnitelno, num;
public:
    Customer(const char *name="", const char *mail="", typeC c=vip, int num=0, int procenti=0, int dopolnitelno=0){
        strcpy(this->name, name);
        strcpy(this->mail, mail);
        this->c=c;
        this->procenti=procenti;
        this->dopolnitelno=dopolnitelno;
        this->num=num;
        if(this->c==1){
            this->procenti=10;
        }
        else if(this->c==2){
            this->procenti=30;
        }
    }
    ~Customer(){}
    void setDiscount1(int n){
        this->procenti=n;
    }
    friend ostream &operator<<(ostream &out, Customer &c){
        out<<c.name<<endl<<c.mail<<endl<<c.num<<endl;
        if(c.c==0){
            out<<"standard "<<c.procenti<<endl;
        }
        else if(c.c==1){
            out<<"loyal "<<c.procenti<<endl;
        }
        else if(c.c==2){
            out<<"vip "<<c.procenti<<endl;
        }
    }
    bool operator==(const Customer &c){
        return strcmp(this->mail, c.mail)==0;
    }
    friend class FINKI_bookstore;
};

class FINKI_bookstore:public Exception{
private:
    Customer *c;
    int number;
public:
    FINKI_bookstore(int number=0){
        this->number=number;
        c=new Customer[number];
    }
    FINKI_bookstore(Customer *c, int number){
        this->number=number;
        this->c=new Customer[number];
        for(int i=0; i<number; i++){
            this->c[i]=c[i];
        }
    }
    ~FINKI_bookstore(){
        delete[]c;
    }
    void setCustomers(Customer *customers,int n){
        delete[]c;
        c=new Customer[n];
        for(int i=0; i<n; i++){
            c[i]=customers[i];
        }
        number=n;
    }
    friend ostream &operator<<(ostream &out, FINKI_bookstore &f){
        for(int i=0; i<f.number; i++){
            out<<f.c[i];
        }
        return out;
    }
    FINKI_bookstore &operator+=(Customer &ch){
        for(int i=0; i<number; i++){
            if(c[i]==ch){
                throw Exception();
            }
        }
        Customer *cc=new Customer[number+1];
        for(int i=0; i<number; i++){
            cc[i]=c[i];
        }
        cc[number]=ch;
        delete[]c;
        c=cc;
        number++;
    }
    void update(){
        for(int i=0; i<number; i++){
            if(c[i].c==0&&c[i].num>=5){
                c[i].c=lojalen;
                c[i].procenti=10;
            }
            else if(c[i].c==1&&c[i].num>=10){
                c[i].c=vip;
                c[i].procenti=30;
            }
        }
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        try{
            fc+=c;
        }
        catch(Exception &e){
            e.print();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
