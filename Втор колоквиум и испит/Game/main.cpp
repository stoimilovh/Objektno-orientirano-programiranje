//Потребно е да се имплементира класа за компјутерска игра (Game), што содржи информации за:
//
//име на играта (низа од макс. 100 знаци)
//цена на играта (децимален број)
//дали е играта купена на распродажба (bool променлива).
//Од класата Game да се изведе класа SubscriptionGame, што дополнително ќе чува:
//
//месечен надоместок за играње (децимален број).
//датум кога играта е купена (месец и година како позитивни цели броеви)
//За класите Game и SubscriptionGame да се преоптоварат операторите за печатење (<<) и читање (>>).
//Да се дефинира и операторот == кој ќе споредува игри според нивното име.
//
//Да се дефинира класа за корисник (User) во која се чуваат:
//
//кориснично име на корисникот (низа од макс. 100 знаци)
//колекција од игри кои се купени од корисникот (динамички алоцирана низа).
//Да се преоптовари операторот += кој ќе овозможи додавање на нова игра во колекцијата на игри.
//        Притоа ако корисникот ја има веќе купено играта, потребно е да се креира исклучок од типот ExistingGame.
//        Класата за имплементација на исклучоци потребно е има соодветен конструктор и метода message за печатење на порака на екран.
//
//Да се креира и метода total_spent() во класата User која ќе пресметува колку пари корисникот потрошил за својата
//колекција од игри. Доколку играта е купена на распродажба, цената на играта е 30% од стандарната цена. Доколку играта е од типот
//SubscriptionGame, потребно е да се вкалкулира и сумата потрошена за месечниот надоместок (број_на_изминати_месеци x цена_на_месечен_надоместок)
//без да се земе во предвид моменталниот месец (мај 2018).
//
//Да се преоптовари и оператоторот за печатење на корисникот, која печати информации во сл. формат (види тест примери 7 до 12):
//
//User: username
//- Game: PUBG, regular price: $70, bought on sale
//- Game: Half Life 2, regular price: $70 - Game: Warcraft 4, regular price: $40, monthly fee: $10, purchased: 1-2017
//
//Листа на дел од методите со нивни прототипови кои се користат во main:
//
//ЕxistingGame::message()
//Game::operator==(Game&)
//User::operator+=(Game&)
//User::get_game(int)
//User::total_spent(int)
//User::get_name()
//User::get_games_number()

#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame{
public:
    void message(){
        cout<<"The game is already in the collection"<<endl;
    }
};

class Game{
protected:
    char name[100];
    float cena;
    bool rasprodazba;
public:
    Game(const char *name="", float cena=0, bool rasprodazba= false){
        strcpy(this->name, name);
        this->cena=cena;
        this->rasprodazba=rasprodazba;
    }
    virtual float getPrice(){
        return cena;
    }
    friend istream &operator>>(istream &in, Game &g){
        in.get();
        in.getline(g.name, 100);
        return in>>g.cena>>g.rasprodazba;
    }
    friend ostream &operator<<(ostream &out, Game &g){
        out<<"Game: "<<g.name<<", regular price: $"<<g.cena;
        if(g.rasprodazba){
            out<<", bought on sale";
        }
        return out;
    }
    friend class User;
};

class SubscriptionGame:public Game{
private:
    float nadomestok;
    int month, year;
public:
    SubscriptionGame(const char *name="", float cena=0, bool rasprodazba= false, float nadomestok=0, int month=0, int year=0):Game(name, cena, rasprodazba){
        this->nadomestok=nadomestok;
        this->month=month;
        this->year=year;
    }
    float getPrice(){
        return cena+nadomestok;
    }
    friend istream &operator>>(istream &in, SubscriptionGame &sg){
        in.get();
        in.getline(sg.name, 100);
        in>>sg.cena>>sg.rasprodazba;
        in>>sg.nadomestok>>sg.month>>sg.year;
        return in;
    }
    friend ostream &operator<<(ostream &out, SubscriptionGame &sg){
        Game *g=dynamic_cast<Game *>(&sg);
        out<<*g;
        out<<", monthly fee: $"<<sg.nadomestok<<", purchased: "<<sg.month<<"-"<<sg.year;
        return out;
    }
    friend class User;
};

class User{
private:
    char ime[100];
    Game **g;
    int num=0;
public:
    User(const char *ime="", Game **g=nullptr, int num=0){
        strcpy(this->ime, ime);
        this->num=num;
        this->g=new Game*[num];
        for(int i=0; i<num; i++){
            this->g[i]=g[i];
        }
    }
    ~User(){
        delete[]g;
    }
    User &operator+=(Game &gg){
        for(int i=0; i<num; i++){
            if(strcmp(g[i]->name, gg.name)==0){
                throw ExistingGame();
            }
        }
        Game **gs=new Game*[num+1];
        for(int i=0; i<num; i++){
            gs[i]=g[i];
        }
        gs[num]=&gg;
        delete[]g;
        g=gs;
        num++;
        return *this;
    }
    friend ostream &operator<<(ostream &out, User &u){
        out<<endl;
        out<<"User: "<<u.ime<<endl;
        for(int i=0; i<u.num; i++){
            SubscriptionGame *sg=dynamic_cast<SubscriptionGame *>(u.g[i]);
            if(sg){
                out<<"- ";
                out<<*sg;
            }
            else{
                out<<"- ";
                out<<*u.g[i]<<endl;
            }
        }
        out<<endl;
        return out;
    }
    float total_spent(){
        float broj=0;
        for(int i=0; i<num; i++){
            broj+=g[i]->getPrice();
            SubscriptionGame *sg=dynamic_cast<SubscriptionGame *>(g[i]);
            if(sg){
                if(sg->year<2018){
                    int mesec=sg->month, godina=sg->year;
                    while(mesec){
                        broj+=sg->nadomestok;
                        mesec++;
                        if(mesec==12){
                            mesec=0;
                            godina++;
                        }
                    }
                    while(mesec!=4){
                        broj+=sg->nadomestok;
                        mesec++;
                    }
                }
            }
        }
        return broj;
    }
};

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout<<u;
        cout<<endl;
        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
    return 0;
}
