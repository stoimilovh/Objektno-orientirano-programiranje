//Во програмскиот јазик C да се креира структура Vozenje за опишување на адреналински возења во
//забавен парк. Структурата треба да содржи: (5 поени)
//
//Име на возењето ( низа од 100 знаци)
//Времетраење во минути (цел број)
//Цена (децимален број)
//Дали има студентски попуст (1-да, 0-не)
//Да се креира структура ZabavenPark, што содржи: (10 поени)
//
//Име на забавниот парк (низа од 100 знаци)
//Локација (низа од 100 знаци)
//Низа од адреналински возења во паркот (низа од максимум 100 елементи од структурата Vozenje)
//Број на елементи во низата (цел број)
//Да се креира функција print за печатење на информациите за сите возења во забавниот парк во формат: (10 поени)
//
//[Ime na parkot] [Lokacija]
//[Ime1] [Vremetraenje1] [Cena1]
//[Ime2] [Vremetraenje2] [Cena2]
//[Ime3] [Vremetraenje3] [Cena3]
//...
//Да се креира функција najdobar_park, што прима низа од променливи од типот ZabavenPark
//и го печати името и локацијата на паркот кој е најефтин за посета од страна на студенти.
//Најефтин парк е оној што содржи најголем број возења со студентски попуст.
//Ако повеќе паркови ги делат овие карактеристики, да се испечати паркот со најголемото времетраење
//од сите возења.* (20 поени)*
//
//Да се дополни функцијата main (5 поени).

#include <stdio.h>
#include <string.h>

typedef struct Vozenje{
    char ime[100];
    int traenje;
    float cena;
    int daliPopust;
} vozenje;

typedef struct ZabavenPark{
    char ime[100], lokacija[100];
    int n;
    vozenje niza[100];
}ZabavenPark;

void pecati(ZabavenPark *ff, int n){
    int i, j;
    for(i=0; i<n; i++){
        printf("%s %s\n", ff[i].ime, ff[i].lokacija);
        for(j=0; j<ff[i].n; j++){
            printf("%s %d %.2f\n", ff[i].niza[j].ime, ff[i].niza[j].traenje, ff[i].niza[j].cena);
        }
    }
}

void najdobar_park(ZabavenPark *ff, int n){
    int i, j, ind=0, max=0, maximum=0, vreme=0, vremetraenje=0;
    for(i=0; i<n; i++){
        for(j=0; j<ff[i].n; j++){
            if(ff[i].niza[j].daliPopust){
                max++;
            }
        }
        if(max>maximum){
            maximum=max;
            max=0;
            ind=i;
        }
        else if(max==maximum){
            for(j=0; j<ff[i].n; j++){
                vreme+=ff[i].niza[j].traenje;
            }
            for(j=0; j<ff[ind].n; j++){
                vremetraenje+=ff[ind].niza[j].traenje;
            }
            if(vreme>vremetraenje){
                maximum=max;
                max=vreme=vremetraenje=0;
                ind=i;
            }
        }
    }
    printf("Najdobar park: %s %s\n", ff[ind].ime, ff[ind].lokacija);
}

int main(){
    int k, i, j;
    scanf("%d", &k);
    ZabavenPark ff[100];
    for(i=0; i<k; i++){
        scanf("%s %s %d", &ff[i].ime, &ff[i].lokacija, &ff[i].n);
        for(j=0; j<ff[i].n; j++){
            scanf("%s %d %f %d", &ff[i].niza[j].ime, &ff[i].niza[j].traenje, &ff[i].niza[j].cena, &ff[i].niza[j].daliPopust);
        }
    }
    pecati(ff, k);
    najdobar_park(ff, k);

    return 0;
}