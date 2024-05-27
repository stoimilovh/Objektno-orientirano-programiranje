//За потребите на една продавница за гитари, потребно е да се направи програма за менаџирање на магацинот.
//За таа цел, треба да се креира класа Gitara (5 поени). Класата треба да содржи:
//
//Сериски број (низа од 25 знаци)
//Набавна цена (реален број)
//Година на производство (цел број)
//Тип (низа од 40 знаци)
//Да се дефинира метод daliIsti кој како аргумент ќе добие објект од тип Gitara и ќе ги спореди двете гитари според нивниот сериски број (5 поени)
//
//Дополнително, за оваа класа да се направи функција pecati() за печатење на објектот во следниот формат (5 поени):
//
//[СерискиБрој] [Тип] [Цена]
//
//Да се креира класа Magacin (5 поени) која содржи:
//
//Име на магацинот (низа од 30 знаци)
//Локација на магацинот (низа од 60 знаци)
//Низа од гитари кои ги поседува магацинот (динамички алоцирана низа од објекти од класата Gitara)
//Број на објекти во низата (цел број)
//Година на отвoрање (цел број)
//За класата Magacin да се дефинира метод double vrednost() што ќе ја пресметува моменталната вредност на гитарите кои се
//наоѓаат во магацинот. Таа се пресметува како збир од вредноста на сите гитари од кои е составен магацинот (5 поени).
//
//Дополнително, за класата да се дефинираат функциите:
//-void dodadi(Gitara d) за сместување на нова гитара во магацин (додавање на нов објект од класата Gitara во динамички алоцираната низа со гитари) (10 поени)
//-void prodadi(Gitara p) за бришење на дадена гитара од магацинот (бришење на сите објекти кои се исти како аргументот проследен во фунцијата)(10 поени)
//-void pecati(bool daliNovi) за печатење на информации за магацинот така што во првиот ред ќе биде прикажано имете и локацијата на магацинот,
//а потоа во секој нареден ред ќе бидат прикажани гитарите кои се наоѓаат во магацинот. Доколку пратената променлива има вредност true ќе се
//печатат само гитарите кои имаат година на производство понова од годината на отварање на магацинот. Во спротивно се печатат сите гитари (5 поени).
//
//За класите да се дефинираат потребните конструктори, деструктор и сите останати методи за правилно функционирање на програмата (5 поени).
//Сите податочни членови во класите се приватни.

#include <iostream>
#include <cstring>
using namespace std;

class Gitara{
private:
    char seriski[25];
    float cena;
    int godina;
    char tip[40];
    void copy(const Gitara &g){
        strcpy(this->tip, g.tip);
        strcpy(this->seriski, g.seriski);
        this->godina=g.godina;
        this->cena=g.cena;
    }
public:
    Gitara(char *tip="", char *seriski="", int godina=0, float cena=0){
        strcpy(this->tip, tip);
        strcpy(this->seriski, seriski);
        this->godina=godina;
        this->cena=cena;
    }
    Gitara(const Gitara &g){
        copy(g);
    }
    ~Gitara(){}
    int getGodina(){return godina;}
    char *getSeriski(){return seriski;}
    float getNabavna(){return cena;}
    char *getTip(){return tip;}
    float getCena(){return cena;}
    int daliIsti(Gitara g){
        return strcmp(seriski, g.seriski)==0;
    }
    void pecati(){
        cout<<seriski<<" "<<tip<<" "<<cena;
    }
};

class Magacin{
private:
    char ime[30], lokacija[60];
    Gitara *g;
    int n;
    int year;
    void copy(const Magacin &m){
        strcpy(this->ime, m.ime);
        strcpy(this->lokacija, m.lokacija);
        this->n=m.n;
        this->g=new Gitara[m.n];
        for(int i=0; i<n; i++){
            this->g[i]=m.g[i];
        }
        this->year=m.year;
    }
public:
    Magacin(char *ime="", char*lokacija="", int year=0){
        strcpy(this->ime, ime);
        strcpy(this->lokacija, lokacija);
        g=NULL;
        n=0;
        this->year=year;
    }
    Magacin(const Magacin &m){
        copy(m);
    }
    Magacin &operator=(const Magacin &m){
        if(this!=&m){
            delete[]g;
            copy(m);
        }
        return *this;
    }
    ~Magacin(){
        delete[]g;
    }
    int getYear(){return year;}
    double vrednost(){
        double vrednost;
        for(int i=0; i<n; i++){
            vrednost+=g[i].getCena();
        }
        return vrednost;
    }
    void dodadi(Gitara d){
        Gitara *tmp=new Gitara[n+1];
        for(int i=0; i<n; i++){
            tmp[i]=g[i];
        }
        tmp[n]=d;
        delete[]g;
        g=tmp;
        n++;
    }
    void prodadi(Gitara p){
        int j=0, brojach=0;
        for(int i=0; i<n; i++){
            if(strcmp(g[i].getSeriski(), p.getSeriski())){
                g[j]=g[i];
                j++;
            }
            else{
                brojach++;
            }
        }
        n-=brojach;
    }
    void pecati(bool daliNovi){
        cout<<ime<<" "<<lokacija<<endl;
        if(daliNovi){
            for(int i=0; i<n; i++){
                if(g[i].getGodina()>year){
                    g[i].pecati();
                    cout<<endl;
                }
            }
        }
        else{
            for(int i=0; i<n; i++){
                g[i].pecati();
                cout<<endl;
            }
        }
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, godina;
    float cena;
    char seriski[50],tip[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
        cout<<g.getTip()<<endl;
        cout<<g.getSeriski()<<endl;
        cout<<g.getGodina()<<endl;
        cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
        Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;
            Gitara g(tip,seriski, godina,cena);
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            cout<<"gitara dodadi"<<endl;
            kb.dodadi(g);
        }
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
    else if(testCase ==6)
    {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
        cin>>n;
        Gitara brisi;
        for (int i=0;i<n;i++){
            cin>>tip;
            cin>>seriski;
            cin >> godina;
            cin >> cena;

            Gitara g(tip,seriski, godina,cena);
            if(i==2)
                brisi=g;
            kb.dodadi(g);
        }
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
    }
    return 0;

}