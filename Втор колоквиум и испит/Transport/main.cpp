//Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци),
//основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).
//
//Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт кои нудат
//транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата
//има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)
//
//За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
//
//конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
//метод cenaTransport, за пресметување на цената на понудата на следниот начин:
//За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
//За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето
//цената се намалува за 200 (10 поени)
//преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
//Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на
//елементите од низата и една понуда T. Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за
//понудите од низата кои се поскапи од понудата T сортирани во растечки редослед по растојанието до дестинацијата
//(погледни го повикот на функцијата) (10 поени)
//
//Комплетна функционалност на кодот (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

// вашиот код треба да биде тука

class Transport{
protected:
    char destinacija[100];
    int cena, rastojanie;
public:
    Transport(char *destinacija, int cena, int rastojanie){
        strcpy(this->destinacija, destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }
    virtual float cenaTransport()=0;
    friend ostream &operator<<(ostream &out, Transport &t){
        return out<<t.destinacija<<" "<<t.rastojanie<<" "<<t.cenaTransport()<<endl;
    }
    bool operator<(Transport &t){
        return this->cenaTransport()<t.cenaTransport();
    }
};

class AvtomobilTransport:public Transport{
private:
    bool shofer;
public:
    AvtomobilTransport(char *destinacija, int cena, int rastojanie, bool shofer): Transport(destinacija, cena, rastojanie){
        this->shofer=shofer;
    }
    float cenaTransport(){
        if(shofer){
            return cena+(cena*0.2);
        }
        return cena;
    }
};

class KombeTransport:public Transport{
private:
    int lugje;
public:
    KombeTransport(char *destinacija, int cena, int rastojanie, int lugje): Transport(destinacija, cena, rastojanie){
        this->lugje=lugje;
    }
    float cenaTransport(){
        return cena-(200*lugje);
    }
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &nov){
    int h=0;
    Transport **p=new Transport *[n];
    for(int i=0; i<n; i++){
        if(ponudi[i]->cenaTransport()>nov.cenaTransport()){
            p[h]=ponudi[i];
            h++;
        }
    }
    for(int i=0; i<h; i++){
        for(int j=0; j<h-1; j++){
            if(p[j]->cenaTransport()>p[j+1]->cenaTransport()){
                Transport *temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(int i=0; i<h; i++){
        cout<<*p[i];
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
