#include <bits/stdc++.h>
using namespace std;
#define max 1000
typedef int ElemType;
typedef int Position;
struct LIST
{
	ElemType elements[max];
	Position last;
};
void Initial(LIST &L);		  //初始化
void Input(LIST &L);			  //输入数据
void Delete(Position p, LIST &L); //删除给定元素
void DeleteSame(LIST &L);		  //对于已排好序的线性表，删除所有重复元素的算法
void reverse(LIST &L, int start, int end); //将线性表逆置
void DataMove(int k, LIST &L);	  //线性表循环左移/右移 k 位
void Merge(LIST &L1, LIST &L2);//合并两个非递减的线性表
void Print(LIST L);				  //打印线性表

void Initial(LIST &L)
{
	L.last = 0;
}
void Input(LIST &L)
{
	int N;
	cout << "有多少数据？" << endl;
	cin >> N;
	while (N > max - 1)
	{
		cout << "溢出了！" << endl;
		cout << "有多少数据？" << endl;
		cin >> N;
	}
	cout << "请输入数据：" << endl;
	for (int i = 1; i < N + 1; ++i)
	{
		cin >> L.elements[i];
		L.last++;
	}
}
void Delete(Position p, LIST &L)
{
	Position q;
	if (p > L.last || p < 1)
		cout << "指定位置不存在"<<endl;
	else
	{
		L.last = L.last - 1;
		for (q = p; q <= L.last; q++)
			L.elements[q] = L.elements[q + 1];
	}
}
void Print(LIST L)
{
	for (int i = 1; i <= L.last; ++i)
	{
		cout << L.elements[i] << ' ';
	}
}
void DeleteSame(LIST &L)
{
	int i = 1;
	for(int j=i+1;j<=L.last;j++)
	{
		if(L.elements[j]!=L.elements[i])
		{
           L.elements[++i]=L.elements[j];
		}
	}
	L.last=i;
}
void reverse(LIST &L, int start, int end){
	while (start < end)
	{
		swap(L.elements[start], L.elements[end]);
		start++;
		end--;
	}
}
void DataMove(int k, LIST &L){
	k = k % L.last;
	int start = 1;
	int end = L.last;
	reverse(L,start,end);
	reverse(L, start, k);
	reverse(L, k+1, end);
}
void Merge(LIST &L1, LIST &L2){
	int p1 = L1.last;
	int p2 = L2.last;
	int last = L1.last + L2.last;
	L1.last = last;
	int cur;
	while(p1||p2){
		if(!p1){
			cur = L1.elements[p2];
			p2--;
		}
		else if(!p2){
			cur = L1.elements[p1];
			p1--;
		}
		else if(L1.elements[p1]>L2.elements[p2]){
			cur = L1.elements[p1];
			p1--;
		}
		else{
			cur = L2.elements[p2];
			p2--;
		}
		L1.elements[last] = cur;
		last--;
	}
}
int main()
{
	while (1)
	{
		cout << "1、删除给定元素" << endl;
		cout << "2、删除排好序的线性表中的重复数据" << endl;
		cout << "3、将线性表逆置" << endl;
		cout << "4、将线性表循环右移K位" << endl;
		cout << "5、合并两个线性表" << endl;
		cout << "6、退出" << endl;
		cout << "请输入对应功能的序号：" << endl;
		LIST L;
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
			Initial(L);
			Input(L);
			int p;
			cout << "要删除的元素位置为：" << endl;
			cin >> p;
			Delete(p, L);
			cout << "删除后的线性表为：" << endl;
			Print(L);
			getchar();
			getchar();
			break;
		case 2:
			Initial(L);
			Input(L);
			DeleteSame(L);
			cout << "删除后的线性表为：" << endl;
			Print(L);
			getchar();
			getchar();
			break;
		case 3:
			Initial(L);
			Input(L);
			reverse(L,1,L.last);
			cout << "逆置后的线性表为：" << endl;
			Print(L);
			getchar();
			getchar();
			break;
		case 4:
			Initial(L);
			Input(L);
			int k;
			cout << "移动多少位？" << endl;
			cin >> k;
			DataMove(k, L);
			cout << "移动后的线性表为：" << endl;
			Print(L);
			getchar();
			getchar();
			break;
		case 5:
			LIST L2;
			Initial(L);
			Initial(L2);
			Input(L);
			Input(L2);
			Merge(L, L2);
			cout << "合并后的线性表为：" << endl;
			Print(L);
			getchar();
			getchar();
			break;
		case 6:
			return 0;
		}
	}
}
