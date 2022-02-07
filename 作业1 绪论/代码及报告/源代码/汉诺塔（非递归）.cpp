#include<iostream>
#include<stdio.h>
using namespace std;
void Hanoi(int n);
int main(void)
{
    int n;
    cout<<"How many?"<<endl;
    cin >> n;
    Hanoi(n);
    return 0;
}
void Hanoi(int n)
{
    int i, res, t, k;
    int s;
    res = (1 << n) - 1;
    for ( i = 1; i <= res; i++ ) {
        for ( t = 2, s = 1; s <= n; s++, t *= 2)
            if ( i % t == t / 2 ) 
                break; 
        k = i / t; 
        if ( n % 2 == s % 2 ) { 
            if ( (k + 1) % 3 == 0 ) 
                cout << "move " << s << " from " << "B" << " to " << "A" << endl;
            if ( (k + 1) % 3 == 1 )
                cout << "move " << s << " from " << "A" << " to " << "C" << endl;
            if ( (k + 1) % 3 == 2 ) 
                cout << "move " << s << " from " << "C" << " to " << "B" << endl;
        }
        else { 
            if ( (k + 1) % 3 == 0 )
                cout << "move " << s << " from " << "C" << " to " << "A" << endl;
            if ( (k + 1) % 3 == 1 )
                cout << "move " << s << " from " << "A" << " to " << "B" << endl;
            if ( (k + 1) % 3 == 2 ) 
                cout << "move " << s << " from " << "B" << " to " << "C" << endl;
        }
    }
}