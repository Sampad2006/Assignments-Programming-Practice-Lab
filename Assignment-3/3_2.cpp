/*
Q2.Write a function max(a,b) that will return the reference of larger value.Store the returned information to x where x is a) variable of type a or b. ii)VAriable referring to type of a and b.In both the cases modify x.Check also the values of a and b.

NAME:Sampad De
CLASS:BCSE-2
ROLL: 002410501025
*/
#include <iostream>
using namespace std;

int& maxf(int &a,int &b){
    if(a>=b)return a;
    return b;
}

void solve(){
    
    int a,b;
    cout<<"Enter a and b:"<<endl;
    cin>>a>>b;
    int fin=maxf(a,b);
    int &result=maxf(a,b);//storing in type of reference of a 
    cout<<"max(i): "<<fin<<endl;
    cout<<"max(ii): "<<result<<endl;
    
}

int main(){
    int t;
    //scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}