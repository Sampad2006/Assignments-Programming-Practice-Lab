/*
In a library, for each book book-id, serial number (denotes copy number of a
book), title, author, publisher and price are stored. Book-id and serial number
together will be unique identifier for a book. Members are either student or
faculty. Each member has unique member-id. Name, e-mail, address are also to
be stored. For any transaction (book issue or return), members are supposed to
place transactions slip. User will submit member-id, book-id, and serial number
(only for book return). While processing a transaction, check the validity of the
member. While issuing, availability of a copy of the book is to be checked. While
returning a book, it is to be checked whether this copy was issued to the member
or not. A student member can have 2 books issued at a point of time. For faculty
members it is 10. Transaction information is to be stored like date of transaction,
member-id, book-id, serial number, returned or not. An entry is made when
book is issued and updated when the book is returned.
Design the classes and implement. For list consider memory data structure.

Name:Sampad De
Roll-002410501025
*/

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Book {
public:
    int bookID;
    int serialNo;
    string title, author, publisher;
    double price;
    bool issued;

    Book(int id=0,int sn=0,string t="",string a="",string p="",double pr=0.0){
        bookID=id; serialNo=sn; title=t; author=a; publisher=p; price=pr; issued=false;
    }

    void display(){
        cout << "BookID: " << bookID << " | Serial: " << serialNo
             << " | " << title << " | " << author << " | " << publisher
             << " | Rs." << price << (issued ? " | [Issued]" : " | [Available]") << endl;
    }
};

class Member {
public:
    int memberID;
    string name, email, address;
    int maxBooks;
    int issuedCount;

    Member(int id=0,string n="",string e="",string a="",int maxB=2){
        memberID=id; name=n; email=e; address=a; maxBooks=maxB; issuedCount=0;
    }

    virtual string type(){ return "Member"; }

    virtual void display(){
        cout << memberID << " | " << name << " | " << email << " | " << address
             << " | Type: " << type() << " | Books issued: " << issuedCount << endl;
    }

    bool canIssue(){ return issuedCount < maxBooks; }
};

class Student : public Member {
public:
    Student(int id=0,string n="",string e="",string a="") : Member(id,n,e,a,2) {}
    string type(){ return "Student"; }
};

class Faculty : public Member {
public:
    Faculty(int id=0,string n="",string e="",string a="") : Member(id,n,e,a,10) {}
    string type(){ return "Faculty"; }
};

class Transaction {
public:
    int memberID;
    int bookID;
    int serialNo;
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
        d.pop_back(); // remove newline
        return d;
    }

public:
    void addBook(){
        int id,sn;
        string title, author, pub;
        double price;
        cout << "Enter Book ID: "; cin >> id;
        cout << "Enter Serial Number: "; cin >> sn;
        for(auto &b:books)
            if(b.bookID==id && b.serialNo==sn){ cout<<"Book already exists!\n"; return; }
        cin.ignore();
        cout << "Enter Title: "; getline(cin,title);
        cout << "Enter Author: "; getline(cin,author);
        cout << "Enter Publisher: "; getline(cin,pub);
        cout << "Enter Price: "; cin >> price;
        books.push_back(Book(id,sn,title,author,pub,price));
        cout << "Book added.\n";
    }

    void addMember(){
        int id,type;
        string name,email,addr;
        cout << "Enter Member ID: "; cin >> id;
        for(auto m:members)
            if(m->memberID==id){ cout<<"Member already exists!\n"; return; }
        cin.ignore();
        cout << "Enter Name: "; getline(cin,name);
        cout << "Enter Email: "; getline(cin,email);
        cout << "Enter Address: "; getline(cin,addr);
        cout << "Type (1=Student, 2=Faculty): "; cin >> type;
        if(type==1) members.push_back(new Student(id,name,email,addr));
        else members.push_back(new Faculty(id,name,email,addr));
        cout << "Member added.\n";
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
        cout << "Enter Member ID: "; cin >> mid;
        Member* mem=findMember(mid);
        if(!mem){ cout<<"Invalid member!\n"; return; }

        if(!mem->canIssue()){ cout<<"Issue limit reached!\n"; return; }

        cout << "Enter Book ID: "; cin >> bid;
        bool found=false;
        for(auto &b:books){
            if(b.bookID==bid && !b.issued){
                b.issued=true;
                mem->issuedCount++;
                transactions.push_back(Transaction(mid,b.bookID,b.serialNo,currentDate(),false));
                cout << "Book issued successfully.\n";
                found=true;
                break;
            }
        }
        if(!found) cout<<"No available copy found!\n";
    }

    void returnBook(){
        int mid,bid,sn;
        cout << "Enter Member ID: "; cin >> mid;
        Member* mem=findMember(mid);
        if(!mem){ cout<<"Invalid member!\n"; return; }

        cout << "Enter Book ID: "; cin >> bid;
        cout << "Enter Serial Number: "; cin >> sn;

        Book* b=findBook(bid,sn);
        if(!b){ cout<<"Book not found!\n"; return; }

        bool match=false;
        for(auto &t:transactions){
            if(t.memberID==mid && t.bookID==bid && t.serialNo==sn && !t.returned){
                t.returned=true;
                b->issued=false;
                mem->issuedCount--;
                cout<<"Book returned successfully.\n";
                match=true;
                break;
            }
        }
        if(!match) cout<<"No record found of this book being issued to this member!\n";
    }

    void showBooks(){
        cout << "\n--- Books List ---\n";
        for(auto &b:books) b.display();
    }

    void showMembers(){
        cout << "\n--- Members List ---\n";
        for(auto m:members) m->display();
    }

    void showTransactions(){
        cout << "\n--- Transactions ---\n";
        for(auto &t:transactions) t.display();
    }

    ~LibrarySystem(){
        for(auto m:members) delete m;
    }
};

int main(){
    LibrarySystem lib;
    int choice;
    while(true){
        cout << "\n====== LIBRARY MENU ======\n";
        cout << "1. Add Book\n";
        cout << "2. Add Member\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Show Books\n";
        cout << "6. Show Members\n";
        cout << "7. Show Transactions\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice){
            case 1: lib.addBook(); break;
            case 2: lib.addMember(); break;
            case 3: lib.issueBook(); break;
            case 4: lib.returnBook(); break;
            case 5: lib.showBooks(); break;
            case 6: lib.showMembers(); break;
            case 7: lib.showTransactions(); break;
            case 8: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
