/*
Design the class(es) for the following. Each account has account number and
balance amount. A list of account is to be maintained where one can add and
find account, display information of all accounts. While adding, account number
must be unique. Withdraw object has account number (must exist) and amount
(will not exceed balance amount of corresponding account). Withdraw object will
update the balance of corresponding account in the list. User will be able to
search and view account, add account and withdraw money from the
account. Implement your design. Use friend function wherever required and
again, modify your implementation to avoid friend function.


Name: Sampad De
Roll-002410501025
*/

#include <iostream>
#include <vector>
using namespace std;

class Bank; 

class Account {
    int accNo;
    double balance;
public:
    Account(int a=0,double b=0){ accNo=a; balance=b; }
    void display(){ cout<<"Account No: "<<accNo<<" | Balance: "<<balance<<endl; }
    friend class Bank;
    friend void withdrawMoney(Bank&, int, double);
};

class Bank {
    vector<Account> accounts;
public:
    void addAccount(int a,double b){
        for(auto &x:accounts)
            if(x.accNo==a){ cout<<"Account number already exists!\n"; return; }
        accounts.push_back(Account(a,b));
        cout<<"Account added successfully.\n";
    }

    Account* findAccount(int a){
        for(auto &x:accounts)
            if(x.accNo==a) return &x;
        return nullptr;
    }

    void showAll(){
        if(accounts.empty()) cout<<"No accounts found.\n";
        for(auto &x:accounts) x.display();
    }

    friend void withdrawMoney(Bank&, int, double);
};

void withdrawMoney(Bank &b, int a, double amt){
    Account* acc = b.findAccount(a);
    if(!acc){ cout<<"Account not found.\n"; return; }
    if(amt > acc->balance){ cout<<"Insufficient balance.\n"; return; }
    acc->balance -= amt;
    cout<<"Withdrawal successful. New balance: "<<acc->balance<<endl;
}

int main(){
    Bank b;
    int choice;
    while(true){
        cout<<"\n1. Add Account\n2. Search Account\n3. Withdraw Money\n4. Display All\n5. Exit\nEnter choice: ";
        cin>>choice;
        if(choice==1){
            int no; double bal;
            cout<<"Enter account number: "; cin>>no;
            cout<<"Enter initial balance: "; cin>>bal;
            b.addAccount(no,bal);
        }
        else if(choice==2){
            int no; cout<<"Enter account number: "; cin>>no;
            Account* acc = b.findAccount(no);
            if(acc) acc->display();
            else cout<<"Account not found.\n";
        }
        else if(choice==3){
            int no; double amt;
            cout<<"Enter account number: "; cin>>no;
            cout<<"Enter amount to withdraw: "; cin>>amt;
            withdrawMoney(b,no,amt);
        }
        else if(choice==4) b.showAll();
        else if(choice==5) break;
        else cout<<"Invalid choice.\n";
    }
    return 0;
}
