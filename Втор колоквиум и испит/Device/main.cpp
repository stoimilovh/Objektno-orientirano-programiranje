//Да се креира класа за опишување на еден сервис за мобилни уреди. За секој мобилен телефон се чуваат податоци за модел (низа од 100 знаци), тип на уред (смартфон или компјутер), потребни часови за основна проверка (децимален број), година на производство (цел број). (5 поени)
//
//Сите уреди имаат исто времетраење за основна проверка и истата изнесува 1 час. Оваа вредност може да се смени со одлука на сервисот.
//Дополнително, уредите кои се понови од 2015 година имаат потреба од дополнителени 1.5 часа за проверка. При проверка,
//лаптопите имаат потреба од дополнителни 2 часа за софтверска дијагностика (5 поени).
//
//За оваа класа да се имплементира оператор << за печатење на уред во формат:
//
//[modelnauredotl]
//[tipnaured] [casovizaproverka]
//
//Каде часовите за проверка се оние од основната проверка+ дополнителни 2 часа доколку уредот е понов од 2015 + 2 часа доколу уредот е лаптоп (5 поени)
//
//Да се креира класа MobileServis во која се чува адреса (низа од 100 знаци), низа од уреди (динамички алоцирана низа) и број на уреди.(5 поени)
//
//За класата да се обезбедат:
//
//operatoror+= за додавање на нов уред во сервисот.(5 поени) Не смее да се дозволи годината на производство на уредот да биде
//        поголема од 2019 или помала од 2000. Ако се направи обид за додавање на уред со невалидна година, треба да се генерира
//        исклучок InvalidProductionDate. (10 поени)
//
//Функција pecatiUredi со која се печатат сите уреди со времето потребно за нивната проверка во сервисот (5 поени).
//
//Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

enum tip{
    smartfon, kompjuter
};

class InvalidProductionDate{
public:
    void print(){
        cout<<"Невалидна година на производство"<<endl;
    }
};

class Device{
private:
    char model[100];
    tip t;
    static int hours;
    int year;
public:
    Device(const char *model="", tip t=smartfon, int year=0){
        strcpy(this->model, model);
        this->t=t;
        this->year=year;
    }
    friend ostream &operator<<(ostream &out, Device &d){
        out<<d.model<<endl;
        if(d.t){
            out<<"Laptop ";
        }
        else{
            out<<"Mobilen ";
        }
        out<<d.proverka();
        return out;
    }
    int proverka(){
        if(year>2015){
            if(t){
                return hours+2+2;
            }
            return hours+2;
        }
        if(t){
            return hours+2;
        }
        return hours;
    }
    bool operator<(Device &d){
        if(d.year>2000&&d.year<2019){
            return true;
        }
        return false;
    }
    ~Device(){}
    static void setPocetniCasovi(int n){
        hours=n;
    };
    friend class MobileServis;
};

int Device::hours=1;


class MobileServis{
private:
    char adresa[100];
    Device *d;
    int num;
public:
    MobileServis(const char *adresa="", Device *d=nullptr, int num=0){
        strcpy(this->adresa, adresa);
        this->num=num;
        this->d=new Device[num];
        for(int i=0; i<num; i++){
            this->d[i]=d[i];
        }
    }
    MobileServis(const MobileServis &m){
        strcpy(this->adresa, m.adresa);
        this->num=m.num;
        this->d=new Device[num];
        for(int i=0; i<num; i++){
            this->d[i]=m.d[i];
            this->d[i].hours=m.d[i].hours;
        }
    }
    ~MobileServis(){
        delete[]d;
    }
    MobileServis &operator+=(Device ddd){
        if(ddd.year<2000||ddd.year>2019){
            throw InvalidProductionDate();
        }
        else{
            Device *dd=new Device[num+1];
            for(int i=0; i<num; i++){
                dd[i]=d[i];
            }
            dd[num]=ddd;
            num++;
            delete[]d;
            d=dd;
            return *this;
        }
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0; i<num; i++){
            cout<<d[i]<<endl;
        }
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &ip){
                ip.print();
            }

        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &ip){
                ip.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &ip){
                ip.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{
                t+=tmp;
            }
            catch (InvalidProductionDate &ip){
                ip.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}

