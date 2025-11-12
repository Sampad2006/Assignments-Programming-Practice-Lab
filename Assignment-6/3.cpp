/*
Implement a class template for 1D array. Elements may be any basic data type.
Provision to find maximum element, sum of the elements must be there.

Name:Sampad De
Roll-002410501025
*/
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

template <class T>
class Array1D {
    vector<T> arr;
public:
    void input(){
        int n;
        cout << "Enter number of elements: ";
        cin >> n;
        arr.resize(n);
        cout << "Enter " << n << " elements:\n";
        for(int i=0;i<n;i++) cin >> arr[i];
    }

    void display(){
        if(arr.empty()) cout << "Array is empty.\n";
        else{
            cout << "Array elements: ";
            for(auto &x: arr) cout << x << " ";
            cout << endl;
        }
    }

    T sum(){
        if(arr.empty()) return 0;
        T s = 0;
        for(auto &x: arr) s += x;
        return s;
    }

    T maxElement(){
        if(arr.empty()) throw runtime_error("Array is empty!");
        T m = arr[0];
        for(auto &x: arr)
            if(x > m) m = x;
        return m;
    }
};

int main(){
    int choice;
    cout << "Choose data type:\n1. int\n2. float\n3. double\nEnter choice: ";
    cin >> choice;

    if(choice==1){
        Array1D<int> a;
        while(true){
            cout << "\n--- INT ARRAY MENU ---\n";
            cout << "1. Input Elements\n2. Display\n3. Find Sum\n4. Find Maximum\n5. Exit\n";
            cout << "Enter choice: ";
            int ch; cin >> ch;
            switch(ch){
                case 1: a.input(); break;
                case 2: a.display(); break;
                case 3: cout << "Sum = " << a.sum() << endl; break;
                case 4: cout << "Max = " << a.maxElement() << endl; break;
                case 5: return 0;
                default: cout << "Invalid choice!\n";
            }
        }
    }
    else if(choice==2){
        Array1D<float> a;
        while(true){
            cout << "\n--- FLOAT ARRAY MENU ---\n";
            cout << "1. Input Elements\n2. Display\n3. Find Sum\n4. Find Maximum\n5. Exit\n";
            cout << "Enter choice: ";
            int ch; cin >> ch;
            switch(ch){
                case 1: a.input(); break;
                case 2: a.display(); break;
                case 3: cout << "Sum = " << a.sum() << endl; break;
                case 4: cout << "Max = " << a.maxElement() << endl; break;
                case 5: return 0;
                default: cout << "Invalid choice!\n";
            }
        }
    }
    else if(choice==3){
        Array1D<double> a;
        while(true){
            cout << "\n--- DOUBLE ARRAY MENU ---\n";
            cout << "1. Input Elements\n2. Display\n3. Find Sum\n4. Find Maximum\n5. Exit\n";
            cout << "Enter choice: ";
            int ch; cin >> ch;
            switch(ch){
                case 1: a.input(); break;
                case 2: a.display(); break;
                case 3: cout << "Sum = " << a.sum() << endl; break;
                case 4: cout << "Max = " << a.maxElement() << endl; break;
                case 5: return 0;
                default: cout << "Invalid choice!\n";
            }
        }
    }
    else{
        cout << "Invalid data type choice!\n";
    }
}
