/*
Design an ARRAY of integer class with the following features:
a. Array object may be declared for a specific size and a value for initializing
all the elements. Default values for the parameters may be taken as 0.
b. An array object may be declared and initialized with another object.
c. An array object may be declared and initialized with another array (not
the object, standard array as in C language).
Let a and b are two objects:
i. a+b will add corresponding elements.
ii. a=b will do the assignment.
iii. a[I] will return the ith element of the object.
iv. a*5 or 5*a will multiply the elements with 5.

Name: Sampad De
Roll-002410501025
*/

#include <iostream>
using namespace std;

class Array {
    int *arr;
    int size;
public:
    Array(int s=0, int val=0){
        size = s;
        arr = new int[size];
        for(int i=0; i<size; i++) arr[i] = val;
    }

    Array(const Array &a){
        size = a.size;
        arr = new int[size];
        for(int i=0; i<size; i++) arr[i] = a.arr[i];
    }

    Array(int a[], int n){
        size = n;
        arr = new int[size];
        for(int i=0; i<size; i++) arr[i] = a[i];
    }

    ~Array(){ delete[] arr; }

    Array operator+(const Array &b){
        int n = (size < b.size ? size : b.size);
        Array temp(n);
        for(int i=0; i<n; i++)
            temp.arr[i] = arr[i] + b.arr[i];
        return temp;
    }

    Array& operator=(const Array &b){
        if(this != &b){
            delete[] arr;
            size = b.size;
            arr = new int[size];
            for(int i=0; i<size; i++) arr[i] = b.arr[i];
        }
        return *this;
    }

    int& operator[](int i){ return arr[i]; }

    Array operator*(int k){
        Array temp(size);
        for(int i=0; i<size; i++) temp.arr[i] = arr[i] * k;
        return temp;
    }

    friend Array operator*(int k, Array &a){
        Array temp(a.size);
        for(int i=0; i<a.size; i++) temp.arr[i] = k * a.arr[i];
        return temp;
    }

    void input(){
        cout << "Enter size of array: ";
        cin >> size;
        arr = new int[size];
        cout << "Enter " << size << " elements: ";
        for(int i=0; i<size; i++) cin >> arr[i];
    }

    void display(){
        for(int i=0; i<size; i++) cout << arr[i] << " ";
        cout << endl;
    }

    int getSize() const { return size; }
};

int main(){
    Array a, b, c;
    int choice;

    while(true){
        cout << "\n----- ARRAY MENU -----\n";
        cout << "1. Create Array A\n";
        cout << "2. Create Array B\n";
        cout << "3. Display Arrays\n";
        cout << "4. Add (A + B)\n";
        cout << "5. Multiply Array (A*5 or 5*A)\n";
        cout << "6. Access Element (A[i])\n";
        cout << "7. Assign A = B\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1){
            a.input();
        }
        else if(choice == 2){
            b.input();
        }
        else if(choice == 3){
            cout << "Array A: "; a.display();
            cout << "Array B: "; b.display();
        }
        else if(choice == 4){
            c = a + b;
            cout << "Result (A+B): "; c.display();
        }
        else if(choice == 5){
            int k;
            cout << "Enter scalar value: ";
            cin >> k;
            Array temp1 = a * k;
            Array temp2 = k * a;
            cout << "A * " << k << ": "; temp1.display();
            cout << k << " * A: "; temp2.display();
        }
        else if(choice == 6){
            int i;
            cout << "Enter index to access (0-based): ";
            cin >> i;
            if(i >= 0 && i < a.getSize())
                cout << "A[" << i << "] = " << a[i] << endl;
            else
                cout << "Invalid index!\n";
        }
        else if(choice == 7){
            a = b;
            cout << "A assigned from B.\n";
        }
        else if(choice == 8){
            cout << "Exiting...\n";
            break;
        }
        else cout << "Invalid choice.\n";
    }

    return 0;
}
