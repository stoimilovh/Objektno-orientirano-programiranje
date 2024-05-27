//(40 поени)
//
//Да се креира класа Patnik во која се чуваат податоци за патниците на еден воз и тоа: име (низа од максимум 100 знаци),
//класа на вагон во која се вози (цел број 1 или 2) и велосипед (булова променлива).
//
//За оваа класа да се преоптоварат:
//
//Оператор << - за печатење на информациите за патникот во формат:
//Име на патник
//Бројот на класата (1 или 2)
//Дали има велосипед?
//
//Потоа да се креира клaса Voz во која се чува: крајна дестинација (низа од максимум 100 знаци),
//динамички алоцирана низа од објекти од класата Patnik, како и број на елементи во низата (цел број), број на дозволени велосипеди (цел број).
//
//За класата да се обезбедат:
//
//Оператор += – за додавање нов патник во воз. Патник со велосипед ќе може да се качи во воз само ако возот го дозволува тоа.
//Оператор << - за печатење на крајната дестинација до која вози и листата на патници
//Функција со потпис: patniciNemaMesto(). Со оваа функција се пресметува вкупниот број на патници (од 1-ва класа и 2-ра класа)
//за кои нема место да влезат во возот со велосипед. Притоа треба да се внимава дека во пресметувањето на вкупниот број патници
//со велосипеди кои ќе влезат во возот прво треба да се земат предвид патниците од 1-ва класа, а потоа се дозволува да влегуваат
//патниците од 2-ра класа се додека не се достигне максималниот број на дозволени велосипеди во возот. На крај се печати бројот
//на патници со велосипеди кои остануваат (не влегуваат во возот) од 1-ва класа, а потоа од 2-ра класа.

#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    char name[100];
    int klasa;
    bool velosiped;
public:
    Patnik(int klasa=0, bool velosiped=false){}
    Patnik(char *ime, int klasa, bool velosiped){
        strcpy(this->name, ime);
        this->klasa=klasa;
        this->velosiped=velosiped;
    }
    friend ostream &operator<<(ostream &out, const Patnik &p){
        out<<p.name<<endl<<p.klasa<<endl<<p.velosiped<<endl;
        return out;
    }
    bool getBR()const{return velosiped;}
    int getKlasa()const{return klasa;}
    bool sporedi(int v){
        if(velosiped==true&&v>0){
            return true;
        }
        return false;
    }
};

class Voz{
private:
    char dest[100];
    Patnik *p;
    int num=0, v, min=0, prva=0, vtora=0;
public:
    Voz(int num=0){
        num=v=0;
    }
    Voz(char *dest, int v){
        strcpy(this->dest, dest);
        p=NULL;
        this->v=v;
        num=0;
    }
    Voz &operator+=(const Patnik &pr){
        int temp;
        if(v==0){
            if(pr.getBR()==false){
                temp=0;
                Patnik *pp=new Patnik[num+1];
                for(int i=0; i<num; i++){
                    pp[i]=p[i];
                }
                pp[num]=pr;
                delete[]p;
                p=pp;
                num++;
                return *this;
            }
        }
        else if(v>0){
            if(min<=v||pr.getBR()==false||pr.getKlasa()==1){
                temp=1;
                Patnik *pp=new Patnik[num+1];
                for(int i=0; i<num; i++){
                    pp[i]=p[i];
                }
                pp[num]=pr;
                delete[]p;
                p=pp;
                if(pr.getBR()==true){
                    min++;
                }
                num++;
                if(pr.getBR()==true){
                    if(pr.getKlasa()==1){
                        prva++;
                    }
                    else if(pr.getKlasa()==2){
                        vtora++;
                    }
                }
                return *this;
            }
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Voz &v){
        out<<v.dest<<endl;
        for(int i=0; i<v.num; i++){
            out<<v.p[i]<<endl;
        }
        return out;
    }
    void patniciNemaMesto(){
        int broj=0, h;
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: ";
        if(v==prva||v==0){
            cout<<"0"<<endl;
            h=0;
        }
        else if(v>prva){
            cout<<"0"<<endl;
            h=v-prva;
        }
        else{
            cout<<prva-v<<endl;
            h=0;
        }
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: ";
        if(h==0){
            cout<<vtora<<endl;
        }
        else{
            if(vtora-h<0){
                cout<<"0"<<endl;
            }
            else{
                cout<<vtora-h<<endl;
            }
        }
    }
};

int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
