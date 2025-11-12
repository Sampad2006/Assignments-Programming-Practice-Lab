/*
In a library, for each book book-id, serial number (denotes copy number of a book),
title, author, publisher and price are stored. Book-id and serial number together will
be unique identifier for a book. Members are either student or faculty. Each member
has unique member-id. Name, e-mail, address are also to be stored. For any
transaction (book issue or return), members are supposed to place transactions slip.
User will submit member-id, book-id, and serial number (only for book return).
While processing a transaction, check the validity of the member. While issuing,
availability of a copy of the book is to be checked. While returning a book, it is to be
checked whether this copy was issued to the member or not. A student member can
have 2 books issued at a point of time. For faculty members it is 10. Transaction
information is to be stored like date of transaction, member-id, book-id, serial
number, returned or not. An entry is made when book is issued and updated when
the book is returned. For storing the information consider files.
Design the classes and implement.

Name:Sampad De
Roll-002410501025
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class Book {
public:
    int bookID;
    int serialNo;
    string title, author, publisher;
    double price;
    bool issued;

    Book(int id=0,int sn=0,string t="",string a="",string p="",double pr=0.0,bool iss=false){
        bookID=id; serialNo=sn; title=t; author=a; publisher=p; price=pr; issued=iss;
    }

    void display(){
        cout << "BookID: " << bookID << " | Serial: " << serialNo << " | "
             << title << " | " << author << " | " << publisher
             << " | Rs." << price << (issued ? " | [Issued]" : " | [Available]") << endl;
    }
};

class Member {
public:
    int memberID;
    string name, email, address;
    int maxBooks;
    int issuedCount;

    Member(int id=0,string n="",string e="",string a="",int maxB=2,int ic=0){
        memberID=id; name=n; email=e; address=a; maxBooks=maxB; issuedCount=ic;
    }

    virtual string type(){ return "Member"; }

    virtual void display(){
        cout << memberID << " | " << name << " | " << email << " | " << address
             << " | Type: " << type() << " | Books issued: " << issuedCount << endl;
    }

    bool canIssue(){ return issuedCount < maxBooks; }
    virtual ~Member(){}
};

class Student : public Member {
public:
    Student(int id=0,string n="",string e="",string a="",int ic=0)
        : Member(id,n,e,a,2,ic) {}
    string type(){ return "Student"; }
};

class Faculty : public Member {
public:
    Faculty(int id=0,string n="",string e="",string a="",int ic=0)
        : Member(id,n,e,a,10,ic) {}
    string type(){ return "Faculty"; }
};

class Transaction {
public:
    int memberID, bookID, serialNo;
    string date;
    bool returned;

    Transaction(int mid=0,int bid=0,int sn=0,string d="",bool r=false){
        memberID=mid; bookID=bid; serialNo=sn; date=d; returned=r;
    }

    void display(){
        cout << "MemberID: " << memberID << " | BookID: " << bookID
             << " | Serial: " << serialNo << " | Date: " << date
             << (returned ? " | Returned\n" : " | Issued\n");
    }
};

class LibrarySystem {
    vector<Book> books;
    vector<Member*> members;
    vector<Transaction> transactions;

    string currentDate(){
        time_t now = time(0);
        string d = ctime(&now);
        d.pop_back(); 
        return d;
    }

public:
    LibrarySystem(){
        loadBooks();
        loadMembers();
        loadTransactions();
    }

    ~LibrarySystem(){
        saveBooks();
        saveMembers();
        saveTransactions();
        for(auto m:members) delete m;
    }

    void addBook(){
        int id,sn;
        string title,author,pub;
        double price;
        cout<<"Enter Book ID: "; cin>>id;
        cout<<"Enter Serial No: "; cin>>sn;
        for(auto &b:books)
            if(b.bookID==id && b.serialNo==sn){ cout<<"Book already exists!\n"; return; }
        cin.ignore();
        cout<<"Enter Title: "; getline(cin,title);
        cout<<"Enter Author: "; getline(cin,author);
        cout<<"Enter Publisher: "; getline(cin,pub);
        cout<<"Enter Price: "; cin>>price;
        books.push_back(Book(id,sn,title,author,pub,price,false));
        cout<<"Book added.\n";
    }

    void addMember(){
        int id,type;
        string name,email,addr;
        cout<<"Enter Member ID: "; cin>>id;
        for(auto m:members)
            if(m->memberID==id){ cout<<"Member exists!\n"; return; }
        cin.ignore();
        cout<<"Enter Name: "; getline(cin,name);
        cout<<"Enter Email: "; getline(cin,email);
        cout<<"Enter Address: "; getline(cin,addr);
        cout<<"Type (1=Student, 2=Faculty): "; cin>>type;
        if(type==1) members.push_back(new Student(id,name,email,addr));
        else members.push_back(new Faculty(id,name,email,addr));
        cout<<"Member added.\n";
    }

    Member* findMember(int id){
        for(auto m:members)
            if(m->memberID==id) return m;
        return nullptr;
    }

    Book* findBook(int bid,int sn){
        for(auto &b:books)
            if(b.bookID==bid && b.serialNo==sn) return &b;
        return nullptr;
    }

    void issueBook(){
        int mid,bid;
        cout<<"Enter Member ID: "; cin>>mid;
        Member* mem=findMember(mid);
        if(!mem){ cout<<"Invalid member!\n"; return; }

        if(!mem->canIssue()){ cout<<"Issue limit reached!\n"; return; }

        cout<<"Enter Book ID: "; cin>>bid;
        bool found=false;
        for(auto &b:books){
            if(b.bookID==bid && !b.issued){
                b.issued=true;
                mem->issuedCount++;
                transactions.push_back(Transaction(mid,b.bookID,b.serialNo,currentDate(),false));
                cout<<"Book issued.\n";
                found=true;
                break;
            }
        }
        if(!found) cout<<"No available copy found.\n";
    }

    void returnBook(){
        int mid,bid,sn;
        cout<<"Enter Member ID: "; cin>>mid;
        Member* mem=findMember(mid);
        if(!mem){ cout<<"Invalid member!\n"; return; }

        cout<<"Enter Book ID: "; cin>>bid;
        cout<<"Enter Serial No: "; cin>>sn;
        Book* b=findBook(bid,sn);
        if(!b){ cout<<"Book not found!\n"; return; }

        bool match=false;
        for(auto &t:transactions){
            if(t.memberID==mid && t.bookID==bid && t.serialNo==sn && !t.returned){
                t.returned=true;
                b->issued=false;
                mem->issuedCount--;
                cout<<"Book returned.\n";
                match=true;
                break;
            }
        }
        if(!match) cout<<"No matching issue record found!\n";
    }

    void showBooks(){
        cout<<"\n--- Books List ---\n";
        for(auto &b:books) b.display();
    }

    void showMembers(){
        cout<<"\n--- Members List ---\n";
        for(auto m:members) m->display();
    }

    void showTransactions(){
        cout<<"\n--- Transactions ---\n";
        for(auto &t:transactions) t.display();
    }

    // ---------- File Handling ----------

    void saveBooks(){
        ofstream fout("books.txt");
        for(auto &b:books)
            fout<<b.bookID<<"|"<<b.serialNo<<"|"<<b.title<<"|"<<b.author<<"|"
                <<b.publisher<<"|"<<b.price<<"|"<<b.issued<<"\n";
        fout.close();
    }

    void loadBooks(){
        ifstream fin("books.txt");
        if(!fin) return;
        books.clear();
        int id,sn; string title,author,pub; double price; bool issued;
        while(fin>>id){
            char ch;
            fin>>ch>>sn>>ch;
            getline(fin,title,'|');
            getline(fin,author,'|');
            getline(fin,pub,'|');
            fin>>price>>ch>>issued;
            books.push_back(Book(id,sn,title,author,pub,price,issued));
            fin.ignore();
        }
        fin.close();
    }

    void saveMembers(){
        ofstream fout("members.txt");
        for(auto m:members)
            fout<<m->memberID<<"|"<<m->name<<"|"<<m->email<<"|"<<m->address<<"|"
                <<m->type()<<"|"<<m->issuedCount<<"\n";
        fout.close();
    }

    void loadMembers(){
        ifstream fin("members.txt");
        if(!fin) return;
        members.clear();
        int id,ic; string name,email,addr,type;
        while(fin>>id){
            char ch; fin>>ch;
            getline(fin,name,'|');
            getline(fin,email,'|');
            getline(fin,addr,'|');
            getline(fin,type,'|');
            fin>>ic;
            if(type=="Student") members.push_back(new Student(id,name,email,addr,ic));
            else members.push_back(new Faculty(id,name,email,addr,ic));
            fin.ignore();
        }
        fin.close();
    }

    void saveTransactions(){
        ofstream fout("transactions.txt");
        for(auto &t:transactions)
            fout<<t.memberID<<"|"<<t.bookID<<"|"<<t.serialNo<<"|"
                <<t.date<<"|"<<t.returned<<"\n";
        fout.close();
    }

    void loadTransactions(){
        ifstream fin("transactions.txt");
        if(!fin) return;
        transactions.clear();
        int mid,bid,sn; string date; bool ret;
        while(fin>>mid){
            char ch;
            fin>>ch>>bid>>ch>>sn>>ch;
            getline(fin,date,'|');
            fin>>ret;
            transactions.push_back(Transaction(mid,bid,sn,date,ret));
            fin.ignore();
        }
        fin.close();
    }
};

int main(){
    LibrarySystem lib;
    int choice;
    while(true){
        cout<<"\n====== LIBRARY MENU ======\n";
        cout<<"1. Add Book\n";
        cout<<"2. Add Member\n";
        cout<<"3. Issue Book\n";
        cout<<"4. Return Book\n";
        cout<<"5. Show Books\n";
        cout<<"6. Show Members\n";
        cout<<"7. Show Transactions\n";
        cout<<"8. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice){
            case 1: lib.addBook(); break;
            case 2: lib.addMember(); break;
            case 3: lib.issueBook(); break;
            case 4: lib.returnBook(); break;
            case 5: lib.showBooks(); break;
            case 6: lib.showMembers(); break;
            case 7: lib.showTransactions(); break;
            case 8: cout<<"Exiting and saving data...\n"; return 0;
            default: cout<<"Invalid choice!\n";
        }
    }
}
