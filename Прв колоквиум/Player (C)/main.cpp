//Да се креира структура Igrac во која се чуваат податоци за еден играч на компјутерската игра.
//За играчот се чуваат информации за корисничкото име на играчот (низа од 15 знаци), број на ниво до кој играчот е стигнат (цел број)
//и број на освоени поени (цел број) (10 поени).
//
//Потоа да се креирa структура KompjuterskaIgra во која се чуваат податоци за името на играта (низа од 20 знаци),
//низа од играчи кои ја играат играта (најмногу 30) и бројот на играчи. (10 поени)
//
//Треба да се направи функција со потпис (15 поени)
//
//void najdobarIgrac(KompjuterskaIgra *lista, int n)
//Оваа функција треба да го испечати името на најдобриот играч на онаа игра која има најголема популарност
//(ја играат наjголем број на играчи). Најдобар играч е играчот кој има најголем број на освоени поени.
//Ако има повеќе играчи со ист максимален број на освоени поени, најдобар е играчот кој има достигнато најголемо ниво.
//
//Печатењето е во форматот: "Najdobar igrac e igracot so korisnicko ime XXXXX koj ja igra igrata YYYYYY".
//(XXXXXX е корисничкото име на најдобриот играч,а YYYYY е името на играта која ја играат најголем број на играчи)
//
//(Забелешка: секогаш ќе има точно еден најдобар играч)
//Функционалност на задачата и дополнување на main функцијата (10 поени)
//Забелешка: Задачата да се реши во програмскиот јазик C+

#include <iostream>
#include <cstring>
using namespace std;

struct Igrac{
    char name[15];
    int nivo, poeni;
};

struct KompjuterskaIgra{
    char gamename[20];
    int num;
    Igrac i[30];
};

void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int ind=0, indr=0, br=0, max=-9999, igraci=0;
    for(int i=0; i<n; i++){
        if(lista[i].num>igraci){
            igraci=lista[i].num;
            ind=i;
        }
    }
    for(int j=0; j<lista[ind].num; j++){
        if(lista[ind].i[j].poeni>max){
            max=lista[ind].i[j].poeni;
            indr=ind;
            br=j;
        }
        else if(lista[ind].i[j].poeni==max){
            if(lista[ind].i[j].nivo>lista[indr].i[br].nivo){
                max=lista[indr].i[j].poeni;
                indr=ind;
                br=j;
            }
        }

    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<lista[indr].i[br].name<<" koj ja igra igrata "<<lista[ind].gamename;
}

int main()
{
    int n;
    cin>>n;
    KompjuterskaIgra pc[n];
    for(int i=0; i<n; i++){
        cin>>pc[i].gamename>>pc[i].num;
        for(int j=0; j<pc[i].num; j++){
            cin>>pc[i].i[j].name>>pc[i].i[j].nivo>>pc[i].i[j].poeni;
        }
    }
    najdobarIgrac(pc, n);

    return 0;
}