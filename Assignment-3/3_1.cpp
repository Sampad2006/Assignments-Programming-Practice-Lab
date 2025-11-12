/*
Q1.Write a function swap(a,b) to interchange the values of two variables.Do not use pointers.

NAME:Sampad De
CLASS:BCSE-2
ROLL: 002410501025
*/
#include <iostream>
using namespace std;

pair<int,int> swapf(int a,int b){
    auto x=make_pair(b,a);
    return x;
}

void solve(){
    int a,b;
    cout<<"Enter a and b:"<<endl;
    cin>>a>>b;
    auto x=swapf(a,b);
    a=x.first,b=x.second;
    cout<<"a: "<<a<<" b: "<<b<<endl;
    
}

int main(){
    int t;
    //scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}