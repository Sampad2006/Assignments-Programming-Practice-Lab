#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

string currentDate(){
    time_t now = time(0);
    string d = ctime(&now);
    d.pop_back(); 
    return d;
}

class Balance {
    int accNo;
    double bal;
    string lastUpdate;
public:
    Balance(int a=0,double b=0.0,string d=""):accNo(a),bal(b),lastUpdate(d){}
    int getAccNo(){ return accNo; }
    double getBalance(){ return bal; }

    void createAccount(){
        cout<<"Enter Account Number: ";
        cin>>accNo;
        cout<<"Enter Initial Balance: ";
        cin>>bal;
        lastUpdate = currentDate();
        cout<<"Account created successfully!\n";
    }

    void deposit(double amt){
        bal += amt;
        lastUpdate = currentDate();
    }

    bool withdraw(double amt){
        if(amt > bal) return false;
        bal -= amt;
        lastUpdate = currentDate();
        return true;
    }

    void display(){
        cout<<"AccNo: "<<accNo<<" | Balance: "<<bal<<" | Last Update: "<<lastUpdate<<endl;
    }
};

class Transaction {
    int accNo;
    string date;
    double amount;
    char type;  // 'D' or 'W'
public:
    Transaction(int a=0,double amt=0,char t='D'){
        accNo=a; amount=amt; type=t; date=currentDate();
    }

    void process(vector<Balance> &accounts){
        bool found=false;
        for(auto &acc:accounts){
            if(acc.getAccNo()==accNo){
                found=true;
                if(type=='D'){
                    acc.deposit(amount);
                    cout<<"Deposit successful.\n";
                }
                else if(type=='W'){
                    if(acc.withdraw(amount))
                        cout<<"Withdrawal successful.\n";
                    else
                        cout<<"Insufficient balance!\n";
                }
                return;
            }
        }
        if(!found) cout<<"Account not found!\n";
    }

    void display(){
        cout<<"Transaction -> AccNo: "<<accNo<<" | Type: "<<type
            <<" | Amount: "<<amount<<" | Date: "<<date<<endl;
    }
};

class BankSystem {
    vector<Balance> accounts;
    vector<Transaction> history;
public:
    void addAccount(){
        Balance b;
        b.createAccount();
        accounts.push_back(b);
    }

    void showAccounts(){
        if(accounts.empty()) cout<<"No accounts found.\n";
        else{
            cout<<"\n--- Account List ---\n";
            for(auto &b:accounts) b.display();
        }
    }

    void makeTransaction(){
        int accNo; double amt; char type;
        cout<<"Enter Account Number: "; cin>>accNo;
        cout<<"Enter Transaction Type (D/W): "; cin>>type;
        cout<<"Enter Amount: "; cin>>amt;
        Transaction t(accNo,amt,type);
        t.process(accounts);
        history.push_back(t);
    }

    void showTransactions(){
        if(history.empty()) cout<<"No transactions yet.\n";
        else{
            cout<<"\n--- Transaction History ---\n";
            for(auto &t:history) t.display();
        }
    }
};

int main(){
    BankSystem bank;
    int choice;
    while(true){
        cout<<"\n===== BANK MENU =====\n";
        cout<<"1. Add Account\n";
        cout<<"2. Show All Accounts\n";
        cout<<"3. Make Transaction (Deposit/Withdraw)\n";
        cout<<"4. Show Transaction History\n";
        cout<<"5. Exit\n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1: bank.addAccount(); break;
            case 2: bank.showAccounts(); break;
            case 3: bank.makeTransaction(); break;
            case 4: bank.showTransactions(); break;
            case 5: cout<<"Exiting...\n"; return 0;
            default: cout<<"Invalid choice!\n";
        }
    }
}
