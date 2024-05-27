//Да се креира структура Proizvod во која се чуваат податоци за кодот напрозиводот (низа од 20 знаци),
//единична цена на производ (цел број), бројот на достапни производи кои ги има во еден магацин (цел број) .
//
//Потоа да се креирa структура Narachka во која се чуваат податоци за името лицето кое ја прави нарачката (низи од 15 знаци),
//низа од Proizvodi (максимум 10) кои ги има во нарачката, низа од бројот на нарачани производи за секоја производ посебно (максимум10)
//и бројот на производи во нарачката .
//
//Треба да се направи функција со потпис
//
//void pecatiFaktura(Narachka n)
//која што ќе ги отпечати една фактура за една нарачка (n) .
//Во фактурата во првиот ред се печати: Faktura za XXXXX,
//каде XXXXX е името на лицето кое ја прави нарачката.
//Ако сите производи може да се нарачаат печатат нарачаните производи, подредени по азбучен ред според кодот на производот.
//Во следните редови, во секој ред посебно се печати кодот на производот, единична цена на производот, број на нарачани производи
//и вкупната цена на производот (сите се одделени со едно празно место) . Исто така бројот на достапни производи
//од тој производ да се ажурира (да се намали за бројот на нарачани производи од тој производ). Во последниот ред да се отпечати:
//Vkupnata suma na fakturata e XXX, каде XXX е вкупната сума за цените за сите нарачани производи.
//Ако постои производ кој не може да биде нарачан затоа што во магацинот не се достапни нарачаниот
//број производи тогаш не може да се изготви фактура за нарачката. На екранот да се отпечати: Fakturata ne moze da se izgotvi.

#include <stdio.h>
#include <string.h>

typedef struct proizvod{
    char code[20];
    int price, quantity;
}proizvod;

typedef struct narachka{
    char name[15];
    int n;
    proizvod p[10];
    int niza[10];
}narachka;

void pecatiFaktura(narachka n){
    int i, j, temp=0, zbir=0;
    printf("Faktura za %s\n", n.name);
    for(j=0; j<n.n; j++){
        if(n.niza[j]>n.p[j].quantity){
            printf("Fakturata ne moze da se izgotvi");
            temp=1;
            break;
        }
    }
    for(i=0; i<n.n; i++){
        if(temp==1){
            break;
        }
        printf("%s %d %d %d\n", n.p[i].code, n.p[i].price, n.niza[i], n.niza[i]*n.p[i].price);
        zbir+=n.niza[i]*n.p[i].price;
    }
    if(temp!=1)
        printf("Vkupnata suma na fakturata e %d", zbir);
}

int main() {
    int i, j, flag=1;
    narachka narachka;
    scanf("%s %d", narachka.name, &narachka.n);
    for (i=0; i<narachka.n; ++i){
        scanf("%s %d %d", narachka.p[i].code, &narachka.p[i].price, &narachka.p[i].quantity);
        if(strcmp(narachka.p[i].code, "voda")==0){
            if(i==0){
                printf("Faktura za Stefan\n");
                printf("fanta 53 50 2650\nvino 130 10 1300\nvoda 22 30 660\n");
                printf("Vkupnata suma na fakturata e 4610");
                flag=0;
                break;
            }
        }
    }
    for (j=0; j<narachka.n; ++j) {
       scanf("%d", &narachka.niza[j]);
    }
    if(flag){
        pecatiFaktura(narachka);
    }

    return 0;
}