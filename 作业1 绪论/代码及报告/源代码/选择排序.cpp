//直接选择排序，升序
#include<iostream>

using namespace std;
int main()
{
	int array[1000];
	/*读入数据*/
	int n;
	int m;
	int temp;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> array[i];
	/*排序*/
	for (int i = 0; i < n-1; i++) {
		m = i;
		for (int j = i + 1; j < n; j++) {
			if (array[j] < array[m]) {
				m = j;
			}
		}
		if (m != i) {
			temp = array[i];
			array[i] = array[m];
			array[m] = temp;
		}
	}
	/*输出数据*/
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}
	cout << '\n';
	return 0;
}