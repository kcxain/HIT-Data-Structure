#include <iostream>
using namespace std;
void Hanoi(int n, char A, char B, char C);
int main(void)
{
	int n;
	cout<<"How many?"<<endl;
	cin>>n;
	Hanoi(n,'A','B','C');
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
