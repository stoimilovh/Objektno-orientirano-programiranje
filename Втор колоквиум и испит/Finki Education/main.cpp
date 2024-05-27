//Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот
//(низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и
//основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).
//
//За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци)
//и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми
//(реален број) и дали ја има на залиха (логичка променлива). (5 поени)
//
//За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
//Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)
//За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB
//За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg
//Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)
//Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
//Да се имплементира функција mostExpensiveBook со потпис:
//
//void mostExpensiveBook (Book** books, int n)
//
//во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени)
//Потоа се наоѓа и печати најскапата книга. (5 поени)
//Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

class Book{
protected:
    char isbn[20], title[50], author[30];
    float price;
    void copy(const Book &b){
        strcpy(this->isbn, b.isbn);
        strcpy(this->title, b.title);
        strcpy(this->author, b.author);
        this->price=b.price;
    }
public:
    Book(float price=0){}
    Book(char *isbn, char *title, char *author, float price){
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price=price;
    }
    Book(const Book &b){
        copy(b);
    }
    Book &operator=(const Book &b){
        if(this!=&b){
            copy(b);
        }
        return *this;
    }
    ~Book(){}
    virtual double bookPrice()=0;
    virtual bool operator>(const Book &ob1) {
        return (this->price>ob1.price);
    }
    friend ostream &operator<<(ostream &out, Book &b){
        return out<<b.isbn<<": "<<b.title<<", "<<b.author<<" "<<b.bookPrice()<<endl;
    }
};

class OnlineBook:public Book{
private:
    char *url;
    int mb;
public:
    OnlineBook(char *isbn, char *title, char *author, float price, char *url, int mb):Book(isbn, title, author, price){
        this->url=new char[strlen(url)+1];
        strcpy(this->url, url);
        this->mb=mb;
    }
    OnlineBook(const Book &b, char *url, int mb):Book(b){
        this->url=new char[strlen(url)+1];
        strcpy(this->url, url);
        this->mb=mb;
    }
    OnlineBook(const OnlineBook &ob){
        strcpy(this->isbn, ob.isbn);
        strcpy(this->title, ob.title);
        strcpy(this->author, ob.author);
        this->price=ob.price;
        this->url=new char[strlen(ob.url)+1];
        strcpy(this->url, ob.url);
        this->mb=ob.mb;
    }
    OnlineBook &operator=(const OnlineBook &ob){
        if(this!=&ob){
            delete[]url;
            strcpy(this->isbn, ob.isbn);
            strcpy(this->title, ob.title);
            strcpy(this->author, ob.author);
            this->price=ob.price;
            this->url=new char[strlen(ob.url)+1];
            strcpy(this->url, ob.url);
            this->mb=ob.mb;
        }
        return *this;
    }
    ~OnlineBook(){
        delete[]url;
    }
    double bookPrice()override{
        if(mb>=20){
            float cena=price*0.20;
            return price+cena;
        }
        else{
            return price;
        }
    }
    bool operator>(OnlineBook *ob1) {
        return (this->bookPrice()>ob1->bookPrice());
    }
    friend ostream &operator<<(ostream &out, const OnlineBook &pb){
        out<<pb.isbn<<": "<<pb.title<<", "<<pb.author<<" ";
        if(pb.mb>=20){
            out<<pb.price*1.2<<endl;
        }
        else{
            out<<pb.price<<endl;
        }
        return out;
    }
    void setISBN(char *isbn){
        strcpy(this->isbn, isbn);
    }
};

class PrintBook:public Book{
private:
    float kg;
    bool inStock;
public:
    PrintBook(char *isbn, char *title, char *author, float price, float kg, bool inStock):Book(isbn, title, author, price){
        this->kg=kg;
        this->inStock=inStock;
    }
    PrintBook(const Book &b, float kg, bool inStock):Book(b){
        this->kg=kg;
        this->inStock=inStock;
    }
    PrintBook &operator=(const PrintBook &pb){
        if(this!=&pb){
            strcpy(this->isbn, pb.isbn);
            strcpy(this->title, pb.title);
            strcpy(this->author, pb.author);
            this->price=pb.price;
            this->kg=pb.kg;
            this->inStock=pb.inStock;
        }
        return *this;
    }
    ~PrintBook(){}
    double bookPrice()override{
        if(kg>0.7){
            return price*1.15;;
        }
        return price;
    }
    bool operator>(PrintBook *ob1) {
        return (this->bookPrice()>ob1->bookPrice());
    }
    friend ostream &operator<<(ostream &out, const PrintBook &pb){
        out<<pb.isbn<<": "<<pb.title<<", "<<pb.author<<" ";
        if(pb.kg>=0.7){
            out<<pb.price*1.15<<endl;
        }
        else{
            out<<pb.price<<endl;
        }
        return out;
    }
    void setISBN(char *isbn){
        strcpy(this->isbn, isbn);
    }
};

void mostExpensiveBook(Book **books, int n){
    int print=0, online=0;
    for (int i = 0; i < n; ++i) {
        PrintBook *pb=dynamic_cast<PrintBook *>(books[i]);
        if(pb!=0){
            print++;
        }
        else{
            online++;
        }
    }
    int max=-9, ind=0;
    for (int i = 0; i < n-1; ++i) {
        if(books[i]->bookPrice()>max){
            ind=i;
            max=books[ind]->bookPrice();
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<print<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[ind];
}

int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }
    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}

