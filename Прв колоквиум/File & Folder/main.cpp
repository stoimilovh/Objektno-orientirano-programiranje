//Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.
//
//Во класата File треба да се чуваат следниве податоци:
//
//Име на датотеката (динамички алоцирана низа од знаци)
//Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
//Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
//Големина на датотеката (цел број на мегабајти)
//Дополнително, во класата потребно е да се напишат и:
//
//Конструктор без параметри
//Конструктор со параметри
//Конструктор за копирање
//Деструктор
//Преоптоварување на операторот =
//Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
//Метод за проверка на еднаквост помеѓу две датотеки со потпис
//bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
//Метод за споредба на типот помеѓу две датотеки со потпис
//bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
//Во класата Folder треба да се чуваат следниве податоци:
//Име на директориумот (динамички алоцирана низа од знаци)
//Број на датотеки во него (на почеток директориумот е празен)
//Динамички алоцирана низа од датотеки, објекти од класата File
//Дополнително, во класата потребно е да се напишат и:
//
//Конструктор со потпис Folder(const char* name)
//Деструктор
//Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
//Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека
//од директориумот која е еднаква според equals методот
//Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот

#include <iostream>
#include <cstring>
using namespace std;

enum Extension{
    txt, pdf, exe
};

class File{
private:
    char *fileName;
    Extension ex;
    char *fileOwner;
    int fileSize;
    void copy(const File &f){
        this->fileName=new char [strlen(f.fileName)+1];
        strcpy(this->fileName, f.fileName);
        this->fileSize=f.fileSize;
        this->ex=f.ex;
        this->fileOwner=new char [strlen(f.fileOwner)+1];
        strcpy(this->fileOwner, f.fileOwner);
    }
public:
    File(int fileSize=0){
        this->fileName=NULL;
        this->fileOwner=NULL;
        fileSize=0;
    }
    File(char *fileName, char *fileOwner, int fileSize, Extension ex){
        this->fileName=new char [strlen(fileName)+1];
        strcpy(this->fileName, fileName);
        this->fileSize=fileSize;
        this->ex=ex;
        this->fileOwner=new char [strlen(fileOwner)+1];
        strcpy(this->fileOwner, fileOwner);
    }
    File(const File &f){
        copy(f);
    }
    File &operator=(const File &f){
        if(this!=&f){
            delete[]fileName;
            delete[]fileOwner;
            copy(f);
        }
        return *this;
    }
    ~File(){
        delete[]fileName;
        delete[]fileOwner;
    }
    void print(){
        cout<<"File name: "<<fileName;
        if(ex==1){
            cout<<".txt"<<endl;
        }
        else if(ex==0){
            cout<<".pdf"<<endl;
        }
        else if(ex==2){
            cout<<".exe"<<endl;
        }
        cout<<"File owner: "<<fileOwner<<endl<<"File size: "<<fileSize<<endl;
    }
    bool equals(const File & that){
        if(strcmp(fileName, that.fileName)==0){
            if(strcmp(fileOwner, that.fileOwner)==0){
                if(ex==that.ex){
                    return true;
                }
            }
        }
        return false;
    }
    bool equalsType(const File & that){
        if(ex==that.ex){
            return true;
        }
        return false;
    }
};

class Folder{
private:
    char *dirName;
    int num;
    File *f;
    void copy(const Folder &ff){
        this->dirName=new char[strlen(ff.dirName)+1];
        strcpy(this->dirName, ff.dirName);
        this->num=ff.num;
        for(int i=0; i<num; i++){
            this->f[i]=ff.f[i];
        }
    }
public:
    Folder(const char* name){
        this->dirName=new char[strlen(name)+1];
        strcpy(this->dirName, name);
        num=0;
        f=NULL;
    }
    Folder(const Folder &ff){
        copy(ff);
    }
    Folder &operator=(const Folder &ff){
        if(this!=&ff){
            delete[]dirName;
            delete[]f;
            copy(ff);
        }
        return *this;
    }
    void print(){
        cout<<"Folder name: "<<dirName<<endl;
        for(int i=0; i<num; i++){
            f[i].print();
        }
    }
    void remove(const File & file){
        int j=0;
        for(int i=0; i<num; i++){
            if(!f[i].equals(file)){
                f[j]=f[i];
                j++;
            }
        }
        num=j;
    }
     void add(const File & file){
        File *fff=new File[num+1];
        for(int i=0; i<num; i++){
            fff[i]=f[i];
        }
        fff[num]=file;
        delete[]f;
        f=fff;
        num++;
     }
};

int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}