#include<iostream>
#include<stdio.h>
#include<time.h>
using namespace std;
#define Num 5
//计算15个圆盘的汉诺塔

void Hanoi(int n, char A, char B, char C);//递归
void Hanoi_N(int n);//非递归

clock_t start, stop;
double duration;//递归算法耗费时间
double duration_N;//非递归算法耗费时间
int main(void)
{
    start=clock();
    Hanoi(Num,'A','B','C');
    stop=clock();
    duration=(double)(stop-start)/CLK_TCK; //CLK_TCK为clock()函数的时间单位，即时钟打点
    
    start=clock();
    Hanoi_N(Num);
    stop=clock();
    duration_N=(double)(stop-start)/CLK_TCK;
    cout<<"The time of Hanoi:"<<duration<<endl;
    cout<<"The time of Hanoi_N:"<<duration_N<<endl;
    return 0;
}
void Hanoi(int n, char A, char B, char C)/*A通过C移动到B*/
{
    if (n == 1)
        cout << "move " << n << " from " << A << " to " << C << endl;
    else
    {
        Hanoi(n - 1, A, C, B);
        cout << "move " << n << " from " << A << " to " << C << endl;
        Hanoi(n - 1, B, A, C);
    }
}
void Hanoi_N(int n)
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