//Во рамките на еден телекомуникациски оператор, СМС пораките се делат на регуларни и специјални. За секојa СМС порака се знае:
//
//основна цена за една порака до 160 знаци (реален број)
//претплатнички број на кој е испратена (низа од знаци со должина 12)
//Класата за опишување на СМС пораки е апстрактна (5 поени).
//
//За секоја Регуларна СМСдополнително се чуваат податоци за текстот на пораката и тоа дали е користена роаминг услуга
//(bool променлива). За секоја Специјална СМС дополнително се чуваат податоци за тоа дали е наменета за хуманитарни цели (bool променлива). (5 поени)
//
//За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
//
//Метод SMS_cena(), за пресметување на цената на испратена СМС порака на следниот начин: (10 поени)
//
//За регуларна СМС - цената се зголемува за 300% од основната цена ако е испратена од странство, а 18% од
//дома и цената се формира врз база на тоа во колку СМС пораки ќе го собере текстот што сакаме да го испратиме.
//Една регуларна порака може да собере најмногу 160 знаци. Притоа, доколку се надмине 160-от знак, се започнува
//нова порака и цената се пресметува како за две или повеќе пораки (пр. за 162 знаци, цената на СМС е иста како и за 320 знаци).
//За специјална СМС - цената се зголемува за 150% од основната цена ако пораката HE е наменета за хуманитарни цели.
//Доколку е наменета за тоа, данокот од 18% не се пресметува на цената.
//Пресметувањето 18% данок на цената на сите СМС пораки е фиксен и не се менува, додека пак процентот од 300% за
//регуларни и 150% за специјални СМС е променлив и во зависност од операторот може да се менува. Да се обезбеди
//механизам за можност за нивно менување. (5 поени)
//Преоптоварен оператор << за печатење на податоците за СМС пораките во формат: (5 поени)
//
//Тел.број: цена
//        Да се имплементира функција vkupno_SMS со потпис:
//
//void vkupno_SMS(SMS** poraka, int n)
//во која се печати вкупниот број на регуларни СМС пораки и нивната вкупна цена, како и бројот на специјални
//СМС пораки и нивната вкупна цена во проследената низа посебно. (15 поени)
//
//Да се обезбедат сите потребни функции за правилно функционирање на програмата (5 поени).

#include <iostream>
#include <cstring>
using namespace std;

class SMS {
protected:
    float cena;
    char broj[15];
public:
    SMS(char *broj, float cena) {
        this->cena = cena;
        strncpy(this->broj, broj, 13);
    }
    virtual float SMS_cena()=0;
    friend ostream &operator<<(ostream &out, SMS &s){
        return out<<"Tel: "<<s.broj<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
    }
};

class RegularSMS:public SMS{
private:
    char txt[1000];
    bool rom;
    static float procent;
public:
    RegularSMS(char *broj, float cena, char *txt, bool rom):SMS(broj, cena){
        strcpy(this->txt, txt);
        this->rom=rom;
    }
    static void set_rProcent(int p){
        procent=p/100.0;
    }
    float SMS_cena(){
        if(strlen(txt)<160){
            if(rom){
                return cena+(cena*procent);
            }
            else{
                return cena+(cena*0.18);
            }
        }
        else{
            int h=strlen(txt);
            int o=h/160;
            if(h%160>0){
                o++;
            }
            if(rom){
                return o*(cena+(cena*0.3));
            }
            else{
                return o*(cena+(cena*0.18));
            }
        }
    }
};

class SpecialSMS:public SMS{
private:
    bool hum;
    static float procent;
public:
    SpecialSMS(char *broj, float cena, bool hum):SMS(broj, cena){
        this->hum=hum;
    }
    static void set_sProcent(int p){
        procent=p/100.0;
    }
    float SMS_cena(){
        if(hum==0){
            return cena+(cena*procent);
        }
        else{
            return cena;
        }
    }
};

float RegularSMS::procent=3;
float SpecialSMS::procent=1.5;

void vkupno_SMS(SMS** poraka, int n){
    int ss=0, rr=0;
    float reg=0, spec=0;
    for(int i=0; i<n; i++){
        SpecialSMS *s=dynamic_cast<SpecialSMS *>(poraka[i]);
        if(s){
            ss++;
            spec+=s->SMS_cena();
        }
        else if(s==0){
            rr++;
            RegularSMS *r=dynamic_cast<RegularSMS *>(poraka[i]);
            reg+=r->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<rr<<" regularni SMS poraki i nivnata cena e: "<<reg<<endl;
    cout<<"Vkupno ima "<<ss<<" specijalni SMS poraki i nivnata cena e: "<<spec<<endl;
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
