#include<iostream>
#include<fstream>
const int Max = 10000;
using namespace std;
int Binary_Search(int a[],int n,int key,int& count){
	int low = 0,high = n,mid;
	while(low<=high){
		mid = (low+high)>>1;
		count++;
		if(a[mid] == key)
			return mid;
		else if(a[mid]>key)
			high = mid-1;
		else
			low = mid+1;
	}
	return -1;
}
int main(){
	ifstream infile;
	infile.open("inputdata1.txt");
	int in;
	int data[Max];
	int count = 0;
	while(infile>>in){
		data[count++] = in;
	}
	int counts = 0;
  	int j = 0;//查找成功的数的个数
  	int countf = 0;
  	int k = 0;//查找失败的数的个数
  	for (int i = 0; i <= 2048; ++i){
  		if(i%2){//这是能查找成功的
  			j++;
  			Binary_Search(data,count,i,counts);
  		}
  		else{//这是不能查找成功的
  			k++;
  			Binary_Search(data,count,i,countf);
  		}
  	}
  	double ASLs = (double)counts/j;
  	double ASLf = (double)countf/k;
  	cout<<"查找成功的平均查找长度为："<<ASLs<<endl;
  	cout<<"查找失败的平均查找长度为："<<ASLf<<endl;
}