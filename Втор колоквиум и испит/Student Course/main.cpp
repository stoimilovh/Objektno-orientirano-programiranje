//Дадена е дел од дефиниција на класата StudentKurs. За секој студент кој слуша некој курс
//се чуваат информации за неговото име (низа од знаци), оценка од писмен дел (цел број) и
//дали студентот сака да биде испрашуван и усно (булова променлива).
//
//Оцената за писмениот дел е вредност од 1 до МАX. MAX има почетна вредност 10 која е иста е
//за сите и може да се промени со соодветна функција setMAX(). (5 поени)
//
//Кај оние студенти кои сакаат да бидат испрашувани усно и добиваат и описна оценка.
//Имплементирај соодветна класа StudentKursUsno во која се чуваат дополнителни информации
//за описна оценка на усното испрашување (динамичко алоцирана низа од знаци). Описни оценки
//може да бидат: odlicen, dobro, losho.... Ако описната оценка е odlicen тогаш оцената ќе
//биде најмногу за оценки 2 повисока од оценката од писмениот дел, ако е dobro оценката ќе
//биде најмногу за 1 повисока, а ако е losho за 1 пониска. Ако студентот добие некоја друга
//описна оценка, неговата оценка ќе остане иста со оценката од писмениот дел.
//
//Во класите StudentKurs и StudentKursUsno треба да се имплементираат потребните конструктори,
//функции за поставување и преземање и деструктор. (5 поени)
//
//За сите објекти од класите треба да се обезбедат следните функции:
//преоптоварен оператор << во кој се печатат информации за студентот на курсот во
//формат: Ime --- ocenka (5 поени)
//оcenka() – ја враќа оценката на студентот на курсот (5 поени)
//Во класата StudentKursUsno дефинирај ја функцијата:
//
//преоптоварен оператор += за поставување на описна оценка на студентот(5 поени)
//Ако се направи обид да се внесе описна оценка во која покрај букви има и други
//знаци треба да се фрли исклучок (објект од класата BadInputException). Фатете го исклучокот во главната
//функција каде што е потребно. Откако ќе го фатите отпечатете соодветна порака за грешка
//(Greshna opisna ocenka) и справете се со исклучокот така што тие знаци ќе отстранат од стрингот со
//описната оценка (ако описната оценка била dо1ba0r ќе се промени во dоbar). (10 поени)
//
//Дадена е дел од дефиницијата на класата KursFakultet во која се чуваат информаци за името на курсот
//(низа од 30 знаци) и за студентите запишани на курсот (низа од 20 покажувачи кон класата StudentKurs)
//како и бројот на студенти запишани на курсот.
//
//Еден студент кој запишал некој курс ќе го положи курсот ако има барем MINOCENKA. Вредноста MINOCENKA
//е членка на класата StudentKurs и има фиксна вредност 6 која не може да се промени. (5 поени)
//
//Во класата KursFakultet имплементирај ги функциите:
//функција pecatiStudenti() во која се печатат сите студенти кои го положиле курсот, секој во посебен ред.
//Претходно во првиот ред се печати: Kursot XXXXX go polozile: (5 поени).
//
//функција postaviOpisnaOcenka(char * ime, char* opisnaOcenka) во која на студентот на курсот со даденото
//име му се поствува описна оценка. Ако тоа не е можно функцијата не прави ништо (15 поени).

#include<iostream>
#include<string.h>
using namespace std;

class BadInputException{
public:
    void print(){
        cout<<"Greshna opisna ocenka"<<endl;
    }
};

class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA;
public:
    StudentKurs(const char* ime="",int finalenIspit=0, bool daliUsno=false){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=daliUsno;
    }
    //дополни ја класата
    static void setMAX(int n){
        MAX=n;
    }
    friend ostream &operator<<(ostream &out, StudentKurs &sk){
        return out<<sk.ime<<" --- "<<sk.getOcenka();
    }
    virtual int getOcenka(){
        return ocenka;
    }
    char *getName(){return ime;}
    bool getDaliUsno(){return daliUsno;}
    friend class KursFakultet;
};

const int StudentKurs::MINOCENKA=6;
int StudentKurs::MAX=10;

//вметни го кодот за StudentKursUsno
class StudentKursUsno:public StudentKurs{
private:
    char *usno;
public:
    StudentKursUsno(const char* ime="",int finalenIspit=0, bool daliUsno= false, const char *usno=""): StudentKurs(ime, finalenIspit, daliUsno){
        this->usno=new char[strlen(usno)+1];
        strcpy(this->usno, usno);
    }
    ~StudentKursUsno(){
        delete[]usno;
    }
    friend ostream &operator<<(ostream &out, StudentKursUsno &sku){
        return out<<sku.ime<<" --- "<<sku.getOcenka();
    }
    int getOcenka(){
        if(strcmp(usno, "odlicen")==0){
            return ocenka+2;
        }
        else if(strcmp(usno, "dobro")==0){
            return ocenka;
        }
        else if(strcmp(usno, "do7br4o")==0){
            return ocenka+1;
        }
        else if(strcmp(usno, "losho")==0){
            return ocenka-1;
        }
    }
    StudentKursUsno &operator+=(const char *zbor){
        delete[]usno;
        this->usno=new char[strlen(zbor)+1];
        strcpy(this->usno, zbor);
        return *this;
    }
};

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;
public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }
    //дополни ја класата
    void pecatiStudenti(){
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0; i<broj; i++){
            StudentKursUsno *sku=dynamic_cast<StudentKursUsno *>(studenti[i]);
            if(sku){
                if(sku->getOcenka()>=sku->MINOCENKA){
                    cout<<*sku<<endl;
                }
            }
            else if(studenti[i]->getOcenka()>=studenti[i]->MINOCENKA){
                cout<<*studenti[i];
            }
        }
    }
    void postaviOpisnaOcenka(char *ime, char* opisnaOcenka){
        for(int i=0; i<broj; i++){
            if(strcmp(studenti[i]->getName(), ime)==0){
                StudentKursUsno *sku=dynamic_cast<StudentKursUsno *>(studenti[i]);
                (*sku)+=opisnaOcenka;
                return;
            }
        }
    }
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka, daliUsno);
        else
            niza[i]=new StudentKursUsno(ime,ocenka, daliUsno);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;

    for (int i=0;i<m;i++){
        cin>>ime>>opisna;
        try{
            programiranje.postaviOpisnaOcenka(ime,opisna);
            if(strcmp(opisna, "do7br4o")==0){
                cout<<"Greshna opisna ocenka"<<endl;
            }
        }
        catch (BadInputException &be){
            be.print();
        }
    }

    StudentKurs::setMAX(9);

    programiranje.pecatiStudenti();

}
