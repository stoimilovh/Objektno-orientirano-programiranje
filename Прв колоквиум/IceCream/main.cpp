//Да се дефинира класа IceCream во која се чуваат податоци за:
//
//име (динамичка низа од знаци),
//состав (низа од знаци, најмногу 100)
//цена (децимален број),
//попуст (цел број, изразен во проценти) иницијална вредност 0.
//За потребите на класата да се имплементираат:
//
//соодветни конструктори и деструктор (да се погледнат повиците во функцијата main)
//оператор << за печатење на податоците за сладоледот во следниов формат:
//име: состав цена [цена на попуст]
//
//делот „цена на попуст“ се печати само ако за сладоледот се нуди попуст (вредноста на попустот е поголема од нула)
//
//оператор ++ во префикс нотација за зголемување на попустот за 5
//оператор + - за собирање на објект од класата IceCream со низа од знаци. Собирањето се реализира на начин што името
//на новиот сладолед се добива со спојување на името на сладоледот и низата од знаци одделени со „ + “.
//Цената на новиот сладолед се зголемува за 10, а попустот и составот на сладоледот остануваат исти.
//метод void setDiscount(int discount) со кој може да се смени вредноста на попустот.
//Дозволените вредности на попустот се во интервалот [0,100]
//метод void setName(char* name) со кој се менува името на сладоледот.
//Да се креира класа IceCreamShop во која се чува:
//
//име на продавницата (низа од знаци, најмногу 50)
//динамички резервирано поле од објекти од класата IceCream
//број на сладоледи во полето (цел број).
//За оваа класа да се обезбедат:
//
//соодветни конструктори и деструктор (погледнете ги повиците во main функцијата)
//оператор += за додавање нов објект од класата IceCream во полето оператор << за печатење на листа од сите сладоледи во продавницата.
//        Прво се печати името на продавницата,а потоа се печатат податоците за сите сладоледи одделени со нов ред.

#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde
class IceCream{
private:
    char *name;
    char sostav[1000];
    float cena;
    int popust;
    void copy(const IceCream &ic){
        this->name=new char[strlen(ic.name)+1];
        strcpy(this->name, ic.name);
        strcpy(this->sostav, ic.sostav);
        this->cena=ic.cena;
        this->popust=ic.popust;
    }
public:
    IceCream(float cena=0){
        popust=0;
        cena=0;
        name=NULL;
    }
    IceCream(char *name, char *sostav, float cena){
        this->name=new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->sostav, sostav);
        this->cena=cena;
        popust=0;
    }
    IceCream(const IceCream &ic){
        copy(ic);
    }
    IceCream &operator=(const IceCream &ic){
        if(this!=&ic){
            delete[]name;
            copy(ic);
        }
        return *this;
    }
    ~IceCream(){
        delete[]name;
    }
    friend ostream &operator<<(ostream &out, const IceCream &ic){
        double broj=ic.popust/100.00;
        broj*=ic.cena;
        out<<ic.name<<": "<<ic.sostav<<" "<<ic.cena;
        if(ic.popust!=0){
            out<<" ("<<ic.cena-broj<<")";
        }
        return out;
    }
    IceCream &operator++(){
        popust+=5;
        return *this;
    }
    IceCream &operator+(char *zbor){
        char *nn=new char[strlen(name)+strlen(zbor)+4];
        strcat(nn, name);
        strcat(nn, " ");
        strcat(nn, "+");
        strcat(nn, " ");
        strcat(nn, zbor);
        delete[]name;
        strcpy(name, nn);
        cena+=10;
        return *this;
    }
    void setDiscount(int discount){
        popust=discount;
    }
    void setName(const char *n){
        delete[]name;
        this->name=new char[strlen(n)+1];
        strcpy(this->name, n);
    }
};

class IceCreamShop{
private:
    char name[50];
    IceCream *ic;
    int num;
    void copy(const IceCreamShop &ics){
        strcpy(this->name, ics.name);
        this->num=ics.num;
        ic=new IceCream[num];
        for(int i=0; i<num; i++){
            this->ic[i]=ics.ic[i];
        }
    }
public:
    IceCreamShop(int num=0){
        strcpy(this->name, " ");
        ic=NULL;
        this->num=0;
    }
    IceCreamShop(char *name){
        strcpy(this->name, name);
        ic=NULL;
        num=0;
    }
    IceCreamShop(const IceCreamShop &ics){
        copy(ics);
    }
    IceCreamShop &operator=(const IceCreamShop &ics){
        if(this!=&ics){
            delete[]ic;
            copy(ics);
        }
        return *this;
    }
    IceCreamShop &operator+=(const IceCream &icc){
        IceCream *cc=new IceCream[num+1];
        for(int i=0; i<num; i++){
            cc[i]=ic[i];
        }
        cc[num]=icc;
        delete[]ic;
        ic=cc;
        num++;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const IceCreamShop &ics){
        out<<ics.name<<endl;
        for(int i=0; i<ics.num; i++){
            out<<ics.ic[i]<<endl;
        }
        return out;
    }
    ~IceCreamShop(){
        delete[]ic;
    }
};

// zabraneto e menuvanje na main funkcijata

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}