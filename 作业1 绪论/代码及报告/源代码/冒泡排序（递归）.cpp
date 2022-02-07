//直接冒泡排序(递归)，升序
#include<iostream>
using namespace std;
#define swap(a,b)   (a=a+b,b=a-b,a=a-b)
void Inpute(int array[], int n);
void BubbleSort(int array[], int n);
void Print(int array[], int n);
int main(void)
{
	int array[1000];
	int n;
	cin >> n;
	Inpute(array, n);
	BubbleSort(array, n);
	Print(array, n);
	return 0;
}
void Inpute(int array[], int n)
{
	for (int i = 0; i < n; i++)
		cin >> array[i];
}
void BubbleSort(int array[], int n)
{
	if (n == 1)
		return;
	for (int i = 0; i < n - 1; i++)
	{
		if (array[i] > array[i + 1])
		{
			swap(array[i], array[i + 1]);
		}
	}
	n--;
	BubbleSort(array, n);
}
void Print(int array[], int n)
{
	for (int i = 0; i<n; i++) 
	{ 
		cout << array[i] << " "; 
	}
	cout << '\n'; 
}