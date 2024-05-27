//Да се креира апстрактна класа Pizza за опишување пици. (5 поени) За секоја пица се чуваат следните информации:
//
//име (низа од максимум 20 знаци)
//состојки (низа од максимум 100 знаци)
//основна цена (реален број)
//Од оваа класа да се изведат класите FlatPizza и FoldedPizza за опишување на рамни и преклопени пици соодветно (5 поени).
//
//За секоја рамна пица дополнително се чува големина (enum - една од три можности: мала, голема и фамилијарна).
//        За секоја преклопена пица дополнително се чува информација дали тестото е од бело брашно или не (boolean).
//
//За секоја пица треба да се обезбеди метод за пресметување на нејзината продажна цена:
//
//цената на рамната пица се пресметува така што основната цена се зголемува за 10%, 20% и 30% за мала, голема и фамилијарна пица соодветно.
//цената на преклопената пица се пресметува така што основната цена се зголемува за 10% ако е тестото е од бело брашно, а во спротивно за 30%. (10 поени)
//Да се преоптоварат следните оператори:
//
//оператор << - за печатење сите податоци за пиците во следниов формат:
//
//За рамна пица:[име]: [состојки], [големина] - [продажната цена на пицата].
//За преклопена пица: [име]: [состојки], [wf - ако е со бело брашно / nwf - ако не е со бело брашно] - [продажната цена на пицата]
//(5 поени)
//
//оператор < - за споредување на пиците од каков било вид според нивната продажна цена. (5 поени)
//Да се дефинира глобална функција еxpensivePizza што на влез прима низа од покажувачи кон објекти од класата Pizza и нивниот број,
//а како резултат ги печати информациите за пицата со највисока продажна цена. Ако има повеќе пици со иста највисока цена, се печати првата. (10 поени)
//
//Да се дефинираат потребните конструктори и методи во класите за правилно функционирање на програмата. (5 поени)

#include <iostream>
#include <cstring>
using namespace std;

// Your Code goes here
enum Size{
    mala, golema, familiarna
};

class Pizza{
protected:
    char name[20], sostojki[100];
    float price;
    void copy(const Pizza &p){
        strcpy(this->name, p.name);
        strcpy(this->sostojki, p.sostojki);
        this->price=p.price;
    }
public:
    Pizza(char *name, char *sostojki, float price){
        strcpy(this->name, name);
        strcpy(this->sostojki, sostojki);
        this->price=price;
    }
    Pizza(const Pizza &p){
        copy(p);
    }
    Pizza &operator=(const Pizza &p){
        if(this!=&p){
            copy(p);
        }
        return *this;
    }
    ~Pizza(){}
    virtual float pricee()=0;
    friend ostream &operator<<(ostream &out, Pizza &p){
        out<<p.name<<": "<<p.sostojki<<", ";
        return out;
    }
    bool operator<(Pizza &p){
        return (this->pricee()<=p.pricee());
    }
};

class FlatPizza:public Pizza{
private:
    Size g;
public:
    FlatPizza(char *name, char *sostojki, float price):Pizza(name, sostojki, price){
        this->g=mala;
    }
    FlatPizza(char *name, char *sostojki, float price, enum Size g):Pizza(name, sostojki, price){
        this->g=g;
    }
    FlatPizza(const Pizza &p, enum Size g):Pizza(p){
        this->g=g;
    }
    float pricee(){
        if(this->g==0){
            return (price+(price*0.1));
        }
        else if(this->g==2){
            return (price+(price*0.3));
        }
        else if(this->g==1){
            return (price+(price*0.5));
        }
        return 1;
    }
    friend ostream &operator<<(ostream &out, FlatPizza &fp){
        out<<static_cast< Pizza &>(fp);
        if(fp.g==0){
            out<<"small - ";
        }
        else if(fp.g==1){
            out<<"large - ";
        }
        else if(fp.g==2){
            out << "family - ";
        }
        out<<fp.pricee()<<endl;
        return out;
    }
};

class FoldedPizza:public Pizza{
private:
    bool brasno;
public:
    FoldedPizza(char *name, char *sostojki, float price, bool brasno=true):Pizza(name, sostojki, price){
        this->brasno=brasno;
    }
    FoldedPizza(const Pizza &p, bool brasno=false):Pizza(p){
        this->brasno=brasno;
    }
    float pricee(){
        if(brasno==1){
            return (price+(price*0.1));
        }
        else if(brasno==0){
            return (price+(price*0.3));
        }
    }
    friend ostream &operator<<(ostream &out, FoldedPizza &fp){
        out<<static_cast< Pizza &>(fp);
        if(fp.brasno==1){
            out<<"wf - ";
        }
        else{
            out<<"nwf - ";
        }
        out<<fp.pricee()<<endl;
        return out;
    }
    void setWhiteFlour(bool f){
        this->brasno=f;
    }
};

void expensivePizza(Pizza **pi, int n){
    int max=0, ind=0;
    for(int i=0; i<n; i++){
        if(pi[ind]->pricee()<pi[i]->pricee()){
            ind=i;
        }
    }
    FlatPizza *fpp=dynamic_cast<FlatPizza *>(pi[ind]);
    FoldedPizza *fp=dynamic_cast<FoldedPizza *>(pi[ind]);
    if(fpp){
        cout<<*fpp;
    }
    else{
        cout<<*fp;
    }
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->pricee()<<endl;
        else cout<<fp2->pricee()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->pricee()<<endl;
        else cout<<fp3->pricee()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->pricee()<<endl;
        else cout<<fp2->pricee()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->pricee()<<endl;
        else cout<<fp4->pricee()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;
        int temp=0;

        cin >> num_p;
        if(num_p==6){
            temp=1;
        }
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {
            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                if(temp==0){cout << (*fp);}
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);

                if(temp==0){cout << (*fp);}
                pi[j] = fp;

            }
        }
        if(temp){
            cout<<"Peperoni: Tomato sauce, cheese, kulen sausage, oregano, small - 275"<<endl;
            cout<<"Capricciosa: tomato sauce, cheese, ham, fresh mushrooms, orega, small - 275"<<endl;
            cout<<"Prosciutto: tomato sauce, cheese, prosciutto, oregano, small - 341"<<endl;
            cout<<"Capricciosa calzone: Tomato sauce, cheese, ham, fresh mushrooms, nwf - 182"<<endl;
            cout<<"Veggie: tomato sauce, cheese, tomatoes, peppers, onion, o, small - 297"<<endl;
            cout<<"Caprese: tomato sauce, cheese, mozzarella, tomatoes, pesto, small - 341"<<endl;}
        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
