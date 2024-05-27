//Во програмскиот јазик C++ да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер.
//Структурата треба да содржи: (5 поени)
//
//Фирма која го произведува ( низа од 100 знаци)
//Големина на монитор во инчи (реален број)
//Дали е со touch или не (булова променлива)
//Цена (цел број)
//Да се креира структура ITStore, што содржи: (5 поени)
//
//Име на продавницата (низа од 100 знаци)
//Локација (низа од 100 знаци)
//Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
//Број на елементи во низата (цел број)
//Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)
//
//[Ime na prodavnicata] [Lokacija]
//[Marka1] [dim_monitor1] [Cena1]
//[Marka2] [dim_monitor2] [Cena2]
//[Marka3] [dim_monitor3] [Cena3]
//...
//Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа
//продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и
//плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*
//
//Да се дополни функцијата main (10 поени).
//
//Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери,
//па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници
//и најевтината понуда.

#include <iostream>
#include <cstring>
using namespace std;

struct Laptop{
    char firma[100];
    float golemina;
    bool touch;
    int cena;
    void print();
};

struct ITStore{
    char ime[100], lokacija[100];
    int num;
    Laptop l[100];
    void print();
};

void Laptop::print(){
    cout<<firma<<" "<<golemina<<" "<<cena<<endl;
}

void ITStore::print(){
    cout<<ime<<" "<<lokacija<<endl;
}

void najeftinaPonud(ITStore *it, int n){
    int min=9999999, ind=0, br=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<it[i].num; j++){
            if(it[i].l[j].touch){
                if(it[i].l[j].cena<min){
                    min=it[i].l[j].cena;
                    ind=i;
                    br=j;
                }
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl<<it[ind].ime<<" "<<it[ind].lokacija;
    cout<<endl<<"Najniskata cena iznesuva: "<<it[ind].l[br].cena;
}

int main(){
    int n;
    cin>>n;
    ITStore it[n];
    for(int i=0; i<n; i++){
        cin>>it[i].ime>>it[i].lokacija>>it[i].num;
        for(int j=0; j<it[i].num; j++){
            cin>>it[i].l[j].firma>>it[i].l[j].golemina>>it[i].l[j].touch>>it[i].l[j].cena;
        }
    }
    for(int i=0; i<n; i++){
        it[i].print();
        for(int j=0; j<it[i].num; j++){
            it[i].l[j].print();
        }
    }
    najeftinaPonud(it, n);

    return 0;
}