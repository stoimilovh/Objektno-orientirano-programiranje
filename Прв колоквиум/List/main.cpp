//Да се имплементира класа List во којашто ќе се чуваат информации за:
//
//броеви што се дел од листата (динамички алоцирана низа од цели броеви)
//бројот на броеви што се дел од листата
//За класата да се дефинираат следните методи:
//
//конструктор (со аргументи), copy-конструктор, деструктор, оператор =
//void pecati()метод што ќе ги печати информациите за листата во форматот: [број на елементи во листата]: x1 x2 .. xn sum: [сума] average: [просек]
//int sum() метод што ја враќа сумата на елементите во листата
//double average() метод што ќе го враќа просекот на броевите во листата
//Дополнително, креирајте класата ListContainer, во која што ќе се чуваат информации за:
//
//низа од листи (динамички алоцирана низа од објекти од класата List)
//број на елементи во низата од листи (цел број)
//број на обиди за додавање на листа во контејнерот (цел број првично поставен на нула)
//За класата потребно е да ги дефинирате следните методи:
//
//конструктор (default), copy-конструктор, деструктор, оператор =
//void pecati() метод што ќе ги печати информациите за контејнерот во форматот: List number: [реден број на листата]
//List info: [испечатени информации за листата со методот List::pecati()] \n sum: [сума] average: [просек]
//доколку контејнерот е празен се печати само порака The list is empty.
//void addNewList(List l) метод со којшто се додава листа во контејнерот
//Напомена: една листа се додава во контејнерот ако и само ако има различна сума од сите листи што се веќе додадени во контејнерот
//int sum() метод што ја враќа сумата на сите елементи во сите листи
//double average() метод што го враќа просекот на сите елементи во сите листи во контејнерот

#include <iostream>
using namespace std;

class List{
private:
    int *niza;
    int n;
    void copy(const List &l){
        this->n=l.n;
        this->niza=new int[l.n];
        for(int i=0; i<n; i++){
            this->niza[i]=l.niza[i];
        }
    }
public:
    List(int *niza, int n=0){
        this->n=n;
        this->niza=new int[n];
        for(int i=0; i<n; i++){
            this->niza[i]=niza[i];
        }
    }
    List(const int n=0){
        this->n=n;
        this->niza=new int[n];
        for(int i=0; i<n; i++){
            this->niza[i]=niza[i];
        }
    }
    List(const List &l){
        copy(l);
    }
    List &operator=(const List &l){
        if(this!=&l){
            delete[]niza;
            copy(l);
        }
        return *this;
    }
    ~List(){
        delete[]niza;
    }
    int sum(){
        int sum=0;
        for(int i=0; i<n; i++){
            sum+=niza[i];
        }
        return sum;
    }
    double average(){
        return (double)sum()/n;
    }
    int getn(){return n;}
    void pecati(){
        cout<<n<<": ";
        for(int i=0; i<n; i++){
            cout<<niza[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average();
    }
};

class ListContainer{
private:
    List *l;
    int N, obidi=0, fail=0;;
    void copy(const ListContainer &lc){
        this->N=lc.N;
        this->obidi=lc.obidi;
        this->fail=lc.fail;
        this->l=new List[lc.N];
        for(int i=0; i<N; i++){
            this->l[i]=lc.l[i];
        }
    }
public:
    ListContainer(const int N=0){
        this->N=N;
        this->obidi=obidi;
        this->fail=0;
        this->l=new List[N];
        for(int i=0; i<N; i++){
            this->l[i]=l[i];
        }
    }
    ListContainer(List *l, int N=0, int obidi=0){
        this->N=N;
        this->obidi=obidi;
        this->l=new List[N];
        for(int i=0; i<N; i++){
            this->l[i]=l[i];
        }
    }
    ListContainer(const ListContainer &lc){
        copy(lc);
    }
    ListContainer &operator=(const ListContainer &lc){
        if(this!=&lc){
            delete[]l;
            copy(lc);
        }
        return *this;
    }
    ~ListContainer(){
        delete[]l;
    }
    void addNewList(List r){
        for(int i=0; i<N; i++){
            if(r.sum()==l[i].sum()){
                fail++;
                return;
            }
        }
        List *tmp=new List[N+1];
        for(int i=0; i<N; i++){
            tmp[i]=l[i];
        }
        tmp[N]=r;
        delete[]l;
        l=tmp;
        N++;
        obidi++;
    }
    int sum(){
        int sumata=0;
        for(int i=0; i<N; i++){
            sumata+=l[i].sum();
        }
        return sumata;
    }
    double average(){
        int brojach=0, suma=0;
        for(int i=0; i<N; i++){
            brojach+=l[i].getn();
            suma+=l[i].sum();
        }
        return (double)suma/brojach;
    }
    void print(){
        if(N==0){
            cout<<"The list is empty"<<endl;
            return;
        }
        for(int i=0; i<obidi; i++){
            cout<<"List number: "<<i+1<<" List info: ";
            l[i].pecati();
            cout<<endl;
        }
        cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
        cout<<"Successful attempts: "<<obidi<<" Failed attempts: "<<fail<<endl;
    }
};

int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }
}