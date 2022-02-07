//直接插入排序(递归)，升序
#include<iostream>
using namespace std;
#define swap(a,b)   (a=a+b,b=a-b,a=a-b)
void Inpute(int array[], int n);
void InsertSort(int array[], int n);
void Print(int array[], int n);
int main(void)
{
	int array[1000];
	int n;
	cin >> n;
	Inpute(array, n);
	InsertSort(array, n);
	Print(array, n);
	return 0;
}
void Inpute(int array[], int n)
{
	for (int i = 0; i < n; i++)
		cin >> array[i];
}
void InsertSort(int array[], int n)
{
   int i;

    if(n == 1)
        return;
    InsertSort(array, n-1);
    int temp = array[n - 1];
    for (i = n - 2; i >= 0 && temp < array[i]; i--)
    {
        array[i+1] = array[i];
    }
    array[i+1] = temp;
}
void Print(int array[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << '\n';
}