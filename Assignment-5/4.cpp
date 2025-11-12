/*
Each cricketer has name, date of birth and matches played. Cricketer may be a
bowler or batsman. For a bowler, number of wickets taken, average economy is
stored. For a batsman, total runs scored, average score is stored. A double wicket
pair is formed taking a bowler and a batsman. An all-rounder is both a bowler
and batsman. Support must be there to show the details of a cricketer, bowler,
batsmen, all-rounder and the pair.
Design the classes and implement.

Name:Sampad De
Roll-002410501025
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cricketer {
protected:
    string name, dob;
    int matches;
public:
    Cricketer(string n="", string d="", int m=0){
        name = n; dob = d; matches = m;
    }
    virtual void display(){
        cout << "Name: " << name << " | DOB: " << dob << " | Matches: " << matches;
    }
    virtual string type(){ return "Cricketer"; }
    string getName(){ return name; }
    virtual ~Cricketer(){}
};

class Batsman : virtual public Cricketer {
protected:
    int totalRuns;
    double avgScore;
public:
    Batsman(string n="", string d="", int m=0, int r=0, double avg=0.0)
        : Cricketer(n,d,m){
        totalRuns = r; avgScore = avg;
    }
    void display() override {
        Cricketer::display();
        cout << " | Role: Batsman | Runs: " << totalRuns << " | Avg: " << avgScore << endl;
    }
    string type() override { return "Batsman"; }
};

class Bowler : virtual public Cricketer {
protected:
    int wickets;
    double economy;
public:
    Bowler(string n="", string d="", int m=0, int w=0, double e=0.0)
        : Cricketer(n,d,m){
        wickets = w; economy = e;
    }
    void display() override {
        Cricketer::display();
        cout << " | Role: Bowler | Wickets: " << wickets << " | Economy: " << economy << endl;
    }
    string type() override { return "Bowler"; }
};

class AllRounder : public Batsman, public Bowler {
public:
    AllRounder(string n="", string d="", int m=0, int r=0, double avg=0.0, int w=0, double e=0.0)
        : Cricketer(n,d,m), Batsman(n,d,m,r,avg), Bowler(n,d,m,w,e) {}

    void display() override {
        Cricketer::display();
        cout << " | Role: All-Rounder | Runs: " << totalRuns << " | Bat Avg: " << avgScore
             << " | Wickets: " << wickets << " | Economy: " << economy << endl;
    }
    string type() override { return "AllRounder"; }
};

class DoubleWicketPair {
    Batsman *batsman;
    Bowler *bowler;
public:
    DoubleWicketPair(Batsman *b=nullptr, Bowler *bo=nullptr){
        batsman = b; bowler = bo;
    }
    void display(){
        cout << "\n=== Double Wicket Pair ===\n";
        if(batsman){ cout << "Batsman: "; batsman->display(); }
        if(bowler){ cout << "Bowler: "; bowler->display(); }
    }
};

class CricketSystem {
    vector<Cricketer*> players;
public:
    void addPlayer(){
        int choice;
        cout << "\n1. Batsman\n2. Bowler\n3. All-Rounder\nEnter choice: ";
        cin >> choice;
        cin.ignore();
        string name, dob;
        int matches, runs, wickets;
        double avg, eco;

        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter DOB: "; getline(cin, dob);
        cout << "Enter Matches Played: "; cin >> matches;

        if(choice == 1){
            cout << "Enter Total Runs: "; cin >> runs;
            cout << "Enter Batting Average: "; cin >> avg;
            players.push_back(new Batsman(name,dob,matches,runs,avg));
        }
        else if(choice == 2){
            cout << "Enter Wickets Taken: "; cin >> wickets;
            cout << "Enter Economy: "; cin >> eco;
            players.push_back(new Bowler(name,dob,matches,wickets,eco));
        }
        else if(choice == 3){
            cout << "Enter Total Runs: "; cin >> runs;
            cout << "Enter Batting Average: "; cin >> avg;
            cout << "Enter Wickets Taken: "; cin >> wickets;
            cout << "Enter Economy: "; cin >> eco;
            players.push_back(new AllRounder(name,dob,matches,runs,avg,wickets,eco));
        }
        else cout << "Invalid choice!\n";
    }

    void showPlayers(){
        if(players.empty()) cout << "No players available.\n";
        else{
            cout << "\n=== Player List ===\n";
            for(auto p : players) p->display();
        }
    }

    Batsman* findBatsman(string nm){
        for(auto p: players){
            Batsman* b = dynamic_cast<Batsman*>(p);
            if(b && b->type() == "Batsman" && b->getName() == nm)
                return b;
        }
        return nullptr;
    }

    Bowler* findBowler(string nm){
        for(auto p: players){
            Bowler* bw = dynamic_cast<Bowler*>(p);
            if(bw && bw->type() == "Bowler" && bw->getName() == nm)
                return bw;
        }
        return nullptr;
    }

    void makePair(){
        cin.ignore();
        string bname, bowname;
        cout << "Enter Batsman Name: "; getline(cin,bname);
        cout << "Enter Bowler Name: "; getline(cin,bowname);

        Batsman *bat = findBatsman(bname);
        Bowler *bow = findBowler(bowname);

        if(!bat || !bow){ cout << "Invalid names or not found!\n"; return; }
        DoubleWicketPair pair(bat,bow);
        pair.display();
    }

    ~CricketSystem(){
        for(auto p:players) delete p;
    }
};

int main(){
    CricketSystem sys;
    int choice;
    while(true){
        cout << "\n===== CRICKET MENU =====\n";
        cout << "1. Add Player\n";
        cout << "2. Show All Players\n";
        cout << "3. Create Double Wicket Pair\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice){
            case 1: sys.addPlayer(); break;
            case 2: sys.showPlayers(); break;
            case 3: sys.makePair(); break;
            case 4: cout<<"Exiting...\n"; return 0;
            default: cout<<"Invalid choice!\n";
        }
    }
}
