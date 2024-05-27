//Да се креира структура SkiLift во која се чуваат податоци за името на ски лифтот (низа од 15 знаци),
//максимален број на корисници што може да опслужи на едно возење, дали е пуштен во функција.
//
//Потоа да се креирa структура SkiCenter во која се чуваат податоци за името на скијачкиот центар, држава во која се наоѓа (низи од 20 знаци),
//низа од ски лифтови (макс 20) што ги има и број на ски лифтови.
//
//Треба да се направи функција со потпис
//void najgolemKapacitet(SkiCenter *sc, int n)
//која што ќе го отпечати ски центарот што има најголем капацитет за опслужување скијачи
//(вкупниот број на скијачи кои може да се опслужуваат во еден момент вкупно на сите ски лифтови во центарот).
//Доколку два ски центри имаат ист капацитет, тогаш се печати оној кој има поголем број на ски лифтови.
//Притоа треба да се испечатат во посебен ред името, државата и капацитетот на ски центарот.
//Кога се пресметува капацитет на еден ски центар во предвид се земаат само ски лифтовите кои се поставени дека се во функција.

#include <stdio.h>

typedef struct skylift{
    char namesky[50];
    int max, num;
}skylift;

typedef struct skycenter{
    char name[50], country[20];
    int number;
    skylift sl[100];
}skycenter;

void najgolemKapacitet(skycenter sc[], int n){
    int i, j, max, maximum=0, a;
    for(i=0; i<n; i++){
        max=0;
        for(j=0; j<sc[i].number; j++){
            if(sc[i].sl[j].num==1){
                max+=sc[i].sl[j].max;
            }
        }
        if(max==maximum){
            if(sc[i].number>sc[a].number){
                maximum=max;
                a=i;
            }
        }
        else if(max>maximum){
            maximum=max;
            a=i;
        }
    }
    printf("%s\n%s\n%d", sc[a].name, sc[a].country, maximum);
}

int main()
{
    int n, i, j;
    skycenter sc[100];
    scanf("%d", &n);
    for(i=0; i<n; i++){
        scanf("%s %s %d", sc[i].name, sc[i].country, &sc[i].number);
        for(j=0; j<sc[i].number; j++){
            scanf("%s %d %d", sc[i].sl[j].namesky, &sc[i].sl[j].max, &sc[i].sl[j].num);
        }
    }
    najgolemKapacitet(sc, n);

    return 0;
}
