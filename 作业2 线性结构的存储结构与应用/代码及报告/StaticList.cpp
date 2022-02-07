#include<bits/stdc++.h>
using namespace std;
#define MaxSize 10
#define ElemType int
typedef struct{
	ElemType data;
	int next;
}spacestr;
spacestr SPACE[MaxSize];
int av;
//初始化
void Initialize(){
	int j;
	for(j=0;j<MaxSize-1;j++)
		SPACE[j].next = j+1;
	SPACE[j].next = -1;
	av = 0;
}
//打印
void Input(){
	cout<<"Inpute 10 numbers:"<<endl;
	int p = av;
	int i = 0;
	while(p!=-1){
		cin>>SPACE[p].data;
		p = SPACE[p].next;
		i++;
	}
}
void Print(){
	int p = av;
	while(p!=-1){
		cout<<SPACE[p].data<<' ';
		p = SPACE[p].next;
	}
	cout<<endl;
}
//逆置
int revearse(){
	int pre = -1;
	int p = av;
	while(p!=-1){
		p = SPACE[av].next;
		SPACE[av].next = pre;
		pre = av;
		av = p;
	}
	return pre;
}
int main(){
	Initialize();
	Input();
	Print();
	av = revearse();
	cout<<"逆置后的数据为："<<endl;
	Print();
	return 0;
}