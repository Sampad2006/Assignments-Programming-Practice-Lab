/*
Q2.Write a function that will have income and tax rate as arguments and will return tax amount.In case tax rate is not provided it will be automatically taken as 10%.Call it with and without tax rate.

NAME:Sampad De
CLASS:BCSE-2
ROLL: 002410501025
*/

#include <iostream>
using namespace std;

double tax(double income,double taxrate=10){
    return (0.01*income*taxrate);
}

void solve(){
    int t,i;
    cout<<"Enter income and taxrate: "<<endl;
    cin>>t>>i;
    double fin=tax(t,i);//storing the amount 
    cout<<"tax: "<<fin<<endl;

}

int main(){
    int t;
    //scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}