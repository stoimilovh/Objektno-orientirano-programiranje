//Во програмскиот јазик C да се креира структура Pacient и истата треба да содржи: (5 поени)
//
//Име и презиме на пациентот ( низа од макс. 100 знаци)
//Дали е здраствено осигуран (1-да, 0-не)
//Број на прегледи во текот на последниот месец (цел број)
//Да се креира структура MaticenDoktor, која во себе содржи: (5 поени)
//
//Име на докторот (низа од 100 знаци)
//Број на пациенти (цел број)
//Листа од пациенти (низа од максимум 200 елементи од структурата Pacient)
//Цена на преглед (децимален број)
//Да се креираат метода najuspesen_doktor, која прима низа од променливи од типот MaticenDoktor и нивниот број;
//и го печати името, заработената сума и бројот на прегледи на оној доктор кој заработил најголема сума од пациенти
//кои ги прегледувал приватно (не се здраствено осигурани) (10 поени). Доколку два или повеќе доктори имаат иста сума,
//тогаш се печати оној доктор кој има направено најголем број на прегледи вкупно во текот на последниот месец. (20 поени)

#include <stdio.h>

typedef struct pacient{
    char name[100];
    int temp, pregledi;
}pacient;

typedef struct maticendoktor{
    char doc[100];
    int num;
    float price;
    pacient list[200];
}maticendoktor;

void najuspesenDoktor(maticendoktor dr[], int n){
    int i, j, temp, pregledi=0, pr, a;
    float zbir, maximum=0;
    for(i=0; i<n; i++){
        zbir=temp=pregledi=0;
        for(j=0; j<dr[i].num; j++){
            if(dr[i].list[j].temp==0){
                zbir+=dr[i].list[j].pregledi*dr[i].price;
            }
            pregledi+=dr[i].list[j].pregledi;
        }
        if(zbir==maximum){
            if(pregledi>pr){
                maximum=zbir;
                a=i;
                pr=pregledi;
            }
        }
        else if(zbir>maximum){
            maximum=zbir;
            a=i;
            pr=pregledi;
        }
    }
    printf("%s %.2f %d", dr[a].doc, maximum, pr);
}

int main()
{
    int n, i, j;
    maticendoktor dr[100];
    scanf("%d", &n);
    for(i=0; i<n; i++){
        scanf("%s %d %f", dr[i].doc, &dr[i].num, &dr[i].price);
        for(j=0; j<dr[i].num; j++){
            scanf("%s %d %d", dr[i].list[j].name, &dr[i].list[j].temp, &dr[i].list[j].pregledi);
        }
    }
    najuspesenDoktor(dr, n);

    return 0;
}