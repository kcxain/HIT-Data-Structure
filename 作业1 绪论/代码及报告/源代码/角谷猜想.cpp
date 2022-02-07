#include<iostream>
using namespace std;
int main(void)
{
	int i = 0;//记录操作次数
	int MaxTimes = 1;//记录最大操作次数
	int MaxTimes_n = 2;//记录最大操作次数的
	for (int n = 1; n <= 100; n++)
	{
		int n_pre = n;
		cout << n;
		while (n > 1) {
			if (n % 2) {
				n = 3 * n + 1;
				i++;
				cout << "->" << n;
			}
			else {
				n = n / 2;
				i++;
				cout << "->" << n;
			}
		}
		n = n_pre;
		if (MaxTimes < i) {
			MaxTimes = i;
			MaxTimes_n = n;
		}
		cout << '\n' << "Times:" << i << '\n' << endl;
		i = 0;
	}
	cout << "最长序列的数为：" << MaxTimes_n << endl;
	cout << "最长操作次数为：" << MaxTimes << endl;
	return 0;
}