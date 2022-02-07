//直接选择排序(递归)，升序
#include<iostream>
using namespace std;
#define swap(a,b)   (a=a+b,b=a-b,a=a-b)
void Inpute(int array[], int n);
void ChioceSort(int array[], int n);
void Print(int array[], int n);
int main(void)
{
	int array[1000];
	int n;
	cin >> n;
	Inpute(array, n);
	ChioceSort(array, n);
	Print(array, n);
	return 0;
}
void Inpute(int array[], int n)
{
	for (int i = 0; i < n; i++)
		cin >> array[i];
}
void ChioceSort(int array[], int n)
{
	if (n == 1)
		return;
	int temp=0;
	int i;
	for (i = 0; i < n; i++)
	{
		if (array[i] < array[0])
			temp = i;
	}
	if (temp != 0)
	{
		swap(array[0], array[temp]);
	}
	array++;
	n--;
	ChioceSort(array, n);
}
void Print(int array[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << '\n';
}