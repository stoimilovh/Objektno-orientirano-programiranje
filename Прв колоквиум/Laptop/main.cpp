//Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер.
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
//Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа продавница
//која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch.
//Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*
//
//Да се дополни функцијата main (10 поени).
//
//Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери,
//па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници
//и најевтината понуда.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <cmath>

typedef struct Laptop{
    char firma[100];
    float golemina;
    bool touch;
    int cena;
}Laptop;

typedef struct ITStore{
    char ime[100], lokacija[100];
    Laptop l[100];
    int n;
}ITStore;

void print(ITStore *it, int n){
    int i, j;
    for(i=0; i<n; i++){
        printf("%s %s\n", it[i].ime, it[i].lokacija);
        for(j=0; j<it[i].n; j++){
            printf("%s ", it[i].l[j].firma);
            if(floor(it[i].l[j].golemina)==it[i].l[j].golemina){
                printf("%.f %d\n", it[i].l[j].golemina, it[i].l[j].cena);
            }
            else{
                printf("%.1f %d\n", it[i].l[j].golemina, it[i].l[j].cena);
            }
        }
    }
}

void najeftina_ponuda(ITStore *it, int n){
    int min=999999, i, j, ind=0, inj=0;
    for(i=0; i<n; i++){
        for(j=0; j<it[i].n; j++){
            if(it[i].l[j].touch){
                if(it[i].l[j].cena<min){
                    min=it[i].l[j].cena;
                    ind=i;
                    inj=j;
                }
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n", it[ind].ime, it[ind].lokacija);
    printf("Najniskata cena iznesuva: %d", min);
}

int main(){
    int n, i, j;
    ITStore s[100];
    scanf("%d", &n);
    for(i=0; i<n; i++){
        scanf("%s %s %d", &s[i].ime, &s[i].lokacija, &s[i].n);
        for(j=0; j<s[i].n; j++){
            scanf("%s %f %d %d", &s[i].l[j].firma, &s[i].l[j].golemina, &s[i].l[j].touch, &s[i].l[j].cena);
        }
    }
    print(s, n);
    najeftina_ponuda(s, n);

    return 0;
}