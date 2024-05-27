//Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци),
//предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).
//
//Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци),
//низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).
//
//Треба да се направи функција со потпис
//void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
//во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри),
//а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри,
//да се испечати релацијата на последниот таков.
//
//Забелешка: Задачата да се реши во програмскиот јазик C++

#include <iostream>
#include <cstring>
using namespace std;

struct Voz{
    char name[50];
    float kilometri;
    int patnici;
};

struct ZeleznickaStanica{
    char city[20];
    int num;
    Voz v[30];
};

void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad){
    int min, ind=0, br=0;
    for(int i=0; i<n; i++){
        if(strcmp(zs[i].city, grad)==0){
            min=zs[i].v[0].kilometri;
            for(int j=0; j<zs[i].num; j++){
                if(zs[i].v[j].kilometri<=min){
                    min=zs[i].v[j].kilometri;
                    ind=i;
                    br=j;
                }
            }
        }
    }
    cout<<"Najkratka relacija: "<<zs[ind].v[br].name<<" ("<<zs[ind].v[br].kilometri<<" km)";
}

int main()
{
    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici
    ZeleznickaStanica zStanica[100];
    Voz v[100];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin>>zStanica[i].city>>zStanica[i].num;
        for(int j=0; j<zStanica[i].num; j++){
            cin>>zStanica[i].v[j].name>>zStanica[i].v[j].kilometri>>zStanica[i].v[j].patnici;
        }
    }
    char grad[25];
    cin>>grad;
    najkratkaRelacija(zStanica,n,grad);
	return 0;
}