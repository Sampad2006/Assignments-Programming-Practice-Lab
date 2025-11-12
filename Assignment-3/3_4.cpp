/*
Q2.Write a function void f(int) that prints "inside f(int)".Call the function with actual argument of type i)int ii)char iii)float iv)double.Add one more function f(float) that prints "inside f(float)".Repeat the calls again and observe the outcomes.

NAME:Sampad De
CLASS:BCSE-2
ROLL: 002410501025

*/

#include <iostream>
using namespace std;

void f(int){
    cout<<"inside f(int)"<<endl;
}

// void f(float){
//     cout<<"inside f(float)"<<endl;
// }
void solve(){

   int x;cin>>x;
   double d=x;
   float f=x;
   char c=x;
   cout<<" int:"<<endl;f(2);
   cout<<"float:"<<endl;f(2.5);
   cout<<"double: "<<endl;

}

int main(){
    int t;
    //scanf("%d",&t);
    t=1;
    while(t--){
        solve();
    }
}